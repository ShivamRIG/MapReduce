add_library(NodeHandling STATIC
masterNode.cpp
)
target_include_directories(NodeHandling PUBLIC ${PROJECT_SOURCE_DIR}/DistributedSystemsHandling/NodeHandling)