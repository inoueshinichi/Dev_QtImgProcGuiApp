/**
 * @file GuiApp.cpp
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief GuiAppプロジェクトにおける自作関数用Sourceファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "GuiApp.h"


///////////////////////////////////////////////////////////////////////////////////////
// Global関数
///////////////////////////////////////////////////////////////////////////////////////

std::string getNewSerialNo(const std::string &filename,
                           const std::set<std::string> &filenameSet) {
    /* 最新の連番付きファイル名を取得する.
       連番の付け方: name(-番号).拡張子
       ※番号の最大値+1を新たな番号とするので, 途中歯抜けになっている番号は無視する.
    */
    std::string pattern = R"(^.+\..+$)"; // 拡張子の有無
    std::regex re0(pattern);
    std::smatch match;
    if (std::regex_match(filename, match, re0))
    {
        // 拡張子付きの場合

        if (!filenameSet.contains(filename))
        {
            return filename;
        }

        std::string name;
        std::string ext;
        pattern = R"(^(.+)-([0-9]+)\.(.+)$)";
        std::regex re1(pattern);
        int no = -1;
        if (std::regex_match(filename, match, re1))
        {
            // 連番付き
            name = match[1];
            no = std::stoi(match[2]);
            ext = match[3];
        }
        else
        {
            auto pos = filename.rfind('.');
            if (pos != std::string::npos)
            {
                name = filename.substr(0, pos); // Head
                ext = filename.substr(pos + 1); // Tail
            }
            else
            {
                return std::string();
            }
        }

        // filenameSetにあるファイル名を検索
        pattern = is::common::format_string(R"(^(%s-[0-9]+|(%s-%d-[0-9]+))\.(%s)$)", 
                                name.c_str(), name.c_str(), no, ext.c_str());
        std::regex re2(pattern);
        int count = 0;
        int subCount = 0;
        bool isDoubleCount = false;
        for (auto iter = filenameSet.begin(); iter != filenameSet.end(); ++iter)
        {
            if (std::regex_match(*iter, match, re2))
            {
                count++;
                if (filename == match[0])
                    isDoubleCount = true;
                std::string nameWithIndex = match[2];
                if (!nameWithIndex.empty())
                {
                    subCount++;
                }
            }
        }

        std::string newFilename;
        if (isDoubleCount)
        {
            newFilename = is::common::format_string("%s-%d-%d.%s", name.c_str(), no, subCount, ext.c_str());
        }
        else
        {
            newFilename = is::common::format_string("%s-%d.%s", name.c_str(), count - subCount, ext.c_str());
        }

        return newFilename;
    }
    else
    {
        return std::string();
    }
}


std::pair<QImage::Format, QString> getFormatStr(const QImage &img) {
    /* QImageのフォーマットを文字列で取得 */

#define GET_FORMAT(type)                                     \
    case QImage::type:                                       \
        return std::make_pair(QImage::type, QString(#type)); \
        break;
        
    switch (img.format())
    {
        GET_FORMAT(Format_Invalid);
        GET_FORMAT(Format_Mono);                 // 1bit per pixel
        GET_FORMAT(Format_MonoLSB);              // 1bit per pixel
        GET_FORMAT(Format_Indexed8);             // 8bit per pixel
        GET_FORMAT(Format_RGB32);                // 0xffRRGGBB
        GET_FORMAT(Format_ARGB32);               // 0xAARRGGBB
        GET_FORMAT(Format_ARGB32_Premultiplied); // 0xAARRGGBB
        GET_FORMAT(Format_RGB16);
        GET_FORMAT(Format_ARGB8565_Premultiplied);
        GET_FORMAT(Format_RGB666);
        GET_FORMAT(Format_ARGB6666_Premultiplied);
        GET_FORMAT(Format_RGB555);
        GET_FORMAT(Format_ARGB8555_Premultiplied);
        GET_FORMAT(Format_RGB888);
        GET_FORMAT(Format_RGB444);
        GET_FORMAT(Format_ARGB4444_Premultiplied);
        GET_FORMAT(Format_RGBX8888);
        GET_FORMAT(Format_RGBA8888);
        GET_FORMAT(Format_RGBA8888_Premultiplied);
        GET_FORMAT(Format_BGR30);
        GET_FORMAT(Format_A2BGR30_Premultiplied);
        GET_FORMAT(Format_RGB30);
        GET_FORMAT(Format_A2RGB30_Premultiplied);
        GET_FORMAT(Format_Alpha8);
        GET_FORMAT(Format_Grayscale8);
        GET_FORMAT(Format_Grayscale16);
        GET_FORMAT(Format_RGBX64);
        GET_FORMAT(Format_RGBA64);
        GET_FORMAT(Format_RGBA64_Premultiplied);
        GET_FORMAT(Format_BGR888);
        GET_FORMAT(NImageFormats);
    }

#undef GET_FORMAT
}


// void showStatus(const QImage &img) {
//     /* QImageのステータスをチェック */

//     qint64 cacheKey = img.cacheKey();
//     int bitPlaneCount = img.bitPlaneCount();
// }