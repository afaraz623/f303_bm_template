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
		BS_delay(1000);
	}
}

uint32_t stack_blinky2[40];
OSThread blinky2;
void main_blinky2(void)
{
	while(1)
	{
		BS_gpioToggle(GPIOE, LED_RED);
		BS_delay(800);
	}
}

uint32_t stack_blinky3[40];
OSThread blinky3;
void main_blinky3(void)
{
	while(1)
	{
		BS_gpioToggle(GPIOE, LED_ORANGE);
		BS_delay(600);
	}
}

uint32_t stack_blinky4[40];
OSThread blinky4;
void main_blinky4(void)
{
	while(1)
	{
		BS_gpioToggle(GPIOE, LED_GREEN);
		BS_delay(400);
	}
}

int main(void)
{
	BS_init();
	osInit();

	osThreadStart(&blinky1, main_blinky1, stack_blinky1, sizeof(stack_blinky1));
	osThreadStart(&blinky2, main_blinky2, stack_blinky2, sizeof(stack_blinky2));
	osThreadStart(&blinky3, main_blinky3, stack_blinky3, sizeof(stack_blinky3));
	osThreadStart(&blinky4, main_blinky4, stack_blinky4, sizeof(stack_blinky4));

	BS_irqStartup(); // enable interupts after all the initialization is complete 
	while(1)
	{
		// NOthing to do
	}

	//return 0;
}
