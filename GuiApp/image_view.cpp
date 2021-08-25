#include "image_view.h"
#include "image_scene.h"

#include <QMouseEvent>

//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////
ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
    , isAcceptDragDrop(false)
{
    /*DragDropの有効化*/
    // ドロップイベントは親から子へ伝播する. 
    // 無効化するとMainWindowでドロップ処理をしなければならない.
    this->setAcceptDrops(true); 

    /*Sceneに対するマウス左ボタンのドラッグイベント通達を有効にする*/
    //this->setDragMode(QGraphicsView::DragMode::ScrollHandDrag); // [NoDrag, scrollHandDrag, RubberBandDrag ]
    /* Viewの機能設定 */
    // Viewのアップデート規則 [ FullViewportUpdate, SmartViewportUpdate, BoundingRectViewportUpdate ]
    this->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    // 背景を灰色
    this->setBackgroundBrush(QColor(64, 64, 64, 255)); 
    // Scene上の画像，図形のアンチエイリアスをOFF
    this->setRenderHint(QPainter::Antialiasing, false); 
    // Scene上の文字のアンチエイリアスをON
    this->setRenderHint(QPainter::TextAntialiasing, true); 

    /* SceneとViewの間のアフィン変換 に関する設定
        行先行型Affine変換行列
        [m11, m12, m13],
        [m21, m22, m23],
        [m31, m32, m33]
        並進要素：X方向[m31], Y方向[m32]
        回転・スケール・スキューの合成要素：[m11, m12, m21, m22]
        m33: 1
    */
    // Sceneのアフィン変換の変換原点をマウスポインタの直下とする
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // QGraphicsViewクラスがもつ内部変数を使うこと
    // this->transform()
}


ImageView::~ImageView()
{
    
}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void ImageView::updateStatusBar(QMouseEvent *event)
{
    /*ImageWindowのステータスバーを更新する*/
    auto viewPos = event->pos();
    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    if (p_scene)
    {
        QGraphicsPixmapItem *p_item = p_scene->getEditImgItem(scenePos);
        QPointF localPos;
        if (p_item)
        {
            localPos = p_item->mapToItem(p_item, scenePos);
        }
        emit emitShowPosToStatusBar(localPos, scenePos, viewPos);
    }
}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////
void ImageView::mousePressEvent(QMouseEvent *event) {

    updateStatusBar(event);

    QGraphicsView::mousePressEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {
    updateStatusBar(event);

    // DEBUG_STREAM("ImageView::mouseMoveEvent\n");
    QGraphicsView::mouseMoveEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {
    updateStatusBar(event);

    QGraphicsView::mouseReleaseEvent(event);
}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////