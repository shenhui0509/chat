project(tests CXX C)
set(CMAKE_CXX_COMPIER clang)
cmake_minimum_required(VERSION 2.8)

set(INC_DIRS "~/Dev/googletest/googletest/include/" ${CHAT_SOURCE_DIR}/include)
include_directories(${INC_DIRS})

set(LIB_DIRS "~/Dev/googletest/googletest/build/" ${CHAT_BINARY_DIR}/lib)
link_directories(${LIB_DIRS})

add_executable(test_buffer "test_buffer.cc")
target_link_libraries(test_buffer chat gtest c++)


