#include <stdio.h>
#include <callback.h>



int Callback_Test(SAMPLE_CALLBACK* pCallback, int num)
{
	if (!pCallback)
	{
		printf("pCallback is NULL!!!\n");
		return -1;
	}
	
	/* 根据传进来的num调用对应的回调 */
	switch(num)
	{
		case 1:
		pCallback->CallBack1();
		break;
		case 2:
		pCallback->CallBack2();
		break;
		case 3:
		pCallback->Add(8, 9);	
		break;
		default:
		printf("No match case!!!\n");
		break;
	}	
}