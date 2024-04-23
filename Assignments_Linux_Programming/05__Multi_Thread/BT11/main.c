#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    short thread_identifier;
    char name[30];
    short year_of_birth;
    char tele_num[12];
    char hometown[30];
} human;

void *thread_handler(void *args)
{
    human *data = (human *)args;
    if (data->thread_identifier == 1)
        printf("Arbitrary message from thread1_id\n\n");
    else if (data->thread_identifier == 2)
    {
        strcpy(data->name, "Nguyen Duc Viet");
        data->year_of_birth = 2003;
        strcpy(data->tele_num, "84123456789");
        strcpy(data->hometown, "Da Nang, Viet Nam");

        printf("Name: %s\n", data->name);
        printf("Year of birth: %d\n", data->year_of_birth);
        printf("Telephone number: %s\n", data->tele_num);
        printf("Hometown: %s\n", data->hometown);
    }
}

int main(int argc, char const *argv[])
{
    int ret;
    pthread_t thread1_id, thread2_id;
    human data;

    data.thread_identifier = 1;
    if (ret = pthread_create(&thread1_id, NULL, thread_handler, &data))
    {
        perror("Error creating thread1");
        return EXIT_FAILURE;
    }

    sleep(2);

    data.thread_identifier = 2;
    if (ret = pthread_create(&thread2_id, NULL, thread_handler, &data))
    {
        perror("Error creating thread2");
        return EXIT_FAILURE;
    }

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);

    return 0;
}