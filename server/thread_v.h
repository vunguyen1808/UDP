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

<<<<<<< HEAD
#define MAX_THREADS 50			// Maximum number of threads that can be served at a time
=======
#define MAX_THREADS 3			// Maximum number of threads that can be served at a time
>>>>>>> c1090a55233a0f84d4ca0b0bc590734c3a3368d2

struct Request{
	socklen_t fromlen;
	struct sockaddr_in from;
	char buf[PACK_SIZE];
};

<<<<<<< HEAD
struct Thread{
	int connection_id;
	struct Thread *next_thread;
};


void* handle_request (void* agrv);
short insert_thread();
=======
// struct Thread{
	// int connection_id;
	// struct Thread *next_thread;
// };


void* handle_request (void* agrv);
>>>>>>> c1090a55233a0f84d4ca0b0bc590734c3a3368d2
