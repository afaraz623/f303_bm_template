#ifndef __MIROS_H__
#define __MIROS_H__

/* Thread Control Block (TCB) */
typedef struct 
{
    void *sp;
    // more attributes can be added as the rtos grows
}OSThread;

void osSched(void);

void osInit(void);

typedef void (*osThreadHandler)();

void osThreadStart(OSThread *me, osThreadHandler thread_handler, void *stk_sto, uint32_t stk_size);

#endif