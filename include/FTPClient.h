
#ifndef FTPCLIENT_H // include guard
#define FTPCLIENT_H
#include "cli.h"

    class FTPClient:public CmdLineInterface
    {
        public:
            FTPClient();
            virtual void initCmd();
        private:
            void doHelp(char* cmd_argv[], int cmd_argc);
            void doConnect(char* cmd_argv[], int cmd_argc);
            void doClear(char* cmd_argv[], int cmd_argc);
          
    };

#endif