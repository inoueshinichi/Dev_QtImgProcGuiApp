#ifndef __IMAGE_DRAW_VIEW_H__
#define __IMAGE_DRAW_VIEW_H__

#include <QGraphicsView>
#include <Qt>
#include <QRectF>
#include <QRect>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QDrag>

#include <cassert>


typedef struct zoom_level
{
    int index {0};
    float levels[23] = { 1.f/72, 1.f/48, 1.f/32, 1.f/24, 1.f/16, 1.f/12, 1.f/8, 1.f/6, 1.f/4, 1.f/3, 1.f/2, \
                            0.75f, 1.0f, 1.5f, 2.0f, 3.0f, 4.0f, 6.0f, 8.0f, 12.0f, 16.0f, 24.0f, 32.0f };

    zoom_level() {}

    float operator[](int i)
    {
        assert(i >= 0);
        int length = sizeof(levels) / sizeof(float);
        assert(i < length);
        return levels[i];
    }
} ZoomLevel;

class ImageDrawView : public QGraphicsView
{
    Q_OBJECT

protected:
    ZoomLevel zoom_level;
    bool is_accept_drag_and_drop {false};

public:
    ImageDrawView(QWidget* parent = nullptr);
    virtual ~ImageDrawView();
};
#endif // __IMAGE_DRAW_VIEW_H__