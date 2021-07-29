#include <sys/wait.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <pwd.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 80

int get_entries(char* in, char entry){
    int count = 0;
    while(*in){
        if(*in == entry){
            count++;
        }
        in++;
    }
    return count;
}

int main(int argc, char** argv)
{
    struct passwd* userinfo;
    uid_t userid;
    userinfo = getpwuid(userid);

    char dir[PATH_MAX];
    char command[ARG_MAX];
    char *curChar;
    char subCommand[MAX_SIZE];

    int len;
    int pipe_entries;
    int oldStdout;
    int status;
    int stat;
    int *pipes;
    pid_t *pid;
    char **tasks;

    while(1){
        if(getcwd(dir, PATH_MAX) == NULL){
            perror("getcwd");
            exit(EXIT_FAILURE);
        } else if(userinfo == NULL) {
            perror("userinfo");
            exit(EXIT_FAILURE);
        } else {
            printf("%s:%s>_ ", userinfo->pw_name, dir);
        }
        fgets(command, ARG_MAX, stdin);
        curChar = strchr(command, '\n');
        *curChar = '\0';
        if(command[0] == '\0'){
            continue;
        }
        if(strcmp(command, "quit") == 0){
            exit(EXIT_SUCCESS);
        }
        
        pipe_entries = get_entries(command, '|');
        pipes = (int*)calloc(2 * pipe_entries, sizeof(int*));
        for(int i = 0; i <  pipe_entries; i++){
            pipe(&pipes[2*i]);
        }
        oldStdout = dup(STDOUT_FILENO);
        tasks = (char**)calloc(pipe_entries + 1, sizeof(char*));
        memset(subCommand, 0, MAX_SIZE);

        for(int i = 0; i < pipe_entries + 1; i++){
            if(i == 0){
                strcpy(subCommand, strtok(command, "|"));
            } else {
                strcpy(subCommand, strtok(NULL, "|"));
            }
            len = strlen(subCommand);
            if(subCommand[0] == ' '){
                for(int j = 0; j < len - 1; j++){
                    subCommand[j] = subCommand[j + 1];
                }
                subCommand[len - 1] = '\0';
                len--;
            }
            if(subCommand[len - 1] == ' '){
                subCommand[len - 1] = '\0';
                len--;
            }
            tasks[i] = (char*)calloc(len, sizeof(char));
            strcpy(tasks[i], subCommand);
            memset(subCommand, 0, MAX_SIZE);
        }

        pid = (pid_t*)calloc(pipe_entries + 1, sizeof(pid_t));
        for(int i = 0; i < pipe_entries + 1; i++){
            pid[i] = fork();
            if(pid[i] == 0){
                int argEntry = get_entries(tasks[i], ' ');
                char **args = (char**)calloc(argEntry + 2, sizeof(char*));
                for(int j = 0; j < argEntry + 1; j++){
                    if(j == 0){
                        strcpy(subCommand, strtok(tasks[i], " "));
                    } else {
                        strcpy(subCommand, strtok(NULL, " "));
                    }
                    args[j] = (char*)calloc(strlen(subCommand), sizeof(char));
                    strcpy(args[j], subCommand);
                    memset(subCommand, 0, MAX_SIZE);
                }
                args[argEntry + 1] = NULL;
                if(i == 0){
                    for (int j = 0; j < 2 * pipe_entries; j++) {
                        if (j == 1) {
                            if (pipe_entries != 0) {
                                dup2(pipes[j], STDOUT_FILENO);
                            }
                        }
                    }
                    execvp(args[0], args);
                }
                if (i > 0 && i < pipe_entries) {
                    for (int j = 0; j < 2 * pipe_entries; j++) {
                        if (2 * i - 2 == j) {
                            dup2(pipes[j], STDIN_FILENO);
                        }
                        if (2 * i + 1 == j) {
                            dup2(pipes[j], STDOUT_FILENO);
                        }
                    }
                    execvp(args[0], args);
                }
                for (int j = 0; j < 2 * pipe_entries; j++) {
                    if (2 * i - 2 == j) {
                        dup2(pipes[j], STDIN_FILENO);
                    }
                }
                dup2(oldStdout, STDOUT_FILENO);
                execvp(args[0], args);
            }
            status = waitpid(pid[i], &stat, 0);
            if(i < pipe_entries){
                close(pipes[i]);
            }
        }
        for(int i = 0; i < 2 * pipe_entries; i++){
            if(i % 2 != 0 && i != 2 * pipe_entries - 1){
                close(pipes[i]);
            }
        }
        for(int i = 0; i < pipe_entries + 1; i++){
            free(tasks[i]);
        }
        free(tasks);
        free(pipes);
        free(pid);
    }

    exit(EXIT_SUCCESS);
}
