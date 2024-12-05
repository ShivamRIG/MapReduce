cmake_minimum_required(VERSION 3.13.4)

project(MapReduce)
add_subdirectory(DistributedSystemsHandling)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(MapReduce 
    InterProcessCommunication
)