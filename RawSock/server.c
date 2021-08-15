/*SERVER
 * Transport protocol: UDP
 */

#include "lib_udp.h"

int main(int argc, char* argv[])
{
    struct sockaddr_in server_addr, client_addr;
    size_t nbytes;
    socklen_t addr_len;
    int sockfd, i;
    char buffer[SIZE_BUFFER];
    char IPv4[INET_ADDRSTRLEN];

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    //inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr));
    server_addr.sin_port = htons(PORT_SERVER);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if(bind(sockfd, (struct sockaddr*)&server_addr, 
                sizeof(struct sockaddr_in)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    
   while(1)
   {
        addr_len = sizeof(struct sockaddr_in);
        memset(buffer, 0, SIZE_BUFFER);
        nbytes = recvfrom(sockfd, buffer, SIZE_BUFFER, 0,
                (struct sockaddr*)&client_addr, &addr_len);

        //if(nbytes == 0) break;

        if(nbytes == -1)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        printf("Server received %ld bytes from %s\n", (long)nbytes,
                inet_ntop(AF_INET, &client_addr.sin_addr, IPv4, INET_ADDRSTRLEN));
        printf("BUFFER: %s\n", buffer);

        for(i = 0; i < nbytes; i++)
        {
            buffer[i] = toupper((unsigned char)buffer[i]);
        }

        if((sendto(sockfd, buffer, nbytes, 0,
                        (struct sockaddr*)&client_addr, addr_len)) == -1)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
    }

    if(close(sockfd) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}    
