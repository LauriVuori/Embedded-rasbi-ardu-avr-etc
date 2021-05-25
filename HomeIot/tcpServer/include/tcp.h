#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <signal.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <pthread.h>


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define MAX 80 
#define PORT 8080
#define MAXCONNECTIONS 1
#define SA struct sockaddr

/*!
 * @enum boolean
 * @brief boolean variable
 * @param false 0
 * @param true 1
*/ 
enum boolean {
    false = 0, 
    true = 1
};

/* Global structures */

/*!
 * @struct tcpErrors
 * @brief flag errors
 * @param enum boolean zeroBuffer
*/ 
struct tcpErrors {
    enum boolean zeroBuffer;
};

/*!
 * @struct tcpOptions
 * @brief options for tcp
 * @param enum boolean sendDataBack
*/ 
struct tcpOptions{
    enum boolean sendDataBack;
};

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/
void func(int * sockfd);
void receiveData(int * sockfd, struct tcpErrors * error, struct tcpOptions * options);
void sendData(int * sockfd, char (*data)[MAX]);
int initSocket(struct sockaddr_in * servAddr, int sockfd);
int acceptClient(struct sockaddr_in * client, int * sockfd, int acceptClient);