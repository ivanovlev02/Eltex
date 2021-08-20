#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT_SERVER 7557
#define PORT_CLIENT 5775
#define ADDR_SERVER "127.0.0.2"

#define LEN_UDP_HEAD 8
#define LEN_IP_HEAD 20

#define SIZE_BUFFER 1024
#define SIZE_DGRAM (LEN_IP_HEAD + LEN_UDP_HEAD + SIZE_BUFFER)

//struct sockaddr_in server,client;

struct udp_head
{
	u_short source_port;
	u_short dest_port;
	u_short length;
	u_short checksum;
};
