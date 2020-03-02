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
