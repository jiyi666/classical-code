/*******************************************************************************
 *               Copyright (C) 2008, Huawei Tech. Co., Ltd.
 *                      ALL RIGHTS RESERVED
 *******************************************************************************/

/** @defgroup Module Name

 *  @author  s232191
 *  @version 1.0
 *  @date    2018/11/10 \n

 *  history:\n
 *          1. 2018/11/10, s232191, create this file\n\n
 *
 *  此模块的详细描述...
 *
 * @{
 */

/*******************************************************************************/
/*  包含头文件。次序为:                                                      */
/*  全局头文件(公共头文件, 其中包含了VTOP/TSA系统标准头文件)                 */
/*  其它模块的公共头文件                                                     */
/*  模块自身的公共头文件                                                     */
/*  文件自身的私有头文件                                                     */
/*******************************************************************************/
#include "com_task.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/** TASK参数描述结构 */
typedef struct tagCOM_TASK_S_OBJ
{
    int         bRun;       /**< 任务运行标志 */
    int         bPause;     /**< 任务暂停标志 */
    int         eMode;      /**< 任务运行模式 */
    pthread_t   pthrCtrlId; /**< 任务线程标识 */
    pthread_t   pthrTaskId; /**< 任务线程标识 */
    sem_t       semPause;   /**< 任务暂停信号，控制线程的暂停 */
    sem_t       semResume;  /**< 任务恢复信号，控制线程的运行 */
    void       *pProcData;  /**< 任务处理函数参数 */
    COM_TASK_FN_CMD pfnProc;     /**< 任务处理函数 */
} COM_TASK_S_OBJ, *COM_TASK_S_OBJ_PTR;


int sem_wait2(sem_t *sem)
{
    int ret = COM_TASK_OK;

    do
    {
        errno = 0;
        ret = sem_wait(sem);
        if (COM_TASK_OK == ret)
        {
            break;
        }
        else
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }while (1);

    return ret;
}


/** 任务处理回调函数
 *
 *  @param[in] pTask   任务句柄
 */
void *comTaskProc(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    while (COM_TASK_TRUE == pstTask->bRun)
    {
        /* 任务控制处理 */
        if (COM_TASK_TRUE == pstTask->bPause)
        {
            if (pstTask->pthrCtrlId != pstTask->pthrTaskId)
            {
                sem_post(&pstTask->semPause);
            }
            printf("wait for task!\n");
            sem_wait2(&pstTask->semResume);
            pstTask->bPause = COM_TASK_FALSE;
            continue;
        }

        /* 执行用户回调函数 */
        pstTask->pfnProc(pstTask->pProcData);

        if (COM_TASK_E_ONCE == pstTask->eMode)
        {
            pstTask->bPause = COM_TASK_TRUE;
        }
    }

    return COM_TASK_OK;
}

/** 恢复任务循环执行
 *
 *  @param[in] pTask   任务句柄
 */
void comTaskStart(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    /* 恢复被暂停的任务到运行状态 */
    if ((COM_TASK_TRUE == pstTask->bRun) && (COM_TASK_TRUE == pstTask->bPause))
    {
        sem_post(&pstTask->semResume);
    }

    pstTask->eMode = COM_TASK_E_LOOP;
    return;
}


/** 暂停任务
 *
 *  @param[in] pTask   任务句柄
 */
void comTaskStop(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    /* 设置并等待任务进入暂停状态 */
    if ((COM_TASK_TRUE == pstTask->bRun) && (COM_TASK_FALSE == pstTask->bPause))
    {
        pstTask->bPause = COM_TASK_TRUE;
        sem_wait2(&pstTask->semPause);
    }

    return;
}

/** 恢复任务执行一次
 *
 *  @param[in] pTask   任务句柄
 */
void comTaskStartOnce(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    /* 设置任务运行模式为执行一次并自动停止 */
    pstTask->eMode = COM_TASK_E_ONCE;

    /* 恢复被暂停的任务到运行状态 */
    if ((COM_TASK_TRUE == pstTask->bRun) && (COM_TASK_TRUE == pstTask->bPause))
    {
        sem_post(&pstTask->semResume);
    }

    return;
}

/** 等待执行一次结束
 *
 *  @param[in] pTask   任务句柄
 */
void comTaskWaitOnce(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    if (COM_TASK_E_ONCE == pstTask->eMode)
    {
        sem_wait2(&pstTask->semPause);
        pstTask->eMode = COM_TASK_E_LOOP;
    }

    return;
}

/** 暂停任务
 *  任务自动进入休眠状态
 *
 *  @param[in] pTask   任务句柄
 */
void comTaskSaveStop(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    /* 设置并等待任务进入暂停状态 */
    if ((COM_TASK_TRUE == pstTask->bRun) && (COM_TASK_FALSE == pstTask->bPause))
    {
        pstTask->pthrCtrlId = pthread_self();

        pstTask->bPause = COM_TASK_TRUE;
        printf("pause task!\n");
        /* 如果不是线程内部暂停，此时线程外部需要等待直到任务真正停下来*/
        if (pstTask->pthrCtrlId != pstTask->pthrTaskId)
        {
            sem_wait2(&pstTask->semPause);
        }
    }

    return;
}

/** 撤销任务
 *
 *  @param[in] pTask   任务句柄
 */
void comTaskClose(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    pstTask->bRun = COM_TASK_FALSE;

    if (COM_TASK_TRUE == pstTask->bPause)
    {
        sem_post(&pstTask->semResume);
    }

    pthread_join(pstTask->pthrTaskId, 0);

    sem_destroy(&pstTask->semResume);
    sem_destroy(&pstTask->semPause);
    free(pstTask);

    return;
}


/** 创建任务
 *
 *  @param[in]  pfnTaskProc 任务处理回调函数
 *  @param[in]  pTaskParam  回调函数输入参数
 *  @param[out] pstTaskCB   任务控制块
 *
 *  @retval ::COM_TASK_OK   创建任务成功
 *  @retval ::COM_TASK_ERR  创建任务失败
 */
int COM_TASK_Open(COM_TASK_S_CB   *pstTaskCB,
                  COM_TASK_FN_CMD  pfnTaskProc,
                  void            *pTaskParam)
{
    int  ret = 0;

    COM_TASK_S_OBJ *pstTask = COM_TASK_NULL;

    if ((COM_TASK_NULL == pstTaskCB) || (COM_TASK_NULL == pfnTaskProc))
    {
        fprintf(stderr, "\n[%s,%d] COM_TASK_Open invalid params.", __FILE__, __LINE__);
        return COM_TASK_ERR;
    }

    pstTask = (COM_TASK_S_OBJ *)malloc(sizeof(COM_TASK_S_OBJ));
    if (COM_TASK_NULL == pstTask)
    {
        fprintf(stderr, "\n[%s,%d] COM_TASK_Open malloc failed.", __FILE__, __LINE__);
        return COM_TASK_ERR;
    }

    pstTask->bRun   = COM_TASK_TRUE;
    pstTask->bPause = COM_TASK_TRUE;
    pstTask->eMode  = COM_TASK_E_LOOP;
    pstTask->pfnProc    = pfnTaskProc;
    pstTask->pProcData  = pTaskParam;
    pstTask->pthrCtrlId = 0xFFFFFFFF;

    pstTaskCB->pHandle      = (void *)pstTask;
    pstTaskCB->pfnClose     = comTaskClose;
    pstTaskCB->pfnStart     = comTaskStart;
    pstTaskCB->pfnStop      = comTaskStop;
    pstTaskCB->pfnSaveStop  = comTaskSaveStop;
    pstTaskCB->pfnStartOnce = comTaskStartOnce;
    pstTaskCB->pfnWaitOnce  = comTaskWaitOnce;

    ret = sem_init(&pstTask->semResume, 0, 0);
    if (COM_TASK_OK != ret)
    {
        free(pstTask);
        return COM_TASK_ERR;
    }

    ret = sem_init(&pstTask->semPause, 0, 0);
    if (COM_TASK_OK != ret)
    {
        sem_destroy(&pstTask->semResume);
        free(pstTask);
        return COM_TASK_ERR;
    }

    ret = pthread_create(&pstTask->pthrTaskId,
                         COM_TASK_NULL,
                         comTaskProc, (void *)pstTask);
    if (COM_TASK_OK != ret)
    {
        sem_destroy(&pstTask->semPause);
        sem_destroy(&pstTask->semResume);
        free(pstTask);
        return COM_TASK_ERR;
    }

    /* 这个地方等待是保证上面创建的线程已经运行起来了 */
    sem_wait2(&pstTask->semPause);

    return COM_TASK_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/** @}*/
