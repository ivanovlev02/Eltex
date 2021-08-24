#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    struct sockaddr_in serv_addr;
    int sockd;
    char buffer[] = "Multicast test\n";
    int len = sizeof(buffer);
    
    sockd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset((char*)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("224.0.0.1");
    serv_addr.sin_port = htons(9080);

    if(sendto(sockd, buffer, len, 0, (struct sockaddr*)&serv_addr, 
                sizeof(serv_addr)) == -1)
    {
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
