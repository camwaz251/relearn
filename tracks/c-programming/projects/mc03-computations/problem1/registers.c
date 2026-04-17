#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
uint32_t GPIO_ODR = 0x00000000;

#define PIN_0 (1U << 0)
#define PIN_4 (1U << 4)
#define PIN_7 (1U << 7)
#define PIN_15 (1U << 15)

void reg_set(volatile uint32_t *reg, uint32_t mask){
    *reg |= mask;
}

void reg_clear(volatile uint32_t *reg, uint32_t mask){
    *reg &= ~mask;
}

void reg_toggle(volatile uint32_t *reg, uint32_t mask){
    *reg ^= mask;
}

int reg_read(volatile uint32_t *reg, uint32_t mask){
    return (*reg & mask) != 0;
}

int main(void){
    printf("Address: 0x%08X\n", GPIO_ODR);
    
    reg_set(&GPIO_ODR, PIN_0);
    printf("Set pin 0: 0x%08X\n", GPIO_ODR);
    
    reg_set(&GPIO_ODR, PIN_4);
    printf("Set pin 4: 0x%08X\n", GPIO_ODR);
    
    reg_set(&GPIO_ODR, PIN_7);
    printf("Set pin 7: 0x%08X\n", GPIO_ODR);
    
    reg_set(&GPIO_ODR, PIN_15);
    printf("Set pin 15: 0x%08X\n", GPIO_ODR);
    
    reg_toggle(&GPIO_ODR, PIN_15);
    printf("Toggled pin 15 OFF: 0x%08X\n", GPIO_ODR);
    printf("Pin 15= %d\n", reg_read(&GPIO_ODR, PIN_15));
    
    reg_toggle(&GPIO_ODR, PIN_15);
    printf("Toggled pin 15 ON: 0x%08X\n", GPIO_ODR);
    printf("Pin 15= %d\n", reg_read(&GPIO_ODR, PIN_15));
    
    reg_clear(&GPIO_ODR, PIN_4);
    printf("Clear pin 4: 0x%08X\n", GPIO_ODR);
    printf("Pin 4= %d\n", reg_read(&GPIO_ODR, PIN_4));

    return EXIT_SUCCESS;
    

}
