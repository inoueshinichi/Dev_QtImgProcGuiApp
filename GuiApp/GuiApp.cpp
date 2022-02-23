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

std::string GetNewSerialNo(const std::string &filename,
                           const std::set<std::string> &filenameSet) 
{
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
                {
                    isDoubleCount = true;
                }
                    
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


std::pair<QImage::Format, QString> GetFormatStr(const QImage &img) 
{
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



is::nbla::NdArrayPtr QImage2NdArray(const QImage& img)
{
    /* QImageからNdArrayへの変換 */
    using ubyte = unsigned char;
    using namespace is::nbla;
    const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();

    int width = img.width();
    int height = img.height();
    int mem_channels = img.depth() / 8; // Gray(8), RGB(24), RGBA(32)

    // RGBAの場合, Aを除外する
    int channels = mem_channels > 3 ? 3 : mem_channels;

    IS_DEBUG_STREAM("w: %d, h: %d, c: %d\n", width, height, channels);

    int mem_width = img.bytesPerLine();
    const ubyte* ptr = img.bits();

    // NdArray
    auto dst = zeros<ubyte>({channels, height, width});
    ubyte* data_dst = dst->cast_data_and_get_pointer<ubyte>(ctx);
    auto sh = dst->shape();
    auto st = dst->strides();

    for (int c = 0; c < sh[0]; ++c)
    {
        for (int y = 0; y < sh[1]; ++y)
        {
            for (int x = 0; x < sh[2]; ++x)
            {
                data_dst[c * st[0] + y * st[1] + x * st[2]] = 
                    ptr[y * mem_width + mem_channels * x + c];
            }
        }
    }

    return dst;
}


QImage NdArray2QImage(is::nbla::NdArrayPtr ndarray)
{
    /* NdArrayからQImageへの変換 */
    IS_CHECK_NDARRAY_SHAPE_AS_IMAGE(ndarray);

    using ubyte = unsigned char;
    using namespace is::nbla;
    const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();

    ubyte* data_array = ndarray->cast_data_and_get_pointer<ubyte>(ctx);
    auto sh = ndarray->shape();
    auto st = ndarray->strides();
    int channels = sh[0];
    int height = sh[1];
    int width = sh[2];

    QImage::Format format;
    
    // must c == 1 or 3.
    if (channels == 1)
    {
        format = QImage::Format_Grayscale8;
    }
    else
    {
        format = QImage::Format_RGB888;
    }

    QImage img(width, height, format);
    int mem_width = img.bytesPerLine();
    ubyte* ptr = img.bits();

    for (int c = 0; c < sh[0]; ++c)
    {
        for (int y = 0; y < sh[1]; ++y)
        {
            for (int x = 0; x < sh[2]; ++x)
            {
                ptr[y * mem_width + channels * x + c] =
                    data_array[c * st[0] + y * st[1] + x * st[2]];
            }
        }
    }

    return img;
}