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

void *get_msg(void *ptr)
{
	key_t key;
	message_buff rbuf;
	int msg_id;
	int id;
	
	key = ftok("key_msg",'A');
	msg_id = msgget(key, IPC_CREAT | 0666); 

    while(1)
    {
		if((id = msgrcv(msg_id, &rbuf, sizeof(rbuf), 3L, 0)) > 0)
        {
			printf ("%s\n", rbuf.mtext);
		}
	}
	return 0;
}

void *send_msg(void *ptr)
{
	key_t key;
	message_buff rbuf;
	char text[256];
	int msg_id;

	key = ftok("key_msg",'A');
	msg_id = msgget(key, IPC_CREAT | 0666);
	rbuf.mtype = 2L;
	
    while(1){	
		fgets(text, 256, stdin);
		sprintf(rbuf.mtext, "%d:%s", getpid(), text);
		msgsnd(msg_id, &rbuf, sizeof(rbuf), 0);
	}
	return 0;
}

int main()
{
	key_t key;
	pthread_t get, send;
	message_buff  rbuf;
	int msg_id;

	key = ftok("key_msg",'A');
	msg_id = msgget(key, IPC_CREAT| 0666 );
	if (msg_id == -1){
		printf("Client did not join the queue");
	}

	rbuf.mtype = 1L;
    sprintf(rbuf.mtext,"%d",getpid());
	printf ("Sending pid %s the server\n", rbuf.mtext);
	msgsnd(msg_id, &rbuf, sizeof(rbuf), 0);
		
	pthread_create(&get, NULL, get_msg, NULL);
	pthread_create(&send, NULL, send_msg, NULL);
	pthread_join(get, NULL);
	pthread_join(send, NULL);

	return 0;
}
