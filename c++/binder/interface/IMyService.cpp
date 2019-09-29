#include "IMyService.h"
#include <binder/Parcel.h>
#include <utils/Log.h>

#define LOG_NDEBUG 0
#define LOG_TAG "JzTech: IMyService"

namespace android {

    enum 
    {
        SET_NUM = IBinder::FIRST_CALL_TRANSACTION,
        GET_NUM,
    };

    /* binder代理端 */
    class BpMyService : public BpInterface<IMyService> {
    public:
        BpMyService(const sp<IBinder>& impl)
            : BpInterface<IMyService>(impl) 
        {

        }
        virtual int setNum(int a) {
            ALOGD(" BpMyService::setNum a = %d ", a);
            Parcel data,reply;
            data.writeInt32(a);
            remote()->transact(SET_NUM,data,&reply);
            return reply.readInt32();
        }
        virtual int getNum() {
            ALOGD(" BpMyService::getNum");
            Parcel data,reply;
            data.writeInterfaceToken(IMyService::getInterfaceDescriptor());
            remote()->transact(GET_NUM,data,&reply);
            return reply.readInt32();
        }
    };

    /* 接口:这里面会去new        BpxxxSerivce*/
    IMPLEMENT_META_INTERFACE(MyService, "jztech.binder.IMyService");


    /* naive端代码，即服务端代码 ,此代码的作用是从binder driver中
     * 拿到client端的请求数据，如果有需要设入的值，就从binder driver
     * 中读取出来，然后执行服务器端的函数，将返回值写入binder driver
     * 实际上，Bn的代码就是为binder driver和service服务的通道 */
    status_t BnMyService::onTransact (uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
    {
        int ret = -1;
        switch (code) {
            case SET_NUM: 
                {
                    int num = -1;
                    ALOGD("BnMyService::onTransact  SET_NUM ");
                    num = data.readInt32();
                    ret = setNum(num);
                    reply->writeInt32(ret);
                    return NO_ERROR;
                }
            case GET_NUM:
                {
                    ALOGD("BnMyService::onTransact  GET_NUM ");
                    ret = getNum();
                    reply->writeInt32(ret);
                    return NO_ERROR;
                }
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
}

