#include <iostream>
#include <string>
#include <iomanip>


#include "Display.h"


using namespace std;

void Display::home_screen(){
    std::cout<<" _______  _______  ___   ______    ___   _______  __   __" <<endl;
    std::cout<<"|       ||       ||   | |    _ |  |   | |       ||  | |  |" <<endl;
    std::cout<<"|  _____||    _  ||   | |   | ||  |   | |_     _||  |_|  |"<<endl;
    std::cout<<"| |_____ |   |_| ||   | |   |_||_ |   |   |   |  |       |"<<endl;
    std::cout<<"|_____  ||    ___||   | |    __  ||   |   |   |  |_     _|"<<endl;
    std::cout<<" _____| ||   |    |   | |   |  | ||   |   |   |    |   |" <<endl;
    std::cout<<"|_______||___|    |___| |___|  |_||___|   |___|    |___|" <<endl;
    std::cout<<"Software "<<endl;
}
void Display::help_screen(int key){
    if(key == 0){
        std::cout << "For more information on a specific command, type HELP command-name" << endl << endl;
        std::cout <<  std::setw(20) << std::left << "CONNECT";
        std::cout <<  std::setw(20) << std::left << "Connect to FTP server" << std::endl;

        std::cout <<  std::setw(20) << std::left << "DIR";
        std::cout <<  std::setw(20) << std::left << "Displays a list of files and subdirectories in a directory." << std::endl;

        std::cout <<  std::setw(20) << std::left << "MOVE";
        std::cout <<  std::setw(20) << std::left << "Moves one or more folder from one directory to another directory." << std::endl;

        std::cout <<  std::setw(20) << std::left << "CREATE";
        std::cout <<  std::setw(20) << std::left << "Create one or more folder from another directory." << std::endl;

        std::cout <<  std::setw(20) << std::left << "RENAME";
        std::cout <<  std::setw(20) << std::left << "Rename one or more folder from another directory." << std::endl;

        std::cout <<  std::setw(20) << std::left << "DOWNLOAD";
        std::cout <<  std::setw(20) << std::left << "Download one or more folder from another directory." << std::endl;

        std::cout <<  std::setw(20) << std::left << "UPLOAD";
        std::cout <<  std::setw(20) << std::left << "Upload one or more folder from another directory." << std::endl;

        std::cout <<  std::setw(20) << std::left << "DEL";
        std::cout <<  std::setw(20) << std::left << "Delete one or more folder from another directory." << std::endl;

        std::cout <<  std::setw(20) << std::left << "CLEAR";
        std::cout <<  std::setw(20) << std::left << "Clears the screen." << std::endl;



        std::cout <<  std::setw(20) << std::left << "EXIT";
        std::cout << std::setw(20) << std::left << "Disconnected to server" << std::endl;
    }
}
void Display::commandline_screen(string str){
    
    if(str.compare("") == 0){
        
        std::cout << "62pm2@spirity>";
    }
    else{
        std::cout << "62pm2@spirity "+str+">";
    }
}
