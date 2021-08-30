cmake_minimum_required(VERSION 3.14.0)

set(LIB_NAME IsCommonLib)

project(${LIB_NAME} LANGUAGES C CXX VERSION ${version_major}.${version_minor}.${version_patch})

message(STATUS ">>>>> ${LIB_NAME}")

# Sources
file(GLOB LIB_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp
    src/singleton/*.cpp
)

# Win32
if (MSVC)
    # Sources
    file(GLOB LIB_WIN32_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        src/win32/*.cpp
    )
    
    # Window(10以降)の場合で, デフォルト(ANSI)コードページ(FileIOなどのエンコード)を強制的にUTF-8にする.
    # プログラム内部からはsetlocale(LC_ALL, ""), std::locale::global(std::locale(""))などで, 
    # システムのデフォルトコードページにすると, OS側でANSIコードページがUTF-8の場合、プログラムに反映できる.
    # ここでは外部(CMake)から設定する方式となる.
    if(BUILD_CPP_MSVC_DEFAULT_LOCALE_UTF8)
        list(APPEND LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/win32/win32_utf8-manifest.xml)
    endif()

    list(APPEND LIB_SOURCES ${LIB_WIN32_SOURCES})
endif()


# Library
if(BUILD_CPP_SHARED_LIBS)
    add_library(${LIB_NAME} SHARED ${LIB_SOURCES})
else()
    add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
endif()


# Include
target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)



if(MSVC)
    # msvc does not append 'lib' - do it here to have consistent name
    set_target_properties(${LIB_NAME} PROPERTIES PREFIX "lib")
    set_target_properties(${LIB_NAME} PROPERTIES IMPORT_PREFIX "lib")
endif()


# EXPORTS or dbg_EXPORTS 定義済みマクロを設定 for windows *.dll
target_compile_definitions(${LIB_NAME} PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:${LIB_NAME}_EXPORTS>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:${LIB_NAME}_dbg_EXPORTS>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:MinSizeRel>>:${LIB_NAME}_EXPORTS>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelWithDebgInfo>>:${LIB_NAME}_dbg_EXPORTS>
)


set(IS_COMMONLIB_TARGET_NAME ${LIB_NAME} PARENT_SCOPE)


message(STATUS "<<<<< ${LIB_NAME}")