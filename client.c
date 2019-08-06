#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 80
#define PORT 12345
#define SA struct sockaddr

int main(void) {
    int sockfd, connfd;
    char *hello = "Hello, I am the client";
    struct sockaddr_in servaddr, cli;

    //create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // check if socket created
    if(sockfd == -1) {
        printf("socket creation failure");
        exit(0);
    }

    //else socket created successfully
    else {
        printf("socket creation successful\n");
    }
    bzero(&servaddr, sizeof(servaddr));

    // assigning ip address and port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    //connect the client socket to the server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection failed");
        exit(0);
    }

    else
    {
        printf("connected to python server\n");
    }

    send(sockfd, hello, strlen(hello), 0);
    close(sockfd);
    
}