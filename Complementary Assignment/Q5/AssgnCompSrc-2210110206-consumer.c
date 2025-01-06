
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    const char *mem_name = "OS";
    const int mem_size = 4096;

    int mem_fd;
    void *mem_ptr;

    mem_fd = shm_open(mem_name, O_RDONLY, 0666);
    if (mem_fd == -1) {
        printf("Failed to open shared memory segment\n");
        exit(-1);
    }

    mem_ptr = mmap(0, mem_size, PROT_READ, MAP_SHARED, mem_fd, 0);
    if (mem_ptr == MAP_FAILED) {
        printf("Mapping shared memory segment failed\n");
        exit(-1);
    }

    printf("%s", (char *)mem_ptr);

    if (shm_unlink(mem_name) == -1) {
        printf("Error removing shared memory segment: %s\n", mem_name);
        exit(-1);
    }

    return 0;
}
