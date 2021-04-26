#ifndef FTPCLIENT_CLI_H // include guard
#define FTPCLIENT_CLI_H

#include "cli.h"
#include "tcpsocket.h"
#include "FTPClient.h"
#include "iostream"
#include <iomanip>
#include <sstream>
#include <stdlib.h>


class FTPClientCLI: public CmdLineInterface{
        public:
        
            FTPClient ftpClient;
            FTPClientCLI();
            virtual void initCmd();
            
        private:
            
            void doClose(char* cmd_argv[], int cmd_argc);
            void doHelp(char* cmd_argv[], int cmd_argc);
            void doConnect(char* cmd_argv[], int cmd_argc);
            void doClear(char* cmd_argv[], int cmd_argc);
            void doLogin(char* cmd_argv[], int cmd_argc);
};

#endif