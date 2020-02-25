#include <string>
#include "IProtoService.h"

enum {
	SETTEXT = IBinder::FIRST_CALL_TRANSACTION,
	GETTEXT = IBinder::FIRST_CALL_TRANSACTION + 1,
};

class BpProtoService: public BpInterface<IProtoService> {
	public:
		BpProtoService(const sp<IBinder>& impl): BpInterface<IProtoService>(impl) {}
        proto_service::Empty setText(proto_service::Data req) {
			printf("BpProtoService::setText\n");
			Parcel data, reply;
			data.writeInterfaceToken(IProtoService::getInterfaceDescriptor());
            size_t size = req.ByteSizeLong();
            if (size) {
                void *sendBuffer = malloc(size);
                req.SerializeToArray(sendBuffer, size);
                data.writeByteArray(size, static_cast<uint8_t *>(sendBuffer));
                free(sendBuffer);
            }
			remote()->transact(SETTEXT, data, &reply);
            int respSize = reply.readInt32();
            proto_service::Empty resp;
            // https://github.com/Emill/android_bluetooth/blob/master/service/ipc/binder/parcel_helpers.cpp#L42
            if (respSize != -1) {
                void *respBuffer = malloc(respSize); 
                reply.read(respBuffer, respSize);
                resp.ParseFromArray(respBuffer, respSize);
                free(respBuffer);
            }
            return resp;
		}

        proto_service::Data getText(proto_service::Empty req) {
			printf("BpProtoService::getText\n");
			Parcel data, reply;
			data.writeInterfaceToken(IProtoService::getInterfaceDescriptor());
            size_t size = req.ByteSizeLong();
            if (size) {
                void *sendBuffer = malloc(size);
                req.SerializeToArray(sendBuffer, size);
                data.writeByteArray(size, static_cast<uint8_t *>(sendBuffer));
                free(sendBuffer);
            }
			remote()->transact(GETTEXT, data, &reply);
            int respSize = reply.readInt32();
            proto_service::Data resp;
            if (respSize != -1) {
                void *respBuffer = malloc(respSize); 
                reply.read(respBuffer, respSize);
                resp.ParseFromArray(respBuffer, respSize);
                free(respBuffer);
            }
            return resp;
		}
};

IMPLEMENT_META_INTERFACE(ProtoService, "me.anthann.protoservice");

status_t BnProtoService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags) {
    printf("BnProtoService::onTransace");
	switch(code) {
	case SETTEXT: {
		CHECK_INTERFACE(IProtoService, data, reply);
        int paramSize = data.readInt32();
        proto_service::Data param;
        if (paramSize != -1) {
            void *buffer = malloc(paramSize); 
            data.read(buffer, paramSize);
            param.ParseFromArray(buffer, paramSize);
            free(buffer);
        }
        proto_service::Empty resp = setText(param);
        size_t respSize = resp.ByteSizeLong();
        if (respSize) {
            void *respBuffer = malloc(respSize);
            resp.SerializeToArray(respBuffer, respSize);
            reply->writeByteArray(respSize, static_cast<uint8_t *>(respBuffer));
            free(respBuffer);
        }
		break;
	}	
	case GETTEXT: {
		CHECK_INTERFACE(IProtoService, data, reply);
        int paramSize = data.readInt32();
        proto_service::Empty param;
        if (paramSize != -1) {
            void *buffer = malloc(paramSize); 
            data.read(buffer, paramSize);
            param.ParseFromArray(buffer, paramSize);
            free(buffer);
        }
        proto_service::Data resp = getText(param);
        size_t respSize = resp.ByteSizeLong();
        if (respSize) {
            void *respBuffer = malloc(respSize);
            resp.SerializeToArray(respBuffer, respSize);
            reply->writeByteArray(respSize, static_cast<uint8_t *>(respBuffer));
            free(respBuffer);
        }
		break;
	}
	default:
		break;
	}
	return NO_ERROR;
}
