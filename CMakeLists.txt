cmake_minimum_required(VERSION 3.25.1)

project(Playground)

# find_package(Boost REQUIRED)
# find_package(FFMPEG REQUIRED)
# find_package(fmt CONFIG REQUIRED)
# find_package(spdlog CONFIG REQUIRED)
# find_package(unofficial-breakpad CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(gstreamer-1.0 REQUIRED gstreamer-1.0)
include_directories(${gstreamer-1.0_INCLUDE_DIRS})
link_directories(${gstreamer-1.0_LIBRARY_DIRS})

pkg_check_modules(glib-2.0 REQUIRED glib-2.0)
include_directories(${glib-2.0_INCLUDE_DIRS})
link_directories(${glib-2.0_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++23")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")

# add_subdirectory(cpp)
add_subdirectory(codec)
add_subdirectory(gst)
