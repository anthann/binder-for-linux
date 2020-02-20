#include "IBasicService.h"

int main() {
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder = sm->getService(String16("service.basic"));
	sp<IBasicService> service = interface_cast<IBasicService>(binder);
	service->sayHello();
	return 0;
}
