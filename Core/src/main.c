#include <stdint.h>
#include <miros.h>
#include <stm32f3xx.h>
#include <board_support.h>

uint32_t stack_blinky1[40];
OSThread blinky1;
void main_blinky1(void)
{
	while(1)
	{
		BS_gpioToggle(GPIOE, LED_BLUE);
		osDelay(1000);
	}
}

uint32_t stack_blinky2[40];
OSThread blinky2;
void main_blinky2(void)
{
	while(1)
	{
		BS_gpioToggle(GPIOE, LED_RED);
		osDelay(500);
	}
}

uint32_t stack_idle_thd[40];

int main(void)
{
	BS_init();
	osInit(stack_idle_thd, sizeof(stack_idle_thd));

	osThreadStart(&blinky1, main_blinky1, stack_blinky1, sizeof(stack_blinky1));
	osThreadStart(&blinky2, main_blinky2, stack_blinky2, sizeof(stack_blinky2));

	BS_irqStartup(); // enable interupts after all the initialization is complete 
	while(1)
	{
		// NOthing to do
	}

	//return 0;
}
