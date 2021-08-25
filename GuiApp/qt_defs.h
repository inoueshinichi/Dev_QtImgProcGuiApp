#pragma once

#include <Qt>
#include <QColor>
#include <QPen>
#include <QImage>
#include <QPixmap>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>

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
};


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