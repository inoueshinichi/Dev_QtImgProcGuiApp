#pragma once

#include <Qt>
#include <QColor>
#include <QPen>
#include <QImage>
#include <QPixmap>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include <map>
#include <tuple>

class CrossLine 
{
    QGraphicsLineItem* mItemLineX;
    QGraphicsLineItem* mItemLineY;

    bool mIsCrossLine{false};

public:
    CrossLine() 
    {
        mItemLineX = new QGraphicsLineItem();
        mItemLineY = new QGraphicsLineItem();
        mItemLineX->setPen(QPen(QColor(Qt::green)));
        mItemLineY->setPen(QPen(QColor(Qt::green)));
    }

    ~CrossLine() 
    {
        if (mItemLineX) 
        {
            delete mItemLineX;
            mItemLineX = nullptr;
        }
        if (mItemLineY) 
        {
            delete mItemLineY;
            mItemLineY = nullptr;
        }
    }

    bool GetChecked() const { return mIsCrossLine; }
    void SetChecked(bool checked) { mIsCrossLine = checked; }

    QGraphicsLineItem* GetLineItemX() { return mItemLineX; }
    QGraphicsLineItem* GetLineItemY() { return mItemLineY; }
};


class Direction
{
    friend class Profile;

    QPainterPath mPathRed;
    QPainterPath mPathGreen;
    QPainterPath mPathBlue;
    QGraphicsPathItem* mItemPathRed;
    QGraphicsPathItem* mItemPathGreen;
    QGraphicsPathItem* mItemPathBlue;

    bool mIsPathRed{false};
    bool mIsPathGreen{false};
    bool mIsPathBlue{false};
    
    bool mIsAddedRed{false};
    bool mIsAddedGreen{false};
    bool mIsAddedBlue{false};

public:

    Direction() 
    {
        mItemPathRed = new QGraphicsPathItem();
        mItemPathGreen = new QGraphicsPathItem();
        mItemPathBlue = new QGraphicsPathItem();
    }

    ~Direction() 
    {
        if (mItemPathRed) 
        {
            delete mItemPathRed;
            mItemPathRed = nullptr;
        }
        if (mItemPathGreen) 
        {
            delete mItemPathGreen;
            mItemPathGreen = nullptr;
        }
        if (mItemPathBlue) 
        {
            delete mItemPathBlue;
            mItemPathBlue = nullptr;
        }
    }

    void SetPathRed() { mItemPathRed->setPath(mPathRed); }
    void SetPathGreen() { mItemPathGreen->setPath(mPathGreen); }
    void SetPathBlue() { mItemPathBlue-> setPath(mPathBlue); }
    QPainterPath& GetPathRed() { return mPathRed; }
    QPainterPath& GetPathGreen() { return mPathGreen; }
    QPainterPath& GetPathBlue() { return mPathBlue; }
    QGraphicsPathItem* GetItemPathRed() { return mItemPathRed; }
    QGraphicsPathItem* GetItemPathGreen() { return mItemPathGreen; }
    QGraphicsPathItem* GetItemPathBlue() { return mItemPathBlue; }

    bool GetPathRedChecked() const { return mIsPathRed; }
    void SetPathRedChecked(bool checked) {  mIsPathRed = checked; }
    bool GetPathGreenChecked() const { return mIsPathGreen; }
    void SetPathGreenChecked(bool checked) {  mIsPathGreen = checked; }
    bool GetPathBlueChecked() const { return mIsPathBlue; }
    void SetPathBlueChecked(bool checked) {  mIsPathBlue = checked; }

    bool GetAddedRedChecked() const { return mIsAddedRed; }
    void SetAddedRedChecked(bool checked) {  mIsAddedRed = checked; }
    bool GetAddedGreenChecked() const { return mIsAddedGreen; }
    void SetAddedGreenChecked(bool checked) {  mIsAddedGreen = checked; }
    bool GetAddedBlueChecked() const { return mIsAddedBlue; }
    void SetAddedBlueChecked(bool checked) {  mIsAddedBlue = checked; }

};

class Profile 
{
    Direction mDirectX;
    Direction mDirectY;

public:
    Direction& GetDirectionX() { return mDirectX; }
    Direction& GetDirectionY() { return mDirectY; }

    void ClearPath()
    {
        mDirectX.GetPathRed().clear();
        mDirectX.GetPathGreen().clear();
        mDirectX.GetPathBlue().clear();
        mDirectY.GetPathRed().clear();
        mDirectY.GetPathGreen().clear();
        mDirectY.GetPathBlue().clear();
    }


    void MoveToDirXRed(double x, double y) { mDirectX.mPathRed.moveTo(x, y); }
    void LineToDirXRed(double x, double y) { mDirectX.mPathRed.lineTo(x, y); }
    void MoveToDirXGreen(double x, double y) { mDirectX.mPathGreen.moveTo(x, y); }
    void LineToDirXGreen(double x, double y) { mDirectX.mPathGreen.lineTo(x, y); }
    void MoveToDirXBlue(double x, double y) { mDirectX.mPathBlue.moveTo(x, y); }
    void LineToDirXBlue(double x, double y) { mDirectX.mPathBlue.lineTo(x, y); }

    void MoveToDirYRed(double x, double y) { mDirectY.mPathRed.moveTo(x, y); }
    void LineToDirYRed(double x, double y) { mDirectY.mPathRed.lineTo(x, y); }
    void MoveToDirYGreen(double x, double y) { mDirectY.mPathGreen.moveTo(x, y); }
    void LineToDirYGreen(double x, double y) { mDirectY.mPathGreen.lineTo(x, y); }
    void MoveToDirYBlue(double x, double y) { mDirectY.mPathBlue.moveTo(x, y); }
    void LineToDirYBlue(double x, double y) { mDirectY.mPathBlue.lineTo(x, y); }


    
};


template <typename QtItemOnScene>
class RegionFigure 
{
public:
    bool m_isRegionFigure {false};
    std::map<int, QtItemOnScene *> m_regionFigures;

    RegionFigure() {}
    ~RegionFigure() { Release(); }

    void Release() 
    {
        for (auto iter = m_regionFigures.begin(); 
            iter != m_regionFigures.end(); ++iter) 
        {
            if (iter->second) 
            {
                delete iter->second;
                iter->second = nullptr;
            }
        }
        m_regionFigures.clear();
    }

    void MakeRect(QGraphicsScene *scene, const QRectF &rect) 
    {
        QtItemOnScene *p_item = new QtItemOnScene();

        Qt::GlobalColor globalColor;

        // constexpr if によるコンパイル時条件分岐
        if constexpr (std::is_same_v<QtItemOnScene, QGraphicsRectItem>) 
        {
            globalColor = Qt::magenta;
        }
        else if constexpr (std::is_same_v<QtItemOnScene, QGraphicsEllipseItem>) 
        {
            globalColor = Qt::cyan;
        }
        else if constexpr (std::is_same_v<QtItemOnScene, QGraphicsLineItem>) 
        {
            globalColor = Qt::yellow;
        }
        else 
        {
            globalColor = Qt::white;
        }

        p_item->setPen(QPen(QColor(globalColor)));

        p_item->setRect(rect); // (幅,高さ)=(0,0)
        int index = m_regionFigures.size();
        m_regionFigures.insert({index, p_item});
        scene->addItem(p_item);
        IS_DEBUG_STREAM("New Rect[%d]: (%f, %f, %f, %f)\n",
                     index, rect.x(), rect.y(), rect.width(), rect.height());
    }

    void UpdateRect(QGraphicsScene *scene, const QRectF &rect) 
    {
        int last = m_regionFigures.size() - 1;
        if (last < 0) return;

        IS_DEBUG_STREAM("Update Rect[%d]: (%f, %f, %f, %f)\n",
                     last, rect.x(), rect.y(), rect.width(), rect.height());

        auto p_item = m_regionFigures[last];
        scene->removeItem(p_item);
        p_item->setRect(rect);
        scene->addItem(p_item);
    }

     void RemoveRect(QGraphicsScene *scene, int index) 
     {
        if (m_regionFigures.contains(index)) 
        {
            auto p_item = m_regionFigures[index];
            scene->removeItem(p_item);
            delete p_item; p_item = nullptr;
            m_regionFigures.erase(index);
            IS_DEBUG_STREAM("Rm Rect[%d]\n", index);
        }
    }

    void RemoveRect(QGraphicsScene *scene, QGraphicsItem *item) 
    {
        for (auto iter = m_regionFigures.begin(); 
            iter != m_regionFigures.end();) 
        {
            if (iter->second == item) 
            {
                int index = iter->first;
                scene->removeItem(iter->second);
                delete iter->second;
                iter->second = nullptr;
                iter = m_regionFigures.erase(iter);
                IS_DEBUG_STREAM("Rm Rect[%d]\n", index);
                return;
            }
            else 
            {
                ++iter;
            }
        }
    }
};

using RoiRect = RegionFigure<QGraphicsRectItem>;
using RoiEllipse = RegionFigure<QGraphicsEllipseItem>;

// typedef struct Roi {
//     bool m_isRoi{false};
//     std::map<int, QGraphicsRectItem *> m_rois;

//     Roi() {}
//     ~Roi() {
//         release();
//     }

//     void release() {
//         for (auto iter = m_rois.begin();
//              iter != m_rois.end(); ++iter)
//         {
//             if (iter->second)
//             {
//                 delete iter->second;
//                 iter->second = nullptr;
//             }
//         }
//         m_rois.clear();
//     }

//     void makeRect(QGraphicsScene *scene, const QRectF &rect) {
//         QGraphicsRectItem *p_item = new QGraphicsRectItem();
//         p_item->setPen(QPen(QColor(Qt::magenta)));
//         p_item->setRect(rect); // (幅,高さ)=(0,0)
//         int index = m_rois.size();
//         m_rois.insert({index, p_item});
//         scene->addItem(p_item);
//         IS_DEBUG_STREAM("New Rect[%d]: (%f, %f, %f, %f)\n",
//                      index, rect.x(), rect.y(), rect.width(), rect.height());
//     }

//     void updateRect(QGraphicsScene *scene, const QRectF &rect) {
//         int last = m_rois.size() - 1;
//         if (last < 0)
//             return;

//         IS_DEBUG_STREAM("Update Rect[%d]: (%f, %f, %f, %f)\n",
//                      last, rect.x(), rect.y(), rect.width(), rect.height());

//         auto p_item = m_rois[last];
//         scene->removeItem(p_item);
//         p_item->setRect(rect);
//         scene->addItem(p_item);
//     }

//     void removeRect(QGraphicsScene *scene, int index) {
//         if (m_rois.contains(index)) {
//             auto p_item = m_rois[index];
//             scene->removeItem(p_item);
//             delete p_item; p_item = nullptr;
//             m_rois.erase(index);
//             IS_DEBUG_STREAM("Rm Rect[%d]\n", index);
//         }
//     }

//     void removeRect(QGraphicsScene *scene, QGraphicsItem *item) {
//         for (auto iter = m_rois.begin(); iter != m_rois.end();) {
//             if (iter->second == item) {
//                 int index = iter->first;
//                 scene->removeItem(iter->second);
//                 delete iter->second;
//                 iter->second = nullptr;
//                 iter = m_rois.erase(iter);
//                 IS_DEBUG_STREAM("Rm Rect[%d]\n", index);
//                 return;
//             }
//             else {
//                 ++iter;
//             }
//         }
//     }

// } Roi;


