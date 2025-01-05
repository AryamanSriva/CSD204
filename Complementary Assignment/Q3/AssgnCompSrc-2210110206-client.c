#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_NUMBER 8080
#define BUFFER_SIZE 1024

int main() {
    struct sockaddr_in server_address;
    int client_socket = 0, bytes_received;
    struct sockaddr_in serv_addr;
    char *message_to_send = "Hello from the client";
    char receiving_buffer[BUFFER_SIZE] = {0};

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation failed \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_NUMBER);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address or address not supported \n");
        return -1;
    }

    if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection to server failed \n");
        return -1;
    }

    send(client_socket, message_to_send, strlen(message_to_send), 0);
    printf("Message sent to the server\n");

    bytes_received = read(client_socket, receiving_buffer, BUFFER_SIZE);
    printf("Server says: %s\n", receiving_buffer);

    return 0;
}
