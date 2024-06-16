cmake_minimum_required(VERSION 3.15)
project(service_test CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch CPM if not already present
if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/cpm.cmake
        "${CMAKE_BINARY_DIR}/cmake/CPM.cmake"
    )
endif()

# Add CPM
include("${CMAKE_BINARY_DIR}/cmake/CPM.cmake")

# Find Protobuf
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
message(STATUS "Using Protobuf ${Protobuf_VERSION}")

# Run userver build:
CPMAddPackage(
    NAME userver
    #VERSION (userver release version or git commit hash)
    #GIT_TAG ("v2.1")
    GIT_TAG bb713ea

    GITHUB_REPOSITORY userver-framework/userver
    OPTIONS
    "USERVER_FEATURE_GRPC ON"
)

# Find userver package
#find_package(userver REQUIRED)

# Add your executable or library
add_executable(${PROJECT_NAME} main.cpp)

# Link userver library
target_link_libraries(${PROJECT_NAME} userver::grpc)
