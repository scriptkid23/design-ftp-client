#include <iostream>
#include "Display.h"

#define USERNAME "123"
#define PASSWORD "123"

using namespace std;

int main(int argc, const char** argv) {

    string syntax;
    Display dp;
    while (true)
    {
        bool flag = true;
        dp.commandline_screen("");
        getline(cin,syntax);
        cout << endl;
        if(syntax.compare("connect localhost 123 123") == 0){
            while (flag)
            {
                dp.commandline_screen("server");
                getline(cin,syntax);
                if(syntax.compare("exit") == 0){
                    flag = false;
                }
            }
            
        }
        else{
            cout << "Username or password not match!" << endl;
        }


    }
    
    return 0;
}
