#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include "tcpsocket.h"

class TcpClient
{
protected:
    TcpSocket localsocket;
    bool connected;
public:
    TcpClient();
    bool isConnected() { return connected;}
    bool open(const string& serverHost, unsigned short port);
    bool open(const string& serverHost, const string& port);
    void sendStringRequest(const string& request);
    void sendDataBuffer(const char* buffer, unsigned int bufLen);
    int recvGetLine(char* buf,unsigned int maxLen);
    int recvDataBuffer(char* buffer, unsigned int bufLen);
    void close();
};

#endif // _TCP_CLIENT_H_
