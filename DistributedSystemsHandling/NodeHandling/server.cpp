#include<RemoteProcedureCalls.h>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <server.h>
#define IFF_LOOPBACK 0x8



namespace endpoints{
 Server::Server():ipPort(getLocalIP()){}

 std::string Server::getLocalIP() {
  struct ifaddrs *interfaces = nullptr;
  struct ifaddrs *ifa = nullptr;
  char ip[INET_ADDRSTRLEN];
  if (getifaddrs(&interfaces) == -1) {
   return ""; // Error retrieving interfaces
  }
  // Loop through the list of interfaces
  for (ifa = interfaces; ifa != nullptr; ifa = ifa->ifa_next) {
   // Check for IPv4 address and non-loopback interfaces
   if (ifa->ifa_addr->sa_family == AF_INET && 
    !(ifa->ifa_flags & IFF_LOOPBACK)) {
    struct sockaddr_in *sa_in = reinterpret_cast<struct sockaddr_in *>(ifa->ifa_addr);
    inet_ntop(AF_INET, &(sa_in->sin_addr), ip, INET_ADDRSTRLEN);
    freeifaddrs(interfaces);
    return std::string(ip); // Return the first valid IP address
   }
  }
  freeifaddrs(interfaces);
  return ""; // No valid IP address found 
 }
 void Server::runServer(std::string &folderPath){
  if((this->ipPort)=="")return;
  CommunicationServiceServer serverImpl(folderPath);
  grpc::ServerBuilder builder;
  builder.AddListeningPort(this->ipPort,grpc::InsecureServerCredentials());
  builder.RegisterService(&serverImpl);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
 }
}