cmake_minimum_required (VERSION 2.6)
project (silencer)
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
SET(CMAKE_BUILD_TYPE release)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
include_directories("${PROJECT_BINARY_DIR}")

# add executable
add_executable(silencer src/problem17.cc)

# link dirs
target_link_libraries(silencer ${CMAKE_THREAD_LIBS_INIT}
  opencv_core opencv_imgproc opencv_highgui opencv_ml
  opencv_video opencv_features2d opencv_calib3d opencv_objdetect
  opencv_contrib opencv_legacy opencv_flann )
