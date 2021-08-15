/*CLIENT
 * Socket: RAW
 * Transport protocol: UDP
 */

#include "lib_udp.h"

int main(int argc, char* argv[])
{
    struct sockaddr_in server_addr;
    head_udp udp_h;
    
    int length_dgram;
    int sockRAW_fd;
    char dgram[SIZE_DGRAM];
    char buffer[SIZE_BUFFER];

    sockRAW_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sockRAW_fd == -1)
    {
        perror("raw_socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    //inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr));
    server_addr.sin_port = htons(PORT_SERVER);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    memset(buffer, 0, SIZE_BUFFER);
    strcpy(buffer, "TEST");

    /*Lengt packet*/
    length_dgram = sizeof(head_udp) + strlen(buffer);

    /*UDP header*/
    udp_h.source_port = htons(PORT_CLIENT);
    udp_h.destination_port = htons(PORT_SERVER);
    udp_h.length = htons(length_dgram);
    udp_h.cheksum = 0;

    memcpy((void*)dgram, (void*)&udp_h, sizeof(head_udp));
    memcpy((void*)dgram + sizeof(head_udp), (void*)buffer, strlen(buffer));

    if(sendto(sockRAW_fd, dgram, length_dgram, 0, 
                (struct sockaddr*)&server_addr, 
                sizeof(struct sockaddr_in)) == -1)
    {
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    if(close(sockRAW_fd) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
