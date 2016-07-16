#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 7747

int sock;
char message [] = "congacon vit";
struct sockaddr_in server;
int main()
{

//socket
	sock = socket (AF_INET, SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
//	server.sin_addr = inet_addr("127.0.0.1");
	inet_aton("127.0.0.1" , &server.sin_addr);

//sendto
	sendto(sock, message, sizeof(message), 0, (const struct sockaddr*)&server, sizeof(struct sockaddr_in));

  return 0;
}
