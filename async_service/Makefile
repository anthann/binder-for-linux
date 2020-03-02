all: server client

ICallbackInterface.o: ICallbackInterface.cpp
	g++ -std=c++11 -c $< -I../libs/include -I..

CallbackInterfaceImpl.o: CallbackInterfaceImpl.cpp
	g++ -std=c++11 -c $< -I../libs/include -I..

ITestInterface.o: ITestInterface.cpp
	g++ -std=c++11 -c $< -I../libs/include -I..

TestInterfaceImpl.o: TestInterfaceImpl.cpp
	g++ -std=c++11 -c $< -I../libs/include -I..

server.o: server.cpp
	g++ -std=c++11 -c $< -I../libs/include -I..

client.o: client.cpp
	g++ -std=c++11 -c $< -I../libs/include -I..

server: ICallbackInterface.o ITestInterface.o TestInterfaceImpl.o server.o
	g++ -std=c++11 -o $@ $^  -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lpthread

client: ICallbackInterface.o ITestInterface.o CallbackInterfaceImpl.o client.o
	g++ -std=c++11 -o $@ $^  -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lpthread

clean:
	rm -f server client *.o
