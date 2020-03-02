#pragma once

#include "ICallbackInterface.h"
class CallbackInterfaceImpl : public BnCallbackInterface
{
public:
    virtual void notifyCallback01(int32_t msgType, int32_t ext1, int32_t ext2); //call from service
public:
    CallbackInterfaceImpl();
    virtual ~CallbackInterfaceImpl();
};