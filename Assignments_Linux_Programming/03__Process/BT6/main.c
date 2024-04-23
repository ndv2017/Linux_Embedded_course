#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("\nIm the child process\n");
        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
    }
    else if (pid > 0)
    {
        // Parent process
        printf("\nIm the parent process\n");
        printf("My PID is: %d\n", getpid());

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            printf("\nChild process exited with status: %d\n", WEXITSTATUS(status));
        else
            printf("\nChild process terminated abnormally\n");
    }
    else
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;   
}