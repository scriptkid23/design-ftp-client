/*
    
    Spirity Company. Inc
    Copyright by HoanDo.

*/
#include "FTPClientCLI.h"

FTPClientCLI::FTPClientCLI() : CmdLineInterface("62pm2@spirity> "){};

void FTPClientCLI::initCmd()
{

    addCmd("connect", CLI_CAST(&FTPClientCLI::doConnect));
    addCmd("help", CLI_CAST(&FTPClientCLI::doHelp));
    addCmd("clear", CLI_CAST(&FTPClientCLI::doClear));

    // using if is connected = true

    addCmd("login", CLI_CAST(&FTPClientCLI::doLogin));
    addCmd("ls", CLI_CAST(&FTPClientCLI::doList));
    addCmd("dir", CLI_CAST(&FTPClientCLI::doDIR));
    addCmd("pwd", CLI_CAST(&FTPClientCLI::doPWD));
    addCmd("cd", CLI_CAST(&FTPClientCLI::doCWD));
    addCmd("rmdir", CLI_CAST(&FTPClientCLI::doDeleteDirectory));
    addCmd("mkdir", CLI_CAST(&FTPClientCLI::doCreateDirectory));
    addCmd("rename", CLI_CAST(&FTPClientCLI::doRenameDirectoryOrFile));
    addCmd("download", CLI_CAST(&FTPClientCLI::doDownload));
    addCmd("upload", CLI_CAST(&FTPClientCLI::doUpload));
    addCmd("del", CLI_CAST(&FTPClientCLI::doDeleteFile));

    addCmd("close", CLI_CAST(&FTPClientCLI::doClose));
}

void FTPClientCLI::doConnect(char *cmd_argv[], int cmd_argc)
{
    try
    {
        if (cmd_argc != 3)
        {
            SetConsoleTextAttribute(console, COLOR_ERROR);
            cerr << "ERROR: The syntax of the command is incorrect." << endl;
            SetConsoleTextAttribute(console, COLOR_DEFAULT);

            return;
        }
        // define variable hostname and port
        std::string hostname;
        std::string port;
        std::stringstream ss;

        ss << cmd_argv[1];
        ss >> hostname;
        ss.clear();
        ss << cmd_argv[2];
        ss >> port;

        FTPClientCLI::ftpClient.connect(hostname, port, this);
        SetConsoleTextAttribute(console, COLOR_PRIMARY);
        cout << "INFO: Connect to server succeeded." << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
}
void FTPClientCLI::doHelp(char *cmd_argv[], int cmd_argc)
{
    if (!FTPClientCLI::ftpClient.is_connected())
    {
        std::cout << "Commands may be abbreviated.  Commands are:" << endl
                  << endl;
        std::cout << std::setw(30) << std::left << "connect <hostname> <port>";
        std::cout << std::setw(20) << std::left << "Connect to FTP server" << std::endl;
        std::cout << std::setw(30) << std::left << "help";
        std::cout << std::setw(20) << std::left << "Print local help information" << std::endl;
        std::cout << std::setw(30) << std::left << "clear";
        std::cout << std::setw(20) << std::left << "Clears the screen" << std::endl;
        std::cout << std::setw(30) << std::left << "quit";
        std::cout << std::setw(20) << std::left << "Exit the program." << std::endl;
    }
    else
    {
        std::cout << "Commands may be abbreviated.  Commands are:" << endl
                  << endl;
        std::cout << std::setw(30) << std::left << "login";
        std::cout << std::setw(20) << std::left << "login to ftp server" << std::endl;
        std::cout << std::setw(30) << std::left << "ls";
        std::cout << std::setw(20) << std::left << "Show list directory or file" << std::endl;
        std::cout << std::setw(30) << std::left << "dir";
        std::cout << std::setw(20) << std::left << "Displays a list of files and subdirectories in a directory." << std::endl;
        std::cout << std::setw(30) << std::left << "pwd";
        std::cout << std::setw(20) << std::left << "Show present working directory." << std::endl;
        std::cout << std::setw(30) << std::left << "cd";
        std::cout << std::setw(20) << std::left << "Displays the name of or changes the current directory." << std::endl;
        std::cout << std::setw(30) << std::left << "rmdir";
        std::cout << std::setw(20) << std::left << "Removes a directory." << std::endl;
        std::cout << std::setw(30) << std::left << "del";
        std::cout << std::setw(20) << std::left << "Removes a file." << std::endl;
        std::cout << std::setw(30) << std::left << "rename";
        std::cout << std::setw(20) << std::left << "Renames a directory or file." << std::endl;
        std::cout << std::setw(30) << std::left << "download";
        std::cout << std::setw(20) << std::left << "Download file" << std::endl;
        std::cout << std::setw(30) << std::left << "upload";
        std::cout << std::setw(20) << std::left << "Upload file." << std::endl;
        std::cout << std::setw(30) << std::left << "help";
        std::cout << std::setw(20) << std::left << "Print local help information" << std::endl;
        std::cout << std::setw(30) << std::left << "clear";
        std::cout << std::setw(20) << std::left << "Clears the screen" << std::endl;
        std::cout << std::setw(30) << std::left << "close";
        std::cout << std::setw(20) << std::left << "Logout." << std::endl;
    }
}
void FTPClientCLI::doClose(char *cmd_argv[], int cmd_argc)
{
    if (FTPClientCLI::ftpClient.is_connected())
    {
        FTPClientCLI::ftpClient.close(this);
    }
}

void FTPClientCLI::doClear(char *cmd_argv[], int cmd_argc)
{
    system("cls");
}

void FTPClientCLI::doLogin(char *cmd_argv[], int cmd_argc)
{

    try
    {
        string username, password;
        std::cout << "Username:";
        std::cin >> username;
        std::cout << "Password:";
        std::cin >> password;
        FTPClientCLI::ftpClient.login(username, password, this);
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
}
void FTPClientCLI::doList(char *cmd_argv[], int cmd_argc)
{

    try
    {
        std::cout << FTPClientCLI::ftpClient.get_list_file();
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);

        FTPClientCLI::ftpClient.close(this);
    }
}
void FTPClientCLI::doCWD(char *cmd_argv[], int cmd_argc)
{
    try
    {
        string directory = Extensions::parse_name(cmd_argv, cmd_argc);
        FTPClientCLI::ftpClient.change_current_working_directory(directory, this);
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        FTPClientCLI::ftpClient.close(this);
    }
};
void FTPClientCLI::doDeleteDirectory(char *cmd_argv[], int cmd_argc)
{
    //TODO: code here;
    try
    {
        string directory = Extensions::parse_name(cmd_argv, cmd_argc);
        FTPClientCLI::ftpClient.delete_directory(directory);
        std::cout << "Delete file: " << directory << " succeeded." << endl;
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        FTPClientCLI::ftpClient.close(this);
    }
};
void FTPClientCLI::doCreateDirectory(char *cmd_argv[], int cmd_argc)
{
    try
    {
        string directory = Extensions::parse_name(cmd_argv, cmd_argc);
        FTPClientCLI::ftpClient.create_directory(directory);
        std::cout << "Create directory: " << directory << " succeeded." << endl;
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        FTPClientCLI::ftpClient.close(this);
    }
};
void FTPClientCLI::doRenameDirectoryOrFile(char *cmd_argv[], int cmd_argc)
{
    try
    {
        std::string src, dest;
        cout << "Source folder name or file name: ";
        getline(cin, src);
        cout << "Destination folder name or file name: ";
        getline(cin, dest);

        FTPClientCLI::ftpClient.rename_directory_or_file(src, dest);
        std::cout << "Rename folder or file succeeded" << endl;
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        FTPClientCLI::ftpClient.close(this);
    }
    //TODO: code here;
};
void FTPClientCLI::doDeleteFile(char *cmd_argv[], int cmd_argc)
{
    //TODO: code here;
    try
    {
        string filename = Extensions::parse_name(cmd_argv, cmd_argc);
        FTPClientCLI::ftpClient.delete_file(filename);
        std::cout << "Delete file succeeded" << endl;
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        FTPClientCLI::ftpClient.close(this);
    }
};
void FTPClientCLI::doDownload(char *cmd_argv[], int cmd_argc)
{
    try
    {
        string filename = Extensions::parse_name(cmd_argv, cmd_argc);
        FTPClientCLI::ftpClient.download(filename);
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);

        FTPClientCLI::ftpClient.close(this);
    }
};
void FTPClientCLI::doUpload(char *cmd_argv[], int cmd_argc)
{
    try
    {
        string filename = Extensions::parse_name(cmd_argv, cmd_argc);
        FTPClientCLI::ftpClient.upload(filename);
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        FTPClientCLI::ftpClient.close(this);
    }
};
void FTPClientCLI::doPWD(char *cmd_argv[], int cmd_argc)
{
    try
    {
        string response = FTPClientCLI::ftpClient.get_present_working_directory();
        cout << "'" << response << "'"
             << " is current directory" << endl;
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        FTPClientCLI::ftpClient.close(this);
    }
}
void FTPClientCLI::doDIR(char *cmd_argv[], int cmd_argc)
{
    try
    {
        std::cout << FTPClientCLI::ftpClient.get_directory();
    }
    catch (CustomizeException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
    }
    catch (SocketException &e)
    {
        SetConsoleTextAttribute(console, COLOR_ERROR);
        cerr << "ERROR: " << e.what() << endl;
        SetConsoleTextAttribute(console, COLOR_DEFAULT);
        FTPClientCLI::ftpClient.close(this);
    }
}
