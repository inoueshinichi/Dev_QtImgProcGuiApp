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

#include "common.h"

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

    void updateStatusBar(const QPoint &viewPos);

    void drawCrossLine(const QPoint &viewPos);
    void drawProfile(const QPoint &viewPos,
                     bool isXRed, bool isXGreen, bool isXBlue,
                     bool isYRed, bool isYGreen, bool isYBlue);
    void drawFigure(const QPoint &viewPos, bool isCenterDrag, bool isSquareDrag);

protected:
    ZoomLevel m_zoomLevel;
    bool isAcceptDragDrop {false};

public:
    explicit ImageView(QWidget *parent=nullptr);
    virtual ~ImageView();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void emitShowPosToStatusBar(
        const QPointF &imgLocalPos,
        const QPointF &scenePos,
        const QPoint &viewPos);
};