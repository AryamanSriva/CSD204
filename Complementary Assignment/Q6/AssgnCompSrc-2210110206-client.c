#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>

#define SOCKET_PATH "/tmp/socket"  

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];

    int file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int socket_descriptor = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_descriptor == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    if (connect(socket_descriptor, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    ssize_t bytes_read;

    while ((bytes_read = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
        if (write(socket_descriptor, buffer, bytes_read) != bytes_read) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    close(file_descriptor);
    close(socket_descriptor);

    return 0;
}
