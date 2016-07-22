cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++11")

project(CHAT)
set(EXECUTABLE_OUTPUT_PATH ${CHAT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CHAT_BINARY_DIR}/lib)
add_subdirectory(src)
add_subdirectory(tests)
