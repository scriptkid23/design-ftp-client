#ifdef _WIN32
#include <winsock2.h>         // For socket(), connect(), send(), and recv()
#include <ws2tcpip.h>
typedef int socklen_t;
typedef char raw_type;       // Type used for raw data on this platform
#else
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
typedef void raw_type;       // Type used for raw data on this platform
#endif

#include <errno.h>             // For errno
#include "tcpsocket.h"
void fillAddr(const string&,unsigned short, sockaddr_in&);

using namespace std;

// TcpSocket Code

TcpSocket::TcpSocket() : Socket(SOCK_STREAM,IPPROTO_TCP)
{
}

TcpSocket::TcpSocket(int newConnSD) : Socket(newConnSD)
{
}

TcpSocket::TcpSocket(const string &remoteAddress, unsigned short port) : Socket(SOCK_STREAM, IPPROTO_TCP)
{
    connect(remoteAddress, port);
}

TcpSocket& TcpSocket::operator=(const TcpSocket& socket)
{
    this->sockDesc = socket.sockDesc;
    return *this;
}

void TcpSocket::connect(const string &remoteAddress,
                        unsigned short port)
{
    // Get the address of the requested host
    sockaddr_in destAddr;
    fillAddr(remoteAddress, port, destAddr);
    // If sockDesc is INVALID_SOCKET
    if(sockDesc == -1)
    {
        // Make a new socket
        if ((sockDesc = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        {
            throw SocketException("Socket creation failed (socket())", true);
        }
    }
    // Try to connect to the given port
    if (::connect(sockDesc, (sockaddr *) &destAddr, sizeof(destAddr)) < 0)
    {
        throw SocketException("Connect failed (connect())");
    }
}


void TcpSocket::connect(const string &remoteAddress,
                        const string& service)
{
    // Get the address of the requested host
    sockaddr_in destAddr;
    unsigned short port;
    struct servent* p = getservbyname(service.c_str(),"tcp");
    if(p)
    {
        port = ntohs(p->s_port);
    }
    else
        port = atoi(service.c_str());
    fillAddr(remoteAddress, port, destAddr);
    // If sockDesc is INVALID_SOCKET
    if(sockDesc == -1)
    {
        // Make a new socket
        if ((sockDesc = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        {
            throw SocketException("Socket creation failed (socket())", true);
        }
    }
    // Try to connect to the given port
    if (::connect(sockDesc, (sockaddr *) &destAddr, sizeof(destAddr)) < 0)
    {
        throw SocketException("Connect failed (connect())");
    }
}

void TcpSocket::send(const void *buffer, int bufferLen)
{
    int r = ::send(sockDesc, (raw_type *) buffer, bufferLen, 0);
    if ( r < 0)
    {
        throw SocketException("Send failed (send())", true);
    } //else if (r==0) {
    //    throw SocketException("Send failed (send()) - Connection reset", true);
    //}
}

void TcpSocket::send(const char *str)
{
    int r = ::send(sockDesc, (raw_type *)str,strlen(str), 0);
    if ( r < 0)
    {
        throw SocketException("Send failed (send())", true);
    } //else if (r==0) {
    //    throw SocketException("Send failed (send()) - Connection reset", true);
    //}
}

void TcpSocket::send(const string& str)
{
    int r = ::send(sockDesc, (raw_type *)str.c_str(),str.size(), 0);
    if ( r < 0)
    {
        throw SocketException("Send failed (send())", true);
    } //else if (r==0) {
    //    throw SocketException("Send failed (send()) - Connection reset", true);
    //}
}

int TcpSocket::recv(void *buffer, int bufferLen)
{
    int rtn = ::recv(sockDesc, (raw_type *) buffer, bufferLen, 0);
    if (rtn < 0)
    {
        throw SocketException("Received failed (recv())", true);
    }
    return rtn;
}

int TcpSocket::recvLine(char* buffer, int bufLen)
{
    bool b_eol = false;
    int total_byte_recv = 0;
    int byte_recv;


    byte_recv = ::recv(sockDesc, buffer, 1, 0);
    while(!b_eol && byte_recv>0)
    {
        total_byte_recv += byte_recv;

        if(total_byte_recv>=2 && buffer[total_byte_recv-1]=='\n'&& buffer[total_byte_recv-2]=='\r')
            b_eol = true;
        if(total_byte_recv>=bufLen)
            b_eol = true;
        if (b_eol)
            continue;

        byte_recv = ::recv(sockDesc,buffer+total_byte_recv, 1, 0);
    }
    if(byte_recv==-1)
    {
        throw SocketException("Received failed (recv())", true);
    }
    else if(byte_recv==0)
    {
        return 0;
    }
    else
        return total_byte_recv;
}

void TcpSocket::shutdown(int& type)
{
#ifdef _WIN32
    if(type==SHUTDOWN_SEND)
        ::shutdown(this->sockDesc,SD_SEND);
    else if(type==SHUTDOWN_RECV)
        ::shutdown(this->sockDesc,SD_RECEIVE);
    else if(type==SHUTDOWN_BOTH)
        ::shutdown(sockDesc,SD_BOTH);
#else
    if(type==SHUTDOWN_SEND)
        ::shutdown(this->sockDesc,SHUT_RD);
    else if(type==SHUTDOWN_RECV)
        ::shutdown(this->sockDesc,SHUT_WR);
    else if(type==SHUTDOWN_BOTH)
        ::shutdown(sockDesc,SHUT_RDWR);
#endif // _WIN32
}

string TcpSocket::getRemoteAddress()
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    if (getpeername(sockDesc, (sockaddr *) &addr,(socklen_t *) &addr_len) < 0)
    {
        throw SocketException("Fetch of foreign address failed (getpeername())", true);
    }
    return inet_ntoa(addr.sin_addr);
}

unsigned long TcpSocket::getRemoteIPv4Address()
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    if (getpeername(sockDesc, (sockaddr *) &addr,(socklen_t *) &addr_len) < 0)
    {
        throw SocketException("Fetch of foreign address failed (getpeername())", true);
    }
    return addr.sin_addr.s_addr;
}


unsigned short TcpSocket::getRemotePort()
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);
    if (getpeername(sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0)
    {
        throw SocketException("Fetch of foreign port failed (getpeername())", true);
    }
    return ntohs(addr.sin_port);
}








