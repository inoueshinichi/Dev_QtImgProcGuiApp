/**
 * @file image_window.cpp
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief Qt 自作ImageWindowのSourceファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "image_window.h"
#include "main_window.h"

#include "utility.h"

#include <IsCommonLib/include/format_string.hpp>

// Qt
#include <QGraphicsItem>


#include <cstring>
#include <ctime>
#include <string>
#include <iostream>

//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

ImageWindow::ImageWindow(QWidget *p_parent)
    : QMainWindow(p_parent)
    , m_pUi(new Ui::ImageWindow())
    , m_pStatusBarLabel(new QLabel())
{
    // ui
    m_pUi->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // view
    m_pScene = new ImageScene(this);
    m_pUi->graphicsViewImage->setScene(m_pScene);

    // statusbar
    slotShowPosToStatusBar(QPointF(0, 0), QPointF(0, 0), QPoint(0, 0));

    /*Singal/Slot*/
    uiConnection();
    memuBarConnection();
    toolBarConnection();
    customConnection();

}

ImageWindow::~ImageWindow()
{
    if (m_pUi) 
    {
        delete m_pUi;
        m_pUi = nullptr;
    }

    if (m_pScene)
    {
        delete m_pScene;
        m_pScene = nullptr;
    }
}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void ImageWindow::uiConnection()
{

}

void ImageWindow::memuBarConnection()
{

}

void ImageWindow::toolBarConnection()
{
    // connect(m_pUi->actionCrossLine, &QAction::toggled, m_pScene, &ImageScene::slotToggleCrossLine);

    /* QAction -> ImageScene */

    // CrossLine
    connect(m_pUi->actionCrossLine, &QAction::toggled, this, &ImageWindow::slotToggleCrossLine);

    // Profile-X(R)
    connect(m_pUi->actionProfileXRed, &QAction::toggled, this, &ImageWindow::slotToggleProfile);
    // Profile-X(G)
    connect(m_pUi->actionProfileXGreen, &QAction::toggled, this, &ImageWindow::slotToggleProfile);
    // Profile-X(B)
    connect(m_pUi->actionProfileXBlue, &QAction::toggled, this, &ImageWindow::slotToggleProfile);
    // Profile-Y(R)
    connect(m_pUi->actionProfileYRed, &QAction::toggled, this, &ImageWindow::slotToggleProfile);
    // Profile-Y(G)
    connect(m_pUi->actionProfileYGreen, &QAction::toggled, this, &ImageWindow::slotToggleProfile);
    // Profile-Y(B)
    connect(m_pUi->actionProfileYBlue, &QAction::toggled, this, &ImageWindow::slotToggleProfile);
}

void ImageWindow::customConnection()
{
    /* ImageWindow -> MainWindow */
    connect(this, &ImageWindow::rmImgWin, 
        (MainWindow *)(this->parent()), &MainWindow::slotRmImgWin);
    connect(this, &ImageWindow::activeImgWin, 
        (MainWindow *)(this->parent()), &MainWindow::slotActiveImgWin);

    /* ImageView -> ImageWindow */
    connect(m_pUi->graphicsViewImage, &ImageView::emitShowPosToStatusBar,
            this, &ImageWindow::slotShowPosToStatusBar);
}

bool ImageWindow::event(QEvent *event)
{
    /*イベントの基底*/
    // 各イベントが到達する前にフックする.

    if (event->type() == QEvent::WindowActivate)
    {
        emit activeImgWin(this);
    }

    return QMainWindow::event(event);
}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////
void ImageWindow::closeEvent(QCloseEvent *event)
{
    /*登録解除*/
    emit rmImgWin(this);
}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

void ImageWindow::setFilename(const QString& filename)
{
    /*ファイル名 + 時間*/

    // 時間取得
    char timeString[256];
    std::memset((void *)&timeString, '\0', sizeof(timeString));
    time_t theTime = time(nullptr);
    struct tm *stm = localtime(&theTime);
    if (theTime == -1 || stm == nullptr)
    {
        std::snprintf(timeString, 256, "Unknown");
    }
    else
    {
        strftime(timeString, 256, "%Y-%m-%d %H:%M ", stm);
    }
    QString timeNow(timeString);
    this->setWindowTitle(timeNow + filename);
    m_filename = filename;
}

QString ImageWindow::filename() const { return m_filename; }

ImageScene* ImageWindow::scene() const { return m_pScene; }


//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

void ImageWindow::slotShowPosToStatusBar(
    const QPointF &imgLocalPos,
    const QPointF &scenePos,
    const QPoint &viewPos) {
    /* 編集画像上のローカル座標, シーン座標, ビュー座標
       を取得してステータスバーに表示.
    */
   using namespace is::common;

    m_posStatus = format_string("ImageLocalPos(%.1f, %.1f), ScenePos(%.1f, %.1f), ViewPos(%d, %d)",
                               imgLocalPos.x(), imgLocalPos.y(),
                               scenePos.x(), scenePos.y(),
                               viewPos.x(), viewPos.y());
    m_pStatusBarLabel->setText(QString::fromStdString(m_posStatus));
    this->statusBar()->addPermanentWidget(m_pStatusBarLabel);
}

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////

void ImageWindow::slotToggleCrossLine(bool checked)
{
    /*十字線の(非)表示*/
    m_pScene->m_crossLine.m_isCrossLine = checked;

    if (!checked) {
        m_pScene->removeItem(m_pScene->m_crossLine.m_pItemLineX);
        m_pScene->removeItem(m_pScene->m_crossLine.m_pItemLineY);
    }
}

void ImageWindow::slotToggleProfile(bool checked)
{
    /*プロファイルの(非)表示*/
    auto p_sender = QObject::sender();
    if (p_sender == m_pUi->actionProfileXRed) {
        if (!checked)
            m_pScene->removeItem(m_pScene->m_profile.m_directX.m_pItemPathRed);
        m_pScene->m_profile.m_directX.m_isPathRed = checked;
    }
    else if (p_sender == m_pUi->actionProfileXGreen) {
        if (!checked)
            m_pScene->removeItem(m_pScene->m_profile.m_directX.m_pItemPathGreen);
        m_pScene->m_profile.m_directX.m_isPathGreen = checked;
    }
    else if (p_sender == m_pUi->actionProfileXBlue) {
        if (!checked)
            m_pScene->removeItem(m_pScene->m_profile.m_directX.m_pItemPathBlue);
        m_pScene->m_profile.m_directX.m_isPathBlue = checked;
    }
    else if (p_sender == m_pUi->actionProfileYRed) {
        if (!checked)
            m_pScene->removeItem(m_pScene->m_profile.m_directY.m_pItemPathRed);
        m_pScene->m_profile.m_directY.m_isPathRed = checked;
    }
    else if (p_sender == m_pUi->actionProfileYGreen) {
        if (!checked)
            m_pScene->removeItem(m_pScene->m_profile.m_directY.m_pItemPathGreen);
        m_pScene->m_profile.m_directY.m_isPathGreen = checked;
    }
    else if (p_sender == m_pUi->actionProfileYBlue) {
        if (!checked)
            m_pScene->removeItem(m_pScene->m_profile.m_directY.m_pItemPathBlue);
        m_pScene->m_profile.m_directY.m_isPathBlue = checked;
    }

}