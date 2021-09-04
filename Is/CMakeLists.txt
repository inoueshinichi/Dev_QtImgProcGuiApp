cmake_minimum_required(VERSION 3.14.6)
###############################################################################
# Version
###############################################################################
# Project Version
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt versions NEWLINE_CONSUME)
string(REGEX REPLACE [[^([A-z0-9.\-_]+).*$]] [[\1]] version ${versions})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\1]] version_major ${version})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\2]] version_minor ${version})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\3]] version_patch ${version})

# Project
get_filename_component(DIRNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${DIRNAME} LANGUAGES C CXX VERSION ${version_major}.${version_minor}.${version_patch})

message(STATUS ">>>>> ${PROJECT_NAME}")

message(STATUS "========== [START] Version Management ==========")
message(STATUS "CMake Ver: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION}")
message(STATUS "Project Ver: ${version_major}.${version_minor}.${version_patch}")
message(STATUS "========== [END] Version Management ==========")

###############################################################################
# C++ core
###############################################################################
message(STATUS "========== [START] C++ Build Core ==========")

# Third-party
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party)

# Include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/IsCommon)
# add_subdirectory(src/IsNdArray)
# add_subdirectory(src/IsCv)

message(STATUS "========== [END] C++ Build Core ==========")

###############################################################################
# C++ Testing
###############################################################################
message(STATUS "========== [START] Test ==========")

# Google Test
if(BUILD_CPP_TEST)
include(CTest)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

message(STATUS "========== [END] Test ==========")

message(STATUS "<<<<< ${PROJECT_NAME}")