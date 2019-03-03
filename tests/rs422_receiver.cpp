#include "mbed.h"

// Meant to be run on FC

#define BAUDRATE (115200)

int run_test(){
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
