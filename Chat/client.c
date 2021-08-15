#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
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
	
	key = ftok("key_msg", 'A');
	msg_id = msgget(key, IPC_CREAT | 0666 );
	
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
    FILE* fout;

	key_t key;
	message_buff rbuf;
	char text[256];
	int msg_id;

	key = ftok("key_msg", 'A');
	msg_id = msgget(key, IPC_CREAT | 0666 );
	rbuf.mtype = 2L;
	
    while(1)
    {
        fout = fopen("msg.txt", "a");
        gets(text);
		//fgets(text, 256, stdin);
        if(strcmp(text, "quitserver") == 0)
        {
            printf("GoodBuy!\n");
            exit(EXIT_SUCCESS);
        }

		sprintf(rbuf.mtext, "%d: %s", getpid(), text);
        fprintf(fout, "%d: %s\n", getpid(), text);
		msgsnd(msg_id, &rbuf, sizeof(rbuf), 0);
        fclose(fout);
	}
    
	return 0;
}

int main()
{
    FILE* fin;
    char c;

	key_t key;
	pthread_t get, send;
	message_buff  rbuf;
	int msg_id;
    int pid;

	key = ftok("key_msg",'A');
	msg_id = msgget(key, IPC_CREAT | 0666 );
	if (msg_id == -1){
		printf("Client didn't join the queue");
	}
	
    fin = fopen("msg.txt", "r");
	/* посылка pid серверу*/
	rbuf.mtype = 1L; // приоритет
	sprintf(rbuf.mtext,"%d", getpid());
	printf ("Sending pid %s the server\n", rbuf.mtext);
	msgsnd(msg_id, &rbuf, sizeof(rbuf), 0);

    while(fscanf(fin, "%c", &c) == 1)
    {
        fprintf(stdout, "%c", c);
    }
    fclose(fin);
	pthread_create(&get, NULL, get_msg, NULL);
	pthread_create(&send, NULL, send_msg, NULL);
	pthread_join(get, NULL);
	pthread_join(send, NULL);

	return 0;
}
