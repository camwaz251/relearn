#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// define Flags
#define SR_BUSY        (1U << 0)
#define SR_RX_FULL     (1U << 2)
#define SR_TX_EMPTY    (1U << 4)
#define SR_PARITY_ERR  (1U << 6)
#define SR_FRAME_ERR   (1U << 8)


int main(void){
    uint32_t status_reg = 0x00000055;

    if (status_reg & SR_BUSY){
        printf("SR_BUSY Peripheal is busy\n");
    }
    
    return 0;
}
