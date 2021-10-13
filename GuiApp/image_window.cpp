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

#include <cstring>
#include <ctime>
#include <string>
#include <iostream>

#include <QGraphicsItem>


//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

ImageWindow::ImageWindow(QWidget *p_parent)
    : QMainWindow(p_parent)
    , m_pMainWindow(qobject_cast<MainWindow *>(p_parent))
    , m_pUi(new Ui::ImageWindow())
    , m_pStatusBarLabel(new QLabel()) {
    
    // ui
    m_pUi->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // view
    m_pScene = new ImageScene(this);
    m_pUi->graphicsViewImage->setScene(m_pScene);

    // statusbar
    slotShowPosToStatusBar(QPointF(0, 0), QPointF(0, 0), QPoint(0, 0));

    // timer
    m_pCamTimer = new QTimer(this);

    /*Singal/Slot*/
    uiConnection();
    memuBarConnection();
    toolBarConnection();
    customConnection();
}

ImageWindow::~ImageWindow() {
    if (m_pUi) {
        delete m_pUi;
        m_pUi = nullptr;
    }

    if (m_pScene) {
        delete m_pScene;
        m_pScene = nullptr;
    }
}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void ImageWindow::uiConnection() {

    // 仮の設定
    connect(m_pUi->pushButtonStartCapture, &QPushButton::clicked,
        this, &ImageWindow::slotStartCapture);
    
    connect(m_pUi->pushButtonStopCapture, &QPushButton::clicked,
        this, &ImageWindow::slotStopCapture);
}

void ImageWindow::memuBarConnection() {

    /* Menu -> File */
    // New
    connect(m_pUi->actionNew, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarFileNew);

    // Open
    connect(m_pUi->actionOpen, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarFileOpen);

    // Close
    connect(m_pUi->actionClose, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarFileClose);

    // Save
    connect(m_pUi->actionSave, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarFileSave);

    // Save As
    // CSV
    connect(m_pUi->actionSaveAsCsv, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarFileSaveAs);
    // TSV
    connect(m_pUi->actionSaveAsTsv, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarFileSaveAs);

    /* Menu -> Edit */
    // Undo
    connect(m_pUi->actionUndo, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarEditUndo);

    // Rename
    connect(m_pUi->actionRename, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarEditRename);

    // Cut
    connect(m_pUi->actionCut, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarEditCut);

    // Copy
    connect(m_pUi->actionCopy, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarEditCopy);

    // Paste
    connect(m_pUi->actionPaste, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarEditPaste);

    // Clear
    connect(m_pUi->actionClear, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarEditClear);

    // Clear outside
    connect(m_pUi->actionClearOutside, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarEditClearOutside);

    // Fill
    connect(m_pUi->actionFill, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarEditFill);

    // Invert
    connect(m_pUi->actionInvert, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarEditInvert);


    /* Menu -> Image */
    // Type
    connect(m_pUi->actionCvt8bit, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarImageType);
    connect(m_pUi->actionCvt24bit, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarImageType);
    connect(m_pUi->actionCvtRGBA, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarImageType); 

    // ShowInfo

    // Color
    connect(m_pUi->actionRGBToGray, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarImageColor);
    connect(m_pUi->actionGrayToRGB, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarImageColor);
    connect(m_pUi->actionRGBToHSV, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarImageColor);
    connect(m_pUi->actionHSVToRGB, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarImageColor);
    connect(m_pUi->actionRGBToYUV, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarImageColor);
    // connect(m_pUi->actionYUVToRGB, &QAction::triggered,
    //     m_pMainWindow, &MainWindow::slotActMenuBarImageColor);

    // Crop
    connect(m_pUi->actionCrop, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarImageCrop);

    // Duplicate
    connect(m_pUi->actionDuplicate, &QAction::triggered, 
        m_pMainWindow, &MainWindow::slotActMenuBarImageDuplicate);


        
    /* Menu -> Camera */
    connect(m_pUi->actionCameraGeneral, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarCameraWindow);
    connect(m_pUi->actionCameraIds, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarCameraWindow);
    connect(m_pUi->actionCameraOmron, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarCameraWindow);
    connect(m_pUi->actionCameraBasler, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarCameraWindow);
    connect(m_pUi->actionCameraCognex, &QAction::triggered,
        m_pMainWindow, &MainWindow::slotActMenuBarCameraWindow);
}

void ImageWindow::toolBarConnection()
{
    // connect(m_pUi->actionCrossLine, &QAction::toggled, m_pScene, &ImageScene::slotToggleCrossLine);

    /* QAction -> ImageScene */

    // Reset DIB Image
    connect(m_pUi->actionResetImage, &QAction::triggered,
            this, &ImageWindow::slotResetDibImg);

    // CrossLine
    connect(m_pUi->actionCrossLine, &QAction::toggled, 
            this, &ImageWindow::slotToggleCrossLine);

    // Profile-X(R)
    connect(m_pUi->actionProfileXRed, &QAction::toggled, 
            this, &ImageWindow::slotToggleProfile);
    // Profile-X(G)
    connect(m_pUi->actionProfileXGreen, &QAction::toggled, 
            this, &ImageWindow::slotToggleProfile);
    // Profile-X(B)
    connect(m_pUi->actionProfileXBlue, &QAction::toggled, 
            this, &ImageWindow::slotToggleProfile);
    // Profile-Y(R)
    connect(m_pUi->actionProfileYRed, &QAction::toggled, 
            this, &ImageWindow::slotToggleProfile);
    // Profile-Y(G)
    connect(m_pUi->actionProfileYGreen, &QAction::toggled, 
            this, &ImageWindow::slotToggleProfile);
    // Profile-Y(B)
    connect(m_pUi->actionProfileYBlue, &QAction::toggled, 
            this, &ImageWindow::slotToggleProfile);

    // Roi
    connect(m_pUi->actionRoi, &QAction::toggled, 
            this, &ImageWindow::slotToggleRoi);

    // Ellipse
    connect(m_pUi->actionEllipse, &QAction::toggled,
            this, &ImageWindow::slotToggleEllipse);
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

ImageScene *ImageWindow::scene() const { return m_pScene; }

Ui::ImageWindow *ImageWindow::ui() const { return m_pUi; }


void ImageWindow::resetDibImg() {
    /* 原画像に戻す */
    m_pScene->resetRawImg();
}


QImage ImageWindow::getDibImg() {
    /* シーン上の編集画像を取得 */
    return m_pScene->getDibImg();
}

bool ImageWindow::setDibImg(QImage& img, bool isSceneClear, bool isRaw) {
    /* シーン上の編集画像に設定 */

    auto format = getFormatStr(img);
    int width = img.width();
    int height = img.height();
    int depth = img.depth();
    qsizetype datasize = img.sizeInBytes();

    if (depth == 8) {
        img = img.convertToFormat(QImage::Format_Grayscale8);
        m_pUi->actionCvt8bit->setChecked(true);
    } 
    else if (depth == 24) {
        img = img.convertToFormat(QImage::Format_RGB888);
        m_pUi->actionCvt24bit->setChecked(true);
    }
    else if (depth == 32) {
        img = img.convertToFormat(QImage::Format_RGBA8888);
        m_pUi->actionCvtRGBA->setChecked(true);
    }
    else {
        std::string msg = is::common::format_string(
            "No support image format. Given depth is %d", depth);
        throw std::runtime_error(msg.c_str());
    }
    
    std::string status = is::common::format_string("%dx%d@%s, %d-bits, %ld[bytes]", 
                                width, height, 
                                format.second.toStdString().c_str(),
                                depth,
                                datasize);

    m_pUi->lineEditImageStatus->clear();
    m_pUi->lineEditImageStatus->setText(QString::fromStdString(status));

    if (isSceneClear) {
         m_pScene->clear();
    }

    return m_pScene->setDibImg(img, isRaw);
}



std::map<int, QRectF> ImageWindow::getRectsOnDibImg() const {
    /* シーン上のRoiを取得 */

    std::map<int, QRectF> rects;
    for (auto iter = m_pScene->m_roi.m_regionFigures.begin(); 
        iter != m_pScene->m_roi.m_regionFigures.end(); ++iter) 
    {
        rects[iter->first] = iter->second->rect();
    }
    return rects;
}


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

    m_posStatus = format_string("ImageLocalPos(%4.1f, %4.1f), ScenePos(%4.1f, %4.1f), ViewPos(%4d, %4d)",
                               imgLocalPos.x(), imgLocalPos.y(),
                               scenePos.x(), scenePos.y(),
                               viewPos.x(), viewPos.y());
    m_pStatusBarLabel->setText(QString::fromStdString(m_posStatus));
    this->statusBar()->addPermanentWidget(m_pStatusBarLabel);
}

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////

void ImageWindow::slotResetDibImg(bool checked) {
    /* 原画像に戻す */
    resetDibImg();
    IS_DEBUG_STREAM("ImageWindow::slotResetDibImg\n");
}


void ImageWindow::slotToggleCrossLine(bool checked) {
    /*十字線の(非)表示*/
    m_pScene->m_crossLine.m_isCrossLine = checked;

    if (!checked) {
        m_pScene->removeItem(m_pScene->m_crossLine.m_pItemLineX);
        m_pScene->removeItem(m_pScene->m_crossLine.m_pItemLineY);
    }
}

void ImageWindow::slotToggleProfile(bool checked) {
    /*プロファイルの(非)表示*/
    auto p_sender = QObject::sender();
    if (p_sender == m_pUi->actionProfileXRed) {
        if (!checked) {
            m_pScene->removeItem(m_pScene->m_profile.m_directX.m_pItemPathRed);
            m_pScene->m_profile.m_directX.m_isAddedRed = false;
        }
        m_pScene->m_profile.m_directX.m_isPathRed = checked;
    }
    else if (p_sender == m_pUi->actionProfileXGreen) {
        if (!checked) {
            m_pScene->removeItem(m_pScene->m_profile.m_directX.m_pItemPathGreen);
            m_pScene->m_profile.m_directX.m_isAddedGreen = false;
        }
        m_pScene->m_profile.m_directX.m_isPathGreen = checked;
    }
    else if (p_sender == m_pUi->actionProfileXBlue) {
        if (!checked) {
            m_pScene->removeItem(m_pScene->m_profile.m_directX.m_pItemPathBlue);
            m_pScene->m_profile.m_directX.m_isAddedBlue = false;
        }
        m_pScene->m_profile.m_directX.m_isPathBlue = checked;
    }
    else if (p_sender == m_pUi->actionProfileYRed) {
        if (!checked) {
            m_pScene->removeItem(m_pScene->m_profile.m_directY.m_pItemPathRed);
            m_pScene->m_profile.m_directY.m_isAddedRed = false;
        }
        m_pScene->m_profile.m_directY.m_isPathRed = checked;
    }
    else if (p_sender == m_pUi->actionProfileYGreen) {
        if (!checked) {
            m_pScene->removeItem(m_pScene->m_profile.m_directY.m_pItemPathGreen);
            m_pScene->m_profile.m_directY.m_isAddedGreen = false;
        }
        m_pScene->m_profile.m_directY.m_isPathGreen = checked;
    }
    else if (p_sender == m_pUi->actionProfileYBlue) {
        if (!checked) {
            m_pScene->removeItem(m_pScene->m_profile.m_directY.m_pItemPathBlue);
            m_pScene->m_profile.m_directY.m_isAddedBlue = false;
        }
        m_pScene->m_profile.m_directY.m_isPathBlue = checked;
    }

}


void ImageWindow::slotToggleRoi(bool checked) {
    /*矩形領域の(非)表示*/

    m_pScene->m_roi.m_isRegionFigure = checked;

    if (!checked) {
        size_t num = m_pScene->m_roi.m_regionFigures.size();
        for (size_t i = 0; i < num; ++i) {
            m_pScene->m_roi.removeRect(m_pScene, i);
        }
        m_pScene->m_roi.release();
    }
}


void ImageWindow::slotToggleEllipse(bool checked) {
    /* 楕円領域の(非)表示 */

    m_pScene->m_ellipse.m_isRegionFigure = checked;

    if (!checked) {
        size_t num = m_pScene->m_ellipse.m_regionFigures.size();
        for (size_t i = 0; i < num; ++i) {
            m_pScene->m_ellipse.removeRect(m_pScene, i);
        }
        m_pScene->m_ellipse.release();
    }
}


void ImageWindow::slotStartCapture() {
    /* カメラキャプチャ開始 */

    // CameraController
    std::string maker = "general";
    std::string type = "usb";
    m_camCtrl.setCameraType(maker, type);

    if (m_camCtrl.startCamera(0, 0)) {
        // start worker-thread.

        m_camWidth = m_camCtrl.width();
        m_camHeight = m_camCtrl.height();
        m_camChannels = m_camCtrl.channels();
        m_camMemSizePerLine = m_camCtrl.memSizePerLine();

        if (m_camChannels == 1) {
            m_camFormat = QImage::Format_Grayscale8;
        }
        else if (m_camChannels == 3) {
            m_camFormat = QImage::Format_RGB888;
        }
        else if (m_camChannels == 4) {
            m_camFormat = QImage::Format_RGBA8888;
        }
        else {
            IS_DEBUG_STREAM("No support camera format. Given channels is %d\n", m_camChannels);
            m_camCtrl.stopCamera();
            return;
        }

        // WindowTitle
        std::string winTitle = is::common::format_string("%s_%s.bmp", maker.c_str(), type.c_str());
        setFilename(QString::fromStdString(winTitle));

        // QTimer   
        connect(m_pCamTimer, &QTimer::timeout, this, &ImageWindow::slotTimerHandler);
        m_camTimerId = m_pCamTimer->timerId();

        // https://doc.qt.io/qt-5/qt.html#TimerType-enum
        // Qt::TimerType
        // 0 : Qt::PreciseTimer
        // 1 : Qt::CoarseTimer
        // 2 : Qt::VeryCoarseTimer
        m_camTimerType = m_pCamTimer->timerType(); // default: Qt::CoarseTimer
        IS_DEBUG_STREAM("TimerId: %d, TimerType: %d\n", m_camTimerId, m_camTimerType);

        m_pCamTimer->start(30);

        IS_DEBUG_STREAM("Start draw timer for camera frame.\n");
    }
}


void ImageWindow::slotStopCapture() {
    /* カメラキャプチャ停止 */

    // QTimer
    if (m_pCamTimer->isActive()) {
        m_pCamTimer->stop();
        disconnect(m_pCamTimer, &QTimer::timeout, this, &ImageWindow::slotTimerHandler);
        IS_DEBUG_STREAM("Stop draw timer for camera frame.\n");
    }

    // CameraController
    m_camCtrl.stopCamera();
}


void ImageWindow::slotTimerHandler() {
    /* タイマーハンドラ */

    auto frameDesc = m_camCtrl.fetchFrame();
    auto& frame = std::get<0>(frameDesc);
    auto& fps = std::get<1>(frameDesc);

    // IS_DEBUG_STREAM("Timer handler: mem-size: %ld, fps: %f\n", 
    //     frame.size(), fps);

    QImage frameImg(frame.data(), m_camWidth, m_camHeight, 
                    (int)m_camMemSizePerLine, m_camFormat);

   setDibImg(frameImg, false, true);
}