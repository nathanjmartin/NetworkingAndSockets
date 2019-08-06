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

void sendinfo(int sockfd) 
{ 
    //vars
    char buff[MAX];
    int n;

    //constantly listen 
    while(1) { 
        //erasing all buffer data (when exists)
        bzero(buff, sizeof(buff)); 
        //printing prompt
        printf("Send a command to the server: "); 
        //index
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; // wait for user input 
        //send to server
        write(sockfd, buff, sizeof(buff)); 
        
        //clear buffer
        bzero(buff, sizeof(buff));

        //read from server into buffer 
        read(sockfd, buff, sizeof(buff));

        //message from server 
        printf("From Server : %s", buff);

        //if interrupted, print client exit 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client canceled\n"); 
            break; 
        } 
    } 
}

int main(void) {
    int sockfd, connfd;
    char *hello = "Hello, I am the client";
    struct sockaddr_in servaddr, cli;

    //create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // check if socket created
    if(sockfd == -1) {
        printf("socket creation failure\n");
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
        printf("connection failed\n");
        exit(0);
    }

    else
    {
        printf("connected to python server\n");
    }

    //send(sockfd, hello, strlen(hello), 0);
    sendinfo(sockfd);

    close(sockfd);
    
}