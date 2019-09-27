#include <stdio.h>
#include "../interface/IMyService.h"
#include <binder/IServiceManager.h>


#define LOG_NDEBUG 0
#define LOG_TAG "JzTech: Client-main"

using namespace android;

sp<IMyService> mMyService;

void initMyServiceClient() {
    if (mMyService == 0) {
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder;
        do {
            binder = sm->getService(String16("MyService"));
            if (binder != 0)
            {
                break;
            }           
            ALOGE("MyService not published, waiting...");
            sleep(1);
        } while (1);
        mMyService = interface_cast<IMyService>(binder);
    }
}

int main(int argc, char* argv[]) {
    /* 获取binder service */
    initMyServiceClient();

    if(mMyService ==NULL) {
        ALOGE("cannot find MyService");
        return -1;
    }

    while(1) {
        mMyService->setNum(1);
        sleep(1);
        ALOGD("getNum %d", mMyService->getNum());
    }
    return 0;
}

