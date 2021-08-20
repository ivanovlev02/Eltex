#include "lib_udp.h"

int port_dst_src(struct sockaddr_in server, struct udp_head input)
{
	if ((input.dest_port == htons(PORT_CLIENT)))
		return 1;
}

int main(int argc, char* argv[])
{
	int sockfd;
	int bytes_read;
    	char message[] = "I'm client!";
    	char buffer[SIZE_BUFFER];
    	char receive[SIZE_DGRAM];
    	struct sockaddr_in serv_addr, cli_addr;
	struct udp_head udp_header;
	socklen_t len = sizeof(struct sockaddr_in);
	
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sockfd == -1)
    	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_addr.s_addr = inet_addr(ADDR_SERVER);
    
    	memset(&cli_addr, 0, sizeof(struct sockaddr_in));
    	cli_addr.sin_family = AF_INET;
    	cli_addr.sin_addr.s_addr = INADDR_ANY;
    	cli_addr.sin_port = htons(PORT_CLIENT);
    
    	udp_header.source_port = htons(PORT_CLIENT);
    	udp_header.dest_port = htons(PORT_SERVER);
	udp_header.length = htons(sizeof(udp_header)+sizeof(message));
	udp_header.checksum = 0;
    
    	memcpy(buffer, &udp_header, sizeof(udp_header));
	memcpy((void *)(buffer + sizeof(udp_header)), (void *)message, sizeof(message));
    
	if ((sendto(sockfd, buffer, sizeof(udp_header)+sizeof(message), 0,
		(struct sockaddr *)&serv_addr, sizeof(serv_addr))) == -1)
    	{
		perror("sendto");
        	exit(EXIT_FAILURE);
	}
	
	struct udp_head *sender_pack;
	
	while(1)
    	{
		memset(receive, 0, SIZE_DGRAM);
	
       		bytes_read = recvfrom(sockfd, receive, 2*sizeof(receive), 0,
			(struct sockaddr *)&serv_addr, &len);
		sender_pack = (struct udp_head*) &(receive[LEN_IP_HEAD]);
		
		if(port_dst_src(serv_addr, *sender_pack) == 1)
        	{
			printf ("%s\n", &receive[LEN_IP_HEAD + LEN_UDP_HEAD]);
			break;
		}	
	} 
	close(sockfd);	
	exit(EXIT_SUCCESS);
}   		

