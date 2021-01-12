#include "image_draw_view.h"

#include <QString>
#include <QMessageBox>

ImageDrawView::ImageDrawView(QWidget* parent)
    : QGraphicsView(parent)
    , zoom_level()
{
    /* Drag/Drop処理を有効化 */
    this->setAcceptDrops(true); // ドロップイベントは親から子へ伝播する。無効化するとMainWindowでドロップ処理をしなければならない。
    is_accept_drag_and_drop = false;

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

ImageDrawView::~ImageDrawView() 
{}
