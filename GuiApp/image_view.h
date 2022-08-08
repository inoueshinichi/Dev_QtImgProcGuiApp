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

// QtCustom
#include "graphics_item.h"


class ImageView : public QGraphicsView 
{
    Q_OBJECT

    // アイテム
    CrossLine mCrossLine;
    Profile mProfile;
    RoiRect mRoi;
    RoiEllipse mEllipse;
    //RoiLine mLine;

    QRectF mRect;
    QPointF mAnchor;

    // マウス
    bool mIsMousePressLeft{false};
    bool mIsMousePressRight{false};
    bool mIsMousePressMiddle{false};
    bool mIsMouseDrag{false};

    bool mIsGenFigure{false};

    void UpdateStatusBar(const class QPoint& viewPos);

    void DrawCrossLine(const class QPoint& viewPos);
    void DrawProfile(const class QPoint& viewPos,
                     bool isXRed, bool isXGreen, bool isXBlue,
                     bool isYRed, bool isYGreen, bool isYBlue);
    void DrawFigure(const class QPoint& viewPos, bool isCenterDrag, bool isSquareDrag);
    void RemoveFigure(const class QPoint& viewPos);

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

    ZoomLevel mZoomLevel;
    bool mIsAcceptDragDrop {false};

public:
    explicit ImageView(QWidget *parent=nullptr);
    virtual ~ImageView();

    CrossLine& GetCrossLine() { return mCrossLine; }
    Profile& GetProfile() { return mProfile; }
    RoiRect& GetRoiRect() { return mRoi; }
    RoiEllipse& GetRoiEllipse() { return mEllipse; }
    QRectF& GetRectF() { return mRect; }
    QPointF& GetAnchor() { return mAnchor; }

protected:
    virtual void mousePressEvent(class QMouseEvent* event) override;
    virtual void mouseMoveEvent(class QMouseEvent* event) override;
    virtual void mouseReleaseEvent(class QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(class QMouseEvent* event) override;

signals:
    void EmitShowPosToStatusBar(
        const class QPointF& imgLocalPos,
        const class QPointF& scenePos,
        const class QPoint& viewPos);
};


