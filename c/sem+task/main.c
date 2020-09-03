#include <stdio.h>
#include "com_task.h"

/* 编译指令为：gcc -I ./ main.c com_task.c -o test -lpthread */

//#define TEST_ONCE_TASK

/* 任务控制结构体 */
COM_TASK_S_CB     mTask;


/* 任务执行函数 */
void Task_proc()
{
    static int count = 0;
    printf("执行第[%d]任务!\n", count++);
}

int main(void)
{
    int ret = -1, loopMax = 3, count;
    
    /* 初始化任务 */
    ret = COM_TASK_Open(&mTask, Task_proc, NULL);
    if (COM_TASK_OK != ret)
    {
        printf("[%s,%d] Create Task failed.", __FILE__, __LINE__);
        return (-1);
    }

#ifdef TEST_ONCE_TASK
    /* 测试：完整执行一次任务（包括等待执行完成） */
    for (count = 0; count < loopMax; count++)
    {
        mTask.pfnStartOnce(mTask.pHandle);
        mTask.pfnWaitOnce(mTask.pHandle);

    }
#else    
    /* 测试：任务的循环执行:开始->暂停->继续->停止 */
    mTask.pfnStart(mTask.pHandle);
    usleep(10);
    mTask.pfnSaveStop(mTask.pHandle);
    mTask.pfnStart(mTask.pHandle);
    usleep(30);
    mTask.pfnStop(mTask.pHandle);
#endif
    
    /* 结束任务 */
    mTask.pfnClose(mTask.pHandle);
    
    return 0;
}