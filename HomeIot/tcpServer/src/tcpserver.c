// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
#include <../include/tcp.h>

void exit_signal(int sig);
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



int main(void) {
    // @param sockfd − It is a socket descriptor returned by the socket function.
    // @param cliaddr − It is a pointer to struct sockaddr that contains client IP address and port.
    // @param connfd − 
    int sockfd, len;
    int acceptedClient;
    struct sockaddr_in servaddr, client;
    struct tcpErrors error = {false};
    struct tcpOptions options = {false};
    signal(SIGINT, exit_signal); 
    char menu[5];

    sockfd = initSocket(&servaddr, sockfd);
    while (sockfd < 0) {
        sockfd = initSocket(&servaddr, sockfd);
    }
    
    int err = acceptClient(&client, &sockfd, acceptedClient);
    // printf(RED"<%d>"RESET, sockfd);
    // options.sendDataBack = true;


    close(sockfd); 
}
/* OLD MAIN*/
// while (menu[0] != 'e') {
//     receiveData(&acceptedClient, &error, &options);
//     // Get errors and listen new connections
//     // func(&acceptedClient);
//     printf("Out of loop: want to continue 'e' to quit\n");
//     fgets(menu, 2, stdin);
//     if (error.zeroBuffer == 1) {
//         printf("\nFOUND ERROR, TRYING TO GET CONNECTION BACK\n");
//         bzero(&client, sizeof(client));
//         acceptClient(&client, &sockfd, &acceptedClient);
//         error.zeroBuffer = 0;
//     }
// }
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
 * @param int sockfd
 * @param int acceptClient
 * @return writes to target destination
*/
/*********************************************************************/
int acceptClient(struct sockaddr_in * client, int * sockfd, int acceptClient) {
    int len = 0;
    /* int listen(int sockfd,int backlog);
    backlog − It is the number of allowed connections.
    */ 
    if ((listen(*sockfd, MAXCONNECTIONS) != 0)) {
        printf(RED"Listening failed\n"RESET);
    }
    else {
        printf("Server listening..\n");
    }

    len = sizeof(client);
    // int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
    acceptClient = accept(*sockfd,(struct sockaddr*)client, &len);
    if (acceptClient < 0) {
        printf("Accepting server failed\n");
    }

    printf("Server accepted the client\n");
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
int initSocket(struct sockaddr_in * servAddr, int sockfd) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf(RED"ERROR opening socket\n"RESET);
        return -1;
    }
    else {
        printf(GRN"Socket created\n"RESET);
    }
    
    bzero(servAddr, sizeof(servAddr));
    
    servAddr->sin_family = AF_INET;
    servAddr->sin_addr.s_addr = INADDR_ANY;
    servAddr->sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr*)servAddr, sizeof(*servAddr)) < 0) {
        printf("error binding socket");
        return -1;
    }

    printf(GRN"Socket binded\n"RESET);
    return true;
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