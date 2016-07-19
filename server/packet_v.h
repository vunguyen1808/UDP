#include <stdio.h>
#include <string.h>

#define PACK_SIZE 270
#define BUF_SIZE 256			// maximum size of the buffer in a packet
#define SEPARATOR ';'			// SEPARATOR separates the different fields of a packet in a packet string

// ennuneration for packet type
enum packet_type {REQUEST, REQUEST_ACK, DONE, DONE_ACK};

struct Packet{
	short connection_id;
	enum packet_type type;
	short status;
	char buffer[BUF_SIZE];
};

void parse_packet(char *packet_str, struct Packet& packet);
void ptos(short, enum packet_type, short, char*, char*);
void allzero(char*, int);
// void print_packet(struct Packet);
// void print_packet(char*);
