#include "packet_v.h"

void ptos(short con_id, enum packet_type type, short status, char* fpath, char* packet_str)
{
  char con_id_str[7], packet_type_str[2], status_str [2];
  sprintf (con_id_str, "%d", con_id);
  sprintf (packet_type_str, "%d",(int) type);
  sprintf (status_str, "%d", status);
  
  strcat(packet_str, con_id_str);
  strcat(packet_str, ";");
  strcat(packet_str, packet_type_str);
  strcat(packet_str, ";");
  strcat(packet_str, status_str);
  strcat(packet_str, ";");
  strcat(packet_str, fpath);
}