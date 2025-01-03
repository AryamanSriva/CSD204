#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "unix_socket_example"

void reportError(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int sockfd, n;

    struct sockaddr_un serv_addr;
    char buffer[256];

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        reportError("ERROR: Opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_PATH); 

    printf("Please enter your message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    printf("Sending data...\n");
    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (n < 0) 
         reportError("ERROR: Writing to socket");

    close(sockfd);
    return 0;
}
