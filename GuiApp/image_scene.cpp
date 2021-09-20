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
    QGraphicsScene::mouseReleaseEvent(event);
}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

/**
 * @brief Sceneへ画像を登録
 * QImage -> QPixmap -> QGraphicsPixmapitem
 * @param img
 * @return true
 * @return false
 */
bool ImageScene::setDibImg(const QImage &img) {
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

/**
 * @brief DIB画像の取得
 * 
 * @return QImage 
 */
QImage ImageScene::getDibImg() {
    return m_editImgIns.m_memDibImg;
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
}
//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////
