#include "IBasicService.h"

IMPLEMENT_META_INTERFACE(BasicService, "me.anthann.basicservice");

BpBasicService::BpBasicService(const sp<IBinder>& impl): BpInterface<IBasicService>(impl) {}

void BpBasicService::sayHello() {
	printf("BpBasicService::sayHello\n");
	Parcel data, reply;
	data.writeInterfaceToken(IBasicService::getInterfaceDescriptor());
	remote()->transact(HELLO, data, &reply);
	printf("get num from BnMyService: %d\n", reply.readInt32());	
}

status_t BnBasicService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags) {
	switch(code) {
	case HELLO: {
		printf("BnBasicService:: got the client hello\n");
		CHECK_INTERFACE(IBasicService, data, reply);
		sayHello();
		reply->writeInt32(2020);
		return NO_ERROR;
	}
	default:
		break;
	}
	return NO_ERROR;
}

void BnBasicService::sayHello() {
	printf("BnBasicService::sayHello\n");
}

