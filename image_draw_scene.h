#ifndef __IMAGE_DRAW_SCENE_H__
#define __IMAGE_DRAW_SCENE_H__

// 自作
#include "image_draw_scene-figure.h"

// Standard
#include <map>
#include <vector>

// Qt
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>



namespace Is
{
    using std::map;
    using std::vector;

    class ImageDrawScene : public QGraphicsScene
    {
        Q_OBJECT

        SceneImage scene_image; // 画像
        SceneMask scene_mask; // マスキング
        MousePointer scene_mouse_pointer; // マウスポインタ
        CrossLine scene_cross_line; // 十字線
        Profile scene_profile; // プロファイル
        Rectangle scene_roi; // ROI
        Line scene_line; // 直線
        Ellipse scene_ellipse; // 楕円
        Text texts; // テキスト

    public:
        ImageDrawScene(QObject* parent=nullptr);
        virtual ~ImageDrawScene();


        ///////////////////////////////////////////////////////////////
        // Visual Objects
        ///////////////////////////////////////////////////////////////
        void switch_visual_objects(VisualObjectType type, bool is_show);

        // DIB Image
        QImage get_dib_image() const;
        bool set_dib_image(const QImage& image, bool is_raw = false);
        void reset_dib_image();

        // Masking Image
        void set_mask(const QImage& mask);
        QImage get_mask() const;
        void clear_mask();

        // ROI(Rectangle) Figure
        map<QString, QRectF> get_rectangles() const;
        map<QString, QImage> get_rectangle_images() const;

        // Line Figure
        map<QString, QLineF> get_lines() const;
        map<QString, vector<int>> get_line_pixels() const;

        // Ellipse Figure
        map<QString, QRectF> get_ellipses() const;
        map<QString, QImage> get_ellipse_images() const;


    private:
        void _draw_roi(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _draw_ellipse(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _draw_line(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _draw_profile(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _draw_cross_line(const QPointF &scene_pos, bool is_mouse_btn_down, bool is_mouse_move, bool is_show, bool is_center_drag, bool is_square_drag);
        void _add_item_text(const QString &text, const QString &key, const QPointF &pos, QColor color=Qt::magenta, int point_size=10);
        void _remove_item_text(const QString &key);

    signals:
        void signal_show_scene_rect(const QRectF& scene_rect);
        // void on_show_mouse_point(const QPointF &scene_pos);
        // void on_change_status_image(const QImage &qimg);

    };

} // namespace Is
#endif // __IMAGE_DRAW_SCENE_HPP__