cmake_minimum_required (VERSION 2.6)
project (mazer)
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
SET(CMAKE_BUILD_TYPE debug)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
include_directories("${PROJECT_BINARY_DIR}")

# add modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../lib/cmake")

set(sources src/mazer.cc)

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
add_executable(mazer src/problem6.cc ${SourceFiles})
add_executable(runTests ${SourceFiles} ${TestFiles})
# Link test executable against gtest & gtest_main
add_test(runTests build/runTests)

include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})
# link dirs
target_link_libraries(mazer ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(runTests ${CMAKE_THREAD_LIBS_INIT}
    ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES} pthread dl )
