/**
 * @file image_scene.cpp
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief Qt ImageView用SceneクラスのSourceファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "image_scene.h"

#include <iostream>

//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

ImageScene::ImageScene(QObject* parent)
    : QGraphicsScene(parent) {

    // m_crossLine.m_isCrossLine = true; // 仮
}

ImageScene::~ImageScene() {

}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void ImageScene::drawCrossLine(const QPointF &scenePos) {
    /* マウスを中心とした十字線をSceneに描画
    */
    QGraphicsPixmapItem *p_item = getEditImgItem(scenePos);
    if (p_item)
    {
        // DEBUG_STREAM("ScenePos(%.1f, %.1f)\n", scenePos.x(), scenePos.y());

        QPointF localPos = p_item->mapToItem(p_item, scenePos);
        QRectF localRect = p_item->boundingRect(); // Local座標における矩形サイズ

        if (localRect.contains(localPos.toPoint())) {
            DEBUG_STREAM("[CrossLine] Detect target item! LocalPos(%.1f, %.1f)\n", localPos.x(), localPos.y());

            // 水平線
            qreal y = localPos.y();
            m_crossLine.m_pItemLineX->setLine(0, y, localRect.width(), y);

            if (m_crossLine.m_pItemLineX->contains(scenePos)) {
                this->removeItem(m_crossLine.m_pItemLineX);
            }
            this->addItem(m_crossLine.m_pItemLineX);

            // 垂直線
            qreal x = localPos.x(); 
            m_crossLine.m_pItemLineY->setLine(x, 0, x, localRect.height());
            if (m_crossLine.m_pItemLineY->contains(scenePos)) {
                this->removeItem(m_crossLine.m_pItemLineY);
            }
            this->addItem(m_crossLine.m_pItemLineY);
        }
    }
}

void ImageScene::drawProfile(const QPointF &scenePos,
                             bool isXRed, bool isXGreen, bool isXBlue,
                             bool isYRed, bool isYGreen, bool isYBlue)
{
    /* 画像プロファイルの描画
    */

    QGraphicsPixmapItem *p_item = getEditImgItem(scenePos);
    if (p_item)
    {
        // DEBUG_STREAM("ScenePos(%.1f, %.1f)\n", scenePos.x(), scenePos.y());

        QPointF localPos = p_item->mapToItem(p_item, scenePos);
        QRectF localRect = p_item->boundingRect(); // Local座標における矩形サイズ

        if (localRect.contains(localPos.toPoint())) {
            DEBUG_STREAM("[Profile] Detect target item! LocalPos(%.1f, %.1f)\n", localPos.x(), localPos.y());

            // シーンに登録済みのProfileItemを解除
            foreach(QGraphicsItem *p_item, this->items()) {

                // X
                if (p_item == m_profile.m_directX.m_pItemPathRed) {
                    this->removeItem(m_profile.m_directX.m_pItemPathRed);
                    m_profile.m_directX.m_pathRed.clear();
                }
                if (p_item == m_profile.m_directX.m_pItemPathGreen) {
                    this->removeItem(m_profile.m_directX.m_pItemPathGreen);
                    m_profile.m_directX.m_pathGreen.clear();
                }
                if (p_item == m_profile.m_directX.m_pItemPathBlue) {
                    this->removeItem(m_profile.m_directX.m_pItemPathBlue);
                    m_profile.m_directX.m_pathBlue.clear();
                }

                // Y
                if (p_item == m_profile.m_directY.m_pItemPathRed) {
                    this->removeItem(m_profile.m_directY.m_pItemPathRed);
                    m_profile.m_directY.m_pathRed.clear();
                }
                if (p_item == m_profile.m_directY.m_pItemPathGreen) {
                    this->removeItem(m_profile.m_directY.m_pItemPathGreen);
                    m_profile.m_directY.m_pathGreen.clear();
                }
                if (p_item == m_profile.m_directY.m_pItemPathBlue) {
                    this->removeItem(m_profile.m_directY.m_pItemPathBlue);
                    m_profile.m_directY.m_pathBlue.clear();
                }
            }

            int profileY = (int)localPos.y();
            int profileX = (int)localPos.x();
            int width = (int)localRect.width();
            int height = (int)localRect.height();
            QColor color, nextColor;
            int red, green, blue;
            int nextRed, nextGreen, nextBlue;
            DEBUG_STREAM("profileX %d, profileY %d", profileX, profileY);

            // 水平プロファイル
            for (int x = 1; x < width; ++x)
            {
                color = m_editImgIns.m_memDibImg.pixelColor(x - 1, profileY);
                red = color.red();
                green = color.green();
                blue = color.blue();
                nextColor = m_editImgIns.m_memDibImg.pixelColor(x, profileY);
                nextRed = nextColor.red();
                nextGreen = nextColor.green();
                nextBlue = nextColor.blue();
                m_profile.m_directX.m_pathRed.moveTo(x - 1, height + 256 - red); // red
                m_profile.m_directX.m_pathRed.lineTo(x, height + 256 - nextRed);
                m_profile.m_directX.m_pathGreen.moveTo(x - 1, height + 256 - green); // green
                m_profile.m_directX.m_pathGreen.lineTo(x, height + 256 - nextGreen);
                m_profile.m_directX.m_pathBlue.moveTo(x - 1, height + 256 - blue); // blue
                m_profile.m_directX.m_pathBlue.lineTo(x, height + 256 - nextBlue);
            }
            m_profile.m_directX.m_pItemPathRed->setPath(m_profile.m_directX.m_pathRed);
            m_profile.m_directX.m_pItemPathGreen->setPath(m_profile.m_directX.m_pathGreen);
            m_profile.m_directX.m_pItemPathBlue->setPath(m_profile.m_directX.m_pathBlue);

            // 垂直プロファイル
            for (int y = 1; y < height - 1; ++y) {
                color = m_editImgIns.m_memDibImg.pixelColor(profileX, y - 1);
                red = color.red();
                green = color.green();
                blue = color.blue();
                nextColor = m_editImgIns.m_memDibImg.pixelColor(profileX, y);
                nextRed = nextColor.red();
                nextGreen = nextColor.green();
                nextBlue = nextColor.blue();
                m_profile.m_directY.m_pathRed.moveTo(width + 256 - red, y - 1); // red
                m_profile.m_directY.m_pathRed.lineTo(width + 256 - nextRed, y);
                m_profile.m_directY.m_pathGreen.moveTo(width + 256 - green, y - 1); // green
                m_profile.m_directY.m_pathGreen.lineTo(width + 256 - nextGreen, y);
                m_profile.m_directY.m_pathBlue.moveTo(width + 256 - blue, y - 1); // blue
                m_profile.m_directY.m_pathBlue.lineTo(width + 256 - nextBlue, y);
            }
            m_profile.m_directY.m_pItemPathRed->setPath(m_profile.m_directY.m_pathRed);
            m_profile.m_directY.m_pItemPathGreen->setPath(m_profile.m_directY.m_pathGreen);
            m_profile.m_directY.m_pItemPathBlue->setPath(m_profile.m_directY.m_pathBlue);

            if (m_editImgIns.m_memDibImg.isGrayscale())
            {
                /* GRAY */
                m_profile.m_directX.m_pItemPathRed->setPen(QPen(QColor(Qt::green)));
                m_profile.m_directX.m_pItemPathGreen->setPen(QPen(QColor(Qt::green)));
                m_profile.m_directX.m_pItemPathBlue->setPen(QPen(QColor(Qt::green)));
                m_profile.m_directY.m_pItemPathRed->setPen(QPen(QColor(Qt::green)));
                m_profile.m_directY.m_pItemPathGreen->setPen(QPen(QColor(Qt::green)));
                m_profile.m_directY.m_pItemPathBlue->setPen(QPen(QColor(Qt::green)));
            }
            else
            {
                m_profile.m_directX.m_pItemPathRed->setPen(QPen(QColor(Qt::red)));
                m_profile.m_directX.m_pItemPathGreen->setPen(QPen(QColor(Qt::green)));
                m_profile.m_directX.m_pItemPathBlue->setPen(QPen(QColor(Qt::blue)));
                m_profile.m_directY.m_pItemPathRed->setPen(QPen(QColor(Qt::red)));
                m_profile.m_directY.m_pItemPathGreen->setPen(QPen(QColor(Qt::green)));
                m_profile.m_directY.m_pItemPathBlue->setPen(QPen(QColor(Qt::blue)));
            }

            if (isXRed)
                this->addItem(m_profile.m_directX.m_pItemPathRed);
            if (isXGreen)
                this->addItem(m_profile.m_directX.m_pItemPathGreen);
            if (isXBlue)
                this->addItem(m_profile.m_directX.m_pItemPathBlue);
            if (isYRed)
                this->addItem(m_profile.m_directY.m_pItemPathRed);
            if (isYGreen)
                this->addItem(m_profile.m_directY.m_pItemPathGreen);
            if (isYBlue)
                this->addItem(m_profile.m_directY.m_pItemPathBlue);
        }
    }
}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    /* マウスプレスイベント
    */
   auto scenePos = event->scenePos();
   auto mouseButton = event->button();

   if (mouseButton == Qt::MouseButton::LeftButton) {
       m_isMousePressLeft = true;
   }
   else if (mouseButton == Qt::MouseButton::RightButton) {

   }
   else if (Qt::MouseButton::MiddleButton) {

   }
   else {
       DEBUG_STREAM("Unknown mouse button in mousePressEvent...\n");
   }

    // 十字線@Press
    if (m_crossLine.m_isCrossLine) {
       drawCrossLine(scenePos);
    }

    // プロファイル@Press
    if (m_profile.m_directX.m_isPathRed ||
        m_profile.m_directX.m_isPathGreen ||
        m_profile.m_directX.m_isPathBlue ||
        m_profile.m_directY.m_isPathRed ||
        m_profile.m_directY.m_isPathGreen ||
        m_profile.m_directY.m_isPathBlue) {
        drawProfile(scenePos,
                    m_profile.m_directX.m_isPathRed,
                    m_profile.m_directX.m_isPathGreen,
                    m_profile.m_directX.m_isPathBlue,
                    m_profile.m_directY.m_isPathRed,
                    m_profile.m_directY.m_isPathGreen, 
                    m_profile.m_directY.m_isPathBlue);
    }

    // 描画命令
    this->update();

    QGraphicsScene::mousePressEvent(event);
}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    /* マウスムーブイベント
    */
    auto scenePos = event->scenePos();

    // 十字線@Move
    if (m_crossLine.m_isCrossLine) {
        drawCrossLine(scenePos);
    }

    // プロファイル@Move
    if (m_profile.m_directX.m_isPathRed ||
        m_profile.m_directX.m_isPathGreen ||
        m_profile.m_directX.m_isPathBlue ||
        m_profile.m_directY.m_isPathRed ||
        m_profile.m_directY.m_isPathGreen ||
        m_profile.m_directY.m_isPathBlue)
    {
        drawProfile(scenePos,
                    m_profile.m_directX.m_isPathRed,
                    m_profile.m_directX.m_isPathGreen,
                    m_profile.m_directX.m_isPathBlue,
                    m_profile.m_directY.m_isPathRed,
                    m_profile.m_directY.m_isPathGreen,
                    m_profile.m_directY.m_isPathBlue);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void ImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    /* マウスリリースイベント
    */
    auto scenePos = event->scenePos();
    auto mouseButton = event->button();

    if (mouseButton == Qt::MouseButton::LeftButton)
    {
        m_isMousePressLeft = false;
    }
    else if (mouseButton == Qt::MouseButton::RightButton)
    {
    }
    else if (Qt::MouseButton::MiddleButton)
    {
    }
    else
    {
        DEBUG_STREAM("Unknown mouse button in mouseMoveEvent...\n");
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

bool ImageScene::setDibImgOnScreen(const QImage &img) {
    /* Sceneへ画像を登録.
       QImage -> QPixmap -> QGraphicsPixmapitem
    */

    if (img.isNull()) {
        return false;
    }

    m_editImgIns.m_memDibImg = img;
    if (m_rawDibImg.isNull())
    {
        m_rawDibImg = img.copy();
    }

    // ディスプレイに表示するQImageはARGB32(OxffRRGGBB)フォーマットで統一
    m_editImgIns.m_offScreenDdbImg = QPixmap::fromImage(img); // ARGB32に統一される？

    // QGraphicsPixmapItemにセット
    m_editImgIns.m_pItemOffScreenDdbImg->setPixmap(m_editImgIns.m_offScreenDdbImg);
    this->addItem(m_editImgIns.m_pItemOffScreenDdbImg);

    // 描画指令
    this->update();

   return true;
}

void ImageScene::resetRawImg() {
    /*原画像に戻す
    */
    // ディスプレイに表示するQImageはARGB32(OxffRRGGBB)フォーマットで統一
    m_editImgIns.m_offScreenDdbImg = QPixmap::fromImage(m_rawDibImg); // ARGB32に統一される？

    // QGraphicsPixmapItemにセット
    m_editImgIns.m_pItemOffScreenDdbImg->setPixmap(m_editImgIns.m_offScreenDdbImg);
    this->addItem(m_editImgIns.m_pItemOffScreenDdbImg);

    // 描画指令
    this->update();
}

QGraphicsPixmapItem *ImageScene::getEditImgItem(const QPointF &scenePos)
{
    /* QGraphicsPixmapItem上のローカル座標を計算
    */
    auto p_item = m_editImgIns.m_pItemOffScreenDdbImg;
    if (p_item->contains(scenePos)) {
        return p_item;
    }
    else {
        return nullptr;
    }

    // QGraphicsItem *p_item = this->itemAt(scenePos, QTransform()); // QTransform()以外だとエラー出るのはなぜ？ p_view->viewportTransform());// transform()のQTransformは原点が様々移動できるのでマズイと思うが...
    // if (p_item)
    // {
    //     bool isExist = false;
    //     // @Note マウス直下のSceneに登録されたItemは複数あり,
    //     // 重なっている(Z値で判別)ので, その中から該当するItemを取り出す.
    //     if (p_item == m_editImgIns.m_pItemOffScreenDdbImg)
    //     {
    //         isExist = true;
    //     }
    //     else
    //     {
    //         while ((p_item = p_item->parentItem()) != nullptr)
    //         {
    //             if (p_item == m_editImgIns.m_pItemOffScreenDdbImg)
    //             {
    //                 isExist = true;
    //                 break;
    //             }
    //         }
    //     }

    //     if (!isExist)
    //     {
    //         return nullptr;
    //     }

    //     return qobject_cast<QGraphicsPixmapItem *>(p_item);
    //}
}
//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////
