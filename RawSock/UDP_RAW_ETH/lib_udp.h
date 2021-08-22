#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/types.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define PORT_SERVER 7557
#define PORT_CLIENT 5775
#define ADDR_SERVER "192.168.0.3"

#define LEN_UDP_HEAD 8
#define LEN_IP_HEAD 20
#define LEN_ETH_HEAD 14

#define SIZE_BUFFER 1024
#define SIZE_DGRAM (LEN_IP_HEAD + LEN_UDP_HEAD + SIZE_BUFFER)
#define SIZE_IP_HEAD 5
#define SIZE_P_HEAD (LEN_ETH_HEAD + LEN_IP_HEAD + LEN_UDP_HEAD)

#define ETH_ALEN 6
#define ETH_P_ALL 0x0003
#define ETH_P_IP 0x0800

//08:00:27:35:ea:cd - client
#define MAC_SOURCE_0 0x08
#define MAC_SOURCE_1 0x00
#define MAC_SOURCE_2 0x27
#define MAC_SOURCE_3 0x35
#define MAC_SOURCE_4 0xea
#define MAC_SOURCE_5 0xcd

//b8:27:eb:8e:10:40 - server
#define MAC_DEST_0 0xb8
#define MAC_DEST_1 0x27
#define MAC_DEST_2 0xeb
#define MAC_DEST_3 0x8e
#define MAC_DEST_4 0x10
#define MAC_DEST_5 0x40

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
    uint8_t     ip_vhl; 
    uint8_t     ip_tos;
    uint16_t    ip_tot_len;
    uint16_t    ip_id;
    uint16_t    ip_frag_off;
    uint8_t     ip_ttl;
    uint8_t     ip_protocol;
    uint16_t    ip_check;
    uint32_t    ip_saddr;
    uint32_t    ip_daddr;
};

struct eth_head
{
    unsigned char eth_dest[ETH_ALEN];
    unsigned char eth_source[ETH_ALEN];
    __be16 eth_proto;
};

struct sockaddr_ll
{
    unsigned short      sll_family;     /*Always AF_PACKET*/
    unsigned short      sll_protocol;   /*Physical-layer protocol*/
    int                 sll_ifindex;    /*Interface number*/
    unsigned short int  sll_hatype;     /*ARP hardware type*/
    unsigned char       sll_pkttype;    /*Packet type*/
    unsigned char       sll_halen;      /*Length of address*/
    unsigned char       sll_addr[8];    /*Physical-layer address*/
};
