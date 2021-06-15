#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
void exit_signal(int sig);
int main(void) {
    signal(SIGINT, exit_signal); 
    while (1) {
        printf("SLEEP\n");
        sleep(1);
    }
}

void exit_signal(int sig) {
    printf("CTRL-C exit");
    exit(1);
}