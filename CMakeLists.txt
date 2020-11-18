cmake_minimum_required(VERSION 3.14.0)

project(QtImgProcGuiApp LANGUAGES CXX VERSION 0.1.0)

# CMake Version
message("CMake Version: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION}")

# 詳細情報の表示
set(CMAKE_VERBOSE_MAKEFILE ON)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message("CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

# プラットフォーム毎のコンパイラオプション(マルチ・コンフィギュレーションに対応)
if (MSVC)
    # ソースコードでUTF-8を使う(MSVC++)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

    # C++11以降を利用した場合にマクロ変数__cplusplusの値を利用中のC++バージョンに合わせる(つけないとC++98相当の値になる)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

    # Build Options
	set(CMAKE_CXX_FLAGS "/EHsc /W3 /GR /openmp /D_WINDOWS /DWIN32") # /constexpr
	set(CMAKE_CXX_FLAGS_DEBUG "/Ob0 /Od /MDd /Zi /RTC1 /D_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "/Ob2 /O2 /MD /DNDEBUG")
	set(CMAKE_CXX_FLAGS_MINSIZEREL "/O1 /MD /DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Od /MDd /Zi /RTC1 /D_DEBUG")
    
    # プリコンパイル済みヘッダーの使用(/Yu)を全体に設定
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yu")

elseif(APPLE)


else()
    # Linux GCC

    # C++標準に準拠しない拡張機能を無効化
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --pedantic-errors")

    # Build Options
	set(CMAKE_CXX_FLAGS "-O1 -Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
    
    # C++11以降を利用した場合にマクロ変数__cplusplusの値を利用中のC++バージョンに合わせる(つけないとC++98相当の値になる)
    add_compile_options("$<$<CXX_COMPILER_ID:UNIX>:/Zc:__cplusplus>")

endif()



message("-------------------- Compiler Options in Multi Configuration --------------------")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_MINSIZEREL: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

message("-------------------- Qt Configuration --------------------")
# set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# find_package: Configモード
set(QT5_DIR "C:/Qt/5.15.1/msvc2019_64")
set(QT5_QPA_PLATFORM_PLUGIN_PATH "${QT5_DIR}/plugins/platforms")
set(QT5_CMAKE_DIR "${QT5_DIR}/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "${QT5_CMAKE_DIR}")
find_package(QT NAMES Qt6 Qt5)
message("Qt Version Major : ${QT_VERSION_MAJOR}")
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
	Core
	Gui
	Widgets
	LinguistTools
	REQUIRED
)

# 多言語サポート
file(GLOB TS_FILES "*.ts")

# mocで生成されたファイルをインクルードするはずなので，有効にしておくが吉
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# *.uiのサーチパスを設定
# set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} "${CMAKE_CURRENT_SOURCE_DIR}/ui")
# message("Auto Uic Searched Paths : ${CMAKE_AUTOUIC_SEARCH_PATHS}")

# # *.uiファイルのコンパイル結果の出力先を指定
# set(AUTOGEN_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ui")
# message("Auto Gen Output Path: ${AUTOGEN_BUILD_DIR}")

# *.uiファイルをコンパイル
file(GLOB UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui")
# qt_wrap_ui(UI_HEADER_FILES ${UI_FILES}) # UIC compile
message("Ui Files: ${UI_FILES}")
# message("Ui Header Files: ${UI_HEADER_FILES}")

# ui_**.hppファイルを回収
file(GLOB UI_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.hpp")

# Qt Resource Files
file(GLOB_RECURSE RC_FILES ".qrc")
message("Gui Rc Files: ${RC_FILES}")


message("-------------------- Collect *.hpp, *.cpp --------------------")

# Header Files
file(GLOB INCLUDES 
            "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" 
            "${CMAKE_CURRENT_SOURCE_DIR}/windows/*.hpp"
    )
message("Header Files: ${INCLUDES}")

# Source Files
file(GLOB SOURCES 
            "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" 
            "${CMAKE_CURRENT_SOURCE_DIR}/windows/*.cpp"
    )
message("Source Files: ${SOURCES}")


include(CTest)
enable_testing()

# # Windows My Lib
# add_subdirectory("${PROJECT_SOURCE_DIR}/windows")

add_executable(${PROJECT_NAME} 
            ${TS_FILES}
            ${INCLUDES}
            ${SOURCES}
            ${UI_HEADER_FILES}
            # ${UI_FILES}
            ${RC_FILES}
            )


# message("-------------------- Link Windows library --------------------")
# target_link_libraries(QtCMakeApp PRIVATE mywinlib)


message("-------------------- Link Qt library --------------------")
target_link_libraries(${PROJECT_NAME} PRIVATE 
                    Qt${QT_VERSION_MAJOR}::Widgets
                    Qt${QT_VERSION_MAJOR}::Core
                    Qt${QT_VERSION_MAJOR}::Gui)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})



# Qt5 dllファイルを実行ファイル.exeと同じフォルダにコピーする
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Qt5 pluginファイルを実行ファイル.exeと同じフォルダにコピーする
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::QWindowsDirect2DIntegrationPlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
