#ifndef __MIROS_H__
#define __MIROS_H__

/* Thread Control Block (TCB) */
typedef struct 
{
    void *sp; // stack pointer
    uint32_t timeout; // timeout delay down-counter
    // more attributes can be added as the rtos grows
}OSThread;

typedef void (*osThreadHandler)();

void osThreadStart(OSThread *me, osThreadHandler thread_handler, void *stk_sto, uint32_t stk_size);

void osInit(void *stk_sto, uint32_t stk_size);

void osSched(void);

void osTick(void);

void osDelay(uint32_t ticks);

void osOnIdle(void);

#endif