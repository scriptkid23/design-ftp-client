#include "tcpclient.h"
#include <iostream>

TcpClient::TcpClient()
{
    connected = false;
}


bool TcpClient::open(const string& serverHost, unsigned short port)
{
    try
    {
        this->localsocket.connect(serverHost,port);
        this->connected = true;
        return true;

    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

bool TcpClient::open(const string& serverHost, const string& port)
{
    char buffer[256];
    try
    {
        this->localsocket.connect(serverHost,port);
        /*
            fix bug: response from server to client not match
            because: first time response, server will send message code 220
                     so we add this->localsocket.recv(buffer,256); go to handle;
        */
        this->localsocket.recv(buffer,256);
        this->connected = true;
        return true;

    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}


void TcpClient::sendStringRequest(const string& request)
{
    try
    {
        this->localsocket.send(request);

    }
    catch(SocketException& e)
    {
        cerr << e.what();
    }

}
void TcpClient::sendDataBuffer(const char* buffer, unsigned int bufLen)
{
    try
    {
        this->localsocket.send(buffer, bufLen);
    }
    catch(SocketException& e)
    {
        cerr << e.what();
    }
}
int TcpClient::recvGetLine(char* buffer, unsigned int maxLen)
{
    int bytes;
    try
    {
        bytes = localsocket.recvLine(buffer, maxLen);
        return bytes;

    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}

int TcpClient::recvDataBuffer(char* buffer, unsigned int bufLen)
{
    int bytes;
    try
    {
        bytes = localsocket.recv(buffer, bufLen);
        return bytes;
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}

void TcpClient::close()
{
    try
    {
        localsocket.close();
    }
    catch(SocketException& e)
    {
        cerr<< e.what() << endl;
    }
    connected = false;
}
