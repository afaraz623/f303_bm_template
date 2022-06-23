#include <stm32f3xx.h>


#define DELAY 100000

int main(void)
{   
    uint32_t leds_set[] = {
							GPIO_BSRR_BS_8, GPIO_BSRR_BS_9, 
							GPIO_BSRR_BS_10, GPIO_BSRR_BS_11, 
							GPIO_BSRR_BS_12, GPIO_BSRR_BS_13, 
							GPIO_BSRR_BS_14, GPIO_BSRR_BS_15
                          };

    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOEEN);
    SET_BIT(GPIOE->MODER, GPIO_MODER_MODER8_0  | GPIO_MODER_MODER9_0  | 
                          GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | 
                          GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | 
                          GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
    
    while(1)
    {
        for(int i = 0; i < sizeof(leds_set) / sizeof(uint32_t); ++i)
        {
            SET_BIT(GPIOE->BSRR, leds_set[i]);
            for(int volatile i = 0; i < DELAY; ++i);
        }

        for(int i = 0; i < sizeof(leds_set) / sizeof(uint32_t); ++i)
        {
            SET_BIT(GPIOE->BSRR, leds_set[i] << 16U);
            for(int volatile i = 0; i < DELAY; ++i);
        }   
    }
    
    return 0;
}