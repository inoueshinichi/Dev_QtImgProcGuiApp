#ifndef __IMAGE_DRAW_SCENE_FIGURE_H__
#define __IMAGE_DRAW_SCENE_FIGURE_H__

// 自作
#include "defs.h"

// Standard
#include <string>
#include <memory>
#include <map>

// Qt
#include <Qt>
#include <QObject>
#include <QString>

#include <QPen>
#include <QBrush>
#include <QFont>
#include <QColor>
#include <QPainter>
#include <QPainterPath>

#include <QPointF>
#include <QPoint>
#include <QRectF>
#include <QRect>
#include <QLineF>

#include <QImage>
#include <QPixmap>

#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

namespace Is
{
    using std::shared_ptr;
    using std::make_shared;

    /* 画像 */
    typedef struct scene_image
    {
        QImage raw_dib_qimage; // 原画像
        QImage source_dib_qimage; // 編集用画像
        QPixmap off_screen_ddb_qpixmap; // 描画用画像
        shared_ptr<QGraphicsPixmapItem> item_qpixmap; // 描画用アイテム画像
        QPointF item_qpixmap_local_pos; // Scene上にあるPixmapアイテムのローカル座標

        scene_image()
            : raw_dib_qimage()
            , source_dib_qimage()
            , off_screen_ddb_qpixmap()
            , item_qpixmap(nullptr)
            , item_qpixmap_local_pos(0.0, 0.0)
        {}

    } SceneImage;


    /* マスキング画像 */
    typedef struct scene_mask
    {
        QImage mask_qimage;
        QPixmap mask_qpixmap;
        shared_ptr<QGraphicsPixmapItem> item_mask_qpixmap;
        bool is_mask {false};

        scene_mask()
            : mask_qimage()
            , mask_qpixmap()
            , item_mask_qpixmap(nullptr)
        {}

    } SceneMask;


    /* マウスポインタ */
    typedef struct mouse_pointer
    {
        QPointF scene_mouse_pos;
        map<QString, bool> is_btns_down;

        mouse_pointer()
            : scene_mouse_pos(0.0, 0.0)
            , is_btns_down{ {"LB"s, false}, {"MB"s, false}, {"RB"s, false} }
        {}

    } MousePointer;


    /* 十字線 */
    typedef struct cross_line
    {
        bool is_cross_line {false};
        map<QString, QPainterPath> cross_paths;
        map<QString, shared_ptr<QGraphicsPathItem>> item_cross_paths;
        map<QString, bool> is_item_cross_lines;

        cross_line()
            : cross_paths{ {"x"s, QPainterPath()}, {"y"s, QPainterPath()} }
            , item_cross_paths{ {"x"s, nullptr}, {"y"s, nullptr} }
            , is_item_cross_lines{ {"x"s, false}, {"y"s, false}}
        {}

    } CrossLine;


    /* プロファイル */
    typedef struct profile
    {
        bool is_profile {false};
        map<QString, QPainterPath> x_profile_paths;
        map<QString, QPainterPath> y_profile_paths;
        map<QString, shared_ptr<QGraphicsPathItem>> item_x_profile_paths;
        map<QString, shared_ptr<QGraphicsPathItem>> item_y_profile_paths;
        map<QString, bool> is_item_x_profile_paths;
        map<QString, bool> is_item_y_profile_paths;

        profile()
            : x_profile_paths{ {"red"s, QPainterPath()}, {"green"s, QPainterPath()}, {"blue"s, QPainterPath()} }
            , y_profile_paths{ {"red"s, QPainterPath()}, {"green"s, QPainterPath()}, {"blue"s, QPainterPath()} }
            , item_x_profile_paths{ {"red"s, nullptr}, {"green"s, nullptr}, {"blue"s, nullptr} }
            , item_y_profile_paths{ {"red"s, nullptr}, {"green"s, nullptr}, {"blue"s, nullptr} }
            , is_item_x_profile_paths{ {"red"s, false}, {"green"s, false}, {"blue"s, false} }
            , is_item_y_profile_paths{ {"red"s, false}, {"green"s, false}, {"blue"s, false} }
        {}
        
    } Profile;


    /* Rectangle(ROI) */
    typedef struct rectangle
    {
        bool is_draw_rectangle {false};
        bool is_gen_rectangle {false};
        map<QString, shared_ptr<QGraphicsRectItem>> item_rectangles;
        QRectF current_rect;
        QPointF current_anchor;
        QColor color;

        rectangle()
            : item_rectangles{}
            , current_rect(0, 0, 0, 0)
            , current_anchor(0, 0)
            , color(Qt::red)
        {}

    } Rectangle;


    /* Line(直線) */
    typedef struct line
    {
        bool is_draw_line {false};
        bool is_gen_line {false};
        map<QString, shared_ptr<QGraphicsLineItem>> item_lines;
        QPointF current_line_point;
        QPointF current_line_anchor;
        QColor color;

        line()
            : item_lines{}
            , current_line_point(0, 0)
            , current_line_anchor(0, 0)
            , color(Qt::yellow)
        {}

    } Line;


    /* Ellipse(楕円領域) */
    typedef struct ellipse
    {
        bool is_draw_ellipse {false};
        bool is_gen_ellipse {false};
        map<QString, shared_ptr<QGraphicsEllipseItem>> item_ellipses;
        QRectF ellipse_current_rect;
        QPointF ellipse_current_anchor;
        QColor color;

        ellipse()
            : item_ellipses{}
            , ellipse_current_rect(0, 0, 0, 0)
            , ellipse_current_anchor(0, 0)
            , color(Qt::cyan)
        {}

    } Ellipse;


    /* Text */
    typedef struct text
    {
        map<QString, shared_ptr<QGraphicTextItem>> scene_texts;

        text() : scene_texts{} {}
    } Text;
}
#endif