#include "FTPClient.h"
#include "Extensions.h"

FTPClient::FTPClient(){
    connected = false;
};

void FTPClient::connect(const string &hostname, const string &port, CmdLineInterface *callback){
        try{
                char buffer[256];
                socketControl.connect(hostname, port);
                
                socketControl.recv(buffer,256);
                set_host_name(hostname);
                callback->setCmdPrompt(hostname+"> ");

                this->connected = true;

        }
        catch(SocketException &e){
                cerr<< e.what() << endl;
        }
        
}
void FTPClient::close(){
     try
    {
        socketControl.close();
    }
    catch(SocketException& e)
    {
        cerr<< e.what() << endl;
    }
    this->connected = false;
}
bool FTPClient::is_connected(){
    return this->connected;
}

void FTPClient::set_host_name(string hostname){
    this->hostname = hostname;
}

string FTPClient::get_host_name(){
    return this->hostname;
}

void FTPClient::send_string_request(TcpSocket &socket, const string &request){
    try
    {
        socket.send(request);

    }
    catch(SocketException& e)
    {
        cerr << e.what();
    }
}
int FTPClient::recv_data_buffer(TcpSocket &socket,char* buffer, unsigned int bufLen){
    int bytes;
    try
    {
        bytes = socket.recv(buffer, bufLen);
        return bytes;
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}
void FTPClient::login(CmdLineInterface *callback){
    
    std::string username, password, request, prompt;
    Response res;

    std::cout << "Username: ";
    std::cin >> username;
    request = "user "+ username + "\r\n";
   
    
    int bytes;
    char buffer[256];

    send_string_request(socketControl,request);

    bytes = recv_data_buffer(socketControl,buffer,255);
    buffer[bytes] = 0;

    res =  Extensions::convertBufferToResponse(buffer);
    if(bytes > 0){
        

        std::cout << "Password: ";
        std::cin >> password;
        request = "pass "+password+"\r\n";

        send_string_request(socketControl,request);
        bytes = recv_data_buffer(socketControl,buffer,255);
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
        cerr << res.getMessage() << endl;
    }

}
string FTPClient::parse_epsv_response(){
    send_string_request(socketControl,"EPSV\r\n");

    char buffer[256];
    int bytes = recv_data_buffer(socketControl,buffer,256);
    buffer[bytes] = 0;

    // cout << buffer;
    Response res = Extensions::convertBufferToResponse(buffer);
    
    std::regex rx(R"([[:digit:]]+)");
    std::smatch m;
    std::string str = res.getMessage();
    regex_search(str, m, rx);
    string port = m[0];
    return port;
    
}
void FTPClient::get_list_file(){
    try{
        
        string port = parse_epsv_response();
        socketData.connect(hostname, port);

        char buffer[256];
        send_string_request(socketControl,"NLST\r\n");

        int bytes = recv_data_buffer(socketData,buffer,256);
        buffer[bytes] = 0;

        Response res = Extensions::convertBufferToResponse(buffer);
        cout << res.getMessage() << endl;

        
    
    }
    catch(SocketException& e){
        cout << e.what() << endl;
    }
    
}