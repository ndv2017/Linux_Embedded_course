#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    const char *filename = "test.txt";
    char buf1[20] = "Hello anh Phong\n";
    char buf2[20] = "Hello Viet\n";

    int file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (file == -1)
    {
        printf("Cannot open file");
        return 1;
    }

    write(file, buf1, strlen(buf1));
    lseek(file, 0, SEEK_SET);
    write(file, buf2, strlen(buf2));
    
    close(file);
    return 0;
}