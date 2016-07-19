#include <stdio.h>
#include "thread_v.h"
extern int sock;
extern pthread_mutex_t mutex1;
extern struct Thread *h_thread;		// list of threads - sorted on connection id
char buffer[BUF_SIZE], filename[BUF_SIZE];

void* handle_request (void* argv)
{
  Request* request = (Request*)argv;
  char packet_str [PACK_SIZE];
  strcpy (packet_str, request->buf);
  
  char /*buffer[BUF_SIZE], */filename[BUF_SIZE];
	struct Packet packet;
  printf("initial packet.status = %d\n",packet.status);
  parse_packet (packet_str, packet);
  
  pthread_mutex_lock(&mutex1);
  packet.connection_id = insert_thread();
  pthread_mutex_unlock(&mutex1);
//send REQUEST_ACK or REQUEST_REGRET  
  packet.type = REQUEST_ACK;
  strcpy(filename, packet.buffer);
  allzero (packet.buffer, BUF_SIZE);
  strcpy(packet_str,"");
  ptos(packet.connection_id, packet.type, 0, packet.buffer, packet_str);
  printf ("sent REQUEST_ACK message: %s\n", packet_str)  ;
  
  sendto (sock, packet_str, strlen(packet_str), 0, (struct sockaddr*)&request->from, request->fromlen);
  
  if (packet.connection_id == -1)
  {
    printf ("REQUEST_REGRET sent\n");
    pthread_exit(NULL);
  }
  else 
  {
    printf("REQUEST_ACK sent\n");
  }

//send timestamp
  char *timestamp;
	//get_timestamp(filename, timestamp);
	struct stat fstat;
	if(stat(filename, &fstat) != 0){
		packet.status = 1;
    // strcpy(timestamp, "N/A");
	}
  else {
    timestamp = asctime(localtime(&fstat.st_ctime));
    printf("Server::timestamp = %s\n",timestamp);  
  }
	printf("after file_info packet.status = %d\n",packet.status);
  packet.type = DONE;
  strcpy(packet.buffer, timestamp);
  strcpy(packet_str,"");
  ptos(packet.connection_id, packet.type, packet.status, packet.buffer, packet_str);
  printf ("done timestamp message: %s\n",packet_str);
  sendto (sock, packet_str, strlen(packet_str), 0, (struct sockaddr*)&request->from, request->fromlen);
//receive DONE_ACK
  recvfrom(sock, packet_str, PACK_SIZE, 0, (struct sockaddr*)&request->from, &request->fromlen);
}

short insert_thread(){
	struct Thread *new_thread = (Thread*)malloc(sizeof(Thread));	
	if(h_thread == NULL || h_thread->connection_id > 0){
		new_thread->next_thread = h_thread;
		h_thread = new_thread;
		return (new_thread->connection_id = 0);
	}
	struct Thread *lpt = h_thread;
	while(lpt->next_thread != NULL && lpt->next_thread->connection_id == (lpt->connection_id + 1))
		lpt = lpt->next_thread;
	if(lpt->connection_id == MAX_THREADS){
		free(new_thread);
		return -1;
	}
	new_thread->next_thread = lpt->next_thread;
	lpt->next_thread = new_thread;
	return (new_thread->connection_id = (lpt->connection_id + 1));	
}

