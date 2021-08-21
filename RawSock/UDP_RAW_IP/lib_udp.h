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
#define SIZE_IP_HEAD 5


struct udp_head
{
	uint16_t source_port;
	uint16_t dest_port;
	uint16_t length;
	uint16_t checksum;
};

unsigned int ip_version = 4;
unsigned int ip_length = 5;
struct ip_head
{
    uint8_t ip_vhl; //version head length
    uint8_t ip_tos;
    uint16_t ip_total_len;
    uint16_t ip_id;
    uint16_t ip_off;
    uint8_t ip_ttl;
    uint8_t ip_type_prot;
    uint16_t ip_check_sum;
    uint32_t ip_src;
    uint32_t ip_dest;
};
