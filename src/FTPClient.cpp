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

void FTPClient::login(CmdLineInterface *callback){
    
    if(!is_connected()) throw SocketException("You should connect!");

    std::string username, password, request, prompt;
    Response res;

    std::cout << "Username: ";
    std::cin >> username;
    request = "user "+ username + "\r\n";
   
    
    int bytes;
    char buffer[256];

    socketControl.send(request);

    bytes = socketControl.recv(buffer,255);
    buffer[bytes] = 0;

    res =  Extensions::convertBufferToResponse(buffer);
    if(bytes > 0){
        

        std::cout << "Password: ";
        std::cin >> password;
        request = "pass "+password+"\r\n";

        socketControl.send(request);
        bytes = socketControl.recv(buffer,255);
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
    socketControl.send("EPSV\r\n");
    
    char buffer[256];
    int bytes = socketControl.recv(buffer,255);
    buffer[bytes] = 0;

    // cout << buffer;
    Response res = Extensions::convertBufferToResponse(buffer);
    
    std::regex rx(R"([[:digit:]]+)");
    std::smatch m;
    std::string str = res.getMessage();
    regex_search(str, m, rx);

    return m[0];
    
    
}
void FTPClient::get_list_file(){
    if(!is_connected()) throw SocketException("You should connect and login!");

    try{
        char buffer[256];
        int bytes;

        string port = parse_epsv_response();

        socketData.connect(hostname, port);        
        
        //TODO: fix bug NLST
        socketControl.send("NLST\r\n");
        // Beacause response of NLST return 2 response 
        socketControl.recv(buffer,255);
        
        cout << "Info:" << buffer << endl;
        socketControl.recv(buffer,255);
        cout << "Info:" << buffer << endl;

        bytes = socketData.recv(buffer,255);
        buffer[bytes] = 0;
        cout << buffer << endl;

        socketData.close();
    }
    catch(SocketException& e){
        cout << e.what() << endl;
    }
    
}