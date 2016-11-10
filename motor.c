#include "motor.h"

void motor_init(void)
{
	pwm_init();
	pwm_set_period(PWM_CH0, 14);
	pwm_set_period(PWM_CH2, 14);
	pwm_set_duty(PWM_CH0, 0);
	pwm_set_duty(PWM_CH2, 0);
}

void motor_start(void)
{
	pwm_start(PWM_CH0);
	pwm_start(PWM_CH2);
}

void motor_rotate(int t1, int t2)
{
	pwm_set_duty(PWM_CH2, t1);
	pwm_set_duty(PWM_CH0, t2);
}

void motor_stop(void)
{
	pwm_set_duty(PWM_CH2, 100);
	pwm_set_duty(PWM_CH0, 100);
}
