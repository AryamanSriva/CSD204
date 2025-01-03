#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "unix_socket_example"

void report_error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int socket_fd;
     char message_buffer[256];
     struct sockaddr_un server_address, client_address;
     int bytes_received;


     socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
     if (socket_fd < 0) 
        report_error("ERROR opening socket");

     bzero((char *) &server_address, sizeof(server_address));
     server_address.sun_family = AF_UNIX;
     strcpy(server_address.sun_path, SOCK_PATH);

     if (bind(socket_fd, (struct sockaddr *) &server_address,
              sizeof(server_address)) < 0) 
              report_error("ERROR on binding");
     

     bzero(message_buffer,256);
     int client_address_length = sizeof(client_address);

     printf("Server ready\n");
     
     bytes_received = recvfrom(socket_fd, message_buffer, 255, 0, (struct sockaddr *)&client_address, &client_address_length);
     
     if (bytes_received < 0) report_error("ERROR reading from socket");
     printf("Here is the message: %s\n",message_buffer);

     unlink(SOCK_PATH);
     return 0; 
}
