#ifndef LIB_UDP
#define LIB_UDP

#include <bits/stdint-uintn.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define PORT_SERVER 6543
#define PORT_CLIENT 3456
#define SIZE_BUFFER 1024
#define SIZE_DGRAM  4096
#define SERVER_IP   "127.0.0.1"

typedef struct head
{
    uint16_t source_port;
    uint16_t destination_port;
    uint16_t length;
    uint16_t cheksum;
} head_udp;

#endif
