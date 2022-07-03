/* Board support source file consists of board specific peripheral initialization & other functional definitions */
#include <stdint.h>
#include <stm32f3xx.h>
#include <board_support.h>
#include <miros.h>

#define TICKS_PER_MS        1000U
#define BS_TO_BR_OFFSET     16U


/* initial peripheral setup */
void BS_init(void)
{
    // gpioe on and set pins to gp output
    RCC->AHBENR |= RCC_AHBENR_GPIOEEN;

	GPIOE->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0;
}

void BS_irqStartup(void)
{
    SysTick_Config(SystemCoreClock / TICKS_PER_MS); 

    NVIC_SetPriority(SysTick_IRQn, 0U); // set systick priority to above pendsv irq
	__enable_irq();
}

void BS_gpioToggle(GPIO_TypeDef *gpiox, uint32_t gpio_pin)
{
    uint32_t odr;
    odr = gpiox->ODR;
    gpiox->BSRR = ((odr & gpio_pin) << BS_TO_BR_OFFSET) | (~odr & gpio_pin);
}

void SysTick_Handler()
{
    osTick();

    __disable_irq();
    osSched(); // crtical section
    __enable_irq();
}

void osOnIdle(void)
{
    BS_gpioToggle(GPIOE, LED_GREEN);
    __WFI(); // stop the cpu and wait for an interrupt
}

__attribute__((naked)) void assert_failed (char const *file, int line) 
{
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}