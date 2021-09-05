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
#include <QGraphicsScene>

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

    void makeRect(QGraphicsScene *scene, const QRectF &rect) {
        QGraphicsRectItem *p_item = new QGraphicsRectItem();
        p_item->setPen(QPen(QColor(Qt::magenta)));
        p_item->setRect(rect); // (幅,高さ)=(0,0)
        int index = m_rois.size();
        m_rois.insert({index, p_item});
        scene->addItem(p_item);
        DEBUG_STREAM("New Rect[%d]: (%f, %f, %f, %f)\n",
                     index, rect.x(), rect.y(), rect.width(), rect.height());
    }

    void updateRect(QGraphicsScene *scene, const QRectF &rect) {
        int last = m_rois.size() - 1;
        if (last < 0)
            return;

        DEBUG_STREAM("Update Rect[%d]: (%f, %f, %f, %f)\n",
                     last, rect.x(), rect.y(), rect.width(), rect.height());

        auto p_item = m_rois[last];
        scene->removeItem(p_item);
        p_item->setRect(rect);
        scene->addItem(p_item);
    }

    void removeRect(QGraphicsScene *scene, int index) {
        if (m_rois.contains(index)) {
            auto p_item = m_rois[index];
            scene->removeItem(p_item);
            delete p_item; p_item = nullptr;
            m_rois.erase(index);
            DEBUG_STREAM("Rm Rect[%d]\n", index);
        }
    }

    void removeRect(QGraphicsScene *scene, QGraphicsItem *item) {
        for (auto iter = m_rois.begin(); iter != m_rois.end();) {
            if (iter->second == item) {
                int index = iter->first;
                scene->removeItem(iter->second);
                delete iter->second;
                iter->second = nullptr;
                iter = m_rois.erase(iter);
                DEBUG_STREAM("Rm Rect[%d]\n", index);
                return;
            }
            else {
                ++iter;
            }
        }
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