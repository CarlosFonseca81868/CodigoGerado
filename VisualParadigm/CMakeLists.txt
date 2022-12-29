cmake_minimum_required(VERSION 3.16.3)
project(ForbiddenDesert)

set(CMAKE_CXX_STANDARD 14) # enable C++14 standard
include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDebug")

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
  "${PROJECT_SOURCE_DIR}/*.h"
  "${PROJECT_SOURCE_DIR}/*.hpp"
  "${PROJECT_SOURCE_DIR}/*.cpp"
  "${PROJECT_SOURCE_DIR}/*.c"
)

add_executable(generator ${all_SRCS})
target_link_libraries(generator Threads::Threads)
