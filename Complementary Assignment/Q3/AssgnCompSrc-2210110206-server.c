#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_NUMBER 8080
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address;
    int option = 1;
    int address_length = sizeof(server_address);
    char message_buffer[BUFFER_SIZE] = {0};
    const char *response_message = "Greetings from the server";

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT_NUMBER);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    if ((client_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t*)&address_length)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    read(client_socket, message_buffer, BUFFER_SIZE);
    printf("Client says: %s\n", message_buffer);

    send(client_socket, response_message, strlen(response_message), 0);
    printf("Response message sent to the client\n");

    return 0;
}
