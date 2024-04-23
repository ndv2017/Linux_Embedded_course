#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_NAME   "test.txt"
#define CNT_CHARS   10000000

void *thread1_handler(void *args)
{
    int fd;

    fd = open(FILE_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
        perror("open()");
        pthread_exit(NULL);
    }

    for (int i = 0; i < CNT_CHARS; i++)
        write(fd, "V", sizeof("V"));

    close(fd);
}

int main(int argc, char const *argv[])
{
    int ret;
    pthread_t thread_id1;

    if (ret = pthread_create(&thread_id1, NULL, thread1_handler, NULL))
    {
        perror("Error creating thread");
        return EXIT_FAILURE;
    }

    pthread_join(thread_id1, NULL);
    return 0;
}