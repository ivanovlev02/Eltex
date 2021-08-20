#include "lib_udp.h"

/*
 * задача клиента состоит в следующем:
 * клиент формирует RAW сокет UDP и посредством "сырого" сокета отправ-
 * ляет на сервер строку, сервер добавляет к стороке свою строку и от-
 * правляем обратно клиенту. клиент должен это принять и обработать и
 * вывести.
 */
//структура заголовка UDP

//функция сравнения назначения порта с портом клиента.
int port_dst_src(struct sockaddr_in server, struct udp_head input)
{
	if ((input.dest_port == htons(PORT_CLIENT)))
		return 1;
}

int main(int argc, char* argv[])
{
	int sockfd;
	int bytes_read;
    char message[] = "Hello server!";
    char buffer[SIZE_BUFFER];
    char receive[SIZE_DGRAM];
    struct sockaddr_in serv_addr, cli_addr;
	struct udp_head udp_header;
	socklen_t len = sizeof(struct sockaddr_in);
	
	//создание сокета
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sockfd == -1)
    {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	//зануление структуры сокета сервера
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	//заполнения структуры сервера
    serv_addr.sin_family = AF_INET;
    //петля
    serv_addr.sin_addr.s_addr = inet_addr(ADDR_SERVER);
    /*
     * не имеет смысла задавать номер порта, потому что он в
     * заголовке UDP
	 */
    //server.sin_port = htons(3333);
    
    //зануление структуры сокета клиента
    memset(&cli_addr, 0, sizeof(struct sockaddr_in));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = INADDR_ANY;
    cli_addr.sin_port = htons(PORT_CLIENT);
    
    //заполнение заголовка UDP
    udp_header.source_port = htons(PORT_CLIENT);
    udp_header.dest_port = htons(PORT_SERVER);
	udp_header.length = htons(sizeof(udp_header)+sizeof(message));
	udp_header.checksum = 0;
    
    //заполнение буфера с заголовками для отправки.
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
		
		if((bytes_read = recvfrom(sockfd, receive, 2*sizeof(receive), 0,
			(struct sockaddr *)&serv_addr, &len)) > 0)
        {
		}
		
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

