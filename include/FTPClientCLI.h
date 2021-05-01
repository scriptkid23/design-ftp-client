#ifndef FTPCLIENT_CLI_H // include guard
#define FTPCLIENT_CLI_H

#include "cli.h"
#include "tcpsocket.h"
#include "FTPClient.h"
#include "iostream"
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include "constants.h"

class FTPClientCLI: public CmdLineInterface{
        public:
        
            FTPClient ftpClient;
            FTPClientCLI();
            virtual void initCmd();
        protected:
            string hostname;
            string user;
            string cWorkingDirectory;

        private:
            
            void doClose(char* cmd_argv[], int cmd_argc);
            void doHelp(char* cmd_argv[], int cmd_argc);
            void doConnect(char* cmd_argv[], int cmd_argc);
            void doClear(char* cmd_argv[], int cmd_argc);
            void doLogin(char* cmd_argv[], int cmd_argc);
            void doList(char* cmd_argv[], int cmd_argc);
            void doCWD(char* cmd_argv[], int cmd_argc);
            void doDeleteDirectory(char* cmd_argv[], int cmd_argc);
            void doCreateDirectory(char* cmd_argv[], int cmd_argc);
            void doRenameDirectoryOrFile(char* cmd_argv[], int cmd_argc);
            void doDeleteFile(char* cmd_argv[], int cmd_argc);
            void doDownload(char* cmd_argv[], int cmd_argc);
            void doUpload(char* cmd_argv[], int cmd_argc);
            void doPWD(char* cmd_argv[], int cmd_argc);
            void doDIR(char* cmd_argv[], int cmd_argc);
            
};

#endif