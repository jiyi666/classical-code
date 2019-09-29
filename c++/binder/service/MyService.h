#ifndef MyService_H
#define MyService_H
#include "../interface/IMyService.h"
#include <binder/BinderService.h>


namespace android {
class MyService : public BnMyService
{
    public:
        MyService();
        ~MyService();
        static const char* getServiceName() 
        { 
            return "MyService";
        }
        virtual int setNum(int a);
        virtual int getNum();
    protected:
        int myParam;
    };
}

#endif

