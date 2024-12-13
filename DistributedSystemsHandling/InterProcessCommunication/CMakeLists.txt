


find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)



add_library(InterProcessCommunication STATIC
RemoteProcedureCalls.cpp
)
target_link_libraries(InterProcessCommunication gRPC::grpc++)


add_library(protoCommunicationLib STATIC
protofiles/server.proto
)
target_link_libraries(protoCommunicationLib gRPC::grpc++)

target_include_directories(protoCommunicationLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )# CMAKE_CURRENT_BINARY_DIR refers to where build is taking place
protobuf_generate(TARGET protoCommunicationLib LANGUAGE cpp)


target_include_directories(InterProcessCommunication PUBLIC ${PROJECT_SOURCE_DIR}/DistributedSystemsHandling/InterProcessCommunication)