
#ifndef FTPCLIENT_H // include guard
#define FTPCLIENT_H

#include <cstdint>
#include <iostream>
#include <windows.h> 
#include "tcpsocket.h"
#include "Extensions.h"
#include "cli.h"
#include "constants.h"
#include "Response.h"
#include <fstream>
class FTPClient;

// using callback = void (CmdLineInterface::*)(std::string);
// typedef void (CmdLineInterface::*callback)(std::string);


    class FTPClient{
       protected:
            TcpSocket socketControl;
            TcpSocket socketData;
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
            bool connected;
            bool isLogin;
            string hostname;
        
        public:
            FTPClient();
            void connect(const string &hostname, const string &port, CmdLineInterface *callback);
            void set_host_name(string hostname);
            void echo(const string &msg);
            void login(const string &username, const string &password, CmdLineInterface *callback);
            void get_list_file();
            void close(CmdLineInterface *callback);
            void change_current_working_directory(const string &directory, CmdLineInterface *callback);
            void delete_directory(const string &directory);
            void create_directory(const string &directory);
            void rename_directory_or_file(const string &src, const string &dest);
            void delete_file(const string &directory);
            void download(const string &filename);
            void upload(const string &filename);
            string get_present_working_directory();
            void get_directory();
            bool is_connected();
            bool is_login();
        
            string      get_host_name();
            string      parse_epsv_response();
            string      get_receive_socket_data(); // get value from socket data
            Response    get_receive_socket_control(); // get message from socket control 
            /*
                if you want to using callback function
                
                the first:
                    using callback = void (*)([param1],[param2]);
                    void login(callback fnc);
            */
    };

#endif