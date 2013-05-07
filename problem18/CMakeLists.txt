cmake_minimum_required (VERSION 2.6)
project (floyder)
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x -O3 -march=native -mtune=native ${CMAKE_CXX_FLAGS}")
SET(CMAKE_BUILD_TYPE release)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
include_directories("${PROJECT_BINARY_DIR}")

# boost
set(Boost_USE_STATIC_LIBS ON)
set(BUILD_SHARED_LIBS FALSE)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS thread REQUIRED)
find_package(Threads REQUIRED)

# add executable
add_executable(floyder src/problem18.cc)

# link dirs
target_link_libraries(floyder ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
