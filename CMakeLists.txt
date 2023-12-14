cmake_minimum_required(VERSION 3.25.1)

project(Playground)

find_package(Boost REQUIRED)
# find_package(FFMPEG REQUIRED)
# find_package(fmt CONFIG REQUIRED)
# find_package(spdlog CONFIG REQUIRED)
# find_package(unofficial-breakpad CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++23")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")

add_subdirectory(cpp)
add_subdirectory(codec)
