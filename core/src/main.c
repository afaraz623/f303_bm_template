#include <stm32f3xx.h>

int main(void)
{
  	SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOEEN); 			// Enable GPIOE clock
  	SET_BIT(GPIOE->MODER, GPIO_MODER_MODER8_0);			// Set GPIOE mode to general purpose output mode
  	SET_BIT(GPIOE->OSPEEDR, GPIO_OSPEEDER_OSPEEDR8);	// Set GPIOE to high speed 
  	SET_BIT(GPIOE->PUPDR, GPIO_PUPDR_PUPDR8_1);			// Set GPIOE to pull down
   
  	while (1)
  	{
		SET_BIT(GPIOE->BSRR, GPIO_BSRR_BS_8);	
		for (int i = 0; i < 1000000; i++);		
		SET_BIT(GPIOE->BSRR, GPIO_BSRR_BR_8);
		for (int i = 0; i < 1000000; i++);		
  	}

  	return 0;
}