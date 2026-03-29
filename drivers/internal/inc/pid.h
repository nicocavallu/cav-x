#ifndef PID_H
#define PID_H

#include <stdint.h>

// Controller struct
typedef struct {
    int32_t kp;          // Proportional gain (Scaled by 2^16)
    int32_t ki;          // Integral gain (Scaled by 2^16)
    int32_t kd;          // Derivative gain (Scaled by 2^16)
    
    int32_t error_sum;   // Memory of past errors (for Integral)
    int32_t last_error;  // Memory of previous error (for Derivative)
    
    int32_t max_pwm;     // Safety limit 
} PID_Controller;

// Function Prototype
int32_t calculate_pid(PID_Controller *pid, int32_t target_speed, int32_t current_speed);

#endif // PID_H