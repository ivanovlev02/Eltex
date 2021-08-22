#include "lib_udp.h"

unsigned short checksum(unsigned short *buffer, int n);

int main(int argc, char* argv[])
{
    int sockfd;
	int nbytes = -1;
    int val = 1;
    
    char message[] = "I'm client!";
    char msgbuffer[SIZE_P_HEAD + sizeof(message)];
    char *buf;
    char dgram[SIZE_DGRAM];
    
    struct sockaddr_ll serv_addr;
	struct udp_head udp_header;
    struct udp_head *recv;
    struct ip_head ip_header;
    struct eth_head eth_header;

    socklen_t len = sizeof(struct sockaddr_ll);
	
	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(sockfd == -1)
    {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
    /*SERVER*/
	memset(&serv_addr, 0, sizeof(struct sockaddr_ll));
    serv_addr.sll_family = AF_PACKET;
    serv_addr.sll_ifindex = if_nametoindex("enp0s3");
    serv_addr.sll_halen = ETH_ALEN;
    serv_addr.sll_protocol = htons(ETH_P_ALL);
    serv_addr.sll_addr[0] = MAC_DEST_0;
    serv_addr.sll_addr[1] = MAC_DEST_1;
    serv_addr.sll_addr[2] = MAC_DEST_2;
    serv_addr.sll_addr[3] = MAC_DEST_3;
    serv_addr.sll_addr[4] = MAC_DEST_4;
    serv_addr.sll_addr[5] = MAC_DEST_5;
   
    /*UDP HEAD*/
    memset(&udp_header, 0, sizeof(struct udp_head));
    udp_header.source_port = htons(PORT_CLIENT);
    udp_header.dest_port = htons(PORT_SERVER);
	udp_header.length = htons(LEN_UDP_HEAD + sizeof(message));
	udp_header.checksum = 0;

    /*IP HEAD*/
    memset(&ip_header, 0, sizeof(struct ip_head));
    ip_header.ip_vhl = (ip_version << 4) | ip_length;
    ip_header.ip_tos = 0;
    ip_header.ip_tot_len = htons(LEN_IP_HEAD + LEN_UDP_HEAD + sizeof(message));
    ip_header.ip_id = htons(555);
    ip_header.ip_frag_off = 0;
    ip_header.ip_ttl = 64;
    ip_header.ip_protocol = IPPROTO_UDP;
    ip_header.ip_saddr = inet_addr("192.168.0.30");
    ip_header.ip_daddr = inet_addr("192.168.0.3");
    ip_header.ip_check = checksum((unsigned short*)&ip_header, 
           sizeof(struct ip_head) / 2);

    /*ETHERNET HEAD*/
    memset(&eth_header, 0, sizeof(struct eth_head));
    eth_header.eth_dest[0] = MAC_DEST_0;
    eth_header.eth_dest[1] = MAC_DEST_1;
    eth_header.eth_dest[2] = MAC_DEST_2;
    eth_header.eth_dest[3] = MAC_DEST_3;
    eth_header.eth_dest[4] = MAC_DEST_4;
    eth_header.eth_dest[5] = MAC_DEST_5;
    eth_header.eth_source[0] = MAC_SOURCE_0;
    eth_header.eth_source[1] = MAC_SOURCE_1;
    eth_header.eth_source[2] = MAC_SOURCE_2;
    eth_header.eth_source[3] = MAC_SOURCE_3;
    eth_header.eth_source[4] = MAC_SOURCE_4;
    eth_header.eth_source[5] = MAC_SOURCE_5;
    eth_header.eth_proto = htons(ETH_P_IP);

    memcpy(msgbuffer, &eth_header, LEN_ETH_HEAD);
    memcpy((void*)(msgbuffer + LEN_ETH_HEAD), &ip_header, LEN_IP_HEAD);
    memcpy((void*)(msgbuffer + LEN_ETH_HEAD + LEN_IP_HEAD), &udp_header,
            LEN_UDP_HEAD);
    memcpy((void*)(msgbuffer + SIZE_P_HEAD), &message, sizeof(message));
   
    /*Send packet to server*/
	if ((sendto(sockfd, &msgbuffer, sizeof(msgbuffer), 0, 
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
		
        recv = (struct udp_head*)&dgram[LEN_ETH_HEAD + LEN_IP_HEAD];
		
		if(ntohs(recv->dest_port) == PORT_CLIENT)
       	{
            buf = (char*)&dgram[SIZE_P_HEAD];
			printf ("%s\n", buf);
            break;
		}	
	} 

	close(sockfd);	
	exit(EXIT_SUCCESS);
}

unsigned short checksum(unsigned short *buffer, int n)
{
    unsigned long sum;
    for(sum = 0; n > 0; n--)
    {
        sum += *buffer++;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}
