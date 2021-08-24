#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    struct sockaddr_in serv_addr;
    struct ip_mreq mreq;
    int sockd, val = 1;
    char buffer[1024];
    unsigned int len = sizeof(serv_addr);
    
    sockd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset((char*)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9080);

    if(bind(sockd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if(setsockopt(sockd, IPPROTO_IP, IP_ADD_MEMBERSHIP, 
                &mreq, sizeof(mreq)) == -1)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        if(recvfrom(sockd, buffer, sizeof(buffer), 0, 
                    (struct sockaddr*)&serv_addr, &len) == -1)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }
        printf("%s", buffer);
    }
    exit(EXIT_SUCCESS);
}
