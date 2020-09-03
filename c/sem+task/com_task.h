/*******************************************************************************
 *               Copyright (C) 2008, Huawei Tech. Co., Ltd.
 *                      ALL RIGHTS RESERVED
 *******************************************************************************/

/** @defgroup Module Name
 *  @author  s232191
 *  @version 1.0
 *  @date    2018/11/10 \n
 *  history:\n
 *          1. 2018/11/10, s232191, create this file\n
 *
 *
 * @{
 */

/*! \mainpage
 *
 *  ģ��˵��:\n
 *  \section intro_sec ��ģ���ṩ�Ľӿ�:
 *  - ::
 */

#ifndef __COM_TASK_H__
#define __COM_TASK_H__

/*******************************************************************************
 *   ���ļ���Ҫ����������ͷ�ļ�
*******************************************************************************/
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/sem.h>

//#include <cutils/log.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

/*******************************************************************************
 *   �꿪�ض�������������롢���ԡ���ӡ���أ�
 *******************************************************************************/



/*******************************************************************************
 *   �곣��������
 *******************************************************************************/
#define COM_TASK_OK          (0)
#define COM_TASK_ERR         (-1)
#define COM_TASK_TRUE        (1)
#define COM_TASK_FALSE       (0)
#define COM_TASK_NULL        (0)


/*******************************************************************************
 *   �����������
 *******************************************************************************/



/*******************************************************************************
 *   ö�����Ͷ�����
 *******************************************************************************/
typedef enum tagCOM_TASK_E_MODE
{
    COM_TASK_E_ONCE = 0,
    COM_TASK_E_LOOP,
    COM_TASK_E_UNDEF
} COM_TASK_E_MODE;


/*******************************************************************************
 *   ���ݽṹ���ͺ����������Ͷ���
 *******************************************************************************/
typedef void  (*COM_TASK_FN_CMD)(void *pTask);

/** TASK���������ṹ */
typedef struct tagCOM_TASK_S_CB
{
    void           *pHandle;     /**< ������ƾ�� */
    void           *pUserData;   /**< ����͸�����û����� */
    COM_TASK_FN_CMD pfnClose;    /**< ����ע������ */
    COM_TASK_FN_CMD pfnStart;    /**< ����ָ����� */
    COM_TASK_FN_CMD pfnStop;     /**< ������ͣ���� */
    COM_TASK_FN_CMD pfnSaveStop; /**< ������ͣ���� */
    COM_TASK_FN_CMD pfnStartOnce;/**< ����ָ����� */
    COM_TASK_FN_CMD pfnWaitOnce; /**< ����ָ����� */
} COM_TASK_S_CB, *COM_TASK_S_CB_PTR;

/*******************************************************************************
 *   ȫ�ֱ�������(extern)��
 *******************************************************************************/



/*******************************************************************************
 *   ȫ�ֺ�������(extern)��
 *******************************************************************************/
/** ��������
 *
 *  @param[in]  pfnTaskProc ������ص�����
 *  @param[in]  pTaskParam  �ص������������
 *  @param[out] pstTaskCB   ������ƿ�
 *
 *  @retval ::COM_TASK_OK   ��������ɹ�
 *  @retval ::COM_TASK_ERR  ��������ʧ��
 */
int COM_TASK_Open
(
    COM_TASK_S_CB  *pstTaskCB,
    COM_TASK_FN_CMD pfnTaskProc,
    void           *pTaskParam
);


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __COM_TASK_H__ */

/** @}*/
