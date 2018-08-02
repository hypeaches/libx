cmake_minimum_required(VERSION 3.5)

project(x)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

file(GLOB_RECURSE LIBX_SRC_LIST ./src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} STATIC ${LIBX_SRC_LIST})
