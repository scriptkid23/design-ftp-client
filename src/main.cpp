#include <iostream>
#include "FTPClient.h"
#include "Display.h"
using namespace std; 


int main(){
	Display dp;
	dp.home_screen();

	FTPClient ftpClient;
	ftpClient.initCmd();
	ftpClient.run();
	return 0;
}