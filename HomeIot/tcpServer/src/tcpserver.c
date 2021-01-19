// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <../include/tcp.h>
#define MAX 80 
#define PORT 8080
#define MAXCONNECTIONS 1
#define SA struct sockaddr
// struct sockaddr {
//    unsigned short   sa_family;
//    char             sa_data[14];
// };
// struct sockaddr_in {
//    short int            sin_family;
//    unsigned short int   sin_port;
//    struct in_addr       sin_addr;
//    unsigned char        sin_zero[8];
// };



int main() {
    // @param sockfd − It is a socket descriptor returned by the socket function.
    // @param cliaddr − It is a pointer to struct sockaddr that contains client IP address and port.
    // @param connfd − 
    int sockfd, len; 
    int acceptedClient;
    struct sockaddr_in servaddr, client;
    struct errors error = {0};

    initSocket(&servaddr, &sockfd);
    acceptClient(&client, &sockfd, &acceptedClient);
    receiveData(&acceptedClient, &error);

    // Get errors and listen new connections
    if (error.zeroBuffer == 1) {
        printf("\nFOUND ERROR, TRYING TO GET CONNECTION BACK\n");
        acceptClient(&client, &sockfd, &acceptedClient);
        error.zeroBuffer = 0;
    }
    receiveData(&acceptedClient, &error);
    // func(&acceptedClient);
    close(sockfd); 
}

void acceptClient(struct sockaddr_in * client, int * sockfd, int * acceptClient) {
    int len = 0;
    /* int listen(int sockfd,int backlog);
    backlog − It is the number of allowed connections.
    */ 
    if ((listen(*sockfd, MAXCONNECTIONS) != 0)) {
        printf("Listening failed\n");
    }
    else {
        printf("Server listening..\n");
    }

    len = sizeof(client);
    // int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
    *acceptClient = accept(*sockfd,(struct sockaddr*)client, &len);
    if (*acceptClient < 0) {
        printf("Accepting server failed\n");
    }
    else{
        printf("Server accepted the client\n");
    }
}

void initSocket(struct sockaddr_in * servAddr, int * sockfd) {
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("ERROR opening socket\n");
    }
    else{
        printf("Socket created\n");
    }
    
    bzero(servAddr, sizeof(servAddr));
    
    servAddr->sin_family = AF_INET;
    servAddr->sin_addr.s_addr = INADDR_ANY;
    servAddr->sin_port = htons(PORT);
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    if (bind(*sockfd, (const struct sockaddr*)servAddr, sizeof(*servAddr)) < 0) {
        printf("error binding socket");
    }
    else{
        printf("Socket binded\n");
    }
}

void receiveData(int * sockfd, struct errors * error) {
    char buff[MAX];
    int n;
    printf("Receiving data:\n");
    while (((strncmp("exit", buff, 4)) != 0) && (error->zeroBuffer == 0)){
        bzero(buff, MAX);
        // read the message from client and copy it in buffer 
        // int read(int fildes, const void *buf, int nbyte);
        read(*sockfd, buff, sizeof(buff));
        if(buff[0] == '\0') {
            // in case of connection lost etc..
            error->zeroBuffer = 1;
            printf("Got empty buffer, maybe lost connection\n");
        }
        else{
            printf("From client: %s\n", buff);
        }
    }
    printf("Communication ends..\n");
}



void func(int *sockfd) { 
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        read(*sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
}