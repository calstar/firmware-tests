#include "mbed.h"
#include "pins.h"
#include "util.h"
#include "SDBlockDevice.h"

// SD Card Read and Write Test (Copied from the mbed documentation page)

// Print Redirect 
static BufferedSerial serial_port(DEBUG_TX, DEBUG_RX, 9600);

SDBlockDevice sd(SD_CARD_MOSI, SD_CARD_MISO, SD_CARD_SCK, SD_CARD_nSS, 100000)
uint8_t block[512] = "Hello World!\n";

int main()
{
    // Call the SDBlockDevice instance initialisation method
    if (0 != sd.init()) {
        printf("Init failed \n");
        return -1;
    }
    printf("sd size: %llu\n",         sd.size());
    printf("sd read size: %llu\n",    sd.get_read_size());
    printf("sd program size: %llu\n", sd.get_program_size());
    printf("sd erase size: %llu\n",   sd.get_erase_size());

    // Set the frequency
    if (0 != sd.frequency(5000000)) {
        printf("Error setting frequency \n");
    }

    if (0 != sd.erase(0, sd.get_erase_size())) {
        printf("Error Erasing block \n");
    }

    // Write data block to the device
    if (0 == sd.program(block, 0, 512)) {
        // Read the data block from the device
        if (0 == sd.read(block, 0, 512)) {
            // Print the contents of the block
            printf("%s", block);
        }
    }

    // Call the SDBlockDevice instance de-initialisation method
    sd.deinit();
}
