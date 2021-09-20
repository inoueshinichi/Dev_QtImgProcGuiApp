cmake_minimum_required(VERSION 3.14.6)

# Get dirname and set it to libname.
get_filename_component(DIRNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(LIB_TARGET_NAME ${DIRNAME})

project(${LIB_TARGET_NAME} LANGUAGES C CXX VERSION ${version_major}.${version_minor}.${version_patch})

message(STATUS ">>>>> ${LIB_TARGET_NAME}")

# Sources
file(GLOB LIB_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ./*.cpp
)

# Win32
if(MSVC)
    # Sources
    file(GLOB LIB_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        win32/*.cpp
    )
    
    # Window(10以降)の場合で, デフォルト(ANSI)コードページ(FileIOなどのエンコード)を強制的にUTF-8にする.
    # プログラム内部からはsetlocale(LC_ALL, ""), std::locale::global(std::locale(""))などで, 
    # システムのデフォルトコードページにすると, OS側でANSIコードページがUTF-8の場合、プログラムに反映できる.
    # ここでは外部(CMake)から設定する方式となる.
    if(BUILD_CPP_MSVC_DEFAULT_LOCALE_UTF8)
        list(APPEND LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/win32/win32_utf8-manifest.xml)
    endif()

    # Version
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/version-utf8.rc
    )
    execute_process(
        COMMAND ${PYTHON_INTERPRETER}
        ${CMAKE_CURRENT_SOURCE_DIR}/../build-tools/utf8_to_utf16.py
        ${CMAKE_CURRENT_BINARY_DIR}/version-utf8.rc ${CMAKE_CURRENT_BINARY_DIR}/version.rc
    )
    list(APPEND SOURCES ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
endif()


# Library
if(BUILD_CPP_SHARED_LIBS)
    add_library(${LIB_TARGET_NAME} SHARED ${LIB_SOURCES})
else()
    add_library(${LIB_TARGET_NAME} STATIC ${LIB_SOURCES})
endif()

# Thread
find_package(Threads REQUIRED)
target_link_libraries(${LIB_TARGET_NAME}
    PRIVATE Threads::Threads
)


# PDBファイルを出力する
if(MSVC)
    set_target_properties(${LIB_TARGET_NAME} PROPERTIES
        COMPILE_PDB_NAME ${LIB_TARGET_NAME}
    )
endif()


# EXPORTS or dbg_EXPORTS 定義済みマクロを設定 for windows *.dll
target_compile_definitions(${LIB_TARGET_NAME} PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:${LIB_TARGET_NAME}_EXPORTS>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:${LIB_TARGET_NAME}_dbg_EXPORTS>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:MinSizeRel>>:${LIB_TARGET_NAME}_EXPORTS>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelWithDebgInfo>>:${LIB_TARGET_NAME}_dbg_EXPORTS>
)

set(IS_COMMON_TARGET_NAME ${LIB_TARGET_NAME} PARENT_SCOPE)

message(STATUS "<<<<< ${LIB_TARGET_NAME}")