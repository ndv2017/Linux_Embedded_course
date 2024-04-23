#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sign_handler1(int sign_num)
{
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
        printf("Child process %d terminated\n", pid);
}

int main(int argc, char const *argv[])
{
    pid_t pid;

    pid = fork();

    signal(SIGCHLD, sign_handler1);

    if (pid == 0)
    {
        // Child process
        printf("\nIm the child process\n");
        sleep(5);
        printf("Child process exiting\n");
    }
    else if (pid > 0)
    {
        // Parent process
        printf("\nIm the parent process\n");
        sleep(10);
        printf("Parent process exiting\n");
    }
    else
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;   
}