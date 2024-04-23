#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int cnt = 0;

void sig_thread1(int num)
{
    printf("\nHello! Im SIGINT num: %d, cnt = %d\n", num, ++cnt);
    printf("This is a message when press Ctrl + C.\n");
}

int main()
{
    sigset_t current_mask, new_mask;

    if (signal(SIGINT, sig_thread1) == SIG_ERR)
    {
        fprintf(stderr, "signal() error.\n");
        exit(EXIT_FAILURE);
    }

    sigemptyset(&current_mask);
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);

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

        // step 1: block SIGINT
        sigaddset(&new_mask, SIGINT);
        if (sigprocmask(SIG_BLOCK, &new_mask, &current_mask))
        {
            perror("sigprocmask() fail.\n");
            return 1;
        }
        else
        {
            // check current_mask;
            if (sigprocmask(0, NULL, &current_mask) == -1)
            {
                perror("sigprocmask() fail.\n");
                return 1;
            }

            if (sigismember(&current_mask, SIGINT))
            {
                printf("SIGINT after step 1 is blocked.\n");
            }
            else
            {
                printf("SIGINT after step 1 is not blocked.\n");
            }
        }
        sleep(7); //try Ctrl C in 7 secs to check



        // step 2: unblock SIGINT

        if (sigprocmask(SIG_UNBLOCK, &new_mask, &current_mask))
        {
            perror("sigprocmask() fail.\n");
            return 1;
        }
        else
        {
            // check current_mask;
            if (sigprocmask(0, NULL, &current_mask) == -1)
            {
                perror("sigprocmask() fail.\n");
                return 1;
            }

            if (sigismember(&current_mask, SIGINT))
            {
                printf("SIGINT after step 2 is blocked.\n");
            }
            else
            {
                printf("SIGINT after step 2 is not blocked.\n");
            }
        }
    }



    while (1)
    {
        sleep(2);
    }

    return 0;
}