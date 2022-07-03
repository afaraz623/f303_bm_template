#ifndef __BOARD_SUPPORT_H__
#define __BOARD_SUPPORT_H__

#define LED_BLUE GPIO_BSRR_BS_8
#define LED_RED GPIO_BSRR_BS_9
#define LED_ORANGE GPIO_BSRR_BS_10
#define LED_GREEN GPIO_BSRR_BS_11

void BS_init(void);

void BS_irqStartup(void);

void BS_gpioToggle(GPIO_TypeDef *gpiox, uint32_t gpio_pin);

#endif