#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argvp[])
{
    const char *filename = "test.txt";
    int fd;

    fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("error using open()");
        return 1;
    }

    return 0;
}