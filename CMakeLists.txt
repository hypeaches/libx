cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(x)

add_compile_options(-g)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR})

set(X_SRC
        src/error/error_info_factory.cpp
        src/error/error_info_impl.cpp
        src/error/error_info.cpp
        src/string/stringbuf.cpp
        src/task/thread_task/thread_pool_impl.cpp
        src/task/thread_task/thread_pool.cpp
        src/task/timer_task/timer_impl.cpp
        src/task/timer_task/timer_task_impl.cpp
        src/task/timer_task/timer_task.cpp
)

add_library(${PROJECT_NAME} ${X_SRC})
target_link_libraries(${PROJECT_NAME} pthread)