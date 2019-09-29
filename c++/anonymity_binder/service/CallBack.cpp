#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <binder/Parcel.h>
#include <utils/threads.h>


#include <cutils/properties.h>
#include "CallBack.h"
#define LOG_NDEBUG 0
#define LOG_TAG "JzTech: CallBack"

namespace android {
    CallBack::CallBack() {
    }
    CallBack::~CallBack()
    {

    }

    int CallBack::replyCallback(int a) {
        ALOGD("MyService replyCallback, the client value = %d", a);
        return 0;
    }
}


