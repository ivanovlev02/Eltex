#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

void pid_error(pid_t pid){
    if(pid == -1){
        perror("fork()");
        exit(EXIT_FAILURE);
    }
}

int main(){

    pid_t pidB = fork();
    pid_t pidC, pidE, pidF;
    int status[6];

    pidC = fork();
    if(pidB == -1){
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if(pidB == 0){
        //printf("CHILD_B: %i, PARENT_A: %i\n", getpid(), getppid());
        if(pidC > 0){
            printf("CHILD_B: %i, PARENT_A: %i\n", getpid(), getppid());
            pidE = fork();
            if(pidE == 0){
                printf("CHILD_E: %i, PARENT_B: %i\n", getpid(), getppid());
                exit(status[4]);
            }
            exit(status[3]);
        }
        wait(&status[2]);
        printf("CHILD_D: %i, PARENT_B: %i\n", getpid(), getppid());
        exit(status[1]);
    } else {
        wait(&status[1]);
        wait(&status[2]);
        wait(&status[3]);
        wait(&status[4]);
        sleep(1);
        printf("PARENT: %i\n", getpid());
    }
    if(pidC == 0){
        printf("CHILD_C: %i, PARENT_A: %i\n", getpid(), getppid());
        pidF = fork();
        if(pidF == 0){
            printf("CHILD_F: %i, PARENT_C: %i\n", getpid(), getppid());
            exit(status[5]);
        }
        exit(status[2]);
    }
       
    exit(EXIT_SUCCESS);
}
