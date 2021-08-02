#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct msgbuff
{
    long mtype;
    char mtext[256];
} message_buff;

int client[256];
int num = 0;

void* pid_client(void *func)
{
	key_t key = ftok("key_msg",'A');
	int msg_id = msgget(key,IPC_CREAT | 0666);
	message_buff rbuf;
	int id;
	int n;
	
    while((id = msgrcv(msg_id, &rbuf, sizeof(rbuf), 1L, 0)) != -1)
    {
		sscanf(rbuf.mtext,"%d", &n);
        client[num] = n;
		printf("Client %i connected\n", n);
		num++;
	}
	return 0;
}

int main(void)
{
	key_t key;
	pthread_t tid;
	
	message_buff rbuf;
	int msg_id;
	key = ftok("key_msg",'A');
	msg_id = msgget(key,IPC_CREAT| 0666);
	if (msg_id != -1){
		printf("Created queue.\n");
	}
	
	pthread_create(&tid, NULL, pid_client, NULL);
	
	while (1) {
		if( msgrcv(msg_id,&rbuf,sizeof(rbuf),2L,0) > 0 ) {
			int pid; char str[256];
			sscanf(rbuf.mtext,"%d:%s",&pid,str);
			printf("%d -> %s\n",pid,str);
			
			for( int i = 0; i < num; i++){
				rbuf.mtype = 3L;
				msgsnd(msg_id,&rbuf,sizeof(rbuf),0);
			}	
		}
	}
	pthread_join(tid, NULL);

	return 0;
}
