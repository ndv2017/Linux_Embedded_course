#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int cnt = 0;

void sig_thread1(int num)
{
    printf("\nHello! Im SIGINT num: %d, cnt = %d\n", num, ++cnt);
    printf("\nThis is an arbitrary message from Ctrl + C.\n");
}

void sig_thread2(int num)
{
    printf("\nHello! Im SIGUSR1 num: %d, cnt = %d\n", num, ++cnt);
}

void sig_thread3(int num)
{
    printf("\nHello! Im SIGUSR2 num: %d, cnt = %d\n", num, ++cnt);
}

int main()
{
    if (signal(SIGINT, sig_thread1) == SIG_ERR)
    {
        fprintf(stderr, "signal() error.\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR1, sig_thread2) == SIG_ERR)
    {
        fprintf(stderr, "signal() error.\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR2, sig_thread3) == SIG_ERR)
    {
        fprintf(stderr, "signal() error.\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        sleep(2);
    }

    return 0;
}