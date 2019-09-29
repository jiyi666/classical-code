#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <binder/Parcel.h>
#include <utils/threads.h>


#include <cutils/properties.h>
#include "MyService.h"
#define LOG_NDEBUG 0
#define LOG_TAG "JzTech: MyService"

namespace android {
    MyService::MyService() {
        myParam = 0;
    }
    MyService::~MyService()
    {

    }

    int MyService::setNum(int a) {
        ALOGD("MyService::setNum a = %d myParam %d", a, myParam);
        myParam += a;
        /* 回调callback中的函数 */
        if (mCallback != NULL)
        {
            ALOGE("MyService will be callback!");
            mCallback->replyCallback(myParam);
        }
        else
        {
            ALOGE("MyService's mCallback is NULL!");
        }
        return 0;
    }
    int MyService::getNum() {
        ALOGD("MyService::getNum myParam = %d", myParam);
        return myParam;
    }
    /* 设置匿名binder的回调函数 */
    int MyService::setCallback(const sp<ICallBack>& callback) {
        ALOGD("MyService::getNum myParam = %d", myParam);
        mCallback = callback;
        return 0;
    }

    
}

