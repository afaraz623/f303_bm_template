#include <stdint.h>
#include <miros.h>
#include <stm32f3xx.h>
#include <board_support.h>

uint32_t stack_blinky1[40];
OSThread blinky1;
void main_blinky1()
{
	while(1)
	{
		BS_gpioToggle(GPIOE, LED_BLUE);
		BS_delay(1000);
	}
}

uint32_t stack_blinky2[40];
OSThread blinky2;
void main_blinky2()
{
	while(1)
	{
		BS_gpioToggle(GPIOE, LED_RED);
		BS_delay(1000);
	}
}

int main()
{
	BS_init();
	osInit();

	osThreadStart(&blinky1, main_blinky1, stack_blinky1, sizeof(stack_blinky1));
	osThreadStart(&blinky2, main_blinky2, stack_blinky2, sizeof(stack_blinky2));

	while(1)
	{
		// NOthing to do
	}

	//return 0;
}
