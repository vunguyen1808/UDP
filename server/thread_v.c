#include <stdio.h>
#include "thread_v.h"

extern pthread_mutex_t mutex1;
extern struct Thread *h_thread;		// list of threads - sorted on connection id


void* handle_request (void* argv)
{
  Request* request = (Request*)argv;
  char packet_str [PACK_SIZE];
  strcpy (packet_str, request->buf);
  
  char /*buffer[BUF_SIZE], */filename[BUF_SIZE];
	struct Packet packet;
  
  parse_packet (packet_str, packet);
  
  
  
}