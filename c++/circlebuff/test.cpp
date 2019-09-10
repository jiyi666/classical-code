#include <iostream>
#include <cstring> //be about to use memcpy
#include <pthread.h>//be abort thread:when compile files, please use cmd like this:g++ xxx.cpp -o thread -lpthread
#include <unistd.h> //be about usleep
#include "include/cbuff.h"
using namespace std;
#define USE_THREAD


static void* WriteDataThread(void* pParam)
{
	CircleBuffExt* writeHandle = (CircleBuffExt* )pParam;
	char* writeBuff = "0123456789";
	
	while (1)
	{
		writeHandle->circleBuffWrite(writeBuff, 7);
		usleep(1000 * 500);
	}
}

static void* ReadDataThread(void* pParam)
{
	CircleBuffExt* readHandle = (CircleBuffExt* )pParam;	
	char* readBuff = new char[10];
	while(1)
	{
		readHandle->circleBuffRead(readBuff, 5);
		usleep(1000 * 800);
	}
	delete readBuff;
}

int main()
{
	char* circleBuff = new char[100];
	
	CircleBuff cBuffHandle;
	cBuffHandle.mBuffLength = 100;
	cBuffHandle.mReadPos = 0;
	cBuffHandle.mWritePos = 0;
	
	CircleBuffExt* cBuffExt = new CircleBuffExt(&cBuffHandle, circleBuff);

/* note: adjust read/write bytes and sleep time values to test read/write buff not enough */
#ifdef USE_THREAD
	
	pthread_t threadId[2];
	int ret;
	
	ret = pthread_create(&threadId[0], NULL, &WriteDataThread, cBuffExt);
	if (ret)
	{
		cout << "create write data thread failed!" << endl;
		return -1;
	}
	
	ret = pthread_create(&threadId[1], NULL, &ReadDataThread, cBuffExt);
	if (ret)
	{
		cout << "create read data thread failed!" << endl;
		return -1;
	}
	
	pthread_join(threadId[0], NULL);
	pthread_join(threadId[1], NULL);
#else	
	/*just test for four funcs */
	/* alloc a lot of read/write buff to test */
	/* 1.write 5 bytes */
	char* writeBuff0 = "12345";
	cBuffExt->circleBuffWrite(writeBuff0, 5);
	
	/* 2.read 10 bytes */
	char* readBuff0 = new char[10];
	cBuffExt->circleBuffRead(readBuff0, 10);
	delete readBuff0;
	
	/* 3.write 15 bytes */
	char* writeBuff1 = "678901234567890";
	cBuffExt->circleBuffWrite(writeBuff1, 15);
	
	/* 4.read 20 bytes */
	char* readBuff1 = new char[20];
	cBuffExt->circleBuffRead(readBuff1, 20);
	delete readBuff1;

	/* 5.write 90 bytes */
	char* writeBuff2 = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
	cBuffExt->circleBuffWrite(writeBuff2, 90);
	
	/* 6.read 80 bytes */
	char* readBuff2 = new char[80];
	cBuffExt->circleBuffRead(readBuff2, 80);
	delete readBuff2;
#endif
	return 0;
}