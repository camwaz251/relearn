#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ADC_MAX_COUNT 4095u

uint32_t adc_to_mv(uint16_t raw);
uint8_t adc_to_mv_percent(uint16_t raw);

int main(void){
  
  const char *titles[3] = {"raw", "mV", "%"};
  printf("%5s|%5s|%5s\n", titles[0], titles[1], titles[2]);
  for (uint16_t raw = 0; raw < ADC_MAX_COUNT; raw += 512){
	  printf("%5u|%5u|%5u\n", raw, adc_to_mv(raw), adc_to_mv_percent(raw));
  }
  printf("%5u|%5u|%5u\n", ADC_MAX_COUNT, adc_to_mv(ADC_MAX_COUNT), adc_to_mv_percent(ADC_MAX_COUNT));
  return EXIT_SUCCESS;
}

uint32_t adc_to_mv(uint16_t raw){
  uint32_t mv = ((uint32_t)raw * 3300) / ADC_MAX_COUNT;
  return mv;
}

uint8_t adc_to_mv_percent(uint16_t raw){
  uint8_t percent = ((uint32_t)raw * 100) / ADC_MAX_COUNT;
  return percent;
}

