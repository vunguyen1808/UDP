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
struct sockaddr_in server, from;
struct hostent* hp;

int main()
{

//socket
	sock = socket (AF_INET, SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	inet_aton("127.0.0.1" , &server.sin_addr);

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
  
//sendto
	int n = sendto(sock, packet_str, strlen(packet_str), 0, (const struct sockaddr*)&server, sizeof(struct sockaddr_in));
  if (n<0) perror ("sendto");
  printf ("sent packet_str: %s\n", packet_str);
  
//receive REQUEST_ACK
  socklen_t length = sizeof (struct sockaddr_in);
  recvfrom (sock, packet_str, strlen (packet_str), 0, (struct sockaddr*)&from, &length);
  printf ("received packet_str: %s\n", packet_str);
  if (packet_str[0] == '-'){
    printf ("Server is busy\n");
    close(sock);
    return -1;
  }
  else{
    printf ("Received REQUEST_ACK from server\n");
  }
    
//receive file timestamp
  recvfrom (sock, packet_str, PACK_SIZE, 0, (struct sockaddr*)&from, &length);
  char *connection_id_str = (char*)malloc(sizeof(char));
  int i, j = 0;
  for (i = 0; i <3;j++ ){
    if (packet_str [j] == ';') i++ ;
    if (i==1) strncpy(connection_id_str, packet_str, j-1);
  }
  printf ("timestamp = %s\n",packet_str);
  printf ("connection_id = %s\n",connection_id_str);
  
  char* timestamp = &packet_str[j];
  int byte_no = 0;
  while ((timestamp[byte_no++] = packet_str[j++]) != '\0');
  printf ("file timestamp of file %s is: %s\n", filename, timestamp);
  
  short connection_id = atoi(connection_id_str);
  printf ("connection_id = %d\n", connection_id);

//send done ACK    
  ptos(connection_id, DONE_ACK, 0, buffer, packet_str );
  
  sendto (sock, packet_str, strlen(packet_str), 0, (struct sockaddr*)&server, sizeof(struct sockaddr_in));
  
  close (sock);
  return 0;
}