#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "thread_v.h"



#define SERVER_PORT 7747

int sock, length;
struct sockaddr_in server;

int main()
{
// socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
			perror("Opening socket");

	length = sizeof(server);
  
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(SERVER_PORT);

// bind
	if(bind(sock, (struct sockaddr *)&server, length)<0)
			perror("binding");
  
// receive and process message from client
  pthread_t threads[MAX_THREADS];
  int thread_no = 0;
  while (1){
    Request* request = (Request*) malloc (sizeof (Request));
    request->fromlen = sizeof (struct sockaddr_in);
    
    int n = recvfrom (sock, request->buf, PACK_SIZE, 0, (struct sockaddr*)&request->from, &request->fromlen );
    if (n<0) perror ("recvfrom:");
    printf("%s\n", request->buf);
    
    int rc = pthread_create (&threads[thread_no], 0, handle_request, (void*)request);
    if(rc){
      printf ("can't process the message");
    }
    else{
      thread_no++;
    }
  }
	
	return 0;
}