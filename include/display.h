// display.h
#ifndef DISPLAY_H // include guard
#define DISPLAY_H

    class Display
    {
        
        public:
            void home_screen();
            void help_screen(int key);
            void commandline_screen(std::string str);
    };

#endif /* DISPLAY_H */