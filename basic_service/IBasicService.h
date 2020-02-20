#ifndef BASIC_SERVICE
#define BASIC_SERVICE
#include <stdio.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

using namespace android;


class IBasicService: public IInterface {
	public:
		enum {
			HELLO = 1,
		};
		virtual void sayHello() = 0;
		DECLARE_META_INTERFACE(BasicService);
};

class BpBasicService: public BpInterface<IBasicService> {
	public: 
		BpBasicService(const sp<IBinder>& impl);
		virtual void sayHello();
};

class BnBasicService: public BnInterface<IBasicService> {
	public:
		virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
		virtual void sayHello();
};

#endif 
