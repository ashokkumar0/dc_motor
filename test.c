#include <board.h>
#include <delay.h>
#include "motor.h"

int main()
{	
	board_init();
	delay_init();
	motor_init();
	motor_start();
	while (1) {
		motor_rotate(100, 0);
		mdelay(100);
	}	
}
