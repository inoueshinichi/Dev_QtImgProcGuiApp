cmake_minimum_required(VERSION 3.14.6)

project(QtImgProcGuiApp LANGUAGES CXX VERSION 0.1.0)

###############################################################################
# Version
###############################################################################
message(STATUS "========== [START] Version Management ==========")
message(STATUS "CMake Ver: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION}")
message(STATUS "========== [END] Version Management ==========")

###############################################################################
# 全ターゲットに影響を与えるオプション
###############################################################################
message(STATUS "========== [START] C++ All Target Options ==========")

# Switching Option
option(BUILD_PYTHON_INTERPRETER "Enable/Disable: Python interpreter" OFF)
option(BUILD_CPP_OPENMP "Enable/Disable: OpenMP" OFF)
option(BUILD_CPP_TEST "Enable/Disable: Building Test" OFF)
option(BUILD_CPP_SHARED_LIBS "Enable/Disable: Shared Libraries" ON)
option(BUILD_CPP_ZERO_CHECK "Enable/Disable: ZERO_CHECK" OFF)
option(BUILD_CPP_MSVC_DEFAULT_LOCALE_UTF8 "Enable/Disable utf-8 default locale" OFF) # ANSI: ShiftJIS -> UTF8 @ Windows OS
option(BUILD_CPP_MSVC_STATIC_VCRUNTIME "Enable/Disable Static MSVC Runtime" OFF) # MD, MDd -> MT, MTd

# ZERO_CHECKプロジェクトの有無
if(NOT BUILD_CPP_ZERO_CHECK)
    set(CMAKE_SUPPRESS_REGENERATION true)
endif()

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message("CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

# ライブラリフラグ
set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_MINSIZEREL_POSTFIX _minsizerel)
set(CMAKE_RELWITHDEBINFO_POSTFIX _relwithdebinfo)

# プラットフォーム毎のコンパイラオプション(マルチ・コンフィギュレーションに対応)
if (MSVC)
    message(STATUS "Compiler: MSVC in Windows")

    # Build Options
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # デフォルトの`/W[0-4]`を削除
    set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /GR /EHsc /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "/Ob0 /Od /MDd /Zi /RTC1") # /MDd or /Od が指定されている場合、#include <windows>内部で_DEBUGマクロが定義される
    set(CMAKE_CXX_FLAGS_RELEASE "/Ob2 /O2 /MD /DNDEBUG") # /DNDEBUGマクロはstatic_assert()で利用する
    set(CMAKE_CXX_FLAGS_MINSIZEREL "/O1 /MD /DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Od /MDd /Zi /RTC1")

    # Select VC Runtime (Static or Shared)
    if(BUILD_CPP_MSVC_STATIC_VCRUNTIME)
        string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}")
        string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    endif()

    if(BUILD_CPP_OPENMP)
        message(STATUS "Enable OpenMP")
        find_package(OpenMP REQUIRED)
        include_directories(${OpenMP_INCLUDE_DIRS})
        link_directories(${OpenMP_LIBRARY})
        link_libraries(${OpenMP_LIBRARIES})
        add_compile_options("$<$<C_COMPILER_ID:MSVC>:/openmp>")
        add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/openmp>")
    endif()

    # ソースコードでUTF-8を使う(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

    # C++11以降を利用した場合にマクロ変数__cplusplusの値を利用中のC++バージョンに合わせる(つけないとC++98相当の値になる)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

    # オブジェクトファイル(*.obj)のサイズ制限を解放
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/bigobj>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/bigobj>")

    # プリプロセッサ準拠モードを有効にする
    # https://docs.microsoft.com/ja-jp/cpp/preprocessor/preprocessor-experimental-overview?view=msvc-160
    # https://docs.microsoft.com/ja-jp/cpp/build/reference/zc-preprocessor?view=msvc-160
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/Zc:preprocessor>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>")


    # MSVCの標準逸脱のコンパイラ仕様を回避する
    add_compile_definitions(_CRT_NONSTDC_NO_DEPRECATE) # mkdir, closeなどPOSIX関数でコンパイル時に警告発生（unsafe）を抑制.
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS) # strcpy、sprinitfなどでコンパイル時に警告発生（unsafe）を抑制.
    add_compile_definitions(_USE_MATH_DEFINES) # math.hに定義されている円周率等の物理定数を有効化する.

elseif(APPLE)
    message(STATUS "Compiler: Clang in macOS")    

    # message(FATAL_ERROR "No Implimentation of LLVM with Clang(++) in macOS.")

    # Build Options(マルチコンフィギュレーション対応)
    set(CMAKE_CXX_FLAGS "-O1")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    if(BUILD_CPP_OPENMP)
        message(STATUS "Enable OpenMP")
        find_package(OpenMP REQUIRED)
        include_directories(${OpenMP_INCLUDE_DIRS})
        link_directories(${OpenMP_LIBRARY})
        link_libraries(${OpenMP_LIBRARIES})
        add_compile_options("$<$<C_COMPILER_ID:GNU>:-fopenmp>")
        add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-fopenmp>")
    endif()

    # C++標準に準拠しない拡張機能を無効化
    # string(APPEND CMAKE_CXX_FLAGS " --pedantic-errors")

    string(APPEND CMAKE_CXX_FLAGS " -pedantic")
    string(APPEND CMAKE_CXX_FLAGS " -Wall")

else()
    message(STATUS "Compiler: GCC in Linux")

    # 詳細情報の表示
    set(CMAKE_VERBOSE_MAKEFILE ON)

    # Build Options(マルチコンフィギュレーション対応)
    set(CMAKE_CXX_FLAGS "-O1")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    if(BUILD_CPP_OPENMP)
        message(STATUS "Enable OpenMP")
        find_package(OpenMP REQUIRED)
        include_directories(${OpenMP_INCLUDE_DIRS})
        link_directories(${OpenMP_LIBRARY})
        link_libraries(${OpenMP_LIBRARIES})
        add_compile_options("$<$<C_COMPILER_ID:GNU>:-fopenmp>")
        add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-fopenmp>")
    endif()

    # C++標準に準拠しない拡張機能を無効化
    string(APPEND CMAKE_CXX_FLAGS " --pedantic-errors")

    # https://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings/9862800#9862800
    string(APPEND CMAKE_CXX_FLAGS " -pedantic")
    string(APPEND CMAKE_CXX_FLAGS " -Wall")
    # string(APPEND CMAKE_CXX_FLAGS " -Wextra")
    # string(APPEND CMAKE_CXX_FLAGS " -Wcast-align")
    # string(APPEND CMAKE_CXX_FLAGS " -Wcast-qual")
    # string(APPEND CMAKE_CXX_FLAGS " -Wctor-dtor-privacy")
    # string(APPEND CMAKE_CXX_FLAGS " -Wdisabled-optimization")
    # string(APPEND CMAKE_CXX_FLAGS " -Wformat=2 ")
    # string(APPEND CMAKE_CXX_FLAGS " -Winit-self")
    # string(APPEND CMAKE_CXX_FLAGS " -Wlogical-op")
    # string(APPEND CMAKE_CXX_FLAGS " -Wmissing-declarations")
    # string(APPEND CMAKE_CXX_FLAGS " -Wmissing-include-dirs")
    # string(APPEND CMAKE_CXX_FLAGS " -Wnoexcept")
    # string(APPEND CMAKE_CXX_FLAGS " -Wold-style-cast")
    # string(APPEND CMAKE_CXX_FLAGS " -Woverloaded-virtual")
    # string(APPEND CMAKE_CXX_FLAGS " -Wredundant-decls")
    # string(APPEND CMAKE_CXX_FLAGS " -Wshadow")
    # string(APPEND CMAKE_CXX_FLAGS " -Wsign-conversion")
    # string(APPEND CMAKE_CXX_FLAGS " -Wsign-promo")
    # string(APPEND CMAKE_CXX_FLAGS " -Wstrict-null-sentinel")
    # string(APPEND CMAKE_CXX_FLAGS " -Wstrict-overflow=5")
    # string(APPEND CMAKE_CXX_FLAGS " -Wswitch-default")
    # string(APPEND CMAKE_CXX_FLAGS " -Wundef")
    # string(APPEND CMAKE_CXX_FLAGS " -Werror")
    # string(APPEND CMAKE_CXX_FLAGS " -Wno-unused")

endif()

if(UNIX)
message(STATUS "---------- Compiler Options for Single Configuration such as Makefile, Ninja ----------")
else()
message(STATUS "---------- Compiler Options for Multi Configuration such as XCode, MSVC ----------")
endif()
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message(STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

message(STATUS "========== [END] C++ All Target Options ==========")

###############################################################################
# 前処理
###############################################################################
message(STATUS "========== [START] Preprocessing ==========")

if(BUILD_PYTHON_INTERPRETER)
    find_program(PYTHON_INTERPRETER "python3")
    if(NOT EXISTS ${PYTHON_INTERPRETER})
        message(FATAL_ERROR "python [${PYTHON_INTERPRETER}] not found.")
        error() # Place Unknown command to stop cmake process here.
    endif()
    message(STATUS "Python interpreter: ${PYTHON_INTERPRETER}")
endif()

message(STATUS "========== [END] Preprocessing ==========")

###############################################################################
# C++ core
###############################################################################
message(STATUS "========== [START] C++ Build Components ==========")


# ========== Library File ==========
# https://github.com/inoueshinichi/IsLibrary
# https://github.com/inoueshinichi/IsLibrary/archive/refs/heads/main.zip
include (${CMAKE_CURRENT_SOURCE_DIR}/build_tool/cmake/download_third-party.cmake)
set(IS_LIBRARY_DIRNAME Dev_IsLibrary-main)
set(IS_COMMON_TARGET_NAME "")
set(IS_NDARRAY_TARGET_NAME "")
set(IS_COMPUTERVISION_TARGET_NAME "")

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${IS_LIBRARY_DIRNAME})
        # Download
        message(STATUS "Downloading ${IS_LIBRARY_DIRNAME}")
        file(DOWNLOAD
            https://github.com/inoueshinichi/IsLibrary/archive/refs/heads/main.zip
            ${CMAKE_CURRENT_SOURCE_DIR}/${IS_LIBRARY_DIRNAME}.zip
            SHOW_PROGRESS
            STATUS status
            LOG log)
        list(GET status 0 status_code)
        list(GET status 1 status_string)
        if (NOT status_code EQUAL 0)
            if (UNIX OR APPLE)
                message("Failed to download ${IS_LIBRARY_DIRNAME}. Try to download with wget.")
                execute_process(
                    COMMAND wget https://github.com/inoueshinichi/IsLibrary/archive/refs/heads/main.zip
                    -O ${CMAKE_CURRENT_SOURCE_DIR}/${IS_LIBRARY_DIRNAME}.zip
                )
            else()
                message(FATAL_ERROR "Failed to download ${IS_LIBRARY_DIRNAME}. 
                        Please check network connection and proxy settings.
                        status_code: ${status_code}
                        status_string: ${status_string}
                        log: ${log}")
                error() # Place Unknown command to stop cmake process here.
            endif()
        endif()

        # Extract
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E
            chdir ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_COMMAND} -E tar xf ${IS_LIBRARY_DIRNAME}.zip
        )
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${IS_LIBRARY_DIRNAME})



# ========== Executable File ==========
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${IS_LIBRARY_DIRNAME})
    message(STATUS ">>>>>>>>>>>>>>>>>>>> Target GuiApp! <<<<<<<<<<<<<<<<<<<<")
    add_subdirectory(GuiApp)
endif()


message(STATUS "========== [END] C++ Build Components ==========")


###############################################################################
# C++ SandBox
###############################################################################
# message(STATUS "========== [START] C++ Build SandBox ==========")

# set(SANDBOX ON)
# if(${SANDBOX})
#     add_subdirectory(SandBox)
# endif()

# message(STATUS "========== [END] C++ Build SandBox ==========")

