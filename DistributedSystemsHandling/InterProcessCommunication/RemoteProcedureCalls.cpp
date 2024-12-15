// #include <algorithm>
#include "RemoteProcedureCalls.h"
#include <iostream>
#include "gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"

// Constructor
makeCall::makeCall() {
    std::cout << "makeCall constructor called\n";
}

// Destructor
makeCall::~makeCall() {
    std::cout << "makeCall destructor called\n";
}

// Method Implementation
::grpc::Status makeCall::makeSomeRpcCall(::grpc::ServerContext* context, 
                                         const ::someMessage* request, 
                                         ::someOtherMessage* response) {
    std::cout << "RPC method called\n";
    response->set_data(request->name());
    return grpc::Status::OK;
}