#include <string>
#include <exception> 

using namespace std;
class CustomizeException: public exception{
public:

    CustomizeException(const string &message) throw();

    ~CustomizeException() throw();

    const char *what() const throw();

private:
    string userMessage;  // Exception message
};