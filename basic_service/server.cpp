#include "IBasicService.h"

int main() {
	sp<IServiceManager> sm = defaultServiceManager();
	sm->addService(String16("service.basic"), new BnBasicService());
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
	return 0;
}
