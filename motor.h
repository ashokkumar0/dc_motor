#include <pwm.h>
/**
 * motor_init - Initialize the pwm 
 *
 * Initialize the pwm for motor contol
 */
void motor_init(void);

/**
 * motor_start - Generating the pwm signal
 *
 * Generating pwm signal continously
 */
void motor_start(void);

/**
 * motor_rotate - Control the speed and Direction
 * @t1 : terminal1 pwm value
 * @t2 : terminal2 pwm value
 *
 * Control the speed and Direction of Dc motor
 */
void motor_rotate(int t1, int t2);

/**
 * motor_stop - stops the motor
 * 
 * Motor will stop rotating
 */
void motor_stop(void);
