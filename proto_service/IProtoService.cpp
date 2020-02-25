#include <string>
#include "IProtoService.h"

enum {
	SETTEXT = IBinder::FIRST_CALL_TRANSACTION,
	GETTEXT = IBinder::FIRST_CALL_TRANSACTION + 1,
};

class BpProtoService: public BpInterface<IProtoService> {
	public:
		BpProtoService(const sp<IBinder>& impl): BpInterface<IProtoService>(impl) {}
        int setText(const proto_service::Data& req, proto_service::Empty* resp) {
			printf("BpProtoService::setText\n");
			Parcel data, reply;
			data.writeInterfaceToken(IProtoService::getInterfaceDescriptor());
            size_t size = req.ByteSizeLong();
            if (size) {
                void *buffer = malloc(size);
                req.SerializeToArray(buffer, size);
                data.writeByteArray(size, static_cast<uint8_t *>(buffer));
                free(buffer);
            }
			remote()->transact(SETTEXT, data, &reply);
            int ret = reply.readInt32();
            int respSize = reply.readInt32();
            // https://github.com/Emill/android_bluetooth/blob/master/service/ipc/binder/parcel_helpers.cpp#L42
            if (respSize != -1) {
                void *buffer = malloc(respSize); 
                reply.read(buffer, respSize);
                resp->ParseFromArray(buffer, respSize);
                free(buffer);
            }
            return ret;
		}

        int getText(const proto_service::Empty& req, proto_service::Data* resp) {
			printf("BpProtoService::getText\n");
			Parcel data, reply;
			data.writeInterfaceToken(IProtoService::getInterfaceDescriptor());
            size_t size = req.ByteSizeLong();
            if (size) {
                void *buffer = malloc(size);
                req.SerializeToArray(buffer, size);
                data.writeByteArray(size, static_cast<uint8_t *>(buffer));
                free(buffer);
            }
			remote()->transact(GETTEXT, data, &reply);
            int ret = reply.readInt32();
            int respSize = reply.readInt32();
            if (respSize != -1) {
                void *buffer = malloc(respSize); 
                reply.read(buffer, respSize);
                resp->ParseFromArray(buffer, respSize);
                free(buffer);
            }
            return 0;
		}
};

IMPLEMENT_META_INTERFACE(ProtoService, "me.anthann.protoservice");

status_t BnProtoService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags) {
    printf("BnProtoService::onTransace");
	switch(code) {
	case SETTEXT: {
		CHECK_INTERFACE(IProtoService, data, reply);
        int reqSize = data.readInt32();
        proto_service::Data req;
        if (reqSize != -1) {
            void *buffer = malloc(reqSize); 
            data.read(buffer,reqSize);
            req.ParseFromArray(buffer, reqSize);
            free(buffer);
        }
        proto_service::Empty resp;
        int ret = setText(req, &resp);
        reply->writeInt32(ret);
        size_t respSize = resp.ByteSizeLong();
        if (respSize) {
            void *buffer = malloc(respSize);
            resp.SerializeToArray(buffer, respSize);
            reply->writeByteArray(respSize, static_cast<uint8_t *>(buffer));
            free(buffer);
        }
		break;
	}	
	case GETTEXT: {
		CHECK_INTERFACE(IProtoService, data, reply);
        int reqSize = data.readInt32();
        proto_service::Empty req;
        if (reqSize != -1) {
            void *buffer = malloc(reqSize); 
            data.read(buffer, reqSize);
            req.ParseFromArray(buffer, reqSize);
            free(buffer);
        }
        proto_service::Data resp;
        int ret = getText(req, &resp);
        reply->writeInt32(ret);
        size_t respSize = resp.ByteSizeLong();
        if (respSize) {
            void *buffer = malloc(respSize);
            resp.SerializeToArray(buffer, respSize);
            reply->writeByteArray(respSize, static_cast<uint8_t *>(buffer));
            free(buffer);
        }
		break;
	}
	default:
		break;
	}
	return NO_ERROR;
}
