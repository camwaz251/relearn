#include <stdio.h>
#include <stdlib.h>

typedef enum { OFF = 0, ON = 1, FADE_UP = 2, FADE_DOWN = 3, LED_ERROR = 4} LED_State;

void process_state(LED_State s);
LED_State next_state(LED_State s);

int main(int argc, char* argv[argc+1]) {

    if (argc < 2){
        printf("Error: No Arguments Given.\n");
        printf("Usage: ./problem1 <steps>\n");
        return 1;
    } else if (argc > 2) {
        printf("Error: Too Many Arguments Given.\n");
        printf("Usage: ./problem1 <steps>\n");
        return 1;
    }

    size_t steps = (size_t)atoi(argv[1]); 
    LED_State s = OFF;
    for (size_t i = 0; i < steps; i++) {
        process_state(s);
        s = next_state(s);
    }
    
}
void process_state(LED_State s) {

   switch (s) {
    case OFF:
        printf("LED is set OFF\n");
        break;
    case ON:
        printf("LED is set ON\n");
        break;
    case FADE_UP:
        printf("LED is set FADE_UP\n");
        break;
    case FADE_DOWN:
        printf("LED is set FADE_DOWN\n");
        break;
    default:
        printf("ERROR: Unknown option set.\n");
    }

}

LED_State next_state(LED_State s) {

    switch (s) {
    case OFF:
        return ON;
    case ON:
        return FADE_UP;
    case FADE_UP:
        return FADE_DOWN;
    case FADE_DOWN:
        return OFF;
    default:
        return LED_ERROR;
    }
}

