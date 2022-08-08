/**
 * @file image_scene.h
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief Qt ImageView用SceneクラスのHeaderファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "GuiApp.h"

#include <QGraphicsScene>

#include <QGraphicsPathItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>

#include <Qt>

#include <QRectF>
#include <QLineF>
#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPainterPath>
#include <QColor>
#include <QPainter>

#include <QMouseEvent>

typedef struct SceneImage 
{
    QImage m_memDibImg;
    QPixmap m_offScreenDdbImg;
    QGraphicsPixmapItem *m_pItemOffScreenDdbImg;
    bool m_isSceneImg {false};

    SceneImage() 
    {
        m_pItemOffScreenDdbImg = new QGraphicsPixmapItem();
    }

    ~SceneImage() 
    {
        if (m_pItemOffScreenDdbImg) 
        {
            delete m_pItemOffScreenDdbImg;
            m_pItemOffScreenDdbImg = nullptr;
        }
    }
} SceneImage;


class ImageScene : public QGraphicsScene
{
    Q_OBJECT
    
public:
    QImage mRawDibImg;
    SceneImage mEditSceneImg;


    explicit ImageScene(QObject *parent=nullptr);
    virtual ~ImageScene();

    SceneImage& GetEditSceneImg() { return mEditSceneImg; }

    bool SetDibImg(const QImage& img, bool isRaw = false);
    QImage GetDibImg();
    void ResetRawImg();
    class QGraphicsPixmapItem* GetEditImgItem(const class QPointF& scenePos);

protected : 
    virtual void mousePressEvent(class QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(class QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(class QGraphicsSceneMouseEvent* event) override;

public slots:
    

signals:

};