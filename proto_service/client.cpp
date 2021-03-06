#include <iostream>
#include "IProtoService.h"

void get(const sp<IProtoService>& service) {
    proto_service::Empty req;
    proto_service::Data resp;
    int ret = service->getText(req, &resp);
	std::cout<< "client:get: " << resp.text() << std::endl;
    std::cout << "return: " << ret << std::endl;
}

void set(const sp<IProtoService>& service, std::string content) {
    proto_service::Data req;
    req.set_text(content);
    proto_service::Empty resp;
    int ret = service->setText(req, &resp);
    std::cout << "client:set: " << content << std::endl;
    std::cout << "return: " << ret << std::endl;
}

void crash(const sp<IProtoService>& service) { 
    service->crash();
}

int main(int argc, char* argv[]) {
    sp<IProtoService> service;
    int status = getService(String16("service.proto"), &service);
    if (status != 0) {
        std::cout << "Client can't get service" << std::endl; 
        return 0; 
    }
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
        } else if (command == "crash") {
            crash(service);
        } else {
            std::cout << "Usage: sudo ./client (get | set [message])"  << std::endl;
        }
    }
	return 0;
}
