#ifndef IMyService_H  
#define IMyService_H 

#include <binder/IInterface.h>
#include "ICallBack.h"

namespace android {

    /* 固定写法：此处必须继承自IInterface类 */
    class IMyService  : public IInterface   
    {
    public:
        DECLARE_META_INTERFACE(MyService);
        virtual int setNum(int a) = 0;
        virtual int getNum() = 0;
        /* 添加匿名binder的接口 */
        virtual int setCallback(const sp<ICallBack>& callback) = 0;
    };

    /* 对client端而言，只会暴露BnxxxService, 而不知道有BpxxxService
     * 此类也是固定写法 */
    class BnMyService : public BnInterface<IMyService>
    {
    public:
        virtual status_t    onTransact( uint32_t code,
                                        const Parcel& data,
                                        Parcel* reply,
                                        uint32_t flags = 0);
    };

}
#endif

