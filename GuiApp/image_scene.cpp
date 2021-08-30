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

    QGraphicsScene::mousePressEvent(event);
}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    /* マウスムーブイベント
    */
    auto scenePos = event->scenePos();
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
