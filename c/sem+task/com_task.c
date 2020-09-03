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
 *  ��ģ�����ϸ����...
 *
 * @{
 */

/*******************************************************************************/
/*  ����ͷ�ļ�������Ϊ:                                                      */
/*  ȫ��ͷ�ļ�(����ͷ�ļ�, ���а�����VTOP/TSAϵͳ��׼ͷ�ļ�)                 */
/*  ����ģ��Ĺ���ͷ�ļ�                                                     */
/*  ģ������Ĺ���ͷ�ļ�                                                     */
/*  �ļ������˽��ͷ�ļ�                                                     */
/*******************************************************************************/
#include "com_task.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/** TASK���������ṹ */
typedef struct tagCOM_TASK_S_OBJ
{
    int         bRun;       /**< �������б�־ */
    int         bPause;     /**< ������ͣ��־ */
    int         eMode;      /**< ��������ģʽ */
    pthread_t   pthrCtrlId; /**< �����̱߳�ʶ */
    pthread_t   pthrTaskId; /**< �����̱߳�ʶ */
    sem_t       semPause;   /**< ������ͣ�źţ������̵߳���ͣ */
    sem_t       semResume;  /**< ����ָ��źţ������̵߳����� */
    void       *pProcData;  /**< ������������ */
    COM_TASK_FN_CMD pfnProc;     /**< �������� */
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


/** ������ص�����
 *
 *  @param[in] pTask   ������
 */
void *comTaskProc(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    while (COM_TASK_TRUE == pstTask->bRun)
    {
        /* ������ƴ��� */
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

        /* ִ���û��ص����� */
        pstTask->pfnProc(pstTask->pProcData);

        if (COM_TASK_E_ONCE == pstTask->eMode)
        {
            pstTask->bPause = COM_TASK_TRUE;
        }
    }

    return COM_TASK_OK;
}

/** �ָ�����ѭ��ִ��
 *
 *  @param[in] pTask   ������
 */
void comTaskStart(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    /* �ָ�����ͣ����������״̬ */
    if ((COM_TASK_TRUE == pstTask->bRun) && (COM_TASK_TRUE == pstTask->bPause))
    {
        sem_post(&pstTask->semResume);
    }

    pstTask->eMode = COM_TASK_E_LOOP;
    return;
}


/** ��ͣ����
 *
 *  @param[in] pTask   ������
 */
void comTaskStop(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    /* ���ò��ȴ����������ͣ״̬ */
    if ((COM_TASK_TRUE == pstTask->bRun) && (COM_TASK_FALSE == pstTask->bPause))
    {
        pstTask->bPause = COM_TASK_TRUE;
        sem_wait2(&pstTask->semPause);
    }

    return;
}

/** �ָ�����ִ��һ��
 *
 *  @param[in] pTask   ������
 */
void comTaskStartOnce(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    /* ������������ģʽΪִ��һ�β��Զ�ֹͣ */
    pstTask->eMode = COM_TASK_E_ONCE;

    /* �ָ�����ͣ����������״̬ */
    if ((COM_TASK_TRUE == pstTask->bRun) && (COM_TASK_TRUE == pstTask->bPause))
    {
        sem_post(&pstTask->semResume);
    }

    return;
}

/** �ȴ�ִ��һ�ν���
 *
 *  @param[in] pTask   ������
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

/** ��ͣ����
 *  �����Զ���������״̬
 *
 *  @param[in] pTask   ������
 */
void comTaskSaveStop(void *pTask)
{
    COM_TASK_S_OBJ *pstTask = (COM_TASK_S_OBJ *)pTask;

    /* ���ò��ȴ����������ͣ״̬ */
    if ((COM_TASK_TRUE == pstTask->bRun) && (COM_TASK_FALSE == pstTask->bPause))
    {
        pstTask->pthrCtrlId = pthread_self();

        pstTask->bPause = COM_TASK_TRUE;
        printf("pause task!\n");
        /* ��������߳��ڲ���ͣ����ʱ�߳��ⲿ��Ҫ�ȴ�ֱ����������ͣ����*/
        if (pstTask->pthrCtrlId != pstTask->pthrTaskId)
        {
            sem_wait2(&pstTask->semPause);
        }
    }

    return;
}

/** ��������
 *
 *  @param[in] pTask   ������
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


/** ��������
 *
 *  @param[in]  pfnTaskProc ������ص�����
 *  @param[in]  pTaskParam  �ص������������
 *  @param[out] pstTaskCB   ������ƿ�
 *
 *  @retval ::COM_TASK_OK   ��������ɹ�
 *  @retval ::COM_TASK_ERR  ��������ʧ��
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

    /* ����ط��ȴ��Ǳ�֤���洴�����߳��Ѿ����������� */
    sem_wait2(&pstTask->semPause);

    return COM_TASK_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/** @}*/
