#include <stdint.h>
#include <system_stm32f3xx.h>

//extern int __stack_start__;
extern int __stack_end__;

__attribute__ ((naked)) void assert_failed(char const *module, int loc);

/* Function prototypes -----------------------------------------------------*/
void Default_Handler(void);  
void Reset_Handler(void);    
void SystemInit(void);

/* Weak exception handler prototypes ---------------------------------------*/
/* Cortex-M Processor fault exceptions... */
void NMI_Handler                  (void) __attribute__ ((weak));
void HardFault_Handler            (void) __attribute__ ((weak));
void MemManage_Handler            (void) __attribute__ ((weak));
void BusFault_Handler             (void) __attribute__ ((weak));
void UsageFault_Handler           (void) __attribute__ ((weak));

/* Cortex-M Processor non-fault exceptions... */
void SVC_Handler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));

/* External exceptions... */
void WWDG_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_TSC_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_HP_CAN_TX_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_LP_CAN_RX0_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN_RX1_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN_SCE_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM17_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void USBWakeUp_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC3_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel1_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel4_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel5_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC4_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP1_2_3_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP4_5_6_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP7_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_HP_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_LP_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USBWakeUp_RMP_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));


/* Vector Table ------------------------------------------------------------*/
__attribute__ ((section(".isr_vector")))
int const g_pfnVectors[] = {
    (uint32_t)&__stack_end__,     
    (uint32_t)&Reset_Handler,     
    (uint32_t)&NMI_Handler,       
    (uint32_t)&HardFault_Handler, 
    (uint32_t)&MemManage_Handler, 
    (uint32_t)&BusFault_Handler,  
    (uint32_t)&UsageFault_Handler,
    0,                            
    0,                            
    0,                            
    0,                            
    (uint32_t)&SVC_Handler,       
    (uint32_t)&DebugMon_Handler,  
    0,                            
    (uint32_t)&PendSV_Handler,    
    (uint32_t)&SysTick_Handler,   
    (uint32_t)&WWDG_IRQHandler,
	(uint32_t)&PVD_IRQHandler,
	(uint32_t)&TAMP_STAMP_IRQHandler,
	(uint32_t)&RTC_WKUP_IRQHandler,
	(uint32_t)&FLASH_IRQHandler,
	(uint32_t)&RCC_IRQHandler,
	(uint32_t)&EXTI0_IRQHandler,
	(uint32_t)&EXTI1_IRQHandler,
	(uint32_t)&EXTI2_TSC_IRQHandler,
	(uint32_t)&EXTI3_IRQHandler,
	(uint32_t)&EXTI4_IRQHandler,
	(uint32_t)&DMA1_Channel1_IRQHandler,
	(uint32_t)&DMA1_Channel2_IRQHandler,
	(uint32_t)&DMA1_Channel3_IRQHandler,
	(uint32_t)&DMA1_Channel4_IRQHandler,
	(uint32_t)&DMA1_Channel5_IRQHandler,
	(uint32_t)&DMA1_Channel6_IRQHandler,
	(uint32_t)&DMA1_Channel7_IRQHandler,
	(uint32_t)&ADC1_2_IRQHandler,
	(uint32_t)&USB_HP_CAN_TX_IRQHandler,
	(uint32_t)&USB_LP_CAN_RX0_IRQHandler,
	(uint32_t)&CAN_RX1_IRQHandler,
	(uint32_t)&CAN_SCE_IRQHandler,
	(uint32_t)&EXTI9_5_IRQHandler,
	(uint32_t)&TIM1_BRK_TIM15_IRQHandler,
	(uint32_t)&TIM1_UP_TIM16_IRQHandler,
	(uint32_t)&TIM1_TRG_COM_TIM17_IRQHandler,
	(uint32_t)&TIM1_CC_IRQHandler,
	(uint32_t)&TIM2_IRQHandler,
	(uint32_t)&TIM3_IRQHandler,
	(uint32_t)&TIM4_IRQHandler,
	(uint32_t)&I2C1_EV_IRQHandler,
	(uint32_t)&I2C1_ER_IRQHandler,
	(uint32_t)&I2C2_EV_IRQHandler,
	(uint32_t)&I2C2_ER_IRQHandler,
	(uint32_t)&SPI1_IRQHandler,
	(uint32_t)&SPI2_IRQHandler,
	(uint32_t)&USART1_IRQHandler,
	(uint32_t)&USART2_IRQHandler,
	(uint32_t)&USART3_IRQHandler,
	(uint32_t)&EXTI15_10_IRQHandler,
	(uint32_t)&RTC_Alarm_IRQHandler,
	(uint32_t)&USBWakeUp_IRQHandler,
	(uint32_t)&TIM8_BRK_IRQHandler,
	(uint32_t)&TIM8_UP_IRQHandler,
	(uint32_t)&TIM8_TRG_COM_IRQHandler,
	(uint32_t)&TIM8_CC_IRQHandler,
	(uint32_t)&ADC3_IRQHandler,
	0,
	0,
	0,
	(uint32_t)&SPI3_IRQHandler,
	(uint32_t)&UART4_IRQHandler,
	(uint32_t)&UART5_IRQHandler,
	(uint32_t)&TIM6_DAC_IRQHandler,
	(uint32_t)&TIM7_IRQHandler,
	(uint32_t)&DMA2_Channel1_IRQHandler,
	(uint32_t)&DMA2_Channel2_IRQHandler,
	(uint32_t)&DMA2_Channel3_IRQHandler,
	(uint32_t)&DMA2_Channel4_IRQHandler,
	(uint32_t)&DMA2_Channel5_IRQHandler,
	(uint32_t)&ADC4_IRQHandler,
	0,
	0,
	(uint32_t)&COMP1_2_3_IRQHandler,
	(uint32_t)&COMP4_5_6_IRQHandler,
	(uint32_t)&COMP7_IRQHandler,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(uint32_t)&USB_HP_IRQHandler,
	(uint32_t)&USB_LP_IRQHandler,
	(uint32_t)&USBWakeUp_RMP_IRQHandler,
	0,
	0,
	0,
	0,
	(uint32_t)&FPU_IRQHandler
};


/* reset handler -----------------------------------------------------------*/
void Reset_Handler(void) {
    extern int main(void);
    extern int __libc_init_array(void);
    extern unsigned __data_start;       // start of .data in the linker script */
    extern unsigned __data_end__;       // end of .data in the linker script */
    extern unsigned const __data_load;  // initialization values for .data  */
    extern unsigned __bss_start__;      // start of .bss in the linker script */
    extern unsigned __bss_end__;        // end of .bss in the linker script */
    extern void software_init_hook(void) __attribute__((weak));

    unsigned const *src;
    unsigned *dst;

    /* copy the data segment initializers from flash to RAM... */
    src = &__data_load;
    for (dst = &__data_start; dst < &__data_end__; ++dst, ++src) {
        *dst = *src;
    }

    /* zero fill the .bss segment in RAM... */
    for (dst = &__bss_start__; dst < &__bss_end__; ++dst) {
        *dst = 0;
    }

    SystemInit();                       // CMSIS system initialization 
    __libc_init_array();
    (void)main();                       // application's entry point; should never return!

    /* the previous code should not return, but assert just in case... */
    //assert_failed("Reset_Handler", __LINE__);
}


/* fault exception handlers ------------------------------------------------*/
__attribute__((naked)) void NMI_Handler(void);
void NMI_Handler(void) {
    while(1);
}

__attribute__((naked)) void MemManage_Handler(void);
void MemManage_Handler(void) {
    while(1);
}

__attribute__((naked)) void HardFault_Handler(void);
void HardFault_Handler(void) {
    while(1);
}

__attribute__((naked)) void BusFault_Handler(void);
void BusFault_Handler(void) {
    while(1);
}

__attribute__((naked)) void UsageFault_Handler(void);
void UsageFault_Handler(void) {
    while(1);
}

__attribute__((naked)) void Default_Handler(void);
void Default_Handler(void) {
    while(1);
}