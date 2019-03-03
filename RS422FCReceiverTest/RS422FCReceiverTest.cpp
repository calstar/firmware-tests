#include "mbed.h"

#define BAUDRATE (115200)

#define TPC_RX PA_10
#define TPC_TX PA_9

#define DEBUG_RX PA_3
#define DEBUG_TX PA_2

int main(){
    Serial pc(DEBUG_TX, DEBUG_RX);
    pc.baud(BAUDRATE);
    pc.printf("PC connected.\r\n");

    Serial tpc(TPC_TX, TPC_RX);
    tpc.baud(BAUDRATE);
    //char buffer[50];

    while(true){
        //pc.printf("PC connected.\r\n");

        if (tpc.readable())
        {
            //tpc.scanf("%s", &buffer);
            char c = tpc.getc();
            pc.printf("%c", c);
        }
    }
}
