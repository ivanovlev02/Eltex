#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void pid_error(int pid){
    if(-1 == pid){
        perror("fork()");
        exit(1);
    }
}

int main(int argc, char* argv[]){
    pid_t pidB, pidC, pidD, pidE, pidF;
    
    printf("PARENT PID: %d\n", getpid());

    pidB = fork();
    pid_error(pidB);
    if(pidB == 0){
        sleep(1);
        printf("CHILD_B id: %d PARENT_A id: %d\n", getpid(), getppid());
        
        pidD = fork();
        pid_error(pidD);
        if(pidD == 0){
            sleep(1);
            printf("CHILD_D id: %d PARENT_B id: %d\n", getpid(), getppid());
        }
        if(pidD > 0){
            pidE = fork();
            pid_error(pidE);
            if(pidE == 0){
                sleep(1);
                printf("CHILD_E id: %d PARENT_B id: %d\n", getpid(), getppid());
            }
        }
    }
    if(pidB > 0){
        pidC = fork();
        pid_error(pidC);
        if(pidC == 0){
            sleep(1);
            printf("CHILD_C id: %d PARENT_A id: %d\n", getpid(), getppid());
            pidF = fork();
            pid_error(pidF);
            if(pidF == 0){
                sleep(1);
                printf("CHILD_F id: %d PARENT_C id: %d\n", getpid(), getppid());
            }
        }
    }
        
    for(int i = 0; i < 4; i++){
        wait(NULL);
    }

    exit(0);
}
