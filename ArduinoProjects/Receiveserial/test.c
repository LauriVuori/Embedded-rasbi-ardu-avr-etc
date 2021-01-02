#include <stdio.h>

struct serialData{
    int stringComplete;
    int stringCounter;
};


void receive(struct serialData * data);

int main(void){
    struct serialData data = {0,0};

    receive(&data);
    printf("%d\n", data.stringComplete);
    printf("%d", data.stringCounter);

}


void receive(struct serialData * data){
    char ar[15] = {"terve"};
    data->stringComplete = 1;
    data->stringCounter++;
    data->stringCounter++;
        printf("%c", ar[data->stringCounter]);
}