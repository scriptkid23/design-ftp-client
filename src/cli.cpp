#include <iostream>
#include <cstring>
#include "cli.h"


CmdLineInterface::CmdLineInterface()
{
    numCommands = 0;
    cmdPrompt ="cli>";
    bRunning = false;
}

CmdLineInterface::CmdLineInterface(string prompt)
{
    numCommands = 0;
    cmdPrompt = prompt;
    bRunning = false;
}

// Xoa man hinh
void CmdLineInterface::clearScreen()
{
    system("cls");
}

void CmdLineInterface::setCmdPrompt(const string prompt)
{
    this->cmdPrompt = prompt;
}

// Hien thi dau nhac lenh
void CmdLineInterface::showCmdPrompt()
{
    SetConsoleTextAttribute(console, COLOR_INFO);
    cout << this->cmdPrompt ;
    SetConsoleTextAttribute(console, COLOR_DEFAULT);
}

void CmdLineInterface::addCmd(const string name, CLI_CMD_FUNC f)
{
    this->cmdDoFunc[this->numCommands]=f;
    cmdNameList[this->numCommands] = name;
    this->numCommands++;
}

void CmdLineInterface::initCmd(){}


// Doc lenh nhap tu ban phim
void CmdLineInterface::readCmd(char * sCmdBuf, int buflen)
{
    fflush(stdin); //xoa stdin truoc khi nhap xau
    fgets(sCmdBuf, buflen, stdin); // doc xau
    int slen = strlen(sCmdBuf); // cat bo '\n' o cuoi xau
    if( slen > 0 && sCmdBuf[slen -1] == '\n')
        sCmdBuf[slen-1] = '\0';
}

// Ham phan tich cu phap

uint8_t CmdLineInterface::parseCmd(char *sCmdBuf, char * cmd_argv[], int& cmd_argc)
{
    // phan tich xau ki tu nguoi dung nhap vao de xac dinh lenh va tham so
    this->syntax = sCmdBuf;
    // Cu phap:  <ten lenh>space<tham so 1>space<tham so 2>
    //           Moi thanh phan cua lenh cach nhau 1 hoac nhieu dau space
    char * arg;
    cmd_argc = 0; // so tham so = 0
    arg = strtok (sCmdBuf,SPACE); // phan tich xau ki tu trong sCmdBuf
    while (arg != NULL && cmd_argc < CMD_MAX_ARG_NUM)
    {
        cmd_argv[cmd_argc++] = arg;
        arg = strtok (NULL, SPACE);
    }
    int i;
    if(cmd_argc>0)
    {
        for(i = 0; i<this->numCommands; i++)
        {
            if(strcmp(cmd_argv[0],this->cmdNameList[i].c_str())==0)
                return i;
        }
        if(strcmp(cmd_argv[0],CMD_QUIT_NAME)==0)
            return CMD_QUIT_ID;

    }
    else
        return CMD_NOOP_ID;
    return CMD_UNKNOWN_ID;
}

// ham thuc hien khi lenh khong dung "unknown"
void CmdLineInterface::doUnknown()
{
    cerr << "'"<<this->syntax <<"' "<<"is not recognized as an internal or external command, Please type 'help'" << endl;
}

// ham thuc hien lenh "quit"
void CmdLineInterface::doQuit()
{
    this->bRunning = false;
    cout << endl;
}

void CmdLineInterface::doCmd(uint8_t id, char * cmd_argv[], int cmd_argc)
{
    if(id==CMD_NOOP_ID)
        return;
    else if(id==CMD_UNKNOWN_ID)
    {
        doUnknown();
    }
    else if(id==CMD_QUIT_ID)
    {
        doQuit();
    }
    else
    {
        CLI_CMD_FUNC f = this->cmdDoFunc[id];
        if(f!=NULL)
            (this->*f)(cmd_argv, cmd_argc);
    }
}

void CmdLineInterface::run()
{
    char cmdBuf[CMD_BUF_LEN];
    char* cmd_ArgArray[CMD_MAX_ARG_NUM];
    int cmd_ArgCount;
    uint8_t cid;
    bRunning = true;

    while (bRunning) // chu trinh chinh - MAIN LOOP
    {
        // hien thi dau nhac lenh
        cout<< endl;
        showCmdPrompt();
        // nhap lenh
        readCmd(cmdBuf, CMD_BUF_LEN);
        // phan tich lenh
        cid = parseCmd(cmdBuf, cmd_ArgArray, cmd_ArgCount);
        // thuc hien lenh va hien thi ket qua
        doCmd(cid, cmd_ArgArray, cmd_ArgCount);
    }
}


string CmdLineInterface::getPrompt(){
    if(user.size() != 0 && cWorkingDirectory.size() != 0){
        return hostname+" "+user+":~"+cWorkingDirectory+"> ";
    }
    else{
        return hostname+"> ";
    }
};
void CmdLineInterface::set_hostname(const string &hostname){
    this->hostname = hostname;
};
void CmdLineInterface::set_user(const string &user){
    this->user = user;
};
void CmdLineInterface::set_current_working_directory(const string &directory){
    this->cWorkingDirectory = directory;
};