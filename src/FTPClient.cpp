#include "FTPClient.h"
#include "iostream"
#include <iomanip>

FTPClient::FTPClient():CmdLineInterface("spirity> "){};

void FTPClient::initCmd(){
    
    addCmd("connect", CLI_CAST(&FTPClient::doConnect));
    addCmd("help", CLI_CAST(&FTPClient::doHelp));
    addCmd("clear", CLI_CAST(&FTPClient::doClear));
  
}

void FTPClient::doConnect(char* cmd_argv[], int cmd_argc){

}
void FTPClient::doHelp(char* cmd_argv[], int cmd_argc){
            std::cout << "Commands may be abbreviated.  Commands are:" << endl << endl;
            std::cout <<  std::setw(20) << std::left << "connect";
            std::cout <<  std::setw(20) << std::left << "Connect to FTP server" << std::endl;
            std::cout <<  std::setw(20) << std::left << "help";
            std::cout <<  std::setw(20) << std::left << "Print local help information" << std::endl;
            std::cout <<  std::setw(20) << std::left << "clear";
            std::cout <<  std::setw(20) << std::left << "Clears the screen" << std::endl;
            std::cout <<  std::setw(20) << std::left << "quit";
            std::cout << std::setw(20) << std::left << "Exit the program." << std::endl;
}
void FTPClient::doClear(char* cmd_argv[], int cmd_argc){
    system("cls");
}