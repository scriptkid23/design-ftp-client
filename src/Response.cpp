#include "Response.h"

Response::Response(){}

Response::Response(std::string code, std::string message){
    this->code = code;
    this->message = message;
}

std::string Response::getCode(){
    return this->code;
}
std::string Response::getMessage(){
    return this->message;
}
std::string Response::toString(){
    return "(" + this->code + ") " + this->message + ".";
}