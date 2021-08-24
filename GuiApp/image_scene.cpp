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

//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

ImageScene::ImageScene(QObject* parent)
    : QGraphicsScene(parent) {

}

ImageScene::~ImageScene() {

}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void ImageScene::calcSceneImgLocalPos(const QPointF &scenePos) {
    /* QGraphicsPixmapItem上のローカル座標を計算
    */
}

void ImageScene::drawCrossLine(const QPointF &scenePos) {
    /* マウスを中心とした十字線をSceneに描画
    */
   foreach (QGraphicsView *p_view, this->views()) {
       QGraphicsItem *p_item = this->itemAt(scenePos, QTransform()); // QTransform()以外だとエラー出るのはなぜ？ p_view->viewportTransform());// transform()のQTransformは原点が様々移動できるのでマズイと思うが...
       if (p_item) {
            bool isExist = false;
            // @Note マウス直下のSceneに登録されたItemは複数あり,
            // 重なっている(Z値で判別)ので, その中から該当するItemを取り出す.
            if (p_item == m_editImgIns.m_pItemOffScreenDdbImg) {
                isExist = true;
            }
            else {
               while ((p_item = p_item->parentItem()) != nullptr) {
                   if (p_item == m_editImgIns.m_pItemOffScreenDdbImg) {
                       isExist = true;
                       break;
                   }
               }
            }

            m_crossLine.m_isCrossLine = true;
            if (!isExist || !m_crossLine.m_isCrossLine)
            {
                return;
            }

            DEBUG_STREAM("ScenePos(%f, %f)\n", scenePos.x(), scenePos.y());

            QPointF localPos = p_item->mapToItem(p_item, scenePos);
            QRectF localRect = p_item->boundingRect(); // Local座標における矩形サイズ

            DEBUG_STREAM("Detect target item! LocalPos(%f, %f)\n", localPos.x(), localPos.y());

            if (localRect.contains(localPos.toPoint())) {
               
                m_crossLine.m_pItemLineX->setLine(0, localPos.y(), localRect.width(), localPos.y());
                this->addItem(m_crossLine.m_pItemLineX);

                // for (const auto &item : this->items()) {

                // }
            }
       }
   }
}

void ImageScene::drawProfile(const QPointF &scenePos) {

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
       drawCrossLine(scenePos);
   }
   else if (mouseButton == Qt::MouseButton::RightButton) {

   }
   else if (Qt::MouseButton::MidButton) {

   }
   else {
       DEBUG_STREAM("Unknown mouse press button...\n");
   }

   // 描画命令
   this->update();

   QGraphicsScene::mousePressEvent(event);
}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
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

//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

void ImageScene::slotToggleCrossLine(bool isShow)
{
    m_crossLine.m_isCrossLine = isShow;
}

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////
