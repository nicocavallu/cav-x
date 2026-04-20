/* Main -- Curently for testing functions */
#include <stdint.h>
#include <string.h> 
#include <stdio.h>

#include "uart.h"
#include "timer.h"
#include "spi.h"
#include "pid.h"

//Initialize user functions 
int main(void);


//Blink GPIOB Pin 0 - Green LD1 
int main(void)
{
    // 1. Initialize your timer
    tim2pwm_init();
    
    // 2. Set the duty cycle to 64 (roughly 25% of 255)
    tim2_set_duty(64);

    while(1)
    {
        // Do nothing! Let the hardware timer do all the work in the background.
    }
    
}