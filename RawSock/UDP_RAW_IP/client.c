#include "lib_udp.h"

int main(int argc, char* argv[])
{
    int sockfd;
	int nbytes;
    int val = 1;
    
    char message[] = "I'm client!";
    char *buf;
    char dgram[SIZE_DGRAM];
    
    struct sockaddr_in serv_addr, cli_addr;
	struct udp_head *udp_header = (struct udp_head*)&dgram[LEN_IP_HEAD];
    struct udp_head *sender;
    struct ip_head *ip_header = (struct ip_head*)&dgram;

    socklen_t len = sizeof(struct sockaddr_in);
	
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sockfd == -1)
    {
		perror("socket");
		exit(EXIT_FAILURE);
	}

    if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &val, sizeof(val)) == -1)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
	
    /*SERVER*/
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ADDR_SERVER);
    serv_addr.sin_port = htons(PORT_SERVER);
    
    /*CLIENT*/
    memset(&cli_addr, 0, sizeof(struct sockaddr_in));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = inet_addr(ADDR_SERVER);
    cli_addr.sin_port = htons(PORT_CLIENT);
   
    /*UDP HEAD*/
    memset(udp_header, 0, sizeof(struct udp_head));
    udp_header->source_port = htons(PORT_CLIENT);
    udp_header->dest_port = htons(PORT_SERVER);
	udp_header->length = htons(LEN_UDP_HEAD + SIZE_BUFFER);
	udp_header->checksum = 0;

    /*IP HEAD*/
    memset(ip_header, 0, sizeof(struct ip_head));
    ip_header->ip_vhl = (ip_version << 4) | ip_length;
    ip_header->ip_tos = 0;
    ip_header->ip_total_len = SIZE_DGRAM;
    ip_header->ip_id = htonl(555);
    ip_header->ip_off = 64;
    ip_header->ip_ttl = 255;
    ip_header->ip_type_prot = IPPROTO_UDP;
    ip_header->ip_check_sum = 0;
    ip_header->ip_src = INADDR_ANY;
    ip_header->ip_dest = serv_addr.sin_addr.s_addr;

    strcpy(&dgram[LEN_IP_HEAD + LEN_UDP_HEAD], message);
   
    /*Send packet to server*/
	if ((sendto(sockfd, dgram, SIZE_DGRAM, 0, 
                    (struct sockaddr*)&serv_addr, len)) == -1)
    {
		perror("sendto");
       	exit(EXIT_FAILURE);
	}
		
	while(1)
    {
		memset(dgram, 0, SIZE_DGRAM);
	
    	nbytes = recvfrom(sockfd, dgram, 2 * sizeof(dgram), 0,
	    	(struct sockaddr *)&serv_addr, &len);
		
        sender = (struct udp_head*)&dgram[LEN_IP_HEAD];
		
		if(sender->dest_port == htons(PORT_CLIENT))
       	{
            buf = (char*)&dgram[LEN_IP_HEAD + LEN_UDP_HEAD];
			printf ("%s\n", buf);
            break;
		}	
	} 

	close(sockfd);	
	exit(EXIT_SUCCESS);
}   		

