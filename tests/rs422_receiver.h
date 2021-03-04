#include "mbed.h"

// Meant to be run on FC

#define BAUDRATE (115200)

int run_test(){
    BufferedSerial pc_dev(DEBUG_TX, DEBUG_RX, BAUDRATE);
    FILE* pc = fdopen(&pc_dev, "w");
    fprintf(pc, "PC connected.\r\n");

    Bufferederial tpc_dev(TPC_TX, TPC_RX, BAUDRATE);
    FILE* tpc = fdopen(&tpc_dev, "w");
    //char buffer[50];

    while(true){
        //fprintf(pc, "PC connected.\r\n");

        if (tpc.readable())
        {
            //tpc.scanf("%s", &buffer);
            char c = tpc.getc();
            fprintf(pc, "%c", c);
        }
    }
}
