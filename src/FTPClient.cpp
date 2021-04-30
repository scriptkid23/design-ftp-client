#include "FTPClient.h"

FTPClient::FTPClient()
{
    connected = false;
    isLogin = false;
};

void FTPClient::connect(const string &hostname, const string &port, CmdLineInterface *callback)
{
    try
    {
        char buffer[256];
        socketControl.connect(hostname, port);

        socketControl.recv(buffer, 256);

        set_host_name(hostname);
        callback->setCmdPrompt(hostname + "> ");

        this->connected = true;
        SetConsoleTextAttribute(console, COLOR_PRIMARY);
        cout << "INFO: Connect to server succeeded." << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
}
void FTPClient::close(CmdLineInterface *callback)
{
    try
    {
        socketControl.close();
    }
    catch (SocketException &e)
    {
        cerr << "ERROR: " << e.what() << endl;
    }
    this->connected = false;
    this->isLogin = false;
    callback->setCmdPrompt("62pm2@spirity> ");
}
bool FTPClient::is_connected()
{
    return this->connected;
}
bool FTPClient::is_login()
{
    return this->isLogin;
}

void FTPClient::set_host_name(string hostname)
{
    this->hostname = hostname;
}

string FTPClient::get_host_name()
{
    return this->hostname;
}

void FTPClient::login(CmdLineInterface *callback)
{

    if (!is_connected())
        throw SocketException("You should connect!");

    std::string username, password, request, prompt;
    Response res;

    std::cout << "Username: ";
    std::cin >> username;
    request = "user " + username + "\r\n";

    socketControl.send(request);

    res = get_receive_socket_control();

    if (res.getCode() == "331")
    {

        std::cout << "Password: ";
        std::cin >> password;
        request = "pass " + password + "\r\n";

        socketControl.send(request);
        res = get_receive_socket_control();

        if (res.getCode() == "230")
        {
            prompt = this->hostname + " " + username + "> ";
            isLogin = true;
            callback->setCmdPrompt(prompt);
        }
        else
        {
            SetConsoleTextAttribute(console, COLOR_ERROR);
            cout << "ERROR: " << res.getMessage() << endl;
            SetConsoleTextAttribute(console, COLOR_PRIMARY);

            prompt = this->hostname + "> ";
            isLogin = false;
            callback->setCmdPrompt(prompt);
        }
    }
    else
    {
        cerr << "ERROR: " << res.getMessage() << endl;
    }
}
string FTPClient::parse_epsv_response()
{
    socketControl.send("EPSV\r\n");

    Response res = get_receive_socket_control();

    std::regex rx(R"([[:digit:]]+)");
    std::smatch m;
    std::string str = res.getMessage();
    regex_search(str, m, rx);

    return m[0];
}
string FTPClient::get_receive_socket_data()
{
    int bytes;
    char buffer[255];
    string result;
    while (true)
    {
        if ((bytes = socketData.recv(buffer, 255)) == -1)
        {
            std::cout << "recv error: " << strerror(errno) << std::endl;
            exit(1);
        }
        if (bytes == 0)
        {
            break;
        }
        for (int i = 0; i < bytes; i++)
        {
            result += buffer[i];
        }
    }
    return result;
}
Response FTPClient::get_receive_socket_control()
{

    char buffer[255];
    int bytes = socketControl.recv(buffer, 255);
    buffer[bytes] = 0;

    return Extensions::convert_buffer_to_response(buffer);
};
void FTPClient::get_list_file()
{
    if (!is_connected() && !is_login())
        throw SocketException("You should connect and login!");

        Response res;

        string port = parse_epsv_response();

        socketData.connect(hostname, port);

        socketControl.send("NLST\r\n");

        // Beacause response of NLST return 2 response
        get_receive_socket_control();
        get_receive_socket_control();

        // get result from socket data
        cout << get_receive_socket_data();

        // close socket data
        socketData.close();
}
void FTPClient::get_present_working_directory()
{
    if (!is_connected() && !is_login())
        throw SocketException("You should connect and login!");

    socketControl.send("PWD\r\n");
    cout << get_receive_socket_control().getMessage();
};
void FTPClient::get_directory(){
    if (!is_connected() && !is_login())
        throw SocketException("You should connect and login!");
    
    string port = parse_epsv_response();

    socketData.connect(hostname, port);

    socketControl.send("LIST\r\n");

    get_receive_socket_control();
    get_receive_socket_control();

    cout << get_receive_socket_data();

    socketData.close();


}
void FTPClient::download(const string &filename){
    if (!is_connected() && !is_login())
        throw SocketException("You should connect and login!");
    
    Response res;

    string port = parse_epsv_response();

    socketData.connect(hostname, port);

    socketControl.send("TYPE I\r\n");
    res = get_receive_socket_control();
    if(res.getCode() != "200") return;

    string request = "RETR "+filename+"\r\n";
    socketControl.send(request);

    res = get_receive_socket_control();
    if(res.getCode() == "550"){
        
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cout << "ERROR: " <<res.toString() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        socketData.close();
        
        return;

    }
    get_receive_socket_control();

    SetConsoleTextAttribute(console, COLOR_PRIMARY);
    cout << "INFO: Download File: " <<filename<<"..."<< endl;
    SetConsoleTextAttribute(console, COLOR_DEFAULT);

    FILE *file;    


    char *source = const_cast<char*>((filename).c_str());
    file = fopen(source,"wb");
    
    int bytes;
    char buffer[4096];
    while(true){
        if((bytes =socketData.recv(buffer,4096)) == -1){
            std::cout << "recv error: " << strerror(errno) << std::endl;
        }
        if(bytes == 0){
            SetConsoleTextAttribute(console, COLOR_PRIMARY);
            std::cout << "INFO: Download File succeeded." << std::endl;
            SetConsoleTextAttribute(console, COLOR_DEFAULT);
            break;
        }
        fwrite(buffer, bytes, 1, file);
    }
    fclose(file);
    socketData.close();
}
void FTPClient::upload(const string &source){
    if (!is_connected() && !is_login())
        throw SocketException("You should connect and login!");
    
    Response res;
    std::ifstream file(source, std::ios::in | std::ios::binary | std::ios::ate);

    if(file){
        long length = file.tellg();
		file.seekg (0, file.beg);

        string port = parse_epsv_response();

        socketData.connect(hostname, port);

        socketControl.send("TYPE I\r\n");
        res = get_receive_socket_control();
        if(res.getCode() != "200") return;

        string filename = Extensions::get_file_name(source);
        string request = "STOR "+filename+"\r\n";

        socketControl.send(request);
        res = get_receive_socket_control();
        if(res.getCode() != "150"){
            return;
        }
        SetConsoleTextAttribute(console, COLOR_PRIMARY);
        std::cout<<"INFO: Sending File : "<<source<<"..."<<std::endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        
        string data;
		double c_length = length;

        while (length > 0){
			int read_sz = 2048 <length ? 2048 : length;
			char buffer[2048+1];
			
            file.read(buffer,read_sz);
			data.assign(buffer,read_sz);
            
			socketData.send(data);
			length -= read_sz;
		}
        socketData.close();

        res = get_receive_socket_control();
        if(res.getCode() == "226"){
            SetConsoleTextAttribute(console, COLOR_PRIMARY);
            cout << "INFO: Upload file succeeded." << endl;
            SetConsoleTextAttribute(console, COLOR_DEFAULT);
           
        }
        else{
            SetConsoleTextAttribute(console, COLOR_ERROR);
            cout << "INFO: Upload file failed." << endl;
            SetConsoleTextAttribute(console, COLOR_DEFAULT);
           
        }
        file.close();
        
    }
    else{
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cout << "ERROR: Doesn't exist. Please check the filename." << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
        
}