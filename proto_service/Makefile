all: server client service

IProtoService.o: IProtoService.cpp 
	g++ -std=c++11 -c $< -I../libs/include -I.. 

server.o: server.cpp
	g++ -std=c++11 -c $< -I../libs/include -I..
	
client.o: client.cpp
	g++ -std=c++11 -c $< -I../libs/include -I..

WatchDog.o: WatchDog.cpp
	g++ -std=c++11 -c $<  -I../libs/include -I..

service.o: service.cpp
	g++ -std=c++11 -c $<  -I../libs/include -I..

proto_service.pb.o: proto_service.pb.cpp
	g++ -std=c++11 -c $< 

ProtoService.o: ProtoService.cpp
	g++ -std=c++11 -c $<  -I../libs/include -I..

service: proto_service.pb.o IProtoService.o ProtoService.o service.o WatchDog.o
	g++ -std=c++11 -o $@ $^  -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lprotobuf -lpthread 

server: proto_service.pb.o IProtoService.o ProtoService.o server.o
	g++ -std=c++11 -o $@ $^  -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lprotobuf -lpthread 

client: client.o IProtoService.o proto_service.pb.o
	g++ -std=c++11 -o $@ $^  -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1  -lbinder -lprotobuf -lpthread

clean:
	rm -f service server client *.o
