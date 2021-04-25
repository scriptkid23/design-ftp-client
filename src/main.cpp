#include <iostream>
#include "FTPClientCLI.h"
#include "Display.h"
using namespace std; 


int main(){
	Display dp;
	dp.home_screen();

	FTPClientCLI ftpClient;
	ftpClient.initCmd();
	ftpClient.run();
	return 0;
}