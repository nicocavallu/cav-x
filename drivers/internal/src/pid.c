/* 
This source file implements a PID controller to control the pwm output of a motor
PID utilizes fixed-point math (scaled by 2^16) to optimize hardware speed
*/

#include "pid.h"

int32_t calculate_pid(PID_Controller *pid, int32_t target_speed, int32_t current_speed)
{   
    // initialize variables 
    int32_t error, p_term, i_term, d_term, output;

    // Calculate current error and proportional gain
    error = target_speed - current_speed;
    p_term = pid->kp * error;
    
    // Update error sum and integral gain 
    pid->error_sum+=error;
    i_term = pid->ki * pid->error_sum;

    // Calculate derivative gain and update last error 
    d_term = pid->kd *(error - pid->last_error);
    pid->last_error = error;

    // Calculate total gain
    output = p_term + i_term + d_term;

    // Bit shift 
    output = (output >> 16);

    if (output > pid->max_pwm)
    {
        output = pid->max_pwm;
    }
    else if (output < -pid->max_pwm)
    {
        output = -pid->max_pwm;
    } 

    return output;
    
}