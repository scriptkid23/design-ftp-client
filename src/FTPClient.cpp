#include "FTPClient.h"
#include "Extensions.h"

FTPClient::FTPClient(){};
void FTPClient::echo(const string &msg){
    sendStringRequest(msg);
    
}
void FTPClient::login(){
    
    std::string username, password, request;
    std::cout << "Username: ";
    std::cin >> username;
    request = "user "+ username + "\r\n";

    int bytes;
    char buffer[256];

    sendStringRequest(request);
    bytes = recvDataBuffer(buffer,255);
    
    if(bytes > 0){
        buffer[bytes] = 0;

        std::cout << "Password: ";
        std::cin >> password;
        request = "pass "+password+"\r\n";

        sendStringRequest(request);
        bytes = recvDataBuffer(buffer,255);

        buffer[bytes] = 0;;
        cout << Extensions::convertBufferToResponse(buffer).toString();
    }

}