#include <cstdlib>
#include <iostream>
#include <string>
#include "unistd.h"
#include "ProtoService.h"

int main() {
    std::cout << "Starting server" << std::endl;
    ProtoService().initiate();
	return 0;
}
