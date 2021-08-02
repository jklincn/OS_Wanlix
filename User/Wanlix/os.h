#ifndef OS_H
#define OS_H

#ifdef   OS_GLOBALS
#define  OS_EXT
#else
#define  OS_EXT  extern
#endif

typedef char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef char S8;
typedef short S16;
typedef int S32;

typedef void (*FUNC)(void *);

#define MODE_USR 0x01000000
#define NULL 0
#define ALIGN4MASK 0xFFFFFFFC
#define ALIGN8MASK 0xFFFFFFF8
#define TaskStackSize 400


typedef struct stackreg
{
    U32 R0;
    U32 R4;
    U32 R5;
    U32 R6;
    U32 R7;
    U32 R8;
    U32 R9;
    U32 R10;
    U32 R11;
    U32 R12;
    U32 R13;
    U32 R14;
    U32 XPSR;
} STACKREG;

typedef struct w_tcb
{
    STACKREG strStackReg;
} W_TCB;

/*      Task Start     */
void WLX_TaskStart(W_TCB * ptrTcb);
void WLX_TaskSwitch(W_TCB * ptrTcb);

/*      Task Create     */
W_TCB *WLX_TaskCreate(FUNC ptrFunc, void * param,U8 *ptrTaskStack, U32 StackSize);
W_TCB *WLX_TaskTcbInit(FUNC ptrFunc, void * param,U8 *ptrTaskStack, U32 StackSize);
void WLX_TaskStackInit(W_TCB* ptrTcb,FUNC ptrFunc,void * param);

/*             Asm          */
void  WLX_ContextSwitch(STACKREG * CurTaskStackReg,STACKREG * NextTaskStackReg);
void  WLX_SwitchToTask(STACKREG * NextTaskStackReg);

OS_EXT W_TCB* ptrCurrentTcb;             /* 当前运行的任务的TCB */

#endif

