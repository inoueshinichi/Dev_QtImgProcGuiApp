#pragma once

#include "qt_defs.h"

#include <map>

#include <Qt>
#include <QImage>
#include <QString>

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


void showStatus(const QImage &img) {
    /* QImageのステータスをチェック */

    qint64 cacheKey = img.cacheKey();
    int bitPlaneCount = img.bitPlaneCount();
}