#include "ICallbackInterface.h"

using namespace android;

enum
{
    CALLBACK01 = IBinder::FIRST_CALL_TRANSACTION,
};

class BpCallbackInterface : public BpInterface<ICallbackInterface>
{
public:
    BpCallbackInterface(const sp<IBinder> &impl)
        : BpInterface<ICallbackInterface>(impl)
    {
    }
    virtual void notifyCallback01(int32_t msgType, int32_t ext1, int32_t ext2)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ICallbackInterface::getInterfaceDescriptor());
        data.writeInt32(msgType);
        data.writeInt32(ext1);
        data.writeInt32(ext2);
        remote()->transact(CALLBACK01, data, &reply);
    }
};

IMPLEMENT_META_INTERFACE(CallbackInterface, "me.anthann.CallbackInterface");

status_t BnCallbackInterface::onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
    case CALLBACK01:
    {
        CHECK_INTERFACE(ICallbackInterface, data, reply);
        int32_t msgType = data.readInt32();
        int32_t ext1 = data.readInt32();
        int32_t ext2 = data.readInt32();
        notifyCallback01(msgType, ext1, ext2);
        break;
    }
    default:
        break;
    }
    return NO_ERROR;
}
