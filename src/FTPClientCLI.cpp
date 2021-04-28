/*
    
    Spirity Company. Inc
    Copyright by HoanDo.

*/
#include "FTPClientCLI.h"


FTPClientCLI::FTPClientCLI():CmdLineInterface("62pm2@spirity> "){};

void FTPClientCLI::initCmd(){
    
    addCmd("connect", CLI_CAST(&FTPClientCLI::doConnect));
    addCmd("help", CLI_CAST(&FTPClientCLI::doHelp));
    addCmd("clear", CLI_CAST(&FTPClientCLI::doClear));

    // using if is connected = true
    
    addCmd("login", CLI_CAST(&FTPClientCLI::doLogin));
    addCmd("ls",CLI_CAST(&FTPClientCLI::doList));
    addCmd("cd",CLI_CAST(&FTPClientCLI::doCWD));
    addCmd("rmdir",CLI_CAST(&FTPClientCLI::doDeleteDirectory));
    addCmd("mkdir",CLI_CAST(&FTPClientCLI::doCreateDirectory));
    addCmd("rename",CLI_CAST(&FTPClientCLI::doRenameDirectoryOrFile));
    addCmd("download",CLI_CAST(&FTPClientCLI::doDownload));
    addCmd("upload",CLI_CAST(&FTPClientCLI::doUpload));
    addCmd("del",CLI_CAST(&FTPClientCLI::doDeleteFile));

    addCmd("exit", CLI_CAST(&FTPClientCLI::doClose));
  
}

void FTPClientCLI::doConnect(char* cmd_argv[], int cmd_argc){
    
    // define variable hostname and port
    std::string hostname;
    std::string port;
    std::stringstream ss;

    ss << cmd_argv[1];
    ss >> hostname;
    ss.clear();
    ss << cmd_argv[2];
    ss >> port;

   FTPClientCLI::ftpClient.connect(hostname,port,this);
}
void FTPClientCLI::doHelp(char* cmd_argv[], int cmd_argc){
        if(!FTPClientCLI::ftpClient.is_connected()){
            std::cout << "Commands may be abbreviated.  Commands are:" << endl << endl;
            std::cout <<  std::setw(30) << std::left << "connect <hostname> <port>";
            std::cout <<  std::setw(20) << std::left << "Connect to FTP server" << std::endl;
            std::cout <<  std::setw(30) << std::left << "help";
            std::cout <<  std::setw(20) << std::left << "Print local help information" << std::endl;
            std::cout <<  std::setw(30) << std::left << "clear";
            std::cout <<  std::setw(20) << std::left << "Clears the screen" << std::endl;
            std::cout <<  std::setw(30) << std::left << "quit";
            std::cout <<  std::setw(20) << std::left << "Exit the program." << std::endl;
        }
        else{
            std::cout << "Commands may be abbreviated.  Commands are:" << endl << endl;
            std::cout <<  std::setw(30) << std::left << "login";
            std::cout <<  std::setw(20) << std::left << "login to ftp server" << std::endl;
            std::cout <<  std::setw(30) << std::left << "ls";
            std::cout <<  std::setw(20) << std::left << "Show list directory or file" << std::endl;
            std::cout <<  std::setw(30) << std::left << "cd";
            std::cout <<  std::setw(20) << std::left << "Displays the name of or changes the current directory." << std::endl;
            std::cout <<  std::setw(30) << std::left << "rmdir";
            std::cout <<  std::setw(20) << std::left << "Removes a directory." << std::endl;
            std::cout <<  std::setw(30) << std::left << "del";
            std::cout <<  std::setw(20) << std::left << "Removes a file." << std::endl;
            std::cout <<  std::setw(30) << std::left << "rename";
            std::cout <<  std::setw(20) << std::left << "Renames a directory or file." << std::endl;
            std::cout <<  std::setw(30) << std::left << "download";
            std::cout <<  std::setw(20) << std::left << "Download file" << std::endl;
            std::cout <<  std::setw(30) << std::left << "upload";
            std::cout <<  std::setw(20) << std::left << "Upload file." << std::endl;
            std::cout <<  std::setw(30) << std::left << "help";
            std::cout <<  std::setw(20) << std::left << "Print local help information" << std::endl;
            std::cout <<  std::setw(30) << std::left << "clear";
            std::cout <<  std::setw(20) << std::left << "Clears the screen" << std::endl;
            std::cout <<  std::setw(30) << std::left << "exit";
            std::cout <<  std::setw(20) << std::left << "Logout." << std::endl;
        }
            
}
void FTPClientCLI::doClose(char* cmd_argv[], int cmd_argc){
    if(FTPClientCLI::ftpClient.is_connected()){
        FTPClientCLI::ftpClient.close();
        FTPClientCLI::setCmdPrompt("62pm2@spirity> ");
    }
}

void FTPClientCLI::doClear(char* cmd_argv[], int cmd_argc){
    system("cls");
}

void FTPClientCLI::doLogin(char* cmd_argv[], int cmd_argc){
   
    try{
        FTPClientCLI::ftpClient.login(this);  
    }catch(SocketException &e){
        cerr << e.what() << endl;
    }
   
}
void FTPClientCLI::doList(char* cmd_argv[], int cmd_argc){
        
        try{
            FTPClientCLI::ftpClient.get_list_file();
        }catch(SocketException &e){
            cerr << e.what() << endl;
        }
}
void FTPClientCLI::doCWD(char* cmd_argv[], int cmd_argc){
    //TODO: code here;
};
void FTPClientCLI::doDeleteDirectory(char* cmd_argv[], int cmd_argc){
    //TODO: code here;
};
void FTPClientCLI::doCreateDirectory(char* cmd_argv[], int cmd_argc){
    //TODO: code here;
};
void FTPClientCLI::doRenameDirectoryOrFile(char* cmd_argv[], int cmd_argc){
    //TODO: code here;
};
void FTPClientCLI::doDeleteFile(char* cmd_argv[], int cmd_argc){
    //TODO: code here;
};
void FTPClientCLI::doDownload(char* cmd_argv[], int cmd_argc){
    //TODO: code here;
};
void FTPClientCLI::doUpload(char* cmd_argv[], int cmd_argc){
    //TODO: code here;
};