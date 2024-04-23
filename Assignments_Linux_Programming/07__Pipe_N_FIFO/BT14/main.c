#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define MSGSIZE 100

char *msg1 = "Anh Phong";
char *msg2 = "T7 hôm qua";
char *msg3 = "em làm xong module 4 rồi ạ";

int main(int argc, char const *argv[])
{
    char in_buff[MSGSIZE];
    int pipefd[2];
    int num_read = 0;
    pid_t child_pid;

    if (pipe(pipefd) == -1)
    {
        perror("pipe error.");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();
    if (child_pid == 0)
    {
        // Child process read
        printf("\nIm the child process\n");
        close(pipefd[1]);

        while(1)
        {
            num_read = read(pipefd[0], in_buff, MSGSIZE);
            if (num_read == - 1)
            {
                perror("Cannot read pipe, read() fail\n");
                exit(EXIT_FAILURE);
            }
            else if (num_read == 0)
            {
                puts("pipe end_of_pipe");
                break;
            }
            else
                printf("message: %s\n", in_buff);
        }
    }
    else if (child_pid > 0)
    {
        // Parent process write
        printf("\nIm the parent process\n");
        close(pipefd[0]);

        write(pipefd[1], msg1, MSGSIZE);
        write(pipefd[1], msg2, MSGSIZE);
        write(pipefd[1], msg3, MSGSIZE);

        while(1);
    }
    else
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    while(1);

    return 0;   
}