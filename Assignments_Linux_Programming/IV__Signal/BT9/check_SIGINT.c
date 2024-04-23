#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    sigset_t current_mask;

    if (sigprocmask(0, NULL, &current_mask) == -1)
    {
        perror("sigprocmask() fail.\n");
        return 1;
    }

    if (sigismember(&current_mask, SIGINT))
    {
        printf("SIGINT is blocked.\n");
    }
    else
    {
        printf("SIGINT is not blocked.\n");
    }

    return 0;
}