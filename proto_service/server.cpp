#include <cstdlib>
#include <iostream>
#include <string>
#include "IProtoService.h"

class MyProtoService: public BnProtoService {
	public:
		virtual ~MyProtoService() {}
        int setText(const proto_service::Data& req, proto_service::Empty* resp) {
            text = req.text();
            return 1;
		}

        int getText(const proto_service::Empty& req, proto_service::Data* resp) {
            resp->set_text(text);
            return 1;
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
