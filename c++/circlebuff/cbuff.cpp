#include <iostream>
#include <cstring> //be about to use memcpy
#include "include/cbuff.h"

using namespace std;

/*-----------------begin with class define------------------------*/
CircleBuffExt::CircleBuffExt(CircleBuff* pCircleBuff, char* buffer)
{
	this->pCircleBuff = pCircleBuff;
	this->pbuff = buffer;
}

/* check free size of whole circle buff*/
int CircleBuffExt::circleBuffQueryFree()
{
	int freeLen, readPos, writePos;
	
	readPos = pCircleBuff->mReadPos;
	writePos = pCircleBuff->mWritePos;
	
	if (readPos > writePos)
	{
		freeLen = readPos - writePos;
	}
	else
	{
		freeLen = pCircleBuff->mBuffLength - (writePos - readPos);
	}
	
	return freeLen;
}

/* check busy size of whole circle buff*/
int CircleBuffExt::circleBuffQueryBusy()
{
	int busyLen, readPos, writePos;

	readPos = pCircleBuff->mReadPos;
	writePos = pCircleBuff->mWritePos;
	
	if (readPos > writePos)
	{
		busyLen = pCircleBuff->mBuffLength - (readPos - writePos);
	}
	else
	{
		busyLen = writePos - readPos;
	}
	
	return busyLen;
}

int CircleBuffExt::circleBuffWrite(char* buff, int writeLength)
{
	int readPos, writePos;
	
	readPos = pCircleBuff->mReadPos;
	writePos = pCircleBuff->mWritePos;
	
	/* note:if free buff equal to writeLength, which made read pointer equal to 
	   write pointer, and user don't know free buff is zero or full£¡ */
	if (circleBuffQueryFree() <= writeLength)
	{
		cout << "There don't have enough free buff to write!" << endl;
		return 0;
	}
	
	if (readPos > writePos)
	{
		memcpy(pbuff + writePos, buff, writeLength);
		pCircleBuff->mWritePos += writeLength;
		
		cout << "write buff succeed:mReadPos = " << pCircleBuff->mReadPos << ", mWritePos = " << pCircleBuff->mWritePos
		     << ", mBuffLength = " << pCircleBuff->mBuffLength << endl;
		
		return writeLength;
	}
	else
	{
		if (pCircleBuff->mBuffLength >= writePos + writeLength)
		{
			memcpy(pbuff + writePos, buff, writeLength);
			pCircleBuff->mWritePos += writeLength;
			
			cout << "write buff succeed:mReadPos = " << pCircleBuff->mReadPos << ", mWritePos = " << pCircleBuff->mWritePos
				 << ", mBuffLength = " << pCircleBuff->mBuffLength << endl;
		
			return writeLength;	
		}
		else
		{
			memcpy(pbuff + writePos, buff, pCircleBuff->mBuffLength - writePos);
			memcpy(pbuff, buff + (pCircleBuff->mBuffLength - writePos), writeLength - (pCircleBuff->mBuffLength - writePos));
			pCircleBuff->mWritePos = writeLength - (pCircleBuff->mBuffLength - writePos);
			cout << "write buff succeed:mReadPos = " << pCircleBuff->mReadPos << ", mWritePos = " << pCircleBuff->mWritePos
				 << ", mBuffLength = " << pCircleBuff->mBuffLength << endl;
		
			return writeLength;				
			
		}
	}
	
}

int CircleBuffExt::circleBuffRead(char* buff, int readLength)
{
	int readPos, writePos;
	
	readPos = pCircleBuff->mReadPos;
	writePos = pCircleBuff->mWritePos;
	
	/* note:if free buff equal to writeLength, which made read pointer equal to 
	   write pointer, and user don't know free buff is zero or full£¡ */
	if (circleBuffQueryBusy() <= readLength)
	{
		cout << "There don't have enough data to read!" << endl;
		return 0;
	}
	
	if (writePos > readPos)
	{
		memcpy(buff, pbuff + readPos, readLength);
		pCircleBuff->mReadPos += readLength;
		
		cout << "read buff succeed:mReadPos = " << pCircleBuff->mReadPos << ", mWritePos = " << pCircleBuff->mWritePos
			 << ", mBuffLength = " << pCircleBuff->mBuffLength << endl;
		return readLength;
	}
	else
	{
		if (pCircleBuff->mBuffLength >= readPos + readLength)
		{
			memcpy(buff, pbuff + readPos, readLength);
			pCircleBuff->mReadPos += readLength;
			
			cout << "read buff succeed:mReadPos = " << pCircleBuff->mReadPos << ", mWritePos = " << pCircleBuff->mWritePos
				 << ", mBuffLength = " << pCircleBuff->mBuffLength << endl;
			return readLength;			
		}
		else
		{
			memcpy(buff, pbuff + readPos, pCircleBuff->mBuffLength - readPos);
			memcpy(buff + pCircleBuff->mBuffLength - readPos, pbuff, readLength - (pCircleBuff->mBuffLength - readPos));
			
			pCircleBuff->mReadPos = readLength - (pCircleBuff->mBuffLength - readPos);
			
			cout << "read buff succeed:mReadPos = " << pCircleBuff->mReadPos << ", mWritePos = " << pCircleBuff->mWritePos
				 << ", mBuffLength = " << pCircleBuff->mBuffLength << endl;
			return readLength;
		}
	}
}
/*-----------------end of with class define------------------------*/


