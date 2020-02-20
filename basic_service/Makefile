all: server client

IBasicService.o: IBasicService.cpp 
	g++ -std=c++11 -c $< -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lpthread

server.o: server.cpp
	g++ -std=c++11 -c $< -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lpthread
	
client.o: client.cpp
	g++ -std=c++11 -c $< -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lpthread

server: server.o IBasicService.o
	g++ -std=c++11 -o $@ $^  -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lpthread

client: client.o IBasicService.o
	g++ -std=c++11 -o $@ $^  -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lpthread

clean:
	rm -f server client *.o
