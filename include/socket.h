/*
 *   Based on C++ sockets on Unix and Windows
 *   Copyright (C) 2002 by Michael J. Donahoo
 *   Updated by Phong Bui in 2020
 *
 */

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>            // For string
#include <exception>         // For exception class

using namespace std;

class SocketException : public exception
{
public:

    SocketException(const string &message, bool inclSysMsg = false) throw();

    ~SocketException() throw();

    const char *what() const throw();

private:
    string userMessage;  // Exception message
};

/**
 *   Base class representing basic socket
 */
class Socket
{
public:
    /**
     *   Close and deallocate this socket
     */
    ~Socket();
    void close();

    /**
     *   Get the local address
     */
    string getLocalAddress();

    /**
     *   Get the local port
     */

    unsigned short getLocalPort();

    /**
     *   Set the local port to the specified port
     */
    void setLocalPort(unsigned short localPort);

    /**
     *   Set the local port to the specified port and the local address
     *   to the specified address.
     */
    void setLocalAddressAndPort(const string &localAddress,
                                unsigned short localPort = 0);

    /**
     *   Resolve the specified service for the specified protocol to the
     *   corresponding port number in host byte order
     */
    static unsigned short resolveService(const string &service,
                                         const string &protocol = "tcp");


    /**
     *   If WinSock, unload and clean up the WinSock DLLs;
     */
    static void cleanUp();

    /**
     *   If WinSock, load and start up the WinSock DLLs;
     */
    static void startUp();

    /**
     *   Get the address from name
     */
    static string getAddressFromName(const string& hostname);

    /**
     *   Get the name of localhost
     */
    static string getHostname();

private:
    // Prevent the user from trying to use value semantics on this object
    Socket(const Socket &sock);
    void operator=(const Socket &sock);

protected:
    int sockDesc;              // Socket descriptor
    Socket(int type, int protocol);
    Socket(int sockDesc);
};
#endif
