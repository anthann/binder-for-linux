#ifndef BASIC_SERVICE
#define BASIC_SERVICE
#include <stdio.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include "proto_service.pb.h"

using namespace android;

class IProtoService: public IInterface {
	public:
		DECLARE_META_INTERFACE(ProtoService);
		virtual proto_service::Empty setText(proto_service::Data) = 0;
		virtual proto_service::Data getText(proto_service::Empty) = 0;
};

class BnProtoService: public BnInterface<IProtoService> {
	public:
		virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
};

#endif 
