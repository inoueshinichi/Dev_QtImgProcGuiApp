#pragma once

// Common
#include <IsCommon/IsCommon.hpp>
#include <IsCommon/format_string.hpp>
#include <IsCommon/join_string.hpp>
#include <IsCommon/split_string.hpp>
// #include <IsCommon/tm.hpp>
#include <IsCommon/thread_pool.hpp>
#include <IsCommon/singleton_manager.hpp>

// ComputerVision
// #include <IsComputerVision/IsComputerVision.hpp>

// Qt
#include <Qt>
#include <QImage>
#include <QString>


// Std
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
std::string GetNewSerialNo(const std::string& filename,
                           const std::set<std::string>& filenameSet);


/**
 * @brief QImageのフォーマットを取得
 * 
 * @param img 
 * @return std::pair<QImage::Format, QString> 
 */
std::pair<QImage::Format, QString> GetFormatStr(const QImage& img);



/**
 * @brief QImageの各種ステータスを表示
 * 
 * @param img 
 */
// void showStatus(const QImage &img);



// /**
//  * @brief QImage (W, H, C) -> NdArray(byte) (C, H, W)
//  * 
//  * @param img 
//  * @return is::nbla::NdArrayPtr 
//  */
// is::nbla::NdArrayPtr QImage2NdArray(const QImage& img);

// /**
//  * @brief NdArray(byte) (C, H, W) -> QImage
//  * 
//  * @param array 
//  * @return QImage 
//  */
// QImage NdArray2QImage(is::nbla::NdArrayPtr ndarray);


