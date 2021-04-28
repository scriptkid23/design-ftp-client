#include <iostream>
#include "FTPClientCLI.h"
#include "Display.h"
using namespace std; 


int main(){
	Display dp;
	dp.home_screen();

	FTPClientCLI client;
	client.initCmd();
	client.run();
	return 0;
}