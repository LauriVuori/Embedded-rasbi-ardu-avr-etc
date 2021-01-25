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
void initSocket(struct sockaddr_in * servAddr, int * sockfd);
void acceptClient(struct sockaddr_in * servAddr, int * sockfd, int * accClient);