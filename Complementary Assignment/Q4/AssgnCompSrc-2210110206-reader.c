#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char buffer[BUFSIZ];

    fd = open(FIFO_FILE, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    read(fd, buffer, BUFSIZ);
    printf("Reader: Received message: %s\n", buffer);

    close(fd);

    return 0;
}

