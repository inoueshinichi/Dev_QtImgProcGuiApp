cmake_minimum_required(VERSION 3.14.6)

include(${CMAKE_CURRENT_SOURCE_DIR}/../test_case.cmake)


make_test_case("test_imgproc_io.cpp" "test_imgproc_io")
make_test_case("test_imgproc_blur.cpp" "test_imgproc_blur")
make_test_case("test_imgproc_edge_detector.cpp" "test_imgproc_edge_detector")




