#include "packet_v.h"

 /* parse_packet() : takes the raw packet string, parses it and stores its 4 fields into a packet (struct Packet) */
void parse_packet(char *packet_str, struct Packet& packet)
{
	char ch = 'c', sign = '+';
	short byte_no = 0;
	
	// connection id //
	packet.connection_id = 0;
	sign = packet_str[byte_no];
	if(sign == '-'){
		byte_no++;	
	}
	while((ch = packet_str[byte_no++]) != SEPARATOR){
		packet.connection_id += ch - '0';
	}
	if(sign == '-'){
		packet.connection_id *= -1; 
	}
	
	// packet type //
	packet.type = (enum packet_type)(packet_str[byte_no++] - '0');
	byte_no++;
	// packet status //
	packet.status = packet_str[byte_no++] - '0';
	byte_no++;
	
	// buffer //
	short buf_byte = 0;
	while((packet.buffer[buf_byte++] = packet_str[byte_no++]) != '\0');
}