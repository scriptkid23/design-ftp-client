
#ifndef FTPCLIENT_H // include guard
#define FTPCLIENT_H

#include <cstdint>
#include <iostream>
#include <windows.h> 
#include "tcpsocket.h"
#include "Extensions.h"
#include "cli.h"
#include "constants.h"


class FTPClient;

// using callback = void (CmdLineInterface::*)(std::string);
// typedef void (CmdLineInterface::*callback)(std::string);


    class FTPClient{
       protected:
            TcpSocket socketControl;
            TcpSocket socketData;
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
            bool connected;
            string hostname;
        
        public:
            FTPClient();
            void connect(const string &hostname, const string &port, CmdLineInterface *callback);
            void set_host_name(string hostname);
            void echo(const string &msg);
            void login(CmdLineInterface *callback);
            void get_list_file();
            void close();
            void change_current_working_directory();
            void delete_directory();
            void create_directory();
            void rename_directory_or_file();
            void delete_file();
            void download();
            void upload();
       
            bool is_connected();
        
            string get_host_name();
            string parse_epsv_response();
            /*
                if you want to using callback function
                
                the first:
                    using callback = void (*)([param1],[param2]);
                    void login(callback fnc);
            */
    };

#endif