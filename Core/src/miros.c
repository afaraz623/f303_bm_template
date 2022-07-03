#include <stdint.h>
#include <miros.h>
#include <stm32f3xx.h>

#define MAX_THREADS 32

OSThread * volatile OSCurr; // current thread
OSThread * volatile OSNext; // next thread
OSThread *OSThreadArray[MAX_THREADS + 1]; // to keep track of running threads
uint8_t num_thds; // number of threads started so far
uint8_t cur_thd_idx;
uint32_t ready_set; // bitmask for threads that are ready to run

__attribute__((naked)) void assert_failed (char const *file, int line);

OSThread idle_thd;
void idle(void)
{
	while(1)
	{
        osOnIdle();
	}
}

void osInit(void *stk_sto, uint32_t stk_size)
{
    // set the PendSV priority to the lowest level
    *(uint32_t volatile *)0XE000ED20 |= (0XFF << 16);

	osThreadStart(&idle_thd, idle, stk_sto, stk_size);

}

void osSched(void)
{
    if(ready_set == 0U) // if all the threads are blocked
        cur_thd_idx = 0U; // set current thread to idle
    else 
    {
        do
        {
            ++cur_thd_idx;
            if(cur_thd_idx == num_thds)
                cur_thd_idx = 1U; // wrap around to 1 to skip the idle thread
        }while((ready_set & (1U << (cur_thd_idx - 1U))) == 0U); // keep looking for the ready thread
        
    }

    OSNext = OSThreadArray[cur_thd_idx];

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

    if(num_thds < MAX_THREADS)
    {
        OSThreadArray[num_thds] = me;
        
        if(num_thds > 0)
            ready_set |= (1U << (num_thds - 1U)); // when the thread starts, by default its made unblocked. Makes senses....
        
        ++num_thds;
    }
    else
        assert_failed("Number of threads exceeded", __LINE__);
}

void osTick(void)
{
    uint8_t n;
    for(n = 1U; n < num_thds; ++n)
    {
        if(OSThreadArray[n]->timeout != 0U) // check if the threads timeout counter is 0
        {
            --OSThreadArray[n]->timeout; // if not, decrement it 
            if(OSThreadArray[n]->timeout == 0U) // check again
                ready_set |= (1U << (n - 1U));  // if its 0, set the thread's ready bit to 1 to indicate that its been unblocked
        }
    }
}

void osDelay(uint32_t ticks)
{
    __disable_irq();
    if(OSCurr != OSThreadArray[0]) // make sure we are not blocking the idle thread
    {
        OSCurr->timeout = ticks; // transfer ticks var into the threads timeout var
        ready_set &= ~(1U << (cur_thd_idx - 1U)); // clear the ready bit of the thread to indicate that it is blocked
        osSched(); // switch the context away from the thread
    }
    __enable_irq();
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