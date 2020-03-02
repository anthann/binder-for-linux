#include <iostream>
#include "ITestInterface.h"
#include "CallbackInterfaceImpl.h"

using namespace android;

int main(int argc, char **argv)
{
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder = sm->getService(String16("service.test"));
    sp<ITestInterface> pService = interface_cast<ITestInterface>(binder);
    
    pService->InitParam(new CallbackInterfaceImpl());
    std::cout << "Add(10, 20) = " << pService->Add(10, 20) << std::endl;
    pService->CallbackTest();
    std::cout << "[client] end\n" << std::endl;
}
