#include <iostream>
#include <unistd.h>
#include <errno.h>

#include "WatchDog.h"

using namespace android;

void ProtoServiceDeathRecipient::binderDied(const android::wp<android::IBinder>& o) {
    std::cout << "Watchdog: Service Died. Rebooting..." << std::endl;
    // std::cout << o.getInterfaceDescriptor() << std::endl;
    //o.unlinkToDeath(WatchDog::getInstance().dr);
    int ret = fork();
    if (ret == 0) {
        int ret = execl("/home/peiranguo/src/binder-for-linux/proto_service/server", NULL); 
        if (ret == -1) {
            std::cout << strerror(errno) << std::endl;
            std::cout << "Watchdog execl failed" << std::endl; 
        } else {
            std::cout << "fork subprocess to launch server" << std::endl; 
        }
    } else {
        sleep(2);
        std::cout << "restarting server..." << std::endl; 
        if (WatchDog::getInstance().start() != 0) {
            std::cout << "WatchDog failed" << std::endl; 
        } else {
            std::cout << "WatchDog running" << std::endl;
        }
    }
}

int WatchDog::start() {
    dr = NULL;
    dr = sp<ProtoServiceDeathRecipient>(new ProtoServiceDeathRecipient());
    android::sp<android::IServiceManager> sm = defaultServiceManager();
    android::sp<android::IBinder> binder = sm->getService(String16("service.proto"));
    if (binder == 0) {
        std::cout << "get service.proto error" << std::endl; 
        return -1;
    }
    std::cout << "WatchDot add DeathRecipient" << std::endl;
    binder->linkToDeath(dr);
    return 0;
}
