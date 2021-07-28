#include "./app.h"

W_TCB *TaskStartTcb; /* 任务1的TCB指针 */
W_TCB *Task1Tcb;     /* 任务1的TCB指针 */
W_TCB *Task2Tcb;     /* 任务2的TCB指针 */
W_TCB *Task3Tcb;     /* 任务3的TCB指针 */

U8 TaskStartStack[TaskStackSize];
U8 Task1Stack[TaskStackSize];
U8 Task2Stack[TaskStackSize];
U8 Task3Stack[TaskStackSize];

int main(void)
{

    TaskStartTcb = WLX_TaskCreate(TaskStart, (void *)NULL, TaskStartStack, TaskStackSize);

    WLX_TaskStart(TaskStartTcb);
}

void TaskStart(void *param)
{
    U32 print_times1;
    U32 print_times2;
    U32 print_times3;

    BSP_Init();

    Delay();

    print_times1 = 1;
    Task1Tcb = WLX_TaskCreate(Task1, (void *)&print_times1, Task1Stack, TaskStackSize);

    print_times2 = 2;
    Task2Tcb = WLX_TaskCreate(Task2, (void *)&print_times2, Task2Stack, TaskStackSize);

    print_times3 = 3;
    Task3Tcb = WLX_TaskCreate(Task3, (void *)&print_times3, Task3Stack, TaskStackSize);

    WLX_TaskStart(Task1Tcb);
}

void Task1(void *param)
{
    U32 print_times = *((U32 *)param);
    U32 tmp_cnt;

    while (1)
    {
        Delay();

        for (tmp_cnt = 0; tmp_cnt < print_times; tmp_cnt++)
            printf("Task1 is running!");

        printf("\n\n");

        WLX_TaskSwitch(Task3Tcb);
    }
}

void Task2(void *param)
{
    U32 print_times = *((U32 *)param);
    U32 tmp_cnt;

    while (1)
    {
        Delay();

        for (tmp_cnt = 0; tmp_cnt < print_times; tmp_cnt++)
            printf("Task2 is running!");

        printf("\n\n");

        WLX_TaskSwitch(Task1Tcb);
    }
}
void Task3(void *param)
{

    U32 print_times = *((U32 *)param);
    U32 tmp_cnt;

    while (1)
    {
        Delay();

        for (tmp_cnt = 0; tmp_cnt < print_times; tmp_cnt++)
            printf("Task3 is running!");

        printf("\n\n");

        WLX_TaskSwitch(Task2Tcb);
    }
}
void Delay(void)
{
    int i;
    for (i = 0xFFFFFF; i > 0; i--)
        ;
}
