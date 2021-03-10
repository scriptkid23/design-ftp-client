

#include <iostream>
#include <string>

using namespace std;

// enum string_code {
//   help
// };

int main() {
    
    string syntax;
    
    
    cout << "***************************************" << endl;
    cout << "*                                     *" << endl;
    cout << "*             FTP CLient              *" << endl;
    cout << "*                                     *" << endl;
    cout << "***************************************" << endl;
    
    while(true){
        // input syntax
        cout << "62pm2@client> ";
        getline(cin,syntax);
        fflush(stdout);
    
        if(syntax.compare("help") == 0){
          cout << "Hello" << endl;
        }
        else if(syntax.compare("clear") == 0){
          system("CLS");
        }
        else{
          cout << "Invalid syntax" << endl;
        }
    }


    return 0;
}
