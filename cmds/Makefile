all: service

service: service.cpp
	g++ -std=c++11 -o $@ -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1 $<  -lbinder -lpthread

clean:
	rm -f service
