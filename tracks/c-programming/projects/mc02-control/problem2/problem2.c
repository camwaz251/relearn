#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define DEBOUNCE_THRESHOLD 5
#define SAMPLE_COUNT 25u

void debounce(uint8_t *samples, size_t count);

int main(void) { 
    uint8_t reads[SAMPLE_COUNT] = {
        0,1,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,0
    };

    debounce(reads, SAMPLE_COUNT);

    return EXIT_SUCCESS;
}


void debounce(uint8_t *samples, size_t count){

    uint8_t counter = 0;
    for (size_t i = 0; i < count; i++){
        printf("tick %zu: raw=%u stable_count=%u\n", i, samples[i], counter);
        if (samples[i] == 1){
            counter++;
        } else {
            counter = 0;
        }
        if (counter == DEBOUNCE_THRESHOLD   ){
            printf("*** BUTTON PRESS REGISTERED ***\n");
            counter = 0;
        }
    }
}
