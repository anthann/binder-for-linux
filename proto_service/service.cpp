#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <binder/ProcessState.h>
#include "WatchDog.h"

int main() {
    int ret = fork();
    if (ret == 0) {
        if (execl("/home/peiranguo/src/binder-for-linux/proto_service/server", "") == -1) {
            std::cout << "execl failed" << std::endl; 
        }
    } else {
        std::cout << "parent" << std::endl;
        sleep(3); 
        if (WatchDog::getInstance().start() != 0) {
            std::cout << "WatchDog failed" << std::endl; 
        } else {
            std::cout << "WatchDog running" << std::endl;
        }
        android::sp<android::ProcessState> proc(android::ProcessState::self());
        android::ProcessState::self()->startThreadPool();
        while(1) {
            sleep(1); 
        }
    }
	return 0;
}
