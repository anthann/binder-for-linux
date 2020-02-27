#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

class ProtoServiceDeathRecipient: public android::IBinder::DeathRecipient {
    virtual void binderDied(const android::wp<android::IBinder>&);
};

class WatchDog {
    android::sp<ProtoServiceDeathRecipient> dr;
public:

    static WatchDog& getInstance() {
        static WatchDog instance;
        return instance;
    }

    int start();
};

