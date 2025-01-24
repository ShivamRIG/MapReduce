// #include <algorithm>
#include "RemoteProcedureCalls.h"
#include <iostream>
#include "gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"
#include <fstream>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <vector>




// Server Code

// Constructor
CommunicationServiceServer::CommunicationServiceServer(std::string &folderPath) {
 this->folderPath=folderPath;
}
// Destructor
CommunicationServiceServer::~CommunicationServiceServer() {
}
grpc::Status CommunicationServiceServer::getFile(grpc::ServerContext* context, 
 const FileRequest* fileRequest,
 grpc::ServerWriter<FileChunk>* writer){
 std::string fileName=fileRequest->filename(),extension=fileRequest->extension(),task=fileRequest->task();
 int64_t startFrom=fileRequest->startfrom();
 std::string filePath=folderPath+task+"/"+fileName+extension;
 FileChunk chunk;
 char buffer[1024*(this->data_transfer_rate)];// there is some error when trying variable sized array(tried using vector), also this is a const value
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
void CommunicationServiceServer::setFolderPath(std::string &folderpath){
  this->folderPath=folderpath;
}




//Client Code
CommunicationServiceClient::CommunicationServiceClient(std::string &folderPath)
{
 this->folderPath=folderPath;
}


void CommunicationServiceClient::addStub(std::string ipPort){
  (this->stubs)[ipPort]=CommunicationService::NewStub(grpc::CreateChannel(ipPort,
   grpc::InsecureChannelCredentials()));
}


void CommunicationServiceClient::getFile(int64_t startFrom,std::string fileName,std::string task,std::string,std::string extension,std::string ipPort){
 FileRequest request;
 grpc::ClientContext context;
 FileChunk chunk;
 request.set_filename(fileName);
 request.set_task(task);
 request.set_extension(extension);
 request.set_startfrom(startFrom);
 std::string filePath=folderPath+task+"/"+fileName+extension;
 std::cout<<filePath<<'\n';
 std::ofstream file(filePath, std::ios::out | std::ios::binary); 
 std::unique_ptr<grpc::ClientReader<FileChunk>> reader(stubs[ipPort]->getFile(&context,request));
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


void CommunicationServiceClient::setFolderPath(std::string &folderpath){
  this->folderPath=folderpath;
}


// // Method Implementation
// ::grpc::Status makeCall::makeSomeRpcCall(::grpc::ServerContext* context, 
//                                          const ::someMessage* request, 
//                                          ::someOtherMessage* response) {
//     std::cout << "RPC method called\n";
//     response->set_data(request->name());
//     return grpc::Status::OK;
// }