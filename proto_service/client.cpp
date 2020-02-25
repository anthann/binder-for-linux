#include <iostream>
#include "IProtoService.h"

void get(const sp<IProtoService>& service) {
    proto_service::Empty getParam;
    proto_service::Data getRecv = service->getText(getParam);
	std::cout<< "client:get: " << getRecv.text() << std::endl;
}

void set(const sp<IProtoService>& service, std::string content) {
    proto_service::Data send;
    send.set_text(content);
    proto_service::Empty setRecv = service->setText(send);
    std::cout << "client:set: " << content << std::endl;
}

int main(int argc, char* argv[]) {
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder = sm->getService(String16("service.proto"));
	sp<IProtoService> service = interface_cast<IProtoService>(binder);
    if (argc == 1) {
        set(service, "default message");
        get(service);
    } else if (argc > 1) {
        std::string command(argv[1]);
        if (command == "get") {
            get(service);
        } else if (command == "set") {
            if (argc > 2) {
                std::string content(argv[2]);
                set(service, content);
            } else {
                set(service, "default message");
            } 
        } else {
            std::cout << "Usage: sudo ./client (get | set [message])"  << std::endl;
        }
    }
	return 0;
}
