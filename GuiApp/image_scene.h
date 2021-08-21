/**
 * @file image_scene.h
 * @author your name (you@domain.com)
 * @brief モデル・ビュー アーキテクチャ （モデル：QGraphicsScene、ビュー：QGraphicsView）における
 * 　　　 モデルクラス.
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

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
// #include <qDebug>
#include <QLineF>
#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QPen>
#include <QBrush>
#include <QFont>
// #include <qGray>
#include <QPainterPath>
#include <QColor>
#include <QPainter>


#include <map>
#include <vector>


class ImageScene : public QGraphicsScene
{
    Q_OBJECT

    QImage m_rawDibImg;
    QImage m_editDibImgBefore;
    QPixmap m_offScreenDdbImgBefore;
    QGraphicsPixmapItem *m_pItemOffScreenDdbImgBefore;
    QImage m_editDibImgAfter;
    QPixmap m_offScreenDdbImgAfter;
    QGraphicsPixmapItem *m_pItemOffScreenDdbImgAfter;

public:
    explicit ImageScene(QObject *p_parent=nullptr);
    virtual ~ImageScene();

    bool setDibImgBeforeOnScreen(const QImage &beforeImg);
    bool setDibImgAfterOnScreen(const QImage &afterImg);

    // void resetRawImg();
};