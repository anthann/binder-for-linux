#include "ITestInterface.h"

using namespace android;

enum
{
    SETCALLBACK = android::IBinder::FIRST_CALL_TRANSACTION,
    ADD,
    CALLBACKTEST,
    SAYHELLO
};

class BpTestInterface : public BpInterface<ITestInterface>
{
public:
    BpTestInterface(const sp<IBinder> &impl)
        : BpInterface<ITestInterface>(impl)
    {
    }

    virtual int InitParam(const sp<ICallbackInterface> &callback)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ITestInterface::getInterfaceDescriptor());
        //data.writeStrongBinder(callback->asBinder());
        data.writeStrongBinder(IInterface::asBinder(callback));
        remote()->transact(SETCALLBACK, data, &reply);
        return (reply.readInt32());
    }

    virtual int Add(int a, int b)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ITestInterface::getInterfaceDescriptor());
        data.writeInt32(a);
        data.writeInt32(b);
        remote()->transact(ADD, data, &reply);
        return (reply.readInt32());
    }

    virtual int CallbackTest() //force callback
    {
        Parcel data, reply;
        data.writeInterfaceToken(ITestInterface::getInterfaceDescriptor());
        remote()->transact(CALLBACKTEST, data, &reply, IBinder::FLAG_ONEWAY);
        return (reply.readInt32());
    }

    virtual void sayHello(String8 msg, const sp<ICallbackInterface>& callback) {
        Parcel data, reply;
        data.writeInterfaceToken(ITestInterface::getInterfaceDescriptor());
        //auto s = callback.promote();
        //if (s == NULL) {
        //    return; 
        //}
        data.writeStrongBinder(IInterface::asBinder(callback));
        data.writeString8(msg);
        remote()->transact(SAYHELLO, data, &reply, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(TestInterface, "me.anthann.ITestInterface");

status_t BnTestInterface::onTransact(
    uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
    case SETCALLBACK:
    {
        CHECK_INTERFACE(ITestInterface, data, reply);
        sp<ICallbackInterface> callback = interface_cast<ICallbackInterface>(data.readStrongBinder());
        reply->writeInt32(InitParam(callback));
        break;
    }
    case ADD:
    {
        CHECK_INTERFACE(ITestInterface, data, reply);
        int a = data.readInt32();
        int b = data.readInt32();
        reply->writeInt32(Add(a, b));
        break;
    }
    case CALLBACKTEST:
    {
        CHECK_INTERFACE(ITestInterface, data, reply);
        reply->writeInt32(CallbackTest());
        break;
    }
    case SAYHELLO:
    {
        CHECK_INTERFACE(ITestInterface, data, reply);
        sp<ICallbackInterface> callback = interface_cast<ICallbackInterface>(data.readStrongBinder());
        String8 a = data.readString8();
        sayHello(a, callback);
        break;
    }
    default:
        break;
    }
    return NO_ERROR;
}
