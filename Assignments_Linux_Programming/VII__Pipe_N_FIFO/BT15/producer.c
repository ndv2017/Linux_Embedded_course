#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define FIFO_FILE   "./fifo"
#define BUFF_SIZE   100

int main(int argc, char const *argv[])
{
    char buff[BUFF_SIZE];
    int fd;

    mkfifo(FIFO_FILE, 0777);

    while (1)
    {
        // write first
        printf("Message to the consumer: "); 
        fgets(buff, BUFF_SIZE, stdin);

        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buff, strlen(buff) + 1); fflush(stdin);
        close(fd);

        // Read responding message
        fd = open(FIFO_FILE, O_RDONLY);
        read(fd, buff, BUFF_SIZE);

        printf("comsumer respone: %s", buff);
        close(fd);
    }

    return 0;
}