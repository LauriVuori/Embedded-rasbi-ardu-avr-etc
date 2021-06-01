// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
// https://www.geeksforgeeks.org/multithreading-c-2/
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <../include/tcp.h>

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

typedef struct Client{
    struct sockaddr_in client;
    int acceptedClient;
    int sockfd;
} Client;

void* acceptClientThread(void* data);

int main(void) {
    // @param sockfd − It is a socket descriptor returned by the socket function.
    // @param cliaddr − It is a pointer to struct sockaddr that contains client IP address and port.
    // @param connfd − 

    /*SOCKET*/
    int sockfd, len; 
    struct sockaddr_in servaddr, oneclient;
    struct tcpErrors error = {false};
    struct tcpOptions options = {false};
    char menu[5];
    /*SOCKET END*/
    Client client[5];

    pthread_t  thread_id; 

    
    signal(SIGINT, exit_signal); 

    initSocket(&servaddr, &sockfd);
    // Client client[5];
    client[0].sockfd = sockfd;
    client[1].sockfd = sockfd;
    client[0].acceptedClient = -1;
    client[1].acceptedClient = -1;
    int a = pthread_create(&thread_id, NULL, acceptClientThread, (void*)&client[0]);
    while (client[0].acceptedClient < 0) {
    }
    printf("toimii\n");
    int b = pthread_create(&thread_id, NULL, acceptClientThread, (void*)&client[1]);
    printf("KAKSI\n");
    while (client[1].acceptedClient < 0) {
    }

    printf("WORKING");


    close(sockfd);
    pthread_exit(NULL);
}
/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn Thread to make new connections
 * @brief 
 * @param 
 * @return 
*/
/*********************************************************************/
void* acceptClientThread(void* data) {
    static clientCounter = 0;
    clientCounter++;
    printf(RED"CLIENT COUNTER: %d\n"RESET,clientCounter);
    Client * newClient = (Client*)data;
    int len = 0;
    /* int listen(int sockfd,int backlog);
    backlog − It is the number of allowed connections.
    */ 
    if ((listen(newClient->sockfd, MAXCONNECTIONS) != 0)) {
        printf(RED"Listening failed\n"RESET);
    }
    else {
        printf(GRN"Server listening..\n"RESET);
    }

    len = sizeof((struct sockaddr_in *)&newClient->client);
    printf(RED"LEN:<%d>\n"RESET,len);
    // int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
    newClient->acceptedClient = accept(newClient->sockfd, (struct sockaddr*)&newClient->client, &len);
    printf(RED"acceptedClient:<%d>\n"RESET, newClient->acceptedClient);

    if (newClient->acceptedClient < 0) {
        printf(RED"Accepting server failed\n"RESET);
    }
    else{
        printf(GRN"Server accepted the client\n"RESET);
    }
    pthread_exit(NULL);
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn s
 * @brief 
 * @param 
 * @return 
*/
/*********************************************************************/
void acceptMultipleConnections(){
    int i = 0;
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn sendData(int * sockfd, char (*data)[MAX])
 * @brief send data to target address 
 * @param char(*data)[MAX]
 * @return writes to target destination
 * @remark char (*data)[MAX] is this correct way to do
*/
/*********************************************************************/
void sendData(int * sockfd, char (*data)[MAX]) {
    write(*sockfd, *data, sizeof(*data));
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn acceptClient(struct sockaddr_in * client, int * sockfd, int * acceptClient)
 * @brief 
 * @param struct sockaddr_in* client
 * @param int* sockfd
 * @param int* acceptClient
 * @return writes to target destination
*/
/*********************************************************************/
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
    printf(RED"LEN:<%d>\n"RESET,len);
    // int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
    *acceptClient = accept(*sockfd,(struct sockaddr*)client, &len);
    if (*acceptClient < 0) {
        printf("Accepting server failed\n");
    }
    else{
        printf("Server accepted the client\n");
    }
}


/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn initSocket(struct sockaddr_in * servAddr, int * sockfd)
 * @brief initialize socket
 * @param struct sockaddr_in * servAddr
 * @param int* sockfd
 * @return 
*/
/*********************************************************************/
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

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn receiveData(int * sockfd, struct tcpErrors * error, struct tcpOptions * options)
 * @brief Receive data from socket until error, set option to send data back to sender
 * @param int* sockfd
 * @param struct tcpErrors * error
 * @return 
*/
/*********************************************************************/
void receiveData(int * sockfd, struct tcpErrors * error, struct tcpOptions * options) {
    char buff[MAX];
    int n;
    printf("Receiving data:\n");
    while (((strncmp("exit", buff, 4)) != 0) && (error->zeroBuffer == false)){
        bzero(buff, MAX);
        // read the message from client and copy it in buffer 
        // int read(int fildes, const void *buf, int nbyte);
        read(*sockfd, buff, sizeof(buff));
        if(buff[0] == '\0') {
            // in case of connection lost etc..
            error->zeroBuffer = true;
            printf("Got empty buffer, maybe lost connection\n");
        }
        else{
            printf("From client: %s\n", buff);
            if (options->sendDataBack == true) {
                sendData(sockfd, &buff);
            }
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

void exit_signal(int sig) {
    printf("CTRL-C exit");
    exit(1);
}