#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int a = 0;
    pid_t child_pid;

    printf("Initial value of a is: %d\n", a);

    child_pid = fork();

    if (child_pid == 0)
    {
        // Child process
        printf("\nIm the child process, a: %d\n", a);
        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
    }
    else if (child_pid > 0)
    {
        // Parent process
        printf("\nIm the parent process, a: %d\n", --a);
        printf("My PID is: %d\n", getpid());
    }
    else
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;   
}