#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
    
    pid_t pidB, pidC, pidD, pidE, pidF;

    printf("PARENT PID: %d\n", getpid());

    pidB = fork();
    if(pidB < 0){
        perror("fork error");
        exit(1);
    }
    if(pidB == 0){
        printf("CHILD_B id: %d PARENT_A id: %d\n", getpid(), getppid());

        pidD = fork();
        if(pidD < 0){
            perror("fork error");
            exit(1);
        }
        if(pidD == 0){
            printf("CHILD_D id: %d PARENT_B id: %d\n", getpid(), getppid());
            exit(0);
        }
        if(pidD > 0){
            pidE = fork();
            if(pidE < 0){
                perror("fork error");
                exit(1);
            }
            if(pidE == 0){
                printf("CHILD_E id: %d PARENT_C id: %d\n", getpid(), getppid());
                exit(0);
            }
        }
    }
    if(pidB > 0){
        pidC = fork();
        if(pidC < 0){
            perror("fork error");
            exit(1);
        }
        if(pidC == 0){
            printf("CHILD_C id: %d PARENT_A id: %d\n", getpid(), getppid());
            
            if(pidE > 0){
                pidF = fork();
                if(pidF < 0){
                    perror("fork error");
                    exit(1);
                }
                if(pidF == 0){
                    printf("CHILD_F id: %d PARENT_C id: %d\n", 
                            getpid(), getppid());
                    exit(0);
                }
            }
        } 
    }

    wait(NULL);
    exit(0);
}
