#include <stdio.h>
#include <callback.h>

int Function1(void);
int Function2(void);
int Function_Add(int i, int j);


/* 回调的实现者：将三个实体函数“挂上” */
SAMPLE_CALLBACK g_cb =
{
	.CallBack1 = Function1,
	.CallBack2 = Function2,
	.Add = Function_Add
};


/* Function1尝试让调用者回调Function2 */
int Function1()
{
	printf("This is Function1\n");
	Callback_Test(&g_cb, 2);
	return 20;
}

/* Function1尝试让调用者回调Function_Add */
int Function2()
{
	printf("This is Function2\n");
	Callback_Test(&g_cb, 3);
	return 0;
}

/* Function_Add打印两数之和 */
int Function_Add(int i, int j)
{
	printf("This is Add: %d + %d = %d\n", i, j, i + j);
	return 0;
}

int main(void)
{
	
	/* mainh尝试让调用者回调Function1 */
	Callback_Test(&g_cb, 1);

	return 0;
}