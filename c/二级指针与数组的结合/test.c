#include <stdio.h>
#include <stdlib.h>

typedef struct INNER_STRUCT
{
	int inner_num;
	
} INNER_STRUCT;

typedef struct STRUCK
{
	INNER_STRUCT** pInner;
} STRUCK;


int main(void)
{
	STRUCK st;
	/* 给pInner申请了一段能存放四个指针变量的内存 */
	st.pInner = (INNER_STRUCT** )malloc(sizeof(INNER_STRUCT* ) * 4);
	
	/* 给第一个指针变量申请内存，大小为其指向的类型INNER_STRUCT */
	st.pInner[0] = (INNER_STRUCT* )malloc(sizeof(INNER_STRUCT));
	/* 给第二个指针变量申请内存，大小为其指向的类型INNER_STRUCT */
	st.pInner[1] = (INNER_STRUCT* )malloc(sizeof(INNER_STRUCT));

	/* 通过访问第一个变量指向的地址给inner_num赋值 */
	*(int* )((unsigned long long* )*st.pInner) = 598;
	/* 通过访问第二个变量指向的地址给inner_num赋值 */
	st.pInner[1]->inner_num = 954;
	
	/* 验证是否设赋值成功 */
	printf("num1 = %d, num2 = %d\n", st.pInner[0]->inner_num, st.pInner[1]->inner_num);

	return 0;
}
