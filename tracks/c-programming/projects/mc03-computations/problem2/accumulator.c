#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



int main(void){
  uint16_t sum16 = 0;
  uint32_t sum32 = 0;
  
  uint16_t samples[32];
  for (size_t i = 0; i < 32; i++) samples[i]=4000;

  for (size_t i = 0; i < 32; i++) sum16 += samples[i];
  for (size_t i = 0; i < 32; i++) sum32 += (uint32_t)samples[i];

  printf("Sum of the uint16_t: %u\nAverage of the uint16_t: %u\n", sum16, sum16/32);
  printf("Sum of the uint32_t: %u\nAverage of the uint32_t: %u\n", sum32, sum32/32);

  return EXIT_SUCCESS;
}
