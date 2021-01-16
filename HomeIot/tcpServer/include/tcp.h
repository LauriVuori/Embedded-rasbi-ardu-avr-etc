void func(int sockfd);
void initSocket(struct sockaddr_in * servAddr, int * sockfd);
void acceptClient(struct sockaddr_in * servAddr, int * sockfd, int * accClient);