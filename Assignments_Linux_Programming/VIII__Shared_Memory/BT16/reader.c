#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SHARE_MEM_SIZE      4096
#define FILE_NAME           "viet_mmap"

int main()
{
    int shm_fd;
    char *data;

    shm_fd = shm_open(FILE_NAME, O_RDWR, 0);
    if (shm_fd < 0) 
    {
        printf("shm_open() is failed, %s.\n", strerror(errno));
        return -1;
    }

    data = mmap(0, SHARE_MEM_SIZE, PROT_WRITE , MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    printf("%s: Message received: %s\n", __FILE__, data); 

    if (munmap(data, SHARE_MEM_SIZE) == -1) 
    {
        perror("munmap");
        return -1;
    }    

    close(shm_fd);
    shm_unlink(FILE_NAME);

    return 0; 
}