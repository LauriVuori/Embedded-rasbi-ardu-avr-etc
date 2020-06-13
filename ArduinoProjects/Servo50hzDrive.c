#include <stdio.h>

int srvdegrees(int degrees);

int main(void){
    int dgr = 0;
    float degree;

    degree = srvdegrees(dgr);

    printf("%f", degree);


}


int srvdegrees(int degrees){
    float Hz = 0;
    Hz = 912000-(48000.0 / 180.0*degrees);

    return Hz;

}