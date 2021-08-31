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

#include "common.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>
#include <Qt>
#include <QPointF>
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

#include <map>
#include <vector>


class ImageScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QImage m_rawDibImg;
    SceneImage m_editImgIns;
    CrossLine m_crossLine;
    Profile m_profile;
    Roi m_roi;

    explicit ImageScene(QObject *parent=nullptr);
    virtual ~ImageScene();

    bool setDibImgOnScreen(const QImage &img);
    void resetRawImg();
    QGraphicsPixmapItem *getEditImgItem(const QPointF &scenePos);

protected : 
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    

signals:

};