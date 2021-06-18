

#ifndef EXTENSIONS_H // include guard
#define EXTENSIONS_H

#include "Response.h"
#include <regex>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

    class  Extensions
    {   
        public:
            static void str_upper(std::string *str);
            static std::string str_trim(std::string &str);
            static std::vector<std::string> str_split(std::string str,char regex);
            static Response convert_buffer_to_response(const char* buffer);
            static std::string get_file_name(const std::string &source);
            static std::string get_path(const std::string &source);
            static std::string parse_name(char *cmd_argv[], int cmd_argc);
    };

#endif