#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include "packet_v.h"

#define MAX_THREADS 50			// Maximum number of threads that can be served at a time

struct Request{
	socklen_t fromlen;
	struct sockaddr_in from;
	char buf[PACK_SIZE];
};

struct Thread{
	int connection_id;
	struct Thread *next_thread;
};


void* handle_request (void* agrv);
short insert_thread();