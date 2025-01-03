#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    const char *shared_memory_name = "OS";
    const int SIZE = 4096;

    int shared_memory_fd;
    void *shared_memory_ptr;

    shared_memory_fd = shm_open(shared_memory_name, O_RDONLY, 0666);
    if (shared_memory_fd == -1) {
        perror("Error: Unable to access shared memory");
        exit(EXIT_FAILURE);
    }

    shared_memory_ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shared_memory_fd, 0);
    if (shared_memory_ptr == MAP_FAILED) {
        perror("Error: Mapping failed");
        exit(EXIT_FAILURE);
    }

    printf("%s", (char *)shared_memory_ptr);

    if (shm_unlink(shared_memory_name) == -1) {
        perror("Error: Unable to remove shared memory");
        exit(EXIT_FAILURE);
    }

    return 0;
}
