#include <stdio.h>
#include <winsock2.h>

#pragma comment (lib, "ws2_32.lib") 

int main()
{
	WSADATA		wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	sockaddr_in server;
    memset(&server, 0, sizeof(server)); 
    server.sin_family = PF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(1234); 
    bind(sock, (SOCKADDR *)&server, sizeof(SOCKADDR));

	listen(sock, 20);

	sockaddr_in	client;
	int n = sizeof(SOCKADDR);

	while(1)
	{
		SOCKET clit = accept(sock, (SOCKADDR *)&client, &n);
		
	}

	closesocket(sock);

	WSACleanup();

}

