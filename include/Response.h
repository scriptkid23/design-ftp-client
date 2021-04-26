
#ifndef RESPONSE_H // include guard
#define RESPONSE_H
#include <iostream>
#include <string>

    class Response
    {
        private:
            std::string code;
            std::string message;
        public:
            Response();
            Response(std::string code, std::string message);
            std::string getCode();
            std::string getMessage();

            std::string toString();
            
    };

#endif