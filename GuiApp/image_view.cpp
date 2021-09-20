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
            //DEBUG_STREAM("[CrossLine] Detect target item! LocalPos(%.1f, %.1f)\n", localPos.x(), localPos.y());

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
            //DEBUG_STREAM("[Profile] Detect target item! LocalPos(%.1f, %.1f)\n", localPos.x(), localPos.y());

            int profileY = (int)localPos.y();
            int profileX = (int)localPos.x();
            int width = (int)localRect.width();
            int height = (int)localRect.height();
            QColor color, nextColor;
            int red, green, blue;
            int nextRed, nextGreen, nextBlue;
            //DEBUG_STREAM("profileX %d, profileY %d\n", profileX, profileY);

            auto p_viewport = this->viewport();
            int viewWidth = p_viewport->width();
            int viewHeight = p_viewport->height();
            QPointF left = this->mapToScene(0, viewPos.y());
            QPointF top = this->mapToScene(viewPos.x(), 0);
            QPointF right = this->mapToScene(viewWidth, viewPos.y());
            QPointF bottom = this->mapToScene(viewPos.x(), viewHeight);

            p_scene->m_profile.m_directX.m_pathRed.clear();
            p_scene->m_profile.m_directX.m_pathGreen.clear();
            p_scene->m_profile.m_directX.m_pathBlue.clear();
            p_scene->m_profile.m_directY.m_pathRed.clear();
            p_scene->m_profile.m_directY.m_pathGreen.clear();
            p_scene->m_profile.m_directY.m_pathBlue.clear();

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

            if (isXRed && !p_scene->m_profile.m_directX.m_isAddedRed) {
                p_scene->addItem(p_scene->m_profile.m_directX.m_pItemPathRed);
                p_scene->m_profile.m_directX.m_isAddedRed = true;
            }
            if (isXGreen && !p_scene->m_profile.m_directX.m_isAddedGreen) {
                p_scene->addItem(p_scene->m_profile.m_directX.m_pItemPathGreen);
                p_scene->m_profile.m_directX.m_isAddedGreen = true;
            }
            if (isXBlue && !p_scene->m_profile.m_directX.m_isAddedBlue) {
                p_scene->addItem(p_scene->m_profile.m_directX.m_pItemPathBlue);
                p_scene->m_profile.m_directX.m_isAddedBlue = true;
            }
            if (isYRed && !p_scene->m_profile.m_directY.m_isAddedRed) {
                p_scene->addItem(p_scene->m_profile.m_directY.m_pItemPathRed);
                p_scene->m_profile.m_directY.m_isAddedRed = true;
            }
            if (isYGreen && !p_scene->m_profile.m_directY.m_isAddedGreen) {
                p_scene->addItem(p_scene->m_profile.m_directY.m_pItemPathGreen);
                p_scene->m_profile.m_directY.m_isAddedGreen = true;
            }
            if (isYBlue && !p_scene->m_profile.m_directY.m_isAddedBlue) {
                p_scene->addItem(p_scene->m_profile.m_directY.m_pItemPathBlue);
                p_scene->m_profile.m_directY.m_isAddedBlue = true;
            }
        }
    }
}


void ImageView::drawFigure(const QPoint &viewPos, bool isCenterDrag, bool isSquareDrag)
{
    /* 図形(l,t),(r,b)の描画
    */
    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    QGraphicsPixmapItem *p_item = p_scene->getEditImgItem(scenePos);

    if (p_item) {
        QPointF localPos = p_item->mapToItem(p_item, scenePos);
        QRectF localRect = p_item->boundingRect(); // Local座標における矩形サイズ

        if (m_isMousePressLeft && !m_isMouseDrag) {
            // アンカーポイント
            p_scene->m_anchor = localPos;
            p_scene->m_rect.setTopLeft(localPos);
            p_scene->m_rect.setBottomRight(localPos);
        }
        else if (m_isMousePressLeft && m_isMouseDrag) {
            if (!m_isGenFigure) {
                // 矩形
                if (p_scene->m_roi.m_isRoi) {
                    p_scene->m_roi.makeRect(p_scene, p_scene->m_rect); // 新規作成
                }
                m_isGenFigure = true;
            }

            QPointF dp, tl, br;
            qreal dw, dh;

            if (isCenterDrag) {
                dp = localPos - p_scene->m_anchor;
                dw = std::abs(dp.x()); // 幅
                dh = std::abs(dp.y()); // 高さ

                if (isSquareDrag) {
                    dw = (dw < dh) ? dw : dh;
                    dh = dw;
                }
                tl.setX(p_scene->m_anchor.x() - dw);
                tl.setY(p_scene->m_anchor.y() - dh);
                br.setX(p_scene->m_anchor.x() + dw);
                br.setY(p_scene->m_anchor.y() + dh);
            }
            else {
                qreal ax, ay, lx, ly;
                ax = p_scene->m_anchor.x();
                ay = p_scene->m_anchor.y();
                lx = localPos.x();
                ly = localPos.y();
                qreal l, r, t, b;

                if (ax < lx) {
                    l = ax;
                    r = lx;
                }
                else {
                    l = lx;
                    r = ax;
                }
                if (ay < ly) {
                    t = ay;
                    b = ly;
                }
                else {
                    t = ly;
                    b = ay;
                }
                
                if (isSquareDrag) {
                    dw = r - l;
                    dh = b - t;
                    dw = dw < dh ? dw : dh;
                    dh = dw;
                    if (ax < lx && ay < ly) {
                        l = ax;
                        r = l + dw;
                        t = ay;
                        b = t + dh;
                    }
                    else if (ax < lx && ay > ly) {
                        l = ax;
                        r = l + dw;
                        t = ay - dw;
                        b = ay;
                    }
                    else if (ax > lx && ay > ly) {
                        l = ax - dw;
                        r = ax;
                        t = ay - dh;
                        b = ay;
                    }
                    else if (ax > lx && ay < ly) {
                        l = ax - dw;
                        r = ax;
                        t = ay;
                        b = t + dh;
                    }
                } 

                tl.setX(l);
                tl.setY(t);
                br.setX(r);
                br.setY(b);
            }

            p_scene->m_rect.setTopLeft(tl);
            p_scene->m_rect.setBottomRight(br);

            // 矩形
            if (p_scene->m_roi.m_isRoi) {
                p_scene->m_roi.updateRect(p_scene, p_scene->m_rect); // 描画更新
            }
        }
        else if (!m_isMousePressLeft && m_isMouseDrag) {
            // 矩形
            if (p_scene->m_roi.m_isRoi) {
                qreal w, h;
                w = p_scene->m_rect.width();
                h = p_scene->m_rect.height();
                IS_DEBUG_STREAM("w:%d, h:%d\n", (int)w, (int)h);
                if (w > 2 && h > 2) {
                    p_scene->m_roi.updateRect(p_scene, p_scene->m_rect); // 描画更新
                }
                else {
                    p_scene->m_roi.removeRect(p_scene, p_scene->m_roi.m_rois.size() - 1);
                    p_scene->m_rect.setX(0);
                    p_scene->m_rect.setY(0);
                    p_scene->m_rect.setWidth(0);
                    p_scene->m_rect.setHeight(0);
                }
            }

            m_isGenFigure = false;
        }
        else {
            
        }
    }
}

void ImageView::removeFigure(const QPoint &viewPos) {
    /* 図形消去
    */
    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    auto p_item = p_scene->itemAt(scenePos, QTransform());
    if (p_item) {
        // 矩形
        if (p_scene->m_roi.m_isRoi) {
            p_scene->m_roi.removeRect(p_scene, p_item);
        }
    }
}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////
void ImageView::mousePressEvent(QMouseEvent *event) {
    /* マウスプレスイベント
    */

    updateStatusBar(event->pos());

    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    auto mouseButton = event->button();
    if (mouseButton == Qt::MouseButton::LeftButton)
    {
        m_isMousePressLeft = true;
    }
    else if (mouseButton == Qt::MouseButton::RightButton)
    {
        m_isMousePressRight = true;
    }
    else if (Qt::MouseButton::MiddleButton)
    {
        m_isMousePressMiddle = true;
    }
    else
    {
        IS_DEBUG_STREAM("Unknown mouse button in mousePressEvent...\n");
    }

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

    // 図形
    if (p_scene->m_roi.m_isRoi) {
        drawFigure(event->pos(),
                   event->modifiers() & Qt::ControlModifier,
                   event->modifiers() & Qt::ShiftModifier);
    }

    QGraphicsView::mousePressEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {
    /* マウス移動イベント
    */

    updateStatusBar(event->pos());
    auto p_scene = qobject_cast<ImageScene *>(this->scene());

    if (m_isMousePressLeft || m_isMousePressMiddle || m_isMousePressRight) {
        m_isMouseDrag = true;
    }
    else {
        m_isMouseDrag = false;
    }

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

    // 図形
    if (p_scene->m_roi.m_isRoi) {
        drawFigure(event->pos(),
                event->modifiers() & Qt::ControlModifier,
                event->modifiers() & Qt::ShiftModifier);
    }
    
    // DEBUG_STREAM("ImageView::mouseMoveEvent\n");
    QGraphicsView::mouseMoveEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {
    /* マウスリリースイベント
    */

    updateStatusBar(event->pos());
    auto p_scene = qobject_cast<ImageScene *>(this->scene());

    auto mouseButton = event->button();
    if (mouseButton == Qt::MouseButton::LeftButton) {
        m_isMousePressLeft = false;
    }
    else if (mouseButton == Qt::MouseButton::RightButton) {
        m_isMousePressRight = false;
    }
    else if (Qt::MouseButton::MiddleButton) {
        m_isMousePressMiddle = false;
    }
    else {
        IS_DEBUG_STREAM("Unknown mouse button in mouseMoveEvent...\n");
    }

    // 図形
    if (p_scene->m_roi.m_isRoi) {
        drawFigure(event->pos(),
                   event->modifiers() & Qt::ControlModifier,
                   event->modifiers() & Qt::ShiftModifier);
    }

    m_isMouseDrag = false;

    QGraphicsView::mouseReleaseEvent(event);
}

void ImageView::mouseDoubleClickEvent(QMouseEvent *event) {
    /* マウスダブルクリックイベント
    */
    updateStatusBar(event->pos());
    auto p_scene = qobject_cast<ImageScene *>(this->scene());

    auto mouseButton = event->button();
    if (mouseButton == Qt::MouseButton::LeftButton) {
        // 図形の削除
        removeFigure(event->pos());
    }
    else if (mouseButton == Qt::MouseButton::RightButton) {

    }
    else if (Qt::MouseButton::MiddleButton) {

    }
    else {
        IS_DEBUG_STREAM("Unknown mouse button in mouseMoveEvent...\n");
    }

    

    QGraphicsView::mouseDoubleClickEvent(event);
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