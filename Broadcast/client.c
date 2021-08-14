#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char buffer[1024];

int main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_in serv_addr, server;

    unsigned int length = sizeof(server);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7070);
    serv_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if(recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&server, &length) < 0)
    {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }
    printf("%s", buffer);

    close(sockfd);

    exit(EXIT_SUCCESS);
}
