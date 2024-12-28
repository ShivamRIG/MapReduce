// #include <algorithm>
#include "RemoteProcedureCalls.h"
#include <iostream>
#include "gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"
#include <fstream>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <vector>
// Constructor


CommunicationServiceServer::CommunicationServiceServer() {
 // this->data_transfer_rate=dataTransferRate*1024;//In kilobytes/per write
 this->folderPath="/home/mahesh/temp_mapReduce/server/";
}
// // Destructor
CommunicationServiceServer::~CommunicationServiceServer() {
}
grpc::Status CommunicationServiceServer::getFile(grpc::ServerContext* context, 
 const FileRequest* fileRequest,
 grpc::ServerWriter<FileChunk>* writer){
 int64_t keyl=fileRequest->keyl(),keyh=fileRequest->keyh(),startFrom=fileRequest->startfrom(),fileNumber=fileRequest->filenumber();
 std::string filePath=folderPath+std::to_string(keyl)+"_"+std::to_string(keyh)+"_"+std::to_string(fileNumber)+".txt";
 FileChunk chunk;
 char buffer[1024*(this->data_transfer_rate)];// there is some error when trying variable sized array(tried using vector)
 std::ifstream file(filePath,std::ios::binary);
 if (!file.is_open()) {
  std::cout<<filePath<<'\n';
  return grpc::Status(grpc::StatusCode::NOT_FOUND, "File not found");
 }
 file.seekg(startFrom*(this->data_transfer_rate));
 while(file.read(buffer,sizeof(buffer)) || file.gcount()>0){
  chunk.set_data(buffer,file.gcount());
  chunk.set_chunk_number(startFrom);
  chunk.set_size(file.gcount());
  writer->Write(chunk);
  startFrom++;
  
 }
 return grpc::Status::OK;
}

CommunicationServiceClient::CommunicationServiceClient(std::shared_ptr<::grpc::Channel> channel)
: stub_(CommunicationService::NewStub(channel)) {
 this->folderPath="/home/mahesh/temp_mapReduce/client/";
}
void CommunicationServiceClient::getFile(int64_t startFrom,int64_t keyl,int64_t keyh,int64_t fileNumber){
 FileRequest request;
 grpc::ClientContext context;
 FileChunk chunk;
 
 request.set_filenumber(fileNumber);
 request.set_keyh(keyh);
 request.set_keyl(keyl);
 request.set_startfrom(startFrom);
 std::string filePath=folderPath+std::to_string(keyl)+"_"+std::to_string(keyh)+"_"+std::to_string(fileNumber)+".txt";
 std::cout<<filePath<<'\n';
 std::ofstream file(filePath, std::ios::out | std::ios::binary); 
 std::unique_ptr<grpc::ClientReader<FileChunk>> reader(stub_->getFile(&context,request));
 while(reader->Read(&chunk)){
  file.write(chunk.data().data(),chunk.size());
 }
 grpc::Status status = reader->Finish();
  if (status.ok()) {
      std::cout << "ListFeatures rpc succeeded." << std::endl;
    }
    else {
      std::cout<<status.error_message()<<'\n';
      std::cout << "ListFeatures rpc failed." << std::endl;
    }

}
// // Method Implementation
// ::grpc::Status makeCall::makeSomeRpcCall(::grpc::ServerContext* context, 
//                                          const ::someMessage* request, 
//                                          ::someOtherMessage* response) {
//     std::cout << "RPC method called\n";
//     response->set_data(request->name());
//     return grpc::Status::OK;
// }