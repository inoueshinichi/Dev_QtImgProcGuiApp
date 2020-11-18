#ifndef __IMAGE_DRAW_SCENE_HPP__
#define __IMAGE_DRAW_SCENE_HPP__

#include "pch.hpp"

#include <Qt>
#include <QObject>
#include <Qt>
#include <QPointF>
#include <QPoint>
#include <QRectF>
#include <QRect>
#include <QLineF>
#include <QImage>
#include <QPixmap>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPainterPath>
#include <QColor>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>

#include <map>


namespace Is
{
    /* 画像 */
    typedef struct scene_images
    {
        QImage raw_dib_qimage; // 原画像
        QImage source_dib_qimage; // 編集用画像
        QPixmap off_screen_ddb_qpixmap; // 描画用画像
        QGraphicsPixmapItem *item_qpixmap; // 描画用アイテム画像
        QPointF item_qpixmap_local_pos; // Scene上にあるPixmapアイテムのローカル座標

        scene_images()
            : raw_dib_qimage()
            , source_dib_qimage()
            , off_screen_ddb_qpixmap()
            , item_qpixmap(new QGraphicsPixmapItem())
            , item_qpixmap_local_pos(0.0, 0.0)
        {}
        ~scene_images() { delete item_qpixmap; }
    } SceneImages;


    /* マスキング */
    typedef struct scene_mask
    {
        QImage mask_qimage;
        QPixmap mask_qpixmap;
        QGraphicsPixmapItem *item_mask_qpixmap;
        bool is_mask;

        scene_mask()
            : mask_qimage()
            , mask_qpixmap()
            , item_mask_qpixmap(new QGraphicsPixmapItem())
            ,  is_mask(false)
        {}
        ~scene_mask() { delete item_mask_qpixmap; }
    } SceneMask;


    /* マウスポインタ*/
    typedef struct mouse_pointer
    {
        QPointF scene_mouse_pos;
        std::map<QString, bool> is_btns_down;

        mouse_pointer()
            : scene_mouse_pos(0.0, 0.0)
            , is_btns_down{ {"LB", false}, {"MB", false}, {"RB", false} }
        {}
    } MousePointer;


    /* 十字線 */
    typedef struct cross_line
    {
        bool is_cross_line;
        std::map<QString, QPainterPath> cross_paths;
        std::map<QString, QGraphicsPathItem*> item_cross_paths;
        std::map<QString, bool> is_item_cross_lines;

        cross_line()
            : is_cross_line(false)
            , cross_paths{ {"x", QPainterPath()}, {"y", QPainterPath()} }
            , item_cross_paths{ {"x", new QGraphicsPathItem()}, {"y", new QGraphicsPathItem()} }
            , is_item_cross_lines{ {"x", false}, {"y", false}}
        {}
        ~cross_line() { delete item_cross_paths["x"]; delete item_cross_paths["y"]; }
    } CrossLine;


     /* プロファイル */
    typedef struct profile
    {
        bool is_profile;
        std::map<QString, QPainterPath> x_profile_paths;
        std::map<QString, QPainterPath> y_profile_paths;
        std::map<QString, QGraphicsPathItem*> item_x_profile_paths;
        std::map<QString, QGraphicsPathItem*> item_y_profile_paths;
        std::map<QString, bool> is_item_x_profile_paths;
        std::map<QString, bool> is_item_y_profile_paths;

        profile()
            : is_profile(false)
            , x_profile_paths{ {"red", QPainterPath()}, {"green", QPainterPath()}, {"blue", QPainterPath()} }
            , y_profile_paths{ {"red", QPainterPath()}, {"green", QPainterPath()}, {"blue", QPainterPath()} }
            , item_x_profile_paths{ {"red", new QGraphicsPathItem()}, {"green", new QGraphicsPathItem()}, {"blue", new QGraphicsPathItem()} }
            , item_y_profile_paths{ {"red", new QGraphicsPathItem()}, {"green", new QGraphicsPathItem()}, {"blue", new QGraphicsPathItem()} }
            , is_item_x_profile_paths{ {"red", false}, {"green", false}, {"blue", false} }
            , is_item_y_profile_paths{ {"red", false}, {"green", false}, {"blue", false} }
        {}
        ~profile()
        {
            delete item_x_profile_paths["red"]; delete item_x_profile_paths["green"]; delete item_x_profile_paths["blue"];
            delete item_y_profile_paths["red"]; delete item_y_profile_paths["green"]; delete item_y_profile_paths["blue"];
        }
    } Profile;


    /* ROI */
    typedef struct roi
    {
        bool is_draw_roi;
        bool is_gen_roi;
        std::map<QString, QGraphicsRectItem*> item_rois;
        QRectF roi_current_rect;
        QPointF roi_current_anchor;

        roi()
            : is_draw_roi(false)
            , is_gen_roi(false)
            , item_rois()
            , roi_current_rect(0, 0, 0, 0)
            , roi_current_anchor(0, 0)
        {}

        ~roi()
        {
            for(auto item: item_rois)
                delete item.second;
        }
    } Roi;


    /* Line(直線) */
    typedef struct line
    {
        bool is_draw_line;
        bool is_gen_line;
        std::map<QString, QGraphicsLineItem*> item_lines;
        QPointF current_line_point;
        QPointF current_line_anchor;

        line()
            : is_draw_line(false)
            , is_gen_line(false)
            , item_lines()
            , current_line_point(0, 0)
            , current_line_anchor(0, 0)
        {}
        ~line()
        {
            for (auto item: item_lines)
                delete item.second;
        }
    } Line;


    /* Ellipse(楕円領域) */
    typedef struct ellipse
    {
        bool is_draw_ellipse;
        bool is_gen_ellipse;
        std::map<QString, QGraphicsEllipseItem*> item_ellipses;
        QRectF ellipse_current_rect;
        QPointF ellipse_current_anchor;

        ellipse()
            : is_draw_ellipse(false)
            , is_gen_ellipse(false)
            , item_ellipses()
            , ellipse_current_rect(0, 0, 0, 0)
            , ellipse_current_anchor(0, 0)
        {}

        ~ellipse()
        {
            for (auto item: item_ellipses)
                delete item.second;
        }
    } Ellipse;


    


    class ImageWindow;


    class ImageDrawScene : public QGraphicsScene
    {
        Q_OBJECT

        std::shared_ptr<ImageWindow> img_win_;

    protected:
        SceneImages scene_images; // 画像
        SceneMask scene_mask; // マスキング
        MousePointer scene_mouse_pointer; // マウスポインタ
        CrossLine scene_cross_line; // 十字線
        Profile scene_profile; // プロファイル
        Roi scene_roi; // ROI
        Line scene_line; // 直線
        Ellipse scene_ellipse; // 楕円
        std::map<QString, QGraphicsTextItem*> texts; // テキスト

        void _custom_connection();

    public:
        using ROI_ID = std::map<QString, QRectF>;
        using ROI_IMAGE_ID = std::map<QString, QImage>;
        using LINE_ID = std::map<QString, QLineF>;
        using LINE_PIXEL_ID = std::map<QString, std::vector<int>>;
        using ELLIPSE_ID = std::map<QString, QRectF>;
        using ELLIPSE_IMAGE_ID = std::map<QString, QImage>;

        // Mask
        void set_mask(const QImage& mask_qimg);
        QImage get_mask() const;
        void clear_mask();
        void reset_image();

        // Figures
        ROI_ID rois() const;
        ROI_IMAGE_ID roi_images() const;
        LINE_ID lines() const;
        LINE_PIXEL_ID line_pixels() const;
        ELLIPSE_ID ellipses() const;
        ELLIPSE_IMAGE_ID ellipse_images() const;
        void switch_visualization(VisualType type, bool is_show);
        
        // DIB Image
        QImage dib_image();
        bool set_image(const QImage& qimg, bool is_raw = false);

    private:
        void _draw_roi(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _draw_ellipse(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _draw_line(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _draw_profile(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _draw_cross_line(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _add_item_text(const QString &text, const QString &key, const QPointF &pos, QColor color=Qt::magenta, int point_size=10);
        void _remove_item_text(const QString &key);

    signals:
        void on_show_mouse_point(const QPointF &scene_pos);
        void on_change_status_image(const QImage &qimg);

    };

}





#endif // __IMAGE_DRAW_SCENE_HPP__