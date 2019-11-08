#include <stdio.h>

/* 声明了一个结构体，里面有三个函数指针 */
typedef struct SAMPLE_CALLBACK
{
	int (*CallBack1)(void);
	int (*CallBack2)(void);
	int (*Add)(int i, int j);
} SAMPLE_CALLBACK;

/* 回调函数测试：回调的调用者 */
int Callback_Test(SAMPLE_CALLBACK* pCallback, int num);