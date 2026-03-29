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
    // 1. Initialize the UART (This now fires up the DMA and DMAMUX!)
    uart3_init();
    tim2_init();
    spi1_init();

    // Initialize LED on PB0 (Optional)
    RCC_C1_AHB4ENR |= (1 << 1); 
    GPIOB_MODER &= ~(3 << 0);
    GPIOB_MODER |=  (1 << 0);

   

    __asm volatile ("cpsie i" : : : "memory");

      // . Create the motor controller in memory
        PID_Controller left_motor;

        // 3. Initialize the variables. 
        // Remember, we scale by 2^16 (65536).
        // Let's set Kp = 1.5, Ki = 0.1, Kd = 0.5
        left_motor.kp = 98304;   // 1.5 * 65536
        left_motor.ki = 6553;    // 0.1 * 65536
        left_motor.kd = 32768;   // 0.5 * 65536

        // Start with clean memory
        left_motor.error_sum = 0;
        left_motor.last_error = 0;

        // Let's say our motor driver takes a max PWM value of 255 (8-bit timer)
        left_motor.max_pwm = 255;

        // 4. Run a simulated test!
        int32_t target_speed = 100;
        int32_t current_speed = 0;
        delay_ms(10000);

        printf("--- PID Test Starting ---\r\n");

    while(1)
    {

        // Loop 10 times to see how the PID responds as we "accelerate"
        for (int i = 0; i < 10; i++) 
        {
            int32_t pwm_command = calculate_pid(&left_motor, target_speed, current_speed);
            
            printf("Current Speed: %ld | PWM Output: %ld\r\n", current_speed, pwm_command);
            
            // Fake physics: Assume the motor sped up a little bit based on our PWM
            current_speed += (pwm_command / 10); 
            GPIOB_ODR |= (1 << 0);
            delay_ms(100);
        }

        delay_ms(1000);          // Wait ~0.5 seconds
        GPIOB_ODR &= ~(1 << 0);    // LED OFF 
    }
}