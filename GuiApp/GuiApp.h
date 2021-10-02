#pragma once

#include <IsCommon/IsCommon.hpp>
#include <IsCommon/format_string.hpp>
#include <IsCommon/join_string.hpp>
#include <IsCommon/split_string.hpp>
#include <IsCommon/tm.hpp>
#include <IsCommon/thread_pool.hpp>
#include <IsCommon/singleton_manager.hpp>

#include "qt_defs.h"

#include <cassert>
#include <string>
using namespace std::literals::string_literals;
#include <set>
#include <map>
#include <tuple>
#include <vector>
#include <regex>
#include <memory>
#include <string>
#include <cstdio>  // std::snprintf
#include <cstdlib> // std::abort
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;


#include <Qt>
#include <QImage>
#include <QString>

///////////////////////////////////////////////////////////////////////////////////////
// Global関数
///////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 新しいシリアルナンバーを不可した名前を取得
 * 
 * @param filename 
 * @param filenameSet 
 * @return std::string 
 */
std::string getNewSerialNo(const std::string &filename,
                           const std::set<std::string> &filenameSet);


/**
 * @brief QImageのフォーマットを取得
 * 
 * @param img 
 * @return std::pair<QImage::Format, QString> 
 */
std::pair<QImage::Format, QString> getFormatStr(const QImage &img);



/**
 * @brief QImageの各種ステータスを表示
 * 
 * @param img 
 */
// void showStatus(const QImage &img);