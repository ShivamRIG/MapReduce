find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_subdirectory(protofiles)



# target_include_directories(protoCommunicationLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )# CMAKE_CURRENT_BINARY_DIR refers to where build is taking place

add_library(InterNodeCommunication STATIC
RemoteProcedureCalls.cpp
)
target_link_libraries(InterNodeCommunication gRPC::grpc++)

target_link_libraries(InterNodeCommunication gRPC_Communication_Lib)

target_include_directories(InterNodeCommunication PUBLIC ${PROJECT_SOURCE_DIR}/DistributedSystemsHandling/InterNodeCommunication)