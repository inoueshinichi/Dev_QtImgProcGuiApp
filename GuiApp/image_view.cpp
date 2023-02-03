#include "image_view.h"
#include "image_scene.h"

#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QPoint>
#include <QRectF>
#include <QRect>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QString>
#include <QDrag>
#include <Qt>

//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////
ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
    , mIsAcceptDragDrop(false) 
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


ImageView::~ImageView() {}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void ImageView::UpdateStatusBar(const QPoint &viewPos) 
{
    /*ImageWindowのステータスバーを更新する*/

    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    if (p_scene) 
    {
        QGraphicsPixmapItem *p_item = p_scene->GetEditImgItem(scenePos);
        QPointF localPos;

        if (p_item) 
        {
            localPos = p_item->mapToItem(p_item, scenePos);
        }

        emit EmitShowPosToStatusBar(localPos, scenePos, viewPos);
    }
}

void ImageView::DrawCrossLine(const QPoint &viewPos) 
{
    /* マウスを中心とした十字線をSceneに描画 */

    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    QGraphicsPixmapItem *p_item = p_scene->GetEditImgItem(scenePos);
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
            mCrossLine.GetLineItemX()->setLine(0, y, localRect.width(), y);

            if (mCrossLine.GetLineItemX()->contains(scenePos)) 
            {
                p_scene->removeItem(mCrossLine.GetLineItemX());
            }
            p_scene->addItem(mCrossLine.GetLineItemX());

            // 垂直線
            qreal x = localPos.x();
            mCrossLine.GetLineItemY()->setLine(x, 0, x, localRect.height());
            if (mCrossLine.GetLineItemY()->contains(scenePos)) 
            {
                p_scene->removeItem(mCrossLine.GetLineItemY());
            }
            p_scene->addItem(mCrossLine.GetLineItemY());
        }
    }
}

void ImageView::DrawProfile(const QPoint &viewPos,
                            bool isXRed, bool isXGreen, bool isXBlue,
                            bool isYRed, bool isYGreen, bool isYBlue) 
{
    /* 画像プロファイルの描画 */

    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    QGraphicsPixmapItem *p_item = p_scene->GetEditImgItem(scenePos);
    if (p_item) 
    {
        // DEBUG_STREAM("ScenePos(%.1f, %.1f)\n", scenePos.x(), scenePos.y());

        QPointF localPos = p_item->mapToItem(p_item, scenePos);
        QRectF localRect = p_item->boundingRect(); // Local座標における矩形サイズ
        
        if (localRect.contains(localPos.toPoint())) 
        {
            IS_DEBUG_STREAM("[Profile] Detect target item! LocalPos(%.1f, %.1f)\n", localPos.x(), localPos.y());

            int profileY = (int)localPos.y();
            int profileX = (int)localPos.x();
            int width = (int)localRect.width();
            int height = (int)localRect.height();
            QColor color, nextColor;
            int red, green, blue;
            int nextRed, nextGreen, nextBlue;
            // IS_DEBUG_STREAM("profileX %d, profileY %d\n", profileX, profileY);

            auto p_viewport = this->viewport();
            int viewWidth = p_viewport->width();
            int viewHeight = p_viewport->height();
            QPointF left = this->mapToScene(0, viewPos.y());
            QPointF top = this->mapToScene(viewPos.x(), 0);
            QPointF right = this->mapToScene(viewWidth, viewPos.y());
            QPointF bottom = this->mapToScene(viewPos.x(), viewHeight);

            mProfile.ClearPath();

            // 水平プロファイル
            for (int x = left.x() + 1; x < right.x(); ++x) 
            {
                if (x - 1 <= 0 || x >= width) continue;
                    
                color = p_scene->GetEditSceneImg().m_memDibImg.pixelColor(x - 1, profileY);
                red = color.red();
                green = color.green();
                blue = color.blue();
                nextColor = p_scene->GetEditSceneImg().m_memDibImg.pixelColor(x, profileY);
                nextRed = nextColor.red();
                nextGreen = nextColor.green();
                nextBlue = nextColor.blue();
                mProfile.MoveToDirXRed(x - 1, bottom.y() - red); // red
                mProfile.LineToDirXRed(x, bottom.y() - nextRed);
                mProfile.MoveToDirXGreen(x - 1, bottom.y() - green); // green
                mProfile.LineToDirXGreen(x, bottom.y() - nextGreen);
                mProfile.MoveToDirXBlue(x - 1, bottom.y() - blue); // blue
                mProfile.LineToDirXBlue(x, bottom.y() - nextBlue);
            }
            mProfile.GetDirectionX().SetPathRed();
            mProfile.GetDirectionX().SetPathGreen();
            mProfile.GetDirectionX().SetPathBlue();

            // 垂直プロファイル
            for (int y = top.y() + 1; y < bottom.y(); ++y) 
            {
                if (y - 1 <= 0 || y >= height) continue;

                color = p_scene->GetEditSceneImg().m_memDibImg.pixelColor(profileX, y - 1);
                red = color.red();
                green = color.green();
                blue = color.blue();
                nextColor = p_scene->GetEditSceneImg().m_memDibImg.pixelColor(profileX, y);
                nextRed = nextColor.red();
                nextGreen = nextColor.green();
                nextBlue = nextColor.blue();
                mProfile.MoveToDirYRed(right.x() - red, y - 1); // red
                mProfile.LineToDirYRed(right.x() - nextRed, y);
                mProfile.MoveToDirYGreen(right.x() - green, y - 1); // green
                mProfile.LineToDirYGreen(right.x() - nextGreen, y);
                mProfile.MoveToDirYBlue(right.x() - blue, y - 1); // blue
                mProfile.LineToDirYBlue(right.x() - nextBlue, y);
            }
            mProfile.GetDirectionY().SetPathRed();
            mProfile.GetDirectionY().SetPathGreen();
            mProfile.GetDirectionY().SetPathBlue();



            if (p_scene->GetEditSceneImg().m_memDibImg.isGrayscale()) 
            {
                /* GRAY */
                mProfile.GetDirectionX().GetItemPathRed()->setPen(QPen(QColor(Qt::green)));
                mProfile.GetDirectionX().GetItemPathGreen()->setPen(QPen(QColor(Qt::green)));
                mProfile.GetDirectionX().GetItemPathBlue()->setPen(QPen(QColor(Qt::green)));
                mProfile.GetDirectionY().GetItemPathRed()->setPen(QPen(QColor(Qt::green)));
                mProfile.GetDirectionY().GetItemPathGreen()->setPen(QPen(QColor(Qt::green)));
                mProfile.GetDirectionY().GetItemPathBlue()->setPen(QPen(QColor(Qt::green)));
            }
            else 
            {
                mProfile.GetDirectionX().GetItemPathRed()->setPen(QPen(QColor(Qt::red)));
                mProfile.GetDirectionX().GetItemPathGreen()->setPen(QPen(QColor(Qt::green)));
                mProfile.GetDirectionX().GetItemPathBlue()->setPen(QPen(QColor(Qt::blue)));
                mProfile.GetDirectionY().GetItemPathRed()->setPen(QPen(QColor(Qt::red)));
                mProfile.GetDirectionY().GetItemPathGreen()->setPen(QPen(QColor(Qt::green)));
                mProfile.GetDirectionY().GetItemPathBlue()->setPen(QPen(QColor(Qt::blue)));
            }

            if (isXRed && !mProfile.GetDirectionX().GetAddedRedChecked()) 
            {
                p_scene->addItem(mProfile.GetDirectionX().GetItemPathRed());
                mProfile.GetDirectionX().SetAddedRedChecked(true);
            }
            if (isXGreen && !mProfile.GetDirectionX().GetAddedGreenChecked()) 
            {
                p_scene->addItem(mProfile.GetDirectionX().GetItemPathGreen());
                mProfile.GetDirectionX().SetAddedGreenChecked(true);
            }
            if (isXBlue && !mProfile.GetDirectionX().GetAddedBlueChecked()) 
            {
                p_scene->addItem(mProfile.GetDirectionX().GetItemPathBlue());
                mProfile.GetDirectionX().SetAddedBlueChecked(true);
            }
            if (isYRed && !mProfile.GetDirectionY().GetAddedRedChecked()) 
            {
                p_scene->addItem(mProfile.GetDirectionY().GetItemPathRed());
                mProfile.GetDirectionY().SetAddedRedChecked(true);
            }
            if (isYGreen && !mProfile.GetDirectionY().GetAddedGreenChecked()) 
            {
                p_scene->addItem(mProfile.GetDirectionY().GetItemPathGreen());
                mProfile.GetDirectionY().SetAddedGreenChecked(true);
            }
            if (isYBlue && !mProfile.GetDirectionY().GetAddedBlueChecked()) 
            {
                p_scene->addItem(mProfile.GetDirectionY().GetItemPathBlue());
                mProfile.GetDirectionY().SetAddedBlueChecked(true);
            }
        }
    }
}


void ImageView::DrawFigure(const QPoint &viewPos, bool isCenterDrag, bool isSquareDrag) 
{
    /* 図形(l,t),(r,b)の描画 */

    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    QGraphicsPixmapItem *p_item = p_scene->GetEditImgItem(scenePos);

    if (p_item) 
    {
        QPointF localPos = p_item->mapToItem(p_item, scenePos);
        QRectF localRect = p_item->boundingRect(); // Local座標における矩形サイズ

        if (mIsMousePressLeft && !mIsMouseDrag) 
        {
            // アンカーポイント
            mAnchor = localPos;
            mRect.setTopLeft(localPos);
            mRect.setBottomRight(localPos);
        }
        else if (mIsMousePressLeft && mIsMouseDrag) 
        {
            if (!mIsGenFigure) 
            {
                // 矩形
                if (mRoi.m_isRegionFigure) 
                {
                    mRoi.MakeRect(p_scene, mRect); // 新規作成
                }

                // 楕円
                if (mEllipse.m_isRegionFigure) 
                {
                    mEllipse.MakeRect(p_scene, mRect); // 新規作成
                }

                mIsGenFigure = true;
            }

            QPointF dp, tl, br;
            qreal dw, dh;

            if (isCenterDrag) 
            {
                dp = localPos - mAnchor;
                dw = std::abs(dp.x()); // 幅
                dh = std::abs(dp.y()); // 高さ

                if (isSquareDrag) 
                {
                    dw = (dw < dh) ? dw : dh;
                    dh = dw;
                }
                tl.setX(mAnchor.x() - dw);
                tl.setY(mAnchor.y() - dh);
                br.setX(mAnchor.x() + dw);
                br.setY(mAnchor.y() + dh);
            }
            else 
            {
                qreal ax, ay, lx, ly;
                ax = mAnchor.x();
                ay = mAnchor.y();
                lx = localPos.x();
                ly = localPos.y();
                qreal l, r, t, b;

                if (ax < lx) 
                {
                    l = ax; r = lx;
                }
                else 
                {
                    l = lx; r = ax;
                }
                if (ay < ly) 
                {
                    t = ay; b = ly;
                }
                else 
                {
                    t = ly; b = ay;
                }
                
                if (isSquareDrag) 
                {
                    dw = r - l;
                    dh = b - t;
                    dw = dw < dh ? dw : dh;
                    dh = dw;

                    if (ax < lx && ay < ly) 
                    {
                        l = ax;
                        r = l + dw;
                        t = ay;
                        b = t + dh;
                    }
                    else if (ax < lx && ay > ly) 
                    {
                        l = ax;
                        r = l + dw;
                        t = ay - dw;
                        b = ay;
                    }
                    else if (ax > lx && ay > ly) 
                    {
                        l = ax - dw;
                        r = ax;
                        t = ay - dh;
                        b = ay;
                    }
                    else if (ax > lx && ay < ly) 
                    {
                        l = ax - dw;
                        r = ax;
                        t = ay;
                        b = t + dh;
                    }
                } 

                tl.setX(l); tl.setY(t);
                br.setX(r); br.setY(b);
            }

            mRect.setTopLeft(tl);
            mRect.setBottomRight(br);

            // 矩形
            if (mRoi.m_isRegionFigure) 
            {
                mRoi.UpdateRect(p_scene, mRect); // 描画更新
            }

            // 楕円
            if (mEllipse.m_isRegionFigure) 
            {
                mEllipse.UpdateRect(p_scene, mRect); // 描画更新
            }
        }
        else if (!mIsMousePressLeft && mIsMouseDrag) 
        {
            // 矩形
            if (mRoi.m_isRegionFigure) 
            {
                qreal w, h;
                w = mRect.width();
                h = mRect.height();
                IS_DEBUG_STREAM("w:%d, h:%d\n", (int)w, (int)h);
                if (w > 2 && h > 2) 
                {
                    mRoi.UpdateRect(p_scene, mRect); // 描画更新
                }
                else 
                {
                    mRoi.RemoveRect(p_scene, mRoi.m_regionFigures.size() - 1);
                    mRect.setX(0);
                    mRect.setY(0);
                    mRect.setWidth(0);
                    mRect.setHeight(0);
                }
            }

            // 楕円
              if (mEllipse.m_isRegionFigure) 
              {
                qreal w, h;
                w = mRect.width();
                h = mRect.height();
                IS_DEBUG_STREAM("w:%d, h:%d\n", (int)w, (int)h);
                if (w > 2 && h > 2) 
                {
                    mEllipse.UpdateRect(p_scene, mRect); // 描画更新
                }
                else 
                {
                    mEllipse.RemoveRect(p_scene, mEllipse.m_regionFigures.size() - 1);
                    mRect.setX(0);
                    mRect.setY(0);
                    mRect.setWidth(0);
                    mRect.setHeight(0);
                }
            }

            mIsGenFigure = false;
        }
        else 
        {
            
        }
    }
}

void ImageView::RemoveFigure(const QPoint &viewPos) 
{
    /* 図形消去 */

    auto scenePos = this->mapToScene(viewPos);
    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    auto p_item = p_scene->itemAt(scenePos, QTransform());
    if (p_item) 
    {
        // 矩形
        if (mRoi.m_isRegionFigure) 
        {
            mRoi.RemoveRect(p_scene, p_item);
        }

        // 楕円
        if (mEllipse.m_isRegionFigure) 
        {
            mEllipse.RemoveRect(p_scene, p_item);
        }
    }
}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////
void ImageView::mousePressEvent(QMouseEvent *event) 
{
    /* マウスプレスイベント */

    UpdateStatusBar(event->pos());

    auto p_scene = qobject_cast<ImageScene *>(this->scene());
    auto mouseButton = event->button();
    if (mouseButton == Qt::MouseButton::LeftButton) 
    {
        mIsMousePressLeft = true;
    }
    else if (mouseButton == Qt::MouseButton::RightButton) 
    {
        mIsMousePressRight = true;
    }
    else if (Qt::MouseButton::MiddleButton) 
    {
        mIsMousePressMiddle = true;
    }
    else 
    {
        IS_DEBUG_STREAM("Unknown mouse button in mousePressEvent...\n");
    }

    // 十字線@Press
    if (mCrossLine.GetChecked()) 
    {
        DrawCrossLine(event->pos());
    }

    // プロファイル@Press
    if (mProfile.m_directX.m_isPathRed ||
        mProfile.m_directX.m_isPathGreen ||
        mProfile.m_directX.m_isPathBlue ||
        mProfile.m_directY.m_isPathRed ||
        mProfile.m_directY.m_isPathGreen ||
        mProfile.m_directY.m_isPathBlue) 
    {
        DrawProfile(event->pos(),
                    mProfile.m_directX.m_isPathRed,
                    mProfile.m_directX.m_isPathGreen,
                    mProfile.m_directX.m_isPathBlue,
                    mProfile.m_directY.m_isPathRed,
                    mProfile.m_directY.m_isPathGreen,
                    mProfile.m_directY.m_isPathBlue);
    }

    // 図形
    if (mRoi.m_isRegionFigure ||
        mEllipse.m_isRegionFigure) 
    {
        DrawFigure(event->pos(),
                   event->modifiers() & Qt::ControlModifier,
                   event->modifiers() & Qt::ShiftModifier);
    }

    QGraphicsView::mousePressEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent *event) 
{
    /* マウス移動イベント */

    UpdateStatusBar(event->pos());
    auto p_scene = qobject_cast<ImageScene *>(this->scene());

    if (mIsMousePressLeft || mIsMousePressMiddle || mIsMousePressRight) 
    {
        mIsMouseDrag = true;
    }
    else 
    {
        mIsMouseDrag = false;
    }

    // 十字線@Press
    if (mCrossLine.GetChecked())
    {
        DrawCrossLine(event->pos());
    }

    // プロファイル@Press
    if (mProfile.m_directX.m_isPathRed ||
        mProfile.m_directX.m_isPathGreen ||
        mProfile.m_directX.m_isPathBlue ||
        mProfile.m_directY.m_isPathRed ||
        mProfile.m_directY.m_isPathGreen ||
        mProfile.m_directY.m_isPathBlue) 
    {
        DrawProfile(event->pos(),
                    mProfile.m_directX.m_isPathRed,
                    mProfile.m_directX.m_isPathGreen,
                    mProfile.m_directX.m_isPathBlue,
                    mProfile.m_directY.m_isPathRed,
                    mProfile.m_directY.m_isPathGreen,
                    mProfile.m_directY.m_isPathBlue);
    }

    // 図形
    if (mRoi.m_isRegionFigure ||
        mEllipse.m_isRegionFigure) 
    {
        DrawFigure(event->pos(),
                event->modifiers() & Qt::ControlModifier,
                event->modifiers() & Qt::ShiftModifier);
    }
    
    // DEBUG_STREAM("ImageView::mouseMoveEvent\n");
    QGraphicsView::mouseMoveEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) 
{
    /* マウスリリースイベント */

    UpdateStatusBar(event->pos());
    auto p_scene = qobject_cast<ImageScene *>(this->scene());

    auto mouseButton = event->button();
    if (mouseButton == Qt::MouseButton::LeftButton) 
    {
        mIsMousePressLeft = false;
    }
    else if (mouseButton == Qt::MouseButton::RightButton)
    {
        mIsMousePressRight = false;
    }
    else if (Qt::MouseButton::MiddleButton) 
    {
        mIsMousePressMiddle = false;
    }
    else 
    {
        IS_DEBUG_STREAM("Unknown mouse button in mouseMoveEvent...\n");
    }

    // 図形
    if (mRoi.m_isRegionFigure ||
        mEllipse.m_isRegionFigure) 
    {
        DrawFigure(event->pos(),
                   event->modifiers() & Qt::ControlModifier,
                   event->modifiers() & Qt::ShiftModifier);
    }

    mIsMouseDrag = false;

    QGraphicsView::mouseReleaseEvent(event);
}

void ImageView::mouseDoubleClickEvent(QMouseEvent *event) 
{
    /* マウスダブルクリックイベント */
    UpdateStatusBar(event->pos());
    auto p_scene = qobject_cast<ImageScene *>(this->scene());

    auto mouseButton = event->button();
    if (mouseButton == Qt::MouseButton::LeftButton) 
    {
        // 図形の削除
        RemoveFigure(event->pos());
    }
    else if (mouseButton == Qt::MouseButton::RightButton) 
    {

    }
    else if (Qt::MouseButton::MiddleButton) 
    {

    }
    else 
    {
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