/*
	Initialise Winsock
*/
#include <iostream>
#include<stdio.h>
#include<winsock2.h>
#include <string>
#include "Display.h"
#include <unistd.h>  
#include <windows.h>
#include <constants.h>


#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;



int main(int argc , char *argv[])
{
	// WSADATA wsa;
	
	// printf("\nInitialising Winsock...");
	// if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	// {
	// 	printf("Failed. Error Code : %d",WSAGetLastError());
	// 	return 1;
	// }
	
	// printf("Initialised.");
	
	HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

	string syntax;
	Display dp;
	locale ll;
	system("cls");
	dp.home_screen();
	
	
	while(true){
		
		string to, user, pass; // password string pointer
		bool flag = true;
    	SetConsoleTextAttribute(hConsoleColor, 15);
		dp.commandline_screen("");
		getline(cin,syntax);
		
		if(syntax.compare(HELP) == 0){
			dp.help_screen(0);
		}
		else if(syntax.compare(CONNECT) == 0){

			
			cout << "To: ";
			getline(cin,to);

			cout << "Username: ";
			getline(cin,user);
			cout << "type";
			cout << "Password: ";
			HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
			DWORD mode = 0;
			GetConsoleMode(hStdin, &mode);
			SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
			getline(cin,pass);
			SetConsoleMode(hStdin, mode | (~ENABLE_ECHO_INPUT));
			cout << endl;

			if(pass.compare(PASS) == 0 && user.compare(USER) == 0){
				while (flag)
				{
					dp.commandline_screen("server");

					getline(cin,syntax);

					if(syntax.compare(HELP) == 0){
						dp.help_screen(0);
					}
					else if(syntax.compare(EXIT) == 0){
						flag = false;
					}
					else if(syntax.compare(CLEAR) == 0){
						system("cls");
					}
					cout << endl;
				}
			}
		}
		else if(syntax.compare(CLEAR) == 0){
			system("cls");
		}
		else{
			cout <<"'"<<syntax<<"' is not recognized as an internal or external command." << endl;
		}
		cout << endl;
	}
	

	return 0;
}