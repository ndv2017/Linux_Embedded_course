#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main()
{
    const char *filename = "text.txt";
    
    FILE *fd = fopen(filename, "w");
    if (fd == NULL)
    {
        printf("Error opening file.");
        return 1;
    }

    fprintf(fd, "hello Viet, hello anh Phong\n");
    fclose(fd);

    struct stat filestat;
    if (stat(filename, &filestat))
    {
        printf("Error in stat");
        return 1;
    }

    printf("Type of file: %s\n", S_ISREG(filestat.st_mode) ? "Regular file" : "Directory");
    printf("File name: %s\n", filename);
    printf("Last file modification: %s", ctime(&filestat.st_mtime));
    printf("Size of file: %ld bytes\n", filestat.st_size);

    return 0;
}