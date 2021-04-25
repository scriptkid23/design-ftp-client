

#ifndef EXTENSIONS_H // include guard
#define EXTENSIONS_H

#include "Response.h"
#include <regex>
    class  Extensions
    {   
        public:
            static void str_upper(std::string *str);
            static std::string str_trim(std::string &str);
            static std::vector<std::string> str_split(std::string str,char regex);
            static Response convertBufferToResponse(const char* buffer);
    };

#endif