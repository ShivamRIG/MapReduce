#ifndef RemoteProcedureCalls

#define RemoteProcedureCalls
#include <iostream>
#include "gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>
#include <fstream>
#include <vector>

// const std::string folderPath;
class CommunicationServiceServer : public CommunicationService :: Service{
 private:
  static const int data_transfer_rate=5;// In kilobytes
  std::string folderPath;

 public:
  CommunicationServiceServer();
  ~CommunicationServiceServer() override;
  ::grpc::Status getFile(::grpc::ServerContext* context, const ::FileRequest* request, ::grpc::ServerWriter< ::FileChunk>* writer)override;
    
};
class CommunicationServiceClient {
 private:
  std::unique_ptr<CommunicationService::Stub> stub_;
  std::string folderPath;
 public:
 CommunicationServiceClient(std::shared_ptr<grpc::Channel> channel); 

 void getFile(int64_t startFrom,int64_t keyl,int64_t keyh,int64_t fileNumber);
};
#endif
