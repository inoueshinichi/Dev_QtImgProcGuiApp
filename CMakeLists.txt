cmake_minimum_required(VERSION 3.14.0)

project(QtImgProcGuiApp LANGUAGES CXX VERSION 0.1.0)

# CMake Version
message("CMake Version: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION}")

# 詳細情報の表示
set(CMAKE_VERBOSE_MAKEFILE ON)

###############################################################################
# 全ターゲットに影響を与えるオプション
###############################################################################
message(STATUS "========== [START] C++ All Target Options ==========")

# ========== Options ==========
option(BUILD_OPENMP "Enable/Disable OpenMP" ON)
option(BUILD_CPP_TEST "Enable/Disable Test" ON)
option(BUILD_SHARED_LIB "Enable/Disable DLL Libs" ON)
# set(BUILD_SHARED_LIBS ON)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message("CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

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

    if(BUILD_OPENMP)
        set(CMAKE_CXX_FFAGS "${CMAKE_CXX_FFAGS} /openmp")
    endif()

    # ソースコードでUTF-8を使う(MSVC++)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
    # C++11以降を利用した場合にマクロ変数__cplusplusの値を利用中のC++バージョンに合わせる(つけないとC++98相当の値になる)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>)

    # プリコンパイル済みヘッダーの使用(/Yu)を全体に設定
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yu")

elseif(APPLE)

message(STATUS "Compiler: Clang in macOS")    

    # Build Options(マルチコンフィギュレーション:visual studio対応)
    set(CMAKE_CXX_FLAGS "-O1")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

    # 警告
    string(APPEND CMAKE_CXX_FLAGS " -Wall")
    # string(APPEND CMAKE_CXX_FLAGS " -Werror")
    # string(APPEND CMAKE_CXX_FLAGS " -Weverything")
    # string(APPEND CMAKE_CXX_FLAGS " -Wno-c++98-compat")
    # string(APPEND CMAKE_CXX_FLAGS " -Wno-c++98-compat-pedanti")

    # ソースコードでUTF-8を使う(GCC++)
    add_compile_options($<$<CXX_COMPILER_ID:Clang>:/utf-8>)
    # C++11以降を利用した場合にマクロ変数__cplusplusの値を利用中のC++バージョンに合わせる(つけないとC++98相当の値になる)
    add_compile_options($<$<CXX_COMPILER_ID:Clang>:/Zc:__cplusplus>) 

else()
    message(STATUS "Compiler: GCC in Linux")

    # Build Options(マルチコンフィギュレーション:visual studio対応)
    set(CMAKE_CXX_FLAGS "-O1")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

    # C++標準に準拠しない拡張機能を無効化
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --pedantic-errors")

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

    # ソースコードでUTF-8を使う(GCC++)
    add_compile_options($<$<CXX_COMPILER_ID:GCC>:/utf-8>)
    # C++11以降を利用した場合にマクロ変数__cplusplusの値を利用中のC++バージョンに合わせる(つけないとC++98相当の値になる)
    add_compile_options($<$<CXX_COMPILER_ID:GCC>:/Zc:__cplusplus>)

endif()

message("---------- Compiler Options for Multi Configuration ----------")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_MINSIZEREL: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

message(STATUS "========== [END] C++ All Target Options ==========")

###############################################################################
# Qt Configuration
###############################################################################
message(STATUS "========== [START] Qt Configuration ==========")

 # Qt uic, moc, rcc
 set(CMAKE_AUTOUIC ON)
 set(CMAKE_AUTOMOC ON)
 set(CMAKE_AUTORCC ON)


# CMakeのバージョンが3.7.0以下の場合、カレントディレクトリをインクルードパスに追加
# mocで生成されたファイルをインクルードする
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Qt Root Dir (環境変数から取得) for find_package cofig mode.
message(STATUS "Qt env path: $ENV{QT5_DIR}")
set(QT_QPA_PLATFORM_PLUGIN_DIR $ENV{QT5_DIR}/plugins/platforms)
list(APPEND CMAKE_PREFIX_PATH $ENV{QT5_DIR})
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
set(Qt5_DIR $ENV{QT5_DIR}/lib/cmake CACHE PATH "Qt5 cmake script path")
message(STATUS "Qt cmake script path: $CACHE{Qt5_DIR}")

find_package(QT NAMES Qt5 CONFIG)

if(QT_FOUND)

    message(STATUS "Found Qt Library.")
    message(STATUS "Qt Version Major : ${QT_VERSION_MAJOR}")
    message(STATUS "Qt Config File Path: ${QT_CONFIG}")

    find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Charts
        LinguistTools        
    )

   
    # 多言語サポート
    file(GLOB TS_FILES "*.ts")
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

    # UIファイル
    # list(APPEND AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
    # message(STATUS "Auto Search Path List for AUTOUIC of Qt: ${AUTOUIC_SEARCH_PATHS}")
    # file(GLOB QT_UI_FILES ${AUTOUIC_SEARCH_PATHS}/*.ui)
    message(STATUS "Qt Ui Files: ${QT_UI_FILES}")
    # 下記のヘッダーパスは自動でINCLUDE_DIRECTORIES変数に追加されるようだ.
    # https://cmake.org/cmake/help/latest/prop_tgt/AUTOUIC.html#prop_tgt:AUTOUIC
    if (MSVC OR APPLE) # for Multi-Configuration Generator (MSVC, XCode)
        set(QT_UI_INCLUDE_DIR ${AUTOGEN_BUILD_DIR}/include_${CMAKE_BUILD_TYPE})
    else() # for Single-Configuration Generator (Make)
        set(QT_UI_INCLUDE_DIR ${AUTOGEN_BUILD_DIR}/include)
    endif()

    # RCCファイル
    file(GLOB QT_RCC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/rcc/*.qrc)
    message(STATUS "Qt Rcc Files: ${QT_RCC_FILES}")

else()
    message(FATAL_ERROR "Qt ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH} is not found.")
endif()

message(STATUS "========== [END] Qt Configuration ==========")

###############################################################################
# C++ core
###############################################################################
message(STATUS "========== [START] C++ Build Core ==========")

# ========== Library File ==========


# ========== Executable File ==========
# Header Files
file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
message("Header Files: ${EXE_INCLUDES}")

# Source Files
file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
message("Source Files: ${EXE_SOURCES}")

# Executable
# add_executable(${PROJECT_NAME}
#             ${EXE_INCLUDES}      # Exe用ヘッダーファイル
#             ${EXE_SOURCES}       # Exe用ソースファイル
#             ${RC_FILES}          # Qt-RCCリソースファイル
#             ${TS_FILES}          # Qt-TSファイル
# )
add_executable(${PROJECT_NAME}
            main.cpp
            main_window.h
            main_window.cpp
            defs.h
            common.h
)

# QtのAUTOUICで生成されたUIヘッダーファイルは自動でINCLUDE_DIRECTORIESに格納されるが、一応明記.
target_include_directories(${PROJECT_NAME} PRIVATE
                        ${QT_UI_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
                    Qt${QT_VERSION_MAJOR}::Widgets
                    Qt${QT_VERSION_MAJOR}::Core
                    Qt${QT_VERSION_MAJOR}::Gui)

# Qt dllファイルを実行ファイル.exeと同じフォルダにコピーする
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Qt5 pluginファイルを実行ファイル.exeと同じフォルダにコピーする
if(MSVC)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::QWindowsDirect2DIntegrationPlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
elseif(UNIX)



endif()

message(STATUS "========== [END] C++ Build Core ==========")

###############################################################################
# C++ Testing
###############################################################################

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
