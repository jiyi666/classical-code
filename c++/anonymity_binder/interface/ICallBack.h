#ifndef ICallBack_H  
#define ICallBack_H 

#include <binder/IInterface.h>

namespace android {

    /* 固定写法：此处必须继承自IInterface类 */
    class ICallBack  : public IInterface   
    {
    public:
        DECLARE_META_INTERFACE(CallBack);
        virtual int replyCallback(int a) = 0;
    };

    /* 对client端而言，只会暴露BnxxxService, 而不知道有BpxxxService
     * 此类也是固定写法 */
    class BnCallBack : public BnInterface<ICallBack>
    {
    public:
        virtual status_t    onTransact( uint32_t code,
                                        const Parcel& data,
                                        Parcel* reply,
                                        uint32_t flags = 0);
    };

}
#endif


