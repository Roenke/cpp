cmake_minimum_required(VERSION 3.0)


project(huffman)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

set(SOURCE_FILES src/main.cpp)
add_executable(huffman ${SOURCE_FILES})