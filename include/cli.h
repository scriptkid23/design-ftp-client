#ifndef _CLI_H_
#define _CLI_H_

#include <cstdint>
#include <string>
#include <windows.h>
#include "constants.h"

using namespace std;

#define CLI_CAST(p_func_type) static_cast<CLI_CMD_FUNC>(p_func_type)

const uint8_t CMD_MAX_LEN = 32;
const uint8_t CMD_MAX_NUM = 64;
const uint8_t CMD_MAX_ARG_NUM = 16;
const uint16_t CMD_BUF_LEN = 256;

const uint8_t CMD_NOOP_ID  =  CMD_MAX_NUM +1;
const uint8_t CMD_UNKNOWN_ID = CMD_MAX_NUM;
const uint8_t CMD_QUIT_ID = CMD_MAX_NUM + 3;

const char SPACE[]= " ";
const char CMD_QUIT_NAME[] = "quit";

class CmdLineInterface;

typedef void (CmdLineInterface::*CLI_CMD_FUNC)(char*[], int);
class CmdLineInterface {

    private:
        string  cmdPrompt;
        uint8_t cmdIdList[CMD_MAX_NUM];
        CLI_CMD_FUNC cmdDoFunc[CMD_MAX_NUM];
        bool bRunning;
        uint8_t numCommands;
        string  cmdNameList[CMD_MAX_NUM];
        char *syntax;
        string hostname;
        string user;
        string cWorkingDirectory;
    protected:
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    public:
        CmdLineInterface();
        CmdLineInterface(string prompt);
        void setCmdPrompt(const string prompt);
        void clearScreen();
        void showCmdPrompt();   
        void addCmd(const string name, CLI_CMD_FUNC f);
        void run();
        virtual void initCmd();
        string getPrompt();
        void set_hostname(const string &hostname);
        void set_user(const string &user);
        void set_current_working_directory(const string &directory);
    private:
        void readCmd(char *cmd_buf, int buflen);
        uint8_t parseCmd(char *cmd_buf, char *cmd_argv[], int& cmd_argc);
        void doUnknown();
        void doQuit();
        void doCmd(uint8_t id, char *cmd_argv[], int cmd_argc);
};

#endif // _CLI
