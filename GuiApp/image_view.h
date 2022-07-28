/**
 * @file image_view.h
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief Qt ImageWindow用ViewクラスのHeaderファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "GuiApp.h"

#include <QGraphicsView>
#include <Qt>
#include <QRectF>
#include <QRect>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QString>
#include <QDrag>


class ImageView : public QGraphicsView 
{
    Q_OBJECT

    // マウス
    bool m_isMousePressLeft{false};
    bool m_isMousePressRight{false};
    bool m_isMousePressMiddle{false};
    bool m_isMouseDrag{false};

    bool m_isGenFigure{false};

    void UpdateStatusBar(const QPoint &viewPos);

    void DrawCrossLine(const QPoint &viewPos);
    void DrawProfile(const QPoint &viewPos,
                     bool isXRed, bool isXGreen, bool isXBlue,
                     bool isYRed, bool isYGreen, bool isYBlue);
    void DrawFigure(const QPoint &viewPos, bool isCenterDrag, bool isSquareDrag);
    void RemoveFigure(const QPoint &viewPos);

protected:
    typedef struct ZoomLebel 
    {
        int index{0};
        float levels[23] = { 
            1.f / 72, 1.f / 48, 1.f / 32, 1.f / 24, 1.f / 16, 
            1.f / 12, 1.f / 8,  1.f / 6,  1.f / 4,  1.f / 3, 1.f / 2, 
            0.75f,  1.0f, 1.5f, 2.0f, 3.0f, 4.0f, 6.0f, 8.0f, 12.0f, 16.0f, 24.0f, 32.0f
        };

        float operator[](int i) 
        {
            assert(i >= 0);
            int length = sizeof(levels) / sizeof(float);
            assert(i < length);
            return levels[i];
        }
        
    } ZoomLevel;

    ZoomLevel m_zoomLevel;
    bool m_isAcceptDragDrop {false};

public:
    explicit ImageView(QWidget *parent=nullptr);
    virtual ~ImageView();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void EmitShowPosToStatusBar(
        const QPointF &imgLocalPos,
        const QPointF &scenePos,
        const QPoint &viewPos);
};


