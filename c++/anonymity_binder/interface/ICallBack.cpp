#include "ICallBack.h"
#include <binder/Parcel.h>
#include <utils/Log.h>

#define LOG_NDEBUG 0
#define LOG_TAG "JzTech: ICallBack"

namespace android {

    enum 
    {
        REPLY_CALLBACK,
    };

    /* binder代理端 */
    class BpCallBack : public BpInterface<ICallBack> {
    public:
        BpCallBack(const sp<IBinder>& impl)
            : BpInterface<ICallBack>(impl) 
        {

        }
        virtual int replyCallback(int a) {
            ALOGD(" BpCallBack::replyCallback a = %d ", a);
            Parcel data,reply;
            data.writeInt32(a);
            remote()->transact(REPLY_CALLBACK,data,&reply);
            return reply.readInt32();
        }
    };

    /* 接口:这里面会去new        BpxxxSerivce*/
    IMPLEMENT_META_INTERFACE(CallBack, "jztech.binder.ICallBack");


    /* naive端代码，即服务端代码 ,此代码的作用是从binder driver中
     * 拿到client端的请求数据，如果有需要设入的值，就从binder driver
     * 中读取出来，然后执行服务器端的函数，将返回值写入binder driver
     * 实际上，Bn的代码就是为binder driver和service服务的通道 */
    status_t BnCallBack::onTransact (uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
    {
        int ret = -1;
        switch (code) {
            case REPLY_CALLBACK: 
                {
                    int num = -1;
                    ALOGD("BnCallBack::onTransact  REPLY_CALLBACK ");
                    num = data.readInt32();
                    ret = replyCallback(num);
                    reply->writeInt32(ret);
                    return NO_ERROR;
                }
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
}


