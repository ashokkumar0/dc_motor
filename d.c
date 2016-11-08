/*
 * Controlling a DC motor using PWM
 */

#include <board.h>
#include <pwm.h>
#include <delay.h>
#include <button.h>
#include <event.h>

enum motor_direction {
	FORWARD,
	REVERSE,
	SPEEDUP,
	        SPEEDDOWN
};

int duty = 0;
int forward_ch = 0;
int reverse_ch = 0;
int state = FORWARD;

void motor_init(int forward_channel, int reverse_channel)
{
	forward_ch = forward_channel;
	reverse_ch = reverse_channel;

	pwm_set_period(forward_ch, 14);
	pwm_set_period(reverse_ch, 14);
}

/**
 * motor_start - start the motor
 * @direction: direction of the motor rotation (FORWARD | REVERSE)
 * Starts the motor in the current direction.
 */
void motor_start(int direction)
{
	if (direction == FORWARD) {
		pwm_set_duty(reverse_ch, 100);
		pwm_set_duty(forward_ch, duty);
	} else {
		pwm_set_duty(forward_ch, 100);
		pwm_set_duty(reverse_ch, duty);
	}

	pwm_start(forward_ch);
	pwm_start(reverse_ch);
}

/**
 * motor_stop - stops motor
 *
 * stops the motor it slowes down eventually
 */
void motor_stop(void)
{
	pwm_set_duty(forward_ch, 100);
	pwm_set_duty(reverse_ch, 100);
}

/**
 * motor_brake - brakes the motor
 *
 * brakes the motor so it stops immediately
 */
void motor_brake(void)
{
	pwm_set_duty(forward_ch, 0);
	pwm_set_duty(reverse_ch, 0);
}

/**
 * motor_chnage_speed - change the motor speed.
 * @speed - Increment or Decrement of speed (SPEEDUP or SPEEDDOWN)
 **/
void motor_change_speed(int speed)
{
	if (speed == SPEEDUP) {
		duty -= 10;
		if (duty < 0)
			duty = 0;
	} else if (speed == SPEEDDOWN) {
		duty += 10;
		if (duty > 100)
			duty = 100;
	}
}

/**
 * handler - Handle the button events
 **/
void handler(void)
{
	char k;

	k = button_getc();

	if (k == 0) {
		state = FORWARD;
		motor_stop();
		mdelay(100);
	} else if (k == 1) {
		state = REVERSE;
		motor_stop();
		mdelay(100);
	} else if (k == 2) {
		motor_change_speed(SPEEDUP);
	} else if (k == 3) {
		motor_change_speed(SPEEDDOWN);
	}

	motor_start(state);
}


int main(void)
{
	board_init();
	pwm_init();
	delay_init();
	button_init();
	motor_init(PWM_CH2, PWM_CH0);

	button_setcb(handler);

	event_poll();

	return 0;
}
