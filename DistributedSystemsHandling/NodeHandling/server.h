
#ifndef ENDPOINT_SERVER
#define ENDPOINT_SERVER
#include<RemoteProcedureCalls.h>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IFF_LOOPBACK 0x8
namespace endpoints{
class Server{
  private:
   const std::string ipPort;
   std::string getLocalIP();
  public:
   Server();
   void runServer(std::string &folderPath);

};
}

#endif