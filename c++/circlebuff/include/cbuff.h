#include <iostream>
#include <cstring> //be about to use memcpy

/*-----------------begin with class declare------------------------*/
class CircleBuff
{
public:
	int mReadPos;
	int mWritePos;
	int mBuffLength;
};

class CircleBuffExt
{
public:
	CircleBuffExt(CircleBuff* pCircleBuff, char* buffer);
	int circleBuffRead(char* buff, int readLength);
	int circleBuffWrite(char* buff, int writeLength);
	int circleBuffQueryBusy();
	int circleBuffQueryFree();
	
private:
	CircleBuff* pCircleBuff;
	char* pbuff;
};
/*-----------------end of with class declare------------------------*/


