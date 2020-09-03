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
 *  模块说明:\n
 *  \section intro_sec 本模块提供的接口:
 *  - ::
 */

#ifndef __COM_TASK_H__
#define __COM_TASK_H__

/*******************************************************************************
 *   本文件需要包含的其它头文件
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
 *   宏开关定义区（例如编译、调试、打印开关）
 *******************************************************************************/



/*******************************************************************************
 *   宏常量定义区
 *******************************************************************************/
#define COM_TASK_OK          (0)
#define COM_TASK_ERR         (-1)
#define COM_TASK_TRUE        (1)
#define COM_TASK_FALSE       (0)
#define COM_TASK_NULL        (0)


/*******************************************************************************
 *   宏操作定义区
 *******************************************************************************/



/*******************************************************************************
 *   枚举类型定义区
 *******************************************************************************/
typedef enum tagCOM_TASK_E_MODE
{
    COM_TASK_E_ONCE = 0,
    COM_TASK_E_LOOP,
    COM_TASK_E_UNDEF
} COM_TASK_E_MODE;


/*******************************************************************************
 *   数据结构类型和联合体类型定义
 *******************************************************************************/
typedef void  (*COM_TASK_FN_CMD)(void *pTask);

/** TASK参数描述结构 */
typedef struct tagCOM_TASK_S_CB
{
    void           *pHandle;     /**< 任务控制句柄 */
    void           *pUserData;   /**< 任务透传的用户参数 */
    COM_TASK_FN_CMD pfnClose;    /**< 任务注销控制 */
    COM_TASK_FN_CMD pfnStart;    /**< 任务恢复控制 */
    COM_TASK_FN_CMD pfnStop;     /**< 任务暂停控制 */
    COM_TASK_FN_CMD pfnSaveStop; /**< 任务暂停控制 */
    COM_TASK_FN_CMD pfnStartOnce;/**< 任务恢复控制 */
    COM_TASK_FN_CMD pfnWaitOnce; /**< 任务恢复控制 */
} COM_TASK_S_CB, *COM_TASK_S_CB_PTR;

/*******************************************************************************
 *   全局变量声明(extern)区
 *******************************************************************************/



/*******************************************************************************
 *   全局函数声明(extern)区
 *******************************************************************************/
/** 创建任务
 *
 *  @param[in]  pfnTaskProc 任务处理回调函数
 *  @param[in]  pTaskParam  回调函数输入参数
 *  @param[out] pstTaskCB   任务控制块
 *
 *  @retval ::COM_TASK_OK   创建任务成功
 *  @retval ::COM_TASK_ERR  创建任务失败
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
