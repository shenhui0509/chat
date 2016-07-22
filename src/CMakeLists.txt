cmake_minimum_required(VERSION 2.8)
project(CHAT_LIB)
include_directories(${CHAT_SOURCE_DIR}/include)

file(GLOB LIB_SRC "*.cc")
add_library(chat SHARED ${LIB_SRC})
