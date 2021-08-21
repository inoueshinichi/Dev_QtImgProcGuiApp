#include "image_scene.h"

ImageScene::ImageScene(QObject* p_parent)
    : QGraphicsScene(p_parent) {

    m_pItemOffScreenDdbImgBefore = new QGraphicsPixmapItem();
    m_pItemOffScreenDdbImgAfter = new QGraphicsPixmapItem();
}

ImageScene::~ImageScene() {

    if (m_pItemOffScreenDdbImgBefore) {
        delete m_pItemOffScreenDdbImgBefore;
        m_pItemOffScreenDdbImgBefore = nullptr;
    }

    if (m_pItemOffScreenDdbImgAfter) {
        delete m_pItemOffScreenDdbImgAfter;
        m_pItemOffScreenDdbImgAfter = nullptr;
    }
}

bool ImageScene::setDibImgBeforeOnScreen(const QImage &beforeImg) {
    /* Sceneへ画像を登録.
       QImage -> QPixmap -> QGraphicsPixmapitem
    */

   if (beforeImg.isNull()) {
       return false;
   }

   m_editDibImgBefore = beforeImg;
   if (m_rawDibImg.isNull()) {
       m_rawDibImg = beforeImg.copy();
   }

   // ディスプレイに表示するQImageはARGB32(OxffRRGGBB)フォーマットで統一
   m_offScreenDdbImgBefore = QPixmap::fromImage(m_editDibImgBefore); // ARGB32に統一される？

   // QGraphicsPixmapItemにセット
   m_pItemOffScreenDdbImgBefore->setPixmap(m_offScreenDdbImgBefore);
   this->addItem(m_pItemOffScreenDdbImgBefore);
   
//    auto imgRect = m_offScreenDdbImgBefore.rect();
//    QRectF sceneRect(imgRect.top(), imgRect.left(), imgRect.width(), imgRect.height());
//    this->setSceneRect(sceneRect);

   this->update();

   return true;
}


bool ImageScene::setDibImgAfterOnScreen(const QImage &afterImg) {
    if (afterImg.isNull())
    {
        return false;
    }

    m_editDibImgAfter = afterImg;
    m_offScreenDdbImgAfter = QPixmap::fromImage(m_editDibImgAfter);
    m_pItemOffScreenDdbImgAfter->setPixmap(m_offScreenDdbImgAfter);
    this->addItem(m_pItemOffScreenDdbImgAfter);

    this->update();

    return true;
}