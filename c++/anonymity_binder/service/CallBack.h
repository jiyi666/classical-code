#ifndef CallBack_H
#define CallBack_H
#include "../interface/ICallBack.h"
#include <binder/BinderService.h>


namespace android {
class CallBack : public BnCallBack
{
    public:
        CallBack();
        ~CallBack();
        virtual int replyCallback(int a);
    };
}

#endif


