#include <stdint.h>
#include <miros.h>
#include <stm32f3xx.h>

OSThread * volatile OSCurr; // current thread
OSThread * volatile OSNext; // next thread

void osInit(void)
{
    // set the PendSV priority to the lowest level
    *(uint32_t volatile *)0XE000ED20 |= (0XFF << 16);
}

void osSched(void)
{
    extern OSThread blinky1;
    extern OSThread blinky2;
    
    if(OSCurr == &blinky1)
    {
        OSNext = &blinky2;
    }else{
        OSNext = &blinky1;
    }

    if(OSCurr != OSNext)
        *(uint32_t volatile *)0XE000ED04 = (1U << 28); // trigger pendsv irq
}

void osThreadStart(OSThread *me, osThreadHandler thread_handler, void *stk_sto, uint32_t stk_size)
{
    // start the stack at the highest address and align it at the 8-byte boundary
    uint32_t *sp = (uint32_t *)((((uint32_t)stk_sto + stk_size) / 8) * 8);
    uint32_t *stk_limit;

    *(--sp) = (1<<24); 					   //XPSR
	*(--sp) = (uint32_t)thread_handler;    //PC	
	*(--sp) = 0X0000000EU;				   //LR	
	*(--sp) = 0X0000000CU;				   //R12	
	*(--sp) = 0X00000003U;				   //R3	
	*(--sp) = 0X00000002U;				   //R2	
	*(--sp) = 0X00000001U;				   //R1	
	*(--sp) = 0X00000000U;				   //R0
    // additional cpu registers that also need to be restored when switching context 	
    *(--sp) = 0X0000000BU;				   //R11	
	*(--sp) = 0X0000000AU;				   //R10	
	*(--sp) = 0X00000009U;				   //R9	
	*(--sp) = 0X00000008U;				   //R8	
	*(--sp) = 0X00000007U;				   //R7	
	*(--sp) = 0X00000006U;				   //R6	
    *(--sp) = 0X00000005U;				   //R5	
	*(--sp) = 0X00000004U;				   //R4

    // save the top of the stack at the thread's attribute
    me->sp = sp;

    // round up the bottom of the stack to the 8-byte boundary
    stk_limit = (uint32_t *)(((((uint32_t)stk_sto - 1U) / 8) + 1U) * 8);

    // just a prefill to make it easy to see in memory
    for (sp = sp - 1U; sp >= stk_limit; --sp)
    {
        *sp = 0xDEADBEEFU;
    }
}

__attribute__ ((naked, optimize("-fno-stack-protector")))
void PendSV_Handler(void) {
__asm volatile 
(
    /* __disable_irq(); */
    "  CPSID         I                 \n"

    /* if (OS_curr != (OSThread *)0) { */
    "  LDR           r1,=OSCurr        \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  CBZ           r1,PendSV_restore \n"

    /*     push registers r4-r11 on the stack */
    "  PUSH          {r4-r11}          \n"

    /*     OS_curr->sp = sp; */
    "  LDR           r1,=OSCurr        \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  STR           sp,[r1,#0x00]     \n"
    /* } */

    "PendSV_restore:                   \n"
    /* sp = OS_next->sp; */
    "  LDR           r1,=OSNext        \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           sp,[r1,#0x00]     \n"

    /* OS_curr = OS_next; */
    "  LDR           r1,=OSNext        \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           r2,=OSCurr        \n"
    "  STR           r1,[r2,#0x00]     \n"

    /* pop registers r4-r11 */
    "  POP           {r4-r11}          \n"

    /* __enable_irq(); */
    "  CPSIE         I                 \n"

    /* return to the next thread */
    "  BX            lr                \n"
);
}