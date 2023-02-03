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

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPointF>


//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

ImageScene::ImageScene(QObject* parent)
    : QGraphicsScene(parent) 
{
    // mCrossLine.m_isCrossLine = true; // 仮
}

ImageScene::~ImageScene() {}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent *event) 
{
    /* マウスプレスイベント */
    auto scenePos = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) 
{
    /* マウスムーブイベント */
    auto scenePos = event->scenePos();
    QGraphicsScene::mouseMoveEvent(event);
}

void ImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) 
{
    /* マウスリリースイベント */
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
bool ImageScene::SetDibImg(const QImage& img, bool isRaw) 
{
    if (img.isNull()) 
    {
        return false;
    }

    mEditSceneImg.m_memDibImg = img.copy(); // ここのcopy必要!

    if (isRaw)
    {
        mRawDibImg = mEditSceneImg.m_memDibImg.copy();
    }

    // ディスプレイに表示するQImageはARGB32(OxffRRGGBB)フォーマットで統一
    mEditSceneImg.m_offScreenDdbImg = QPixmap::fromImage(mEditSceneImg.m_memDibImg);

    // QGraphicsPixmapItemにセット
    mEditSceneImg.m_pItemOffScreenDdbImg->setPixmap(mEditSceneImg.m_offScreenDdbImg);

    if (!mEditSceneImg.m_isSceneImg) 
    {
        mEditSceneImg.m_isSceneImg = true;
        this->addItem(mEditSceneImg.m_pItemOffScreenDdbImg);
    }

    // 描画指令
    this->update();

   return true;
}

/**
 * @brief DIB画像の取得
 * 
 * @return QImage 
 */
QImage ImageScene::GetDibImg() 
{
    return mEditSceneImg.m_memDibImg;
}

void ImageScene::ResetRawImg() 
{
    /* 原画像に戻す */

    // 初期化
    mEditSceneImg.m_memDibImg = mRawDibImg.copy();

    // ディスプレイに表示するQImageはARGB32(OxffRRGGBB)フォーマットで統一
    mEditSceneImg.m_offScreenDdbImg = QPixmap::fromImage(mRawDibImg);

    // QGraphicsPixmapItemにセット
    mEditSceneImg.m_pItemOffScreenDdbImg->setPixmap(mEditSceneImg.m_offScreenDdbImg);
    if (!mEditSceneImg.m_isSceneImg) {
        mEditSceneImg.m_isSceneImg = true;
        this->addItem(mEditSceneImg.m_pItemOffScreenDdbImg);
    }

    // 描画指令
    this->update();
}

QGraphicsPixmapItem *ImageScene::GetEditImgItem(const QPointF &scenePos)
{
    /* QGraphicsPixmapItem上のローカル座標を計算
    */
    auto p_item = mEditSceneImg.m_pItemOffScreenDdbImg;
    if (p_item->contains(scenePos)) 
    {
        return p_item;
    }
    else 
    {
        return nullptr;
    }
}
//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////
