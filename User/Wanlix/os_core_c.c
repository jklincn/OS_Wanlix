#include "./os.h"

void WLX_TaskStart(W_TCB * ptrTcb)
{
    STACKREG *tmp_NextTaskStackReg;

    /*获取即将运行的任务的寄存器组地址*/
    tmp_NextTaskStackReg = &ptrTcb->strStackReg;

    /*更新当前运行任务的Tcb*/
    ptrCurrentTcb = ptrTcb;

    WLX_SwitchToTask(tmp_NextTaskStackReg);
}

W_TCB *WLX_TaskCreate(FUNC ptrFunc, void * param,U8 *ptrTaskStack, U32 StackSize)
{
    W_TCB *ptrTcb;

    if (ptrFunc == NULL)
    {
        /*指针为空*/
        return (W_TCB *)NULL;
    }

    if ((ptrTaskStack == NULL) || (StackSize == 0))
    {
        /*栈不合法*/
        return (W_TCB *)NULL;
    }

    ptrTcb = WLX_TaskTcbInit(ptrFunc, param, ptrTaskStack, StackSize);

    return ptrTcb;
}

W_TCB *WLX_TaskTcbInit(FUNC ptrFunc, void * param,U8 *ptrTaskStack, U32 StackSize)
{
    W_TCB *ptrTcb;
    U8 *pucStackBy4;

    /*递减栈*/
    /*创建任务时的栈满地址处存放TCB，需要4字节对齐，此行计算4字节对齐的栈顶地址*/
    pucStackBy4 = (U8 *)(((U32)ptrTaskStack + StackSize) & ALIGN4MASK);

    /*TCB地址即运行时使用的栈开始地址，Cortex内核使用8字节对齐*/
    ptrTcb=(W_TCB*)(((U32)pucStackBy4-sizeof(W_TCB))&ALIGN8MASK);

    WLX_TaskStackInit(ptrTcb,ptrFunc,param);

    return ptrTcb;
}

void WLX_TaskSwitch(W_TCB * ptrTcb)
{
    STACKREG* tmp_CurTaskStackReg;
    STACKREG* tmp_NextTaskStackReg;

    /*获取当前任务的StackReg*/
    tmp_CurTaskStackReg=&ptrCurrentTcb->strStackReg;

    /*获取即将运行任务的StackReg*/
    tmp_NextTaskStackReg=&ptrTcb->strStackReg;

    /*更新当前运行任务的Tcb*/
    ptrCurrentTcb = ptrTcb;

    /*切换任务*/
    WLX_ContextSwitch(tmp_CurTaskStackReg,tmp_NextTaskStackReg);
}

void WLX_TaskStackInit(W_TCB* ptrTcb,FUNC ptrFunc,void * param)
{
	STACKREG *tmp_ptrReg;

    tmp_ptrReg = &ptrTcb->strStackReg;

    tmp_ptrReg->R0 = (U32)param;
    tmp_ptrReg->R4 = 0;
    tmp_ptrReg->R5 = 0;
    tmp_ptrReg->R6 = 0;
    tmp_ptrReg->R7 = 0;
    tmp_ptrReg->R8 = 0;
    tmp_ptrReg->R9 = 0;
    tmp_ptrReg->R10 = 0;
    tmp_ptrReg->R11 = 0;
    tmp_ptrReg->R12 = 0;
    tmp_ptrReg->R13 = (U32)ptrTcb;
    tmp_ptrReg->R14 = (U32)ptrFunc;
    tmp_ptrReg->XPSR = MODE_USR;
}
