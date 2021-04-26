
#ifndef FTPCLIENT_H // include guard
#define FTPCLIENT_H

#include <cstdint>
#include "tcpclient.h"
#include <iostream>
// #include "FTPClientCLI.h"
#include "cli.h"

class FTPClient;

// using callback = void (CmdLineInterface::*)(std::string);
// typedef void (CmdLineInterface::*callback)(std::string);


    class FTPClient:public TcpClient{
        private:
            string hostname;
        public:
            void setHostName(string hostname);
            string getHostName();
            FTPClient();
            void echo(const string &msg);
            void login(CmdLineInterface *callback);
    };

#endif