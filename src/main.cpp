/*
	Create a TCP socket
*/
#include <iostream>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");
	
	
	server.sin_addr.s_addr = inet_addr("192.168.0.106");
	server.sin_family = AF_INET;
	server.sin_port = htons( 21 );

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected");

	char loginMsg[] = "USER workpc\r\nPASS 1234\r\n";
	bool flag = false;
	char response[4] = {"\0"};
	// std::cout << send(s, loginMsg, strlen(loginMsg), 0);
	// recv(sock, responce, 3, 0);
	// if (strcmp(responce, "230") != 0)
	send(s, loginMsg, strlen(loginMsg), 0) < 0 ? flag = false : flag = true;
	
	// while (flag)
	// {
	// 	recv(s, responce, 3, 0);
	// 	std::cout << responce << std::endl;
	// }
	

	while (flag)
	{	
		recv(s, response, 3, 0);
		if(strcmp(response,"230") == 0){
			
			std::cout << "Connect Succeeded" << std::endl;
			break;
		}
		if(strcmp(response,"530") == 0){
			std::cout << "USER or PASS incorrect" << std::endl;
			break;
		}
	}	
	
		
	
	
	closesocket(s);
	WSACleanup();

	return 0;
}