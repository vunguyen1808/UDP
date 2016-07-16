#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>



#define SERVER_PORT 7747

int sock, length;
struct sockaddr_in server;
socklen_t address_length;
char* message = (char*) malloc (sizeof(char)*200);//[200];

int main()
{
// socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
			perror("Opening socket");

	length = sizeof(server);
//	bzero(&server,length);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port=htons(SERVER_PORT);


// bind
	if(bind(sock, (struct sockaddr *)&server, length)<0)
			perror("binding");

	address_length = sizeof(struct sockaddr_in);
//receivefrom
	printf("%p \n",message);
	recvfrom (sock, message, 200, 0, (struct sockaddr*)&server, &address_length );

	printf("%s\n", message);
	return 0;
}
