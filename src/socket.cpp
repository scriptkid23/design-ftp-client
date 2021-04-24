/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002 by by Michael J. Donahoo
 *   Updated by Phong Bui in 2020
 *
 *
 */

#include "socket.h"

#ifdef _WIN32
#include <winsock2.h> // For socket(), connect(), send(), and recv()
#include <ws2tcpip.h>
typedef int socklen_t;
typedef char raw_type; // Type used for raw data on this platform
#else
#include <sys/types.h>  // For data types
#include <sys/socket.h> // For socket(), connect(), send(), and recv()
#include <netdb.h>      // For gethostbyname()
#include <arpa/inet.h>  // For inet_addr()
#include <unistd.h>     // For close()
#include <netinet/in.h> // For sockaddr_in
typedef void raw_type; // Type used for raw data on this platform
#include <cstring>
#endif

#include <errno.h> // For errno

using namespace std;

#ifdef _WIN32
static bool initialized = false;
#endif

// SocketException Code

SocketException::SocketException(const string &message, bool inclSysMsg) throw() : userMessage(message)
{

    if (inclSysMsg)
    {
#ifdef _WIN32
        userMessage.append(": ");
        userMessage.append(strerror(WSAGetLastError()));
#else
        userMessage.append(": ");
        userMessage.append(strerror(errno));
#endif // _WIN32
    }
}

SocketException::~SocketException() throw()
{
}

const char *SocketException::what() const throw()
{
    return userMessage.c_str();
}

// Function to fill in address structure given an address and port
void fillAddr(const string &address, unsigned short port,
              sockaddr_in &addr)
{
    memset(&addr, 0, sizeof(addr)); // Zero out address structure
    addr.sin_family = AF_INET;      // Internet address

    hostent *host; // Resolve name
    if ((host = gethostbyname(address.c_str())) == NULL)
    {
        // strerror() will not work for gethostbyname() and hstrerror()
        // is supposedly obsolete
        throw SocketException("Failed to resolve name (gethostbyname())");
    }
    addr.sin_addr.s_addr = *((unsigned long *)host->h_addr_list[0]);

    addr.sin_port = htons(port); // Assign port in network byte order
}

// Socket Code

Socket::Socket(int type, int protocol)
{
#ifdef _WIN32
    if (!initialized)
    {
        WORD wVersionRequested;
        WSADATA wsaData;

        wVersionRequested = MAKEWORD(2, 0);               // Request WinSock v2.0
        if (WSAStartup(wVersionRequested, &wsaData) != 0) // Load WinSock DLL
        {
            throw SocketException("Unable to load WinSock DLL");
        }
        initialized = true;
    }
#endif

    // Make a new socket
    if ((sockDesc = socket(PF_INET, type, protocol)) < 0)
    {
        throw SocketException("Socket creation failed (socket())", true);
    }
}

Socket::Socket(int sockDesc)
{
    this->sockDesc = sockDesc;
}

Socket::~Socket()
{
#ifdef _WIN32
    ::closesocket(sockDesc);
#else
    ::close(sockDesc);
#endif
    sockDesc = -1;
}

void Socket::close()
{
#ifdef _WIN32
    ::closesocket(sockDesc);
#else
    ::close(sockDesc);
#endif
    sockDesc = -1;
}

void Socket::startUp()
{
#ifdef _WIN32
    if (!initialized)
    {
        WORD wVersionRequested;
        WSADATA wsaData;

        wVersionRequested = MAKEWORD(2, 0);               // Request WinSock v2.0
        if (WSAStartup(wVersionRequested, &wsaData) != 0) // Load WinSock DLL
        {
            throw SocketException("Unable to load WinSock DLL");
        }
        initialized = true;
    }
#endif
}

string Socket::getLocalAddress()
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    if (getsockname(sockDesc, (sockaddr *)&addr, (socklen_t *)&addr_len) < 0)
    {
        throw SocketException("Fetch of local address failed (getsockname())", true);
    }
    return inet_ntoa(addr.sin_addr);
}

unsigned short Socket::getLocalPort()
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    if (getsockname(sockDesc, (sockaddr *)&addr, (socklen_t *)&addr_len) < 0)
    {
        throw SocketException("Fetch of local port failed (getsockname())", true);
    }
    return ntohs(addr.sin_port);
}

void Socket::setLocalPort(unsigned short localPort)
{
    // Bind the socket to its port
    sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(localPort);

    if (bind(sockDesc, (sockaddr *)&localAddr, sizeof(sockaddr_in)) < 0)
    {
        throw SocketException("Set of local port failed (bind())", true);
    }
}

void Socket::setLocalAddressAndPort(const string &localAddress,
                                    unsigned short localPort)
{
    // Get the address of the requested host
    sockaddr_in localAddr;
    fillAddr(localAddress, localPort, localAddr);

    if (bind(sockDesc, (sockaddr *)&localAddr, sizeof(sockaddr_in)) < 0)
    {
        throw SocketException("Set of local address and port failed (bind())", true);
    }
}

void Socket::cleanUp()
{
#ifdef WIN32
    if (WSACleanup() != 0)
    {
        throw SocketException("WSACleanup() failed");
    }
#endif
}

unsigned short Socket::resolveService(const string &service,
                                      const string &protocol)
{
    struct servent *serv; /* Structure containing service information */

    if ((serv = getservbyname(service.c_str(), protocol.c_str())) == NULL)
        return atoi(service.c_str()); /* Service is port number */
    else
        return ntohs(serv->s_port); /* Found port (network byte order) by name */
}

string Socket::getAddressFromName(const string &name)
{
    hostent *pHost = gethostbyname(name.c_str());
    in_addr addr;
    if (pHost == NULL)
    {
        throw SocketException("Failed to resolve name (gethostbyname())");
    }
    else
    {
        addr.s_addr = *((unsigned long *)pHost->h_addr_list[0]);
    }
    return inet_ntoa(addr);
}

string Socket::getHostname()
{
    char hostname[128];
    int r = gethostname(hostname, 128);
    if (r == -1)
    {
        throw SocketException("Failed to resolve hostname (gethostname())", true);
    }
    return hostname;
}
