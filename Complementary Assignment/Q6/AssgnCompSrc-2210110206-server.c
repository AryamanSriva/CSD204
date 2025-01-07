#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/socket"  
int main() {
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for incoming connection...\n");

    int clientfd = accept(sockfd, NULL, NULL);
    if (clientfd == -1) {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connection established. Receiving file...\n");

    char buffer[256];
    ssize_t bytes_received;
    while ((bytes_received = read(clientfd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_received);
    }

    close(clientfd);
    close(sockfd);
    printf("File transfer complete.\n");

    return 0;
}
