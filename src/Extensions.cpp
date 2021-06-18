
#include "Extensions.h"

using namespace std;

std::string Extensions::str_trim(std::string &str)
{
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    return str;
}
void Extensions::str_upper(std::string *str)
{
    std::transform(str->begin(), str->end(), str->begin(), ::toupper);
}
std::string Extensions::parse_name(char *cmd_argv[], int cmd_argc)
{
    std::stringstream ss;
    std::string temp;
    std::string name = "";

    for (int i = 1; i < cmd_argc; i++)
    {
        ss << cmd_argv[i];
        ss >> temp;
        if (i == cmd_argc - 1)
        {
            name = name + temp;
        }
        else
        {
            name = name + temp + " ";
        }

        ss.clear();
    }
    return name;
}
vector<string> Extensions::str_split(std::string str, char regex)
{
    vector<string> result;

    string temp;

    stringstream ss(str);

    while (getline(ss, temp, regex))
    {
        str_trim(temp);
        result.push_back(temp);
    }
    return result;
}
Response Extensions::convert_buffer_to_response(const char *buffer)
{

    std::string str(buffer);

    std::regex regexCRLF("\r\n");
    auto result = std::regex_replace(str, regexCRLF, "\0");

    regex regexNumber("[0-9]+");
    smatch m;
    regex_search(result, m, regexNumber);
    string::size_type pos;
    
    pos = result.find(' ', 0);
    std::string message = result.substr(pos + 1);

    Response response = Response(m[0], message);

    return response;
}
string Extensions::get_file_name(const string &source)
{
    string filename = source;
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        filename.erase(0, last_slash_idx + 1);
    }
    return filename;
}
std::string Extensions::get_path(const std::string &source)
{

    std::stringstream ss;
    std::string path;
    ss << source;
    ss >> path;

    std::regex expr("/(?<=\").*?(?=\")/gm");
    std::smatch m;
    std::regex_search(path, m, expr);
    return m[0];
}