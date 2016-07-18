#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "packet_v.h"

#define SERVER_PORT 7747

int sock;
char message [] = "congacon vit";
struct sockaddr_in server;
struct hostent* hp;

int main()
{

//socket
	sock = socket (AF_INET, SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
 //	server.sin_addr = inet_addr("127.0.0.1");
	inet_aton("127.0.0.1" , &server.sin_addr);

  // hp = gethostbyname(argv[1]);
  // if(!hp)
    // error("Unknown host");

  struct Packet packet;
  char filename[BUF_SIZE], packet_str[PACK_SIZE], buffer[BUF_SIZE];
	bzero(filename, BUF_SIZE);
  
//enter the name of file
  printf ("Pls enter the name of file: ");
  scanf ("%s",filename);
  
  bzero(buffer, BUF_SIZE);
	bzero(packet_str, PACK_SIZE);
  
  strcpy(buffer, filename);
  strcpy(packet_str, "");
  
  ptos (-1, REQUEST, 0, buffer, packet_str);
  // printf ("\npacket_str to be sent: %s \n", packet_str);
//sendto
	int n = sendto(sock, packet_str, strlen(packet_str), 0, (const struct sockaddr*)&server, sizeof(struct sockaddr_in));
  if (n<0) perror ("sendto");
  
  return 0;
}