#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char message[] = "\nHELLO!!!\n";
char buffer[255];

int main(int argc, char* argv[])
{
    struct sockaddr_in serv_addr;
    int sockfd;
    int val = 1;
    struct sockaddr_in udp;
    unsigned int length = sizeof(udp);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    udp.sin_family = AF_INET;
    udp.sin_addr.s_addr = inet_addr("255.255.255.255");
    udp.sin_port = htons(7070);

    if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    if(sendto(sockfd, message, sizeof(message), 0, 
                (struct sockaddr*)&udp, length) < 0)
    {
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
