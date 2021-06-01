#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
void exit_signal(int sig) {
    printf("CTRL-C exit");
    exit(1);
}

int main(){
  int a = 5;
  signal(SIGINT, exit_signal); 
  printf(RED"Terve%d"RESET, 5);
} 