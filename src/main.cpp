#include "FTPClientCLI.h"
#include "Display.h"

int main(){
	Display dp;
	dp.home_screen();

	FTPClientCLI client;
	client.initCmd();
	client.run();
	return 0;
}