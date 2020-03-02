#include <unistd.h>
#include <iostream>
#include "TestInterfaceImpl.h"

using namespace android;

TestInterfaceImpl::TestInterfaceImpl() : BnTestInterface()
{
}

TestInterfaceImpl::~TestInterfaceImpl()
{
}

int TestInterfaceImpl::InitParam(const sp<ICallbackInterface> &callback)
{
    _callback = callback;
    return 0;
}

int TestInterfaceImpl::Add(int a, int b)
{
    return (a + b);
}

int TestInterfaceImpl::CallbackTest()
{
    if (_callback.get())
    {
        _callback->notifyCallback01(0, 1, 2);
        return 0;
    }
    return -1;
}

void TestInterfaceImpl::sayHello(String8 msg, const sp<ICallbackInterface>& callback) {
    std::cout << "TestInterfaceImpl::sayHello received: " << msg.string() << std::endl;
    sleep(5);      
    //auto cb = callback.promote();
    String8 rt("Reveived: ");
    rt.append(msg);
    if (callback.get()) {
        std::cout << "TestInterfaceImpl::sayHello send: " << rt.string() << std::endl;
        callback->sayHello_cb(rt); 
    }
}
