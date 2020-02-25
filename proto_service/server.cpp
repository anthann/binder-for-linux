#include <cstdlib>
#include <iostream>
#include <string>
#include "IProtoService.h"

class MyProtoService: public BnProtoService {
	public:
		virtual ~MyProtoService() {}
        proto_service::Empty setText(proto_service::Data input) {
            text = input.text();
		}

        proto_service::Data getText(proto_service::Empty) {
            proto_service::Data data;
            data.set_text(text);
            return data;
		}

    private:
        std::string text;
};

int main() {
	sp<IServiceManager> sm = defaultServiceManager();
	sm->addService(String16("service.proto"), new MyProtoService());
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
	return 0;
}
