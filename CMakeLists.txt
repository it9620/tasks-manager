cmake_minimum_required(VERSION 3.14)
project(userver-samples-hello_service CXX)

###################################################################################################
# Fetch CPM if not already present
if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/cpm.cmake
        "${CMAKE_BINARY_DIR}/cmake/CPM.cmake"
    )
endif()

# Add CPM / Include CPM
#include(cmake/CPM.cmake)
include("${CMAKE_BINARY_DIR}/cmake/CPM.cmake")

###################################################################################################
# Set Protobuf and gRPC directories
set(Protobuf_DIR "/usr/local/lib/cmake/protobuf")
set(gRPC_DIR "/usr/local/lib/cmake/grpc")

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS} ${gRPC_INCLUDE_DIRS})
message(STATUS "Using Protobuf ${Protobuf_VERSION}")


###################################################################################################
# Run userver build:
CPMAddPackage(
    NAME userver
    #VERSION (userver release version or git commit hash)
    #GIT_TAG ("v2.1")
    GIT_TAG bb713ea

    #GIT_REPOSITORY https://github.com/userver-framework/userver.git
    GITHUB_REPOSITORY userver-framework/userver
    OPTIONS
    "USERVER_FEATURE_GRPC ON"
)

###################################################################################################
# Adding userver dependency
 
find_package(userver COMPONENTS core REQUIRED)
# Note: If userver was added via add_subdirectory(path/to/userver), then
# the userver_setup_environment() should be called here.
userver_setup_environment()

# 
 
# 
add_library(${PROJECT_NAME}_objs OBJECT
    src/say_hello.hpp
    src/say_hello.cpp
    src/hello_service.hpp
    src/hello_service.cpp
)
target_link_libraries(${PROJECT_NAME}_objs userver::core)
target_include_directories(${PROJECT_NAME}_objs PUBLIC src)
# 
 
# 
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_objs)
# 
 
# 
add_executable(${PROJECT_NAME}-unittest unittests/say_hello_test.cpp)
target_link_libraries(${PROJECT_NAME}-unittest ${PROJECT_NAME}_objs userver::utest)
add_google_tests(${PROJECT_NAME}-unittest)
# 
 
# 
add_executable(${PROJECT_NAME}_benchmark benchmarks/say_hello_bench.cpp)
target_link_libraries(${PROJECT_NAME}_benchmark ${PROJECT_NAME}_objs userver::ubench)
add_google_benchmark_tests(${PROJECT_NAME}_benchmark)
# 
 
# 
# Makes a virtualenv suitable for running pytests from `test` directory and integrates with `ctest`.
userver_testsuite_add_simple()
# 
