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
        return 0;//OK
    }
    int MyService::getNum() {
        ALOGD("MyService::getNum myParam = %d", myParam);
        return myParam;
    }
}

