project(VDSProject_verify CXX C)
cmake_minimum_required(VERSION 3.10)

add_executable(VDSProject_verify main_verify.cpp)
target_link_libraries(VDSProject_verify Manager)
