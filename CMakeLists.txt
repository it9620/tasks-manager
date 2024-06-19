cmake_minimum_required(VERSION 3.15)
project(service_test CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

#add_subdirectory(third_party/userver)

# Find userver package
find_package(userver REQUIRED)

#include_directories(${userver_INCLUDE_DIRS})

include_directories(/tmp/userver)

###################################################################################################
# Add your executable or library
# add_executable(${PROJECT_NAME} src/main.cpp)

userver_setup_environment()


# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
    src/hello.hpp
    src/hello.cpp
)
target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver::core)


# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)

# Link userver library
# target_link_libraries(${PROJECT_NAME} userver::grpc ${Protobuf_LIBRARIES} gRPC::grpc++ gRPC::grpc)
