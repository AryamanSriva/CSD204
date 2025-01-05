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
    char *message = "Hello from writer";

    mkfifo(FIFO_FILE, 0666);

    fd = open(FIFO_FILE, O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd, message, strlen(message) + 1);
    printf("Writer: Sent message: %s\n", message);

    close(fd);

    return 0;
}