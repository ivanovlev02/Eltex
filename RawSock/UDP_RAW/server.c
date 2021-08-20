#include "lib_udp.h"

int main(int argc, char* argv[])
{
    	struct sockaddr_in serv_addr, cli_addr;
	int sockfd;
    	int nbytes;
    	char response[] = " ++ I'm Server!";
	char buf[SIZE_BUFFER];

	socklen_t len = sizeof(struct sockaddr_in);
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
    	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ADDR_SERVER);
    	serv_addr.sin_port = htons(PORT_SERVER);
    
	if (bind(sockfd, (struct sockaddr *)&serv_addr, len) == -1)
    	{
        	perror("bind");
        	exit(EXIT_FAILURE);
    	}
    	
	while(1)
    	{
		if((nbytes = recvfrom(sockfd, buf, SIZE_BUFFER, 0,
			(struct sockaddr *)&cli_addr, &len)) > 0)
        	{		
			printf("%s\n",buf);	
		}
		strcat(buf, response);
		if ((sendto(sockfd, buf, sizeof(buf), 0, 
			(struct sockaddr *)&cli_addr, len)) == -1)
        	{
			perror("sendto");
            		exit(EXIT_FAILURE);
		}
		nbytes = -1;
	}
		
    	close(sockfd);
    	exit(EXIT_SUCCESS);
}
