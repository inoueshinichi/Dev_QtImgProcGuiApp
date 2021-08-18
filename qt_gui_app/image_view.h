#pragma once

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

class ImageView : public QGraphicsView
{
    Q_OBJECT

protected:
    typedef struct ZoomLebel
    {
        int index {0};
        float levels[23] = { 1.f/72, 1.f/48, 1.f/32, 1.f/24, 1.f/16, 1.f/12, 1.f/8, 1.f/6, 1.f/4, 1.f/3, 1.f/2, \
                            0.75f, 1.0f, 1.5f, 2.0f, 3.0f, 4.0f, 6.0f, 8.0f, 12.0f, 16.0f, 24.0f, 32.0f };
       
        float operator[](int i)
        {
            assert(i >= 0);
            int length = sizeof(levels) / sizeof(float);
            assert(i < length);
            return levels[i];
        }
    } ZoomLevel;
    ZoomLevel zoomLevel;

    bool isAcceptDragDrop {false};

public:
    ImageView(QWidget *parent=nullptr);
    virtual ~ImageView();
};