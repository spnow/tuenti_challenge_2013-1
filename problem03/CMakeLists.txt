cmake_minimum_required (VERSION 2.6)
project (finder)
SET(CMAKE_BUILD_TYPE debug)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
include_directories("${PROJECT_BINARY_DIR}")

# boost
set(Boost_USE_STATIC_LIBS ON)
set(BUILD_SHARED_LIBS FALSE)
find_package(Boost)

# add modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../lib/cmake")

set(sources src/finder.cc)

set(SourceFiles ${sources})

################################
# GTest and GMock
################################
enable_testing()
set(GMOCK_ROOT "../lib/gmock-1.6.0/")
set(GTEST_ROOT "${GMOCK_ROOT}/gtest/")
find_package(GMock REQUIRED)

################################
# Tests
################################
# Add test file
file(GLOB TestFiles **/*_test.cc)

# add executable
add_executable(finder src/problem3.cc ${SourceFiles})
add_executable(runTests ${SourceFiles} ${TestFiles})
# Link test executable against gtest & gtest_main
add_test(runTests build/runTests)

include_directories(${Boost_INCLUDE_DIRS} 
    ${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})
# link dirs
target_link_libraries(finder ${Boost_INCLUDE_DIRS} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(runTests ${Boost_INCLUDE_DIRS} ${CMAKE_THREAD_LIBS_INIT}
    ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES} pthread dl )
