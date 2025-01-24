add_library(NodeHandling STATIC
masterNode.cpp 
# client.cpp 
server.cpp
# channels.cpp
)
target_include_directories(NodeHandling PUBLIC ${PROJECT_SOURCE_DIR}/DistributedSystemsHandling/NodeHandling)
target_link_libraries(NodeHandling PUBLIC InterNodeCommunication)
# target_link_libraries(InterNodeCommunication gRPC_Communication_Lib gRPC::grpc++)
