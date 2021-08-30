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
#include <QGraphicsPixmapItem>
#include <QgraphicsScene>

#include <map>
#include <tuple>

typedef struct CrossLine {
    QGraphicsLineItem *m_pItemLineX;
    QGraphicsLineItem *m_pItemLineY;

    bool m_isCrossLine{false};

    CrossLine() {
        m_pItemLineX = new QGraphicsLineItem();
        m_pItemLineY = new QGraphicsLineItem();
        m_pItemLineX->setPen(QPen(QColor(Qt::green)));
        m_pItemLineY->setPen(QPen(QColor(Qt::green)));
    }

    ~CrossLine() {
        if (m_pItemLineX) {
            delete m_pItemLineX;
            m_pItemLineX = nullptr;
        }
        if (m_pItemLineY) {
            delete m_pItemLineY;
            m_pItemLineY = nullptr;
        }
    }
} CrossLine;


typedef struct Profile 
{
    typedef struct Direction {
        QPainterPath m_pathRed;
        QPainterPath m_pathGreen;
        QPainterPath m_pathBlue;
        QGraphicsPathItem *m_pItemPathRed;
        QGraphicsPathItem *m_pItemPathGreen;
        QGraphicsPathItem *m_pItemPathBlue;

        bool m_isPathRed{false};
        bool m_isPathGreen{false};
        bool m_isPathBlue{false};

        Direction() {
            m_pItemPathRed = new QGraphicsPathItem();
            m_pItemPathGreen = new QGraphicsPathItem();
            m_pItemPathBlue = new QGraphicsPathItem();
        }

        ~Direction() {
            if (m_pItemPathRed) {
                delete m_pItemPathRed;
                m_pItemPathRed = nullptr;
            }
            if (m_pItemPathGreen) {
                delete m_pItemPathGreen;
                m_pItemPathGreen = nullptr;
            }
            if (m_pItemPathBlue) {
                delete m_pItemPathBlue;
                m_pItemPathBlue = nullptr;
            }
        }
    } Direction;

    Direction m_directX;
    Direction m_directY;
} Profile;

typedef struct Roi {
    bool m_isRoi{false};
    QPointF m_anchor;
    std::map<int, QGraphicsRectItem *> m_rois;

    Roi() {}
    ~Roi() {
        release();
    }

    void release() {
        for (auto iter = m_rois.begin();
             iter != m_rois.end(); ++iter)
        {
            if (iter->second)
            {
                delete iter->second;
                iter->second = nullptr;
            }
        }
        m_rois.clear();
    }

    void makeRect(QGraphicsScene *scene, const QPointF &localPos) {
        QGraphicsRectItem *p_item = new QGraphicsRectItem();
        p_item->setPen(QPen(QColor(Qt::magenta)));
        p_item->setRect(localPos.x(), localPos.y(), 0.0, 0.0); // (幅,高さ)=(0,0)
        size_t index = m_rois.size();
        m_rois.insert({index, p_item});
        scene->addItem(p_item);
    }

    void updateRect(QGraphicsScene *scene, 
                    const QPointF &localPos1, 
                    const QPointF &localPos2) {
        size_t last = m_rois.size() - 1;
        if (last < 0)
            return;

        auto p_item = m_rois[last];
        scene->removeItem(p_item);
        p_item->setRect(QRectF(localPos1, localPos2));
        scene->addItem(p_item);
    }

    void removeRect(QGraphicsScene *scene, int index) {
        if (m_rois.contains(index))
        {
            auto p_item = m_rois[index];
            scene->removeItem(p_item);
            delete p_item; p_item = nullptr;
            m_rois.erase(index);
        }
    }

    std::tuple<QPointF, QPointF> calcTlBr(const QPointF &localPos, 
                                    bool isCenterDrag, bool isSquareDrag) {
        QPointF dp, tl, br;
        qreal dw, dh, min;
        QRectF tmpRect;

        dp = localPos - m_anchor;
        dw = std::abs(dp.x()) + 1; // 幅
        dh = std::abs(dp.y()) + 1; // 高さ
        if (isCenterDrag) {
            if (isSquareDrag) {
                min = (dw < dh) ? dw : dh;
                dw = min;
                dh = min;
            }
            tl.setX(m_anchor.x() - dw + 1);
            tl.setY(m_anchor.y() - dh + 1);
            br.setX(m_anchor.x() + dw);
            br.setY(m_anchor.y() + dh);
        }
        else {
            if (isSquareDrag) {
                min = (dw < dh) ? dw : dh;
                dw = min;
                dh = min;
            }
            tl.setX(m_anchor.x());
            tl.setY(m_anchor.y());
            br.setX(m_anchor.x() + dw);
            br.setY(m_anchor.y() + dh);
        }

        tmpRect.setTopLeft(tl);
        tmpRect.setBottomRight(br);

        return std::make_tuple(tmpRect.topLeft(), tmpRect.bottomRight());
    }
} Roi;


typedef struct SceneImage {
    QImage m_memDibImg;
    QPixmap m_offScreenDdbImg;
    QGraphicsPixmapItem *m_pItemOffScreenDdbImg;

    SceneImage() {
        m_pItemOffScreenDdbImg = new QGraphicsPixmapItem();
    }

    ~SceneImage() {
        if (m_pItemOffScreenDdbImg) {
            delete m_pItemOffScreenDdbImg;
            m_pItemOffScreenDdbImg = nullptr;
        }
    }
} SceneImage;