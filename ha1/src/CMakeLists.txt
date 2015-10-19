cmake_minimum_required(VERSION 2.8)

project(huffman)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES "*.c" "*.cpp" "*.h" "*.hpp")

include_directories(
	${CMAKE_SOURCE_DIR}/src
)

add_executable(${PROJECT_NAME} ${SOURCES})
