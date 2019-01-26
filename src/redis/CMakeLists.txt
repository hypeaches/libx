set(LIBXREDIS_PROJECT_NAME xredis)
set(HIREDIS_INCLUDE_DIR "/mnt/c/Users/liuxi/code/libx/github/hiredis")
set(HIREDIS_LIB_DIR "/mnt/c/Users/liuxi/code/libx/github/hiredis")

file(GLOB_RECURSE LIBXREDIS_SOURCE_LIST "*.cpp")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
add_library(${LIBXREDIS_PROJECT_NAME} STATIC ${LIBXREDIS_SOURCE_LIST})
include_directories(
    ${HIREDIS_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src/redis)
target_link_libraries(
    ${LIBXREDIS_PROJECT_NAME}
    ${HIREDIS_LIB_DIR}/libhiredis.a
)