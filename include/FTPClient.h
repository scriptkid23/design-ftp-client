
#ifndef FTPCLIENT_H // include guard
#define FTPCLIENT_H
#include "cli.h"
#include "tcpclient.h"

#include <iostream>
    class FTPClient:public TcpClient{
        
        public:
            FTPClient();
            void echo(const string &msg);
            void login();
    };

#endif