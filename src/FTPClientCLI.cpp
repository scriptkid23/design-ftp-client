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
        
            std::cout <<  std::setw(30) << std::left << "help";
            std::cout <<  std::setw(20) << std::left << "Print local help information" << std::endl;
            std::cout <<  std::setw(30) << std::left << "clear";
            std::cout <<  std::setw(20) << std::left << "Clears the screen" << std::endl;
            std::cout <<  std::setw(30) << std::left << "exit";
            std::cout <<  std::setw(20) << std::left << "Disconnected" << std::endl;
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