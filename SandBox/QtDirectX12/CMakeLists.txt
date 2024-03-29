cmake_minimum_required(VERSION 3.14.0)

get_filename_component(DIRNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(APP_TARGET_NAME ${DIRNAME})

###########################################
# sandbox -> qt_directx
###########################################
project(${APP_TARGET_NAME} LANGUAGES C CXX VERSION 0.1.0)
message(STATUS ">>>>> ${APP_TARGET_NAME}")

# ここで必要なモジュールを指定する
list(APPEND QT_MODULES Core Gui Widgets)

###############################################################################
# Qt Configuration
###############################################################################
# Qt Root Dir (環境変数から取得) for find_package cofig mode.
if($ENV{QT5_DIR} STREQUAL "")
    message(FATAL_ERROR "Not found QT5_DIR env path.")
endif()
message(STATUS "Qt env path: $ENV{QT5_DIR}")

# パスの区切り文字を変換(MSVC)
if(MSVC)
    string(REPLACE "\\" "/" QT_DIR $ENV{QT5_DIR})
else()
    set(QT_DIR $ENV{QT5_DIR})
endif()
message(STATUS "Qt path: ${QT_DIR}")

# プラットフォーム別のプラグインファイルのパスを取得
set(QT_QPA_PLATFORM_PLUGIN_DIR ${QT_DIR}/plugins/platforms)
list(APPEND CMAKE_PREFIX_PATH ${QT_DIR})
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
# set(Qt5_DIR ${QT_DIR}/lib/cmake CACHE PATH "Qt5 cmake script path")
# message(STATUS "Qt cmake script path: $CACHE{Qt5_DIR}")

# Qtパッケージの検索
find_package(QT NAMES Qt5 CONFIG)
if(NOT QT_FOUND)
    message(FATAL_ERROR "Qt ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH} is not found.")
endif()
message(STATUS "Found Qt Library.")
message(STATUS "Qt Version Major : ${QT_VERSION_MAJOR}")
message(STATUS "Qt Config File Path: ${QT_CONFIG}")


find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS
    ${QT_MODULES}
)

# Windows 拡張ライブラリ
if(WIN32)
    find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS
        WinExtras
    )
endif()

###############################################################################
# アプリケーションターゲット
###############################################################################
# ライブラリターゲット設定(注意: AUTO_UIC以降で設定しないと、AUTO_UICが起動しない)
add_executable(${APP_TARGET_NAME} WIN32)

# 警告の抑制
if(MSVC)
    # Warning 抑制 C5054 (演算子の異なる列挙間では非推奨を無視)
    # https://docs.microsoft.com/ja-jp/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999?view=msvc-160
    target_compile_options(${APP_TARGET_NAME} PRIVATE /wd5054)
elseif(APPLE)

else()

endif()

###############################################################################
# AUTOUIC, AUTOMOC と qt_wrap_ui, qt_wrap_cpp の切り替え
###############################################################################
set(UI_DIRNAME "ui")
set(RC_DIRNAME "rc")


# 注意) AUTOUIC, AUTOMOC, AUTORCCは ${CMAKE_SOURCE_DIR} == ${CMAKE_CURRENT_SOURCE_DIR}でしか機能しない！
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

    # Qt uic, moc, rcc 注意) この記述以降のビルドターゲットでAUTO系が有効になる
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    # UI compiler 設定
    # ui_<basename>.hのあるディレクトリは自動でインクルードディレクトリに追加される.
    # 注意) この記述以降のビルドターゲットのAUTOUIC_SEARCH_PATHSの初期化にCMAKE_AUTOUIC_SEARCH_PATHSが利用される.
    list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/${UI_DIRNAME})
    message(STATUS "Auto Search Path List for AUTOUIC of Qt: ${CMAKE_AUTOUIC_SEARCH_PATHS}")

    # 生成されたUIヘッダーの内部に格上げするクラスのヘッダーファイルがインクルードされるのでヘッダーディレクトリを登録
    target_include_directories(${APP_TARGET_NAME} PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    # MOC compiler 設定
    # MOCは自動的にヘッダーファイルの中にあるQtMetaObjectを検出してmoc_<basename>.cppを生成する
    message(STATUS "Directory of Moc sources: ${AUTOGEN_BUILD_DIR}/include")

    # RCC compiler 設定
    file(GLOB QT_QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${RC_DIRNAME}/*.qrc)
    target_sources(${APP_TARGET_NAME} PRIVATE 
        ${QT_QRC_FILES}
    )

else()

    # UIC compiler
    message(STATUS "Generate Qt Ui Header Files(.h)...")
    file(GLOB QT_UI_FORMS ${CMAKE_CURRENT_SOURCE_DIR}/${UI_DIRNAME}/*.ui)
    if(${QT_VERSION_MAJOR} EQUAL 5)
        qt5_wrap_ui(QT_UI_HEADERS ${QT_UI_FORMS})
    else()
        qt_wrap_ui(QT_UI_HEADERS ${QT_UI_FORMS})
    endif()
    message(STATUS "Qt UI Header path generated by qt[5]_wrap_ui() command: ${QT_UI_HEADERS}")

    # MOC compiler
    message(STATUS "Generate Qt moc Source Files(.cpp)...")
    file(GLOB QT_HPP_FOR_MOC ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
    file(GLOB QT_H_FOR_MOC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
    list(APPEND QT_HEADERS_FOR_MOC ${QT_HPP_FOR_MOC} ${QT_H_FOR_MOC})
    message(STATUS "Qt Header Files for MOC : ${QT_HEADERS_FOR_MOC}")
    if(${QT_VERSION_MAJOR} EQUAL 5)
        qt5_wrap_cpp(QT_MOC_SOURCES ${QT_HEADERS_FOR_MOC} TARGET ${APP_TARGET_NAME})
    else()
        qt_wrap_cpp(QT_MOC_SOURCES ${QT_HEADERS_FOR_MOC} TARGET ${APP_TARGET_NAME})
    endif()
    message(STATUS "Qt MOC Source Files generated by qt[5]_wrap_cpp() command : ${QT_MOC_SOURCES}")

    # RCC compiler
    message(STATUS "Generate Qt qrc Files(.cpp)...")
    file(GLOB QT_RC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${RC_DIRNAME}/*.qrc)
    if(${QT_VERSION_MAJOR} EQUAL 5)
        qt5_add_resources(QT_RC_SOURCES ${QT_RC_FILES})
    else()
        qt_add_resources(QT_RC_SOURCES ${QT_RC_FILES})
    endif()


    # UI, MOC, RCをターゲットに追加
    target_sources(${APP_TARGET_NAME} PRIVATE
        ${QT_UI_HEADERS}
        ${QT_MOC_SOURCES}
        ${QT_RC_SOURCES}
    )

    # ui_<basename>.h が生成されたディレクトリをインクルードディレクトリに追加
    target_include_directories(${APP_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

    # 生成されたUIヘッダーの内部に格上げするクラスのヘッダーファイルがインクルードされるのでヘッダーディレクトリを登録
    target_include_directories(${APP_TARGET_NAME} PRIVATE 
        ${CMAKE_CURRENT_DIR}
    )

endif()


###############################################################################
# アプリケーションターゲットのビルド
###############################################################################

# Include
list(APPEND APP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "Include dir: ${APP_INCLUDE_DIR}")

# Sources
file(GLOB APP_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ./*.cpp
)

message(STATUS "Source files: ${APP_SOURCE_FILES}")

# App Sources
target_sources(${APP_TARGET_NAME} PRIVATE 
    ${APP_SOURCE_FILES}
)

# App Include
target_include_directories(${APP_TARGET_NAME} PRIVATE 
    ${APP_INCLUDE_DIR}
)

###############################################################################
# 自作ライブラリのリンク
###############################################################################
target_include_directories(${APP_TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../IsLibrary-main/include
)

target_link_libraries(${APP_TARGET_NAME} PRIVATE
    IsCommon
)

add_dependencies(${APP_TARGET_NAME} IsCommon)

# Copy
add_custom_command(TARGET ${APP_TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:IsCommon> $<TARGET_FILE_DIR:${APP_TARGET_NAME}>
)

###############################################################################
# DirectXのリンク
###############################################################################
target_link_libraries(${APP_TARGET_NAME} PRIVATE
    d3d12
)

###############################################################################
# Qtライブラリのリンク
###############################################################################
foreach(Module ${QT_MODULES})
    message(STATUS "${Module}")
    # Qt-Link
    target_link_libraries(${APP_TARGET_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::${Module}
    )

    # Qt dllファイルをアプリケーション実行ファイルと同じフォルダにコピーする(ビルドイベント)
    add_custom_command(TARGET ${APP_TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::${Module}> $<TARGET_FILE_DIR:${APP_TARGET_NAME}>
    )
endforeach()


# プラットフォーム別のプラグインファイルを実行ファイルと同じフォルダにコピー
if (MSVC)
    add_custom_command(TARGET ${APP_TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::WinExtras> $<TARGET_FILE_DIR:${APP_TARGET_NAME}>
    )

    add_custom_command(TARGET ${APP_TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:${APP_TARGET_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::QWindowsDirect2DIntegrationPlugin> $<TARGET_FILE_DIR:${APP_TARGET_NAME}>
    )
endif()


message(STATUS "<<<<< ${APP_TARGET_NAME}")