#include "image_view.h"
#include "image_scene.h"

#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QPoint>
#include <QRectF>
#include <QRect>

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

void ImageView::updateStatusBar(const QPoint &viewPos)
{
    /*ImageWindowのステータスバーを更新する*/
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

void ImageView::drawCrossLine(const QPoint &viewPos)
{
    /* マウスを中心とした十字線をSceneに描画
    */
    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    QGraphicsPixmapItem *p_item = p_scene->getEditImgItem(scenePos);
    if (p_item)
    {
        // DEBUG_STREAM("ScenePos(%.1f, %.1f)\n", scenePos.x(), scenePos.y());

        QPointF localPos = p_item->mapToItem(p_item, scenePos);
        QRectF localRect = p_item->boundingRect(); // Local座標における矩形サイズ
        
        if (localRect.contains(localPos.toPoint()))
        {
            DEBUG_STREAM("[CrossLine] Detect target item! LocalPos(%.1f, %.1f)\n", localPos.x(), localPos.y());

            // 水平線
            qreal y = localPos.y();
            p_scene->m_crossLine.m_pItemLineX->setLine(0, y, localRect.width(), y);

            if (p_scene->m_crossLine.m_pItemLineX->contains(scenePos))
            {
                p_scene->removeItem(p_scene->m_crossLine.m_pItemLineX);
            }
            p_scene->addItem(p_scene->m_crossLine.m_pItemLineX);

            // 垂直線
            qreal x = localPos.x();
            p_scene->m_crossLine.m_pItemLineY->setLine(x, 0, x, localRect.height());
            if (p_scene->m_crossLine.m_pItemLineY->contains(scenePos))
            {
                p_scene->removeItem(p_scene->m_crossLine.m_pItemLineY);
            }
            p_scene->addItem(p_scene->m_crossLine.m_pItemLineY);
        }
    }
}

void ImageView::drawProfile(const QPoint &viewPos,
                            bool isXRed, bool isXGreen, bool isXBlue,
                            bool isYRed, bool isYGreen, bool isYBlue)
{
    /* 画像プロファイルの描画
    */
    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    QGraphicsPixmapItem *p_item = p_scene->getEditImgItem(scenePos);
    if (p_item)
    {
        // DEBUG_STREAM("ScenePos(%.1f, %.1f)\n", scenePos.x(), scenePos.y());

        QPointF localPos = p_item->mapToItem(p_item, scenePos);
        QRectF localRect = p_item->boundingRect(); // Local座標における矩形サイズ
        
        if (localRect.contains(localPos.toPoint()))
        {
            DEBUG_STREAM("[Profile] Detect target item! LocalPos(%.1f, %.1f)\n", localPos.x(), localPos.y());

            // シーンに登録済みのProfileItemを解除
            foreach (QGraphicsItem *p_item, p_scene->items())
            {
                // X
                if (p_item == p_scene->m_profile.m_directX.m_pItemPathRed)
                {
                    p_scene->removeItem(p_scene->m_profile.m_directX.m_pItemPathRed);
                    p_scene->m_profile.m_directX.m_pathRed.clear();
                }
                if (p_item == p_scene->m_profile.m_directX.m_pItemPathGreen)
                {
                    p_scene->removeItem(p_scene->m_profile.m_directX.m_pItemPathGreen);
                    p_scene->m_profile.m_directX.m_pathGreen.clear();
                }
                if (p_item == p_scene->m_profile.m_directX.m_pItemPathBlue)
                {
                    p_scene->removeItem(p_scene->m_profile.m_directX.m_pItemPathBlue);
                    p_scene->m_profile.m_directX.m_pathBlue.clear();
                }

                // Y
                if (p_item == p_scene->m_profile.m_directY.m_pItemPathRed)
                {
                    p_scene->removeItem(p_scene->m_profile.m_directY.m_pItemPathRed);
                    p_scene->m_profile.m_directY.m_pathRed.clear();
                }
                if (p_item == p_scene->m_profile.m_directY.m_pItemPathGreen)
                {
                    p_scene->removeItem(p_scene->m_profile.m_directY.m_pItemPathGreen);
                    p_scene->m_profile.m_directY.m_pathGreen.clear();
                }
                if (p_item == p_scene->m_profile.m_directY.m_pItemPathBlue)
                {
                    p_scene->removeItem(p_scene->m_profile.m_directY.m_pItemPathBlue);
                    p_scene->m_profile.m_directY.m_pathBlue.clear();
                }
            }

            int profileY = (int)localPos.y();
            int profileX = (int)localPos.x();
            int width = (int)localRect.width();
            int height = (int)localRect.height();
            QColor color, nextColor;
            int red, green, blue;
            int nextRed, nextGreen, nextBlue;
            DEBUG_STREAM("profileX %d, profileY %d\n", profileX, profileY);

            auto p_viewport = this->viewport();
            int viewWidth = p_viewport->width();
            int viewHeight = p_viewport->height();
            QPointF left = this->mapToScene(0, viewPos.y());
            QPointF top = this->mapToScene(viewPos.x(), 0);
            QPointF right = this->mapToScene(viewWidth, viewPos.y());
            QPointF bottom = this->mapToScene(viewPos.x(), viewHeight);

            // 水平プロファイル
            for (int x = left.x() + 1; x < right.x(); ++x)
            {
                if (x - 1 <= 0 || x >= width)
                    continue;

                color = p_scene->m_editImgIns.m_memDibImg.pixelColor(x - 1, profileY);
                red = color.red();
                green = color.green();
                blue = color.blue();
                nextColor = p_scene->m_editImgIns.m_memDibImg.pixelColor(x, profileY);
                nextRed = nextColor.red();
                nextGreen = nextColor.green();
                nextBlue = nextColor.blue();
                p_scene->m_profile.m_directX.m_pathRed.moveTo(x - 1, bottom.y() - red); // red
                p_scene->m_profile.m_directX.m_pathRed.lineTo(x, bottom.y() - nextRed);
                p_scene->m_profile.m_directX.m_pathGreen.moveTo(x - 1, bottom.y() - green); // green
                p_scene->m_profile.m_directX.m_pathGreen.lineTo(x, bottom.y() - nextGreen);
                p_scene->m_profile.m_directX.m_pathBlue.moveTo(x - 1, bottom.y() - blue); // blue
                p_scene->m_profile.m_directX.m_pathBlue.lineTo(x, bottom.y() - nextBlue);
            }
            p_scene->m_profile.m_directX.m_pItemPathRed->setPath(p_scene->m_profile.m_directX.m_pathRed);
            p_scene->m_profile.m_directX.m_pItemPathGreen->setPath(p_scene->m_profile.m_directX.m_pathGreen);
            p_scene->m_profile.m_directX.m_pItemPathBlue->setPath(p_scene->m_profile.m_directX.m_pathBlue);

            // 垂直プロファイル
            for (int y = top.y() + 1; y < bottom.y(); ++y)
            {
                if (y - 1 <= 0 || y >= height)
                    continue;

                color = p_scene->m_editImgIns.m_memDibImg.pixelColor(profileX, y - 1);
                red = color.red();
                green = color.green();
                blue = color.blue();
                nextColor = p_scene->m_editImgIns.m_memDibImg.pixelColor(profileX, y);
                nextRed = nextColor.red();
                nextGreen = nextColor.green();
                nextBlue = nextColor.blue();
                p_scene->m_profile.m_directY.m_pathRed.moveTo(right.x() - red, y - 1); // red
                p_scene->m_profile.m_directY.m_pathRed.lineTo(right.x() - nextRed, y);
                p_scene->m_profile.m_directY.m_pathGreen.moveTo(right.x() - green, y - 1); // green
                p_scene->m_profile.m_directY.m_pathGreen.lineTo(right.x() - nextGreen, y);
                p_scene->m_profile.m_directY.m_pathBlue.moveTo(right.x() - blue, y - 1); // blue
                p_scene->m_profile.m_directY.m_pathBlue.lineTo(right.x() - nextBlue, y);
            }
            p_scene->m_profile.m_directY.m_pItemPathRed->setPath(p_scene->m_profile.m_directY.m_pathRed);
            p_scene->m_profile.m_directY.m_pItemPathGreen->setPath(p_scene->m_profile.m_directY.m_pathGreen);
            p_scene->m_profile.m_directY.m_pItemPathBlue->setPath(p_scene->m_profile.m_directY.m_pathBlue);

            if (p_scene->m_editImgIns.m_memDibImg.isGrayscale())
            {
                /* GRAY */
                p_scene->m_profile.m_directX.m_pItemPathRed->setPen(QPen(QColor(Qt::green)));
                p_scene->m_profile.m_directX.m_pItemPathGreen->setPen(QPen(QColor(Qt::green)));
                p_scene->m_profile.m_directX.m_pItemPathBlue->setPen(QPen(QColor(Qt::green)));
                p_scene->m_profile.m_directY.m_pItemPathRed->setPen(QPen(QColor(Qt::green)));
                p_scene->m_profile.m_directY.m_pItemPathGreen->setPen(QPen(QColor(Qt::green)));
                p_scene->m_profile.m_directY.m_pItemPathBlue->setPen(QPen(QColor(Qt::green)));
            }
            else
            {
                p_scene->m_profile.m_directX.m_pItemPathRed->setPen(QPen(QColor(Qt::red)));
                p_scene->m_profile.m_directX.m_pItemPathGreen->setPen(QPen(QColor(Qt::green)));
                p_scene->m_profile.m_directX.m_pItemPathBlue->setPen(QPen(QColor(Qt::blue)));
                p_scene->m_profile.m_directY.m_pItemPathRed->setPen(QPen(QColor(Qt::red)));
                p_scene->m_profile.m_directY.m_pItemPathGreen->setPen(QPen(QColor(Qt::green)));
                p_scene->m_profile.m_directY.m_pItemPathBlue->setPen(QPen(QColor(Qt::blue)));
            }

            if (isXRed)
                p_scene->addItem(p_scene->m_profile.m_directX.m_pItemPathRed);
            if (isXGreen)
                p_scene->addItem(p_scene->m_profile.m_directX.m_pItemPathGreen);
            if (isXBlue)
                p_scene->addItem(p_scene->m_profile.m_directX.m_pItemPathBlue);
            if (isYRed)
                p_scene->addItem(p_scene->m_profile.m_directY.m_pItemPathRed);
            if (isYGreen)
                p_scene->addItem(p_scene->m_profile.m_directY.m_pItemPathGreen);
            if (isYBlue)
                p_scene->addItem(p_scene->m_profile.m_directY.m_pItemPathBlue);
        }
    }
}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////
void ImageView::mousePressEvent(QMouseEvent *event) {

    updateStatusBar(event->pos());
    auto p_scene = qobject_cast<ImageScene *>(this->scene());

    // 十字線@Press
    if (p_scene->m_crossLine.m_isCrossLine)
    {
        drawCrossLine(event->pos());
    }

    // プロファイル@Press
    if (p_scene->m_profile.m_directX.m_isPathRed ||
        p_scene->m_profile.m_directX.m_isPathGreen ||
        p_scene->m_profile.m_directX.m_isPathBlue ||
        p_scene->m_profile.m_directY.m_isPathRed ||
        p_scene->m_profile.m_directY.m_isPathGreen ||
        p_scene->m_profile.m_directY.m_isPathBlue)
    {
        drawProfile(event->pos(),
                    p_scene->m_profile.m_directX.m_isPathRed,
                    p_scene->m_profile.m_directX.m_isPathGreen,
                    p_scene->m_profile.m_directX.m_isPathBlue,
                    p_scene->m_profile.m_directY.m_isPathRed,
                    p_scene->m_profile.m_directY.m_isPathGreen,
                    p_scene->m_profile.m_directY.m_isPathBlue);
    }

    QGraphicsView::mousePressEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {

    updateStatusBar(event->pos());

    auto p_scene = qobject_cast<ImageScene *>(this->scene());

    // 十字線@Press
    if (p_scene->m_crossLine.m_isCrossLine)
    {
        drawCrossLine(event->pos());
    }

    // プロファイル@Press
    if (p_scene->m_profile.m_directX.m_isPathRed ||
        p_scene->m_profile.m_directX.m_isPathGreen ||
        p_scene->m_profile.m_directX.m_isPathBlue ||
        p_scene->m_profile.m_directY.m_isPathRed ||
        p_scene->m_profile.m_directY.m_isPathGreen ||
        p_scene->m_profile.m_directY.m_isPathBlue)
    {
        drawProfile(event->pos(),
                    p_scene->m_profile.m_directX.m_isPathRed,
                    p_scene->m_profile.m_directX.m_isPathGreen,
                    p_scene->m_profile.m_directX.m_isPathBlue,
                    p_scene->m_profile.m_directY.m_isPathRed,
                    p_scene->m_profile.m_directY.m_isPathGreen,
                    p_scene->m_profile.m_directY.m_isPathBlue);
    }

    // DEBUG_STREAM("ImageView::mouseMoveEvent\n");
    QGraphicsView::mouseMoveEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {

    updateStatusBar(event->pos());

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