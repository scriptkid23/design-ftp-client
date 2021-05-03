


#include "Display.h"


void Display::home_screen(){
    system("cls");
    SetConsoleTextAttribute(console, COLOR_INFO);
    std::cout<<" _______  _______  _______      _______  ___      ___  _______  __    _  _______"       <<std::endl;
    std::cout<<"|       ||       ||       |    |       ||   |    |   ||       ||  |  | ||       |"      <<std::endl;
    std::cout<<"|    ___||_     _||    _  |    |       ||   |    |   ||    ___||   |_| ||_     _|"      <<std::endl;
    std::cout<<"|   |___   |   |  |   |_| |    |       ||   |    |   ||   |___ |       |  |   |"        <<std::endl;
    std::cout<<"|    ___|  |   |  |    ___|    |      _||   |___ |   ||    ___||  _    |  |   | "       <<std::endl;
    std::cout<<"|   |      |   |  |   |        |     |_ |       ||   ||   |___ | | |   |  |   |"        <<std::endl;
    std::cout<<"|___|      |___|  |___|        |_______||_______||___||_______||_|  |__|  |___| v0.1"   <<std::endl;
    
    std::cout<<"Spirity Software" << std::endl;
    SetConsoleTextAttribute(console, COLOR_DEFAULT);
    std::cout << "Commands may be abbreviated.  Commands are:" << std::endl << std::endl;
    std::cout <<  std::setw(30) << std::left << "connect <hostname> <port>";
    std::cout <<  std::setw(20) << std::left << "Connect to FTP server" << std::endl;
    std::cout <<  std::setw(30) << std::left << "help";
    std::cout <<  std::setw(20) << std::left << "Print local help information" << std::endl;
    std::cout <<  std::setw(30) << std::left << "clear";
    std::cout <<  std::setw(20) << std::left << "Clears the screen" << std::endl;
    std::cout <<  std::setw(30) << std::left << "quit";
    std::cout <<  std::setw(20) << std::left << "Exit the program." << std::endl;
}