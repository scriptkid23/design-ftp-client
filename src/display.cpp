#include <iostream>
#include <string>
#include "Display.h"


using namespace std;

void Display::home_screen(){
    //TODO:
}
void Display::help_screen(){
    //TODO:
}
void Display::commandline_screen(string str){
    if(str.compare("") == 0){
        cout << "62pm2@spirity> ";
    }
    else{
        cout << "62pm2@spirity "+str+">";
    }
}
