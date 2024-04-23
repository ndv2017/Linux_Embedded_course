#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define FILE_NAME           "thongtinsinhvien.txt"
#define STUDENT_NUM_MAX     3

typedef struct
{
    char name[30];
    char day_of_birth[20];
    char hometown[50];
} human;


pthread_mutex_t lockmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

void *thread1_handler(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lockmutex);
        pthread_cond_signal(&cond3);
        human *data = (human *)args;
        
        printf("\n\tStudent's name: ");
        fgets(data->name, sizeof(data->name), stdin);
        data->name[strcspn(data->name, "\n")] = '\0';

        printf("\n\tStudent's day of birth: ");
        fgets(data->day_of_birth, sizeof(data->day_of_birth), stdin);
        data->day_of_birth[strcspn(data->day_of_birth, "\n")] = '\0';

        printf("\n\tStudent's hometown: ");
        fgets(data->hometown, sizeof(data->hometown), stdin);
        data->hometown[strcspn(data->hometown, "\n")] = '\0';

        pthread_cond_wait(&cond1, &lockmutex);
        pthread_mutex_unlock(&lockmutex);
    }

    return NULL;
}

void *thread2_handler(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lockmutex);
        pthread_cond_signal(&cond1);

        human *data = (human *)args;
        int fd;

        fd = open(FILE_NAME, O_WRONLY | O_APPEND);
        
        dprintf(fd, "%s, %s, %s.\n", data->name, data->day_of_birth, data->hometown);
        
        close(fd);
        pthread_cond_wait(&cond2, &lockmutex);
        pthread_mutex_unlock(&lockmutex);
    }
}

void *thread3_handler(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lockmutex);
        pthread_cond_signal(&cond2);

        human *data = (human *)args;

        printf("\n\nData was just written in file thongtinsinhvien.txt:\n%s, %s, %s.\n\n", data->name, data->day_of_birth, data->hometown);

        pthread_cond_wait(&cond3, &lockmutex);
        pthread_mutex_unlock(&lockmutex);
    }
}

int main(int argc, char const *argv[])
{
    int fd;
    int ret;
    pthread_t thread1_id, thread2_id, thread3_id;
    human data;

    fd = open(FILE_NAME, O_CREAT | O_RDWR , 0666);

    if (ret = pthread_create(&thread1_id, NULL, thread1_handler, &data))
    {
        perror("Error creating thread1");
        return EXIT_FAILURE;
    }

    if (ret = pthread_create(&thread2_id, NULL, thread2_handler, &data))
    {
        perror("Error creating thread2");
        return EXIT_FAILURE;
    }

    if (ret = pthread_create(&thread3_id, NULL, thread3_handler, &data))
    {
        perror("Error creating thread3");
        return EXIT_FAILURE;
    }

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);
    pthread_join(thread3_id, NULL);

    close(fd);

    return 0;
}