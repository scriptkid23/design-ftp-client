// display.h
#ifndef DISPLAY_H // include guard
#define DISPLAY_H

#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include "constants.h"

    class Display
    {
        protected:
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
        public:
            void home_screen();
            void help_screen(int key);
            void commandline_screen(std::string str);
    };

#endif /* DISPLAY_H */