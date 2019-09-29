#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>

#include "MyService.h"
#define LOG_NDEBUG 0
#define LOG_TAG "JzTech: MyService-main"

using namespace android;

int main(int argc, char** argv)
{

    /* 1. 打开binder driver并且进行内核地址的mmap */
    sp<ProcessState> proc(ProcessState::self());

    /* 2.获取Android的SM并将我们的服务添加进去 */
    sp<IServiceManager> sm = defaultServiceManager();
    sm->addService(String16(MyService::getServiceName()), new MyService());

    /* 3.启动子线程，一般的server都不需要再启动这样一个子线程来协助主线程工作 */
    ProcessState::self()->startThreadPool();

    /* 4.loop循环，从binder driver中获取指令，并由Bn的transact转为onTransact
     * 最终回调到Bn端，进而执行xxxService里面的代码 */
    IPCThreadState::self()->joinThreadPool();

    return 0;
}

