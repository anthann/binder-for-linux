#pragma once

#include "ITestInterface.h"

class TestInterfaceImpl: public BnTestInterface
{
public:
    virtual int InitParam(const android::sp<ICallbackInterface> &callback); //init parameter
    virtual int Add(int a, int b);                                        //return a+b
    virtual int CallbackTest();                                           //force callback
private:
    android::sp<ICallbackInterface> _callback;

public:
    TestInterfaceImpl();
    virtual ~TestInterfaceImpl();
};
