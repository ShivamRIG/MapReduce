#ifndef RemoteProcedureCalls

#define RemoteProcedureCalls
#include <iostream>
#include "gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"

// Class Declaration
class makeCall : public someService::Service {
public:
    makeCall();
    ~makeCall() override;

    ::grpc::Status makeSomeRpcCall(::grpc::ServerContext* context, 
                                   const ::someMessage* request, 
                                   ::someOtherMessage* response) override;
};


#endif