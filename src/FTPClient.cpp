#include "FTPClient.h"
#include "Extensions.h"

FTPClient::FTPClient(){};
void FTPClient::echo(const string &msg){
    sendStringRequest(msg);
    
}
void FTPClient::setHostName(string hostname){
    this->hostname = hostname;
}

string FTPClient::getHostName(){
    return this->hostname;
}

void FTPClient::login(CmdLineInterface *callback){
    
    std::string username, password, request, prompt;
    Response res;

    std::cout << "Username: ";
    std::cin >> username;
    request = "user "+ username + "\r\n";
   
    
    int bytes;
    char buffer[256];

    sendStringRequest(request);
    bytes = recvDataBuffer(buffer,255);
    buffer[bytes] = 0;

    res =  Extensions::convertBufferToResponse(buffer);
    if(bytes > 0){
        

        std::cout << "Password: ";
        std::cin >> password;
        request = "pass "+password+"\r\n";

        sendStringRequest(request);
        bytes = recvDataBuffer(buffer,255);
        buffer[bytes] = 0;

        res =  Extensions::convertBufferToResponse(buffer);
        
        if(res.getCode() == "230"){
            prompt = this->hostname +" "+username+"> ";
            callback->setCmdPrompt(prompt);
        }
        else{
            cout << "Message: " << res.getMessage() <<endl;
            prompt = this->hostname+"> ";
            callback->setCmdPrompt(prompt);
        }

    }
    else{
        cout << res.getMessage() << endl;
    }

}