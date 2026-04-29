#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

int main (void){

    /* const char* names[] = {"char","short","int","long","long long","uint8_t","uint16_t",
                    "float","double","void *"};
    */                    
    printf("Signed:\n");
    printf("%-12s %2zu bytes min=%d bytes max=%d\n", "int8_t", sizeof(int8_t), (long long)INT8_MIN, (long long)INT8_MAX);

    return EXIT_SUCCESS;
}


