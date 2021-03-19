

#ifndef EXTENSIONS_H // include guard
#define EXTENSIONS_H


    class  Extensions
    {
        public:
            void str_upper(std::string *str);
            std::string str_trim(std::string &str);
            std::vector<std::string> str_split(std::string str,char regex);
    };

#endif