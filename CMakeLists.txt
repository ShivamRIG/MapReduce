cmake_minimum_required(VERSION 3.13.4)
project(MapReduce)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(DistributedSystemsHandling)
add_executable(Node main.cpp)


target_link_libraries(Node
    InterProcessCommunication NodeHandling
)
