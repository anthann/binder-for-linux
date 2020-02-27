#include <cstdlib>
#include <iostream>
#include <string>
#include "IProtoService.h"
#include "ProtoService.h"

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

        void crash() {
            throw 0;
        }

    private:
        std::string text;
};

void ProtoService::initiate() {
    std::cout << "initiate" << std::endl;
	sp<IServiceManager> sm = defaultServiceManager();
	sm->addService(String16("service.proto"), new MyProtoService());
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
}
