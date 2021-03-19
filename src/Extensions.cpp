#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#include "Extensions.h"

using namespace std;

std::string Extensions::str_trim(std::string& str){
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ')+1);        
    return str;
}
void Extensions::str_upper(std::string* str){
    std::transform(str->begin(), str->end(), str->begin(), ::toupper);
}
vector<string> Extensions::str_split(std::string str, char regex){
        vector<string> result;
    
        string temp;
        
        stringstream ss(str);

        while (getline(ss,temp,regex))
        {
            str_trim(temp);
            result.push_back(temp);
        }
        return result;
}