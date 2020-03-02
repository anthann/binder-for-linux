#include <iostream>
#include "CallbackInterfaceImpl.h"

CallbackInterfaceImpl::CallbackInterfaceImpl()
{
}
CallbackInterfaceImpl::~CallbackInterfaceImpl()
{
}
void CallbackInterfaceImpl::notifyCallback01(int32_t msgType, int32_t ext1, int32_t ext2)
{
    std::cout << "callback: msgType=" << msgType << ", ext1=" << ext1 << ", ext2=" << ext2 << std::endl; 
}
