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
    uint32_t status_reg2 = 0x00000101;

    if (status_reg & SR_BUSY){
        printf("SR_BUSY flag is set\n");
    } else {
        printf("SR_BUSY flag is not set\n");
    }

    if (status_reg & SR_RX_FULL){
        printf("SR_RX_FULL flag is set.\n");
    } else {
        printf("SR_RX_FULL flag is not set\n");
    }

    if (status_reg & SR_TX_EMPTY){
        printf("SR_TX_EMPTY flag is set.\n");
    } else {
        printf("SR_TX_EMPTY flag is not set\n");
    }

    if (status_reg & SR_PARITY_ERR){
        printf("SR_PARITY_ERR flag is set.\n");
    } else {
        printf("SR_PARITY_ERR flag is not set\n");
    }

    if (status_reg & SR_FRAME_ERR){
        printf("SR_FRAME_ERR flag is set.\n");
    } else {
        printf("SR_FRAME_ERR flag is not set\n");
    }

   printf("Decoded register: 0x%08X\n", status_reg); 

    if (status_reg2 & SR_BUSY){
        printf("SR_BUSY flag is set\n");
    } else {
        printf("SR_BUSY flag is not set\n");
    }

    if (status_reg2 & SR_RX_FULL){
        printf("SR_RX_FULL flag is set.\n");
    } else {
        printf("SR_RX_FULL flag is not set\n");
    }

    if (status_reg2 & SR_TX_EMPTY){
        printf("SR_TX_EMPTY flag is set.\n");
    } else {
        printf("SR_TX_EMPTY flag is not set\n");
    }

    if (status_reg2 & SR_PARITY_ERR){
        printf("SR_PARITY_ERR flag is set.\n");
    } else {
        printf("SR_PARITY_ERR flag is not set\n");
    }

    if (status_reg2 & SR_FRAME_ERR){
        printf("SR_FRAME_ERR flag is set.\n");
    } else {
        printf("SR_FRAME_ERR flag is not set\n");
    }

   printf("Decoded register: 0x%08X\n", status_reg2); 
    return 0;
}
