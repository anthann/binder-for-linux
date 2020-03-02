#pragma once

#include "ITestInterface.h"
#include "ICallbackInterface.h"

class TestInterfaceImpl: public BnTestInterface
{
public:
    virtual int InitParam(const android::sp<ICallbackInterface> &callback); //init parameter
    virtual int Add(int a, int b);                                        //return a+b
    virtual int CallbackTest();                                           //force callback
    virtual void sayHello(android::String8 msg, const android::sp<ICallbackInterface>& callback);
private:
    android::sp<ICallbackInterface> _callback;

public:
    TestInterfaceImpl();
    virtual ~TestInterfaceImpl();
};
