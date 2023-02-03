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
#include "image_scene.h"

#include <cstring>
#include <ctime>
#include <string>
#include <iostream>

#include <QGraphicsItem>
#include <QTimer>
#include <QLabel>



//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

ImageWindow::ImageWindow(QWidget *p_parent)
    : QMainWindow(p_parent)
    , mMainWindow(qobject_cast<MainWindow *>(p_parent))
    , mUi(new Ui::ImageWindow())
    , mStatusBarLabel(new QLabel())
{
    
    // ui
    mUi->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // view
    mScene = new ImageScene(this);
    mUi->graphicsViewImage->setScene(mScene);

    // statusbar
    SlotShowPosToStatusBar(QPointF(0, 0), QPointF(0, 0), QPoint(0, 0));

    // timer
    mCamTimer = new QTimer(this);

    /*Singal/Slot*/
    UiConnection();
    MemuBarConnection();
    ToolBarConnection();
    CustomConnection();
}

ImageWindow::~ImageWindow() 
{
    if (mUi) 
    {
        delete mUi;
        mUi = nullptr;
    }

    if (mScene) 
    {
        delete mScene;
        mScene = nullptr;
    }
}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void ImageWindow::UiConnection() 
{
    // 仮の設定
    connect(mUi->pushButtonStartCapture, &QPushButton::clicked,
        this, &ImageWindow::SlotStartCapture);
    
    connect(mUi->pushButtonStopCapture, &QPushButton::clicked,
        this, &ImageWindow::SlotStopCapture);
}

void ImageWindow::MemuBarConnection() 
{
    /* Menu -> File */
    // New
    connect(mUi->actionNew, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarFileNew);

    // Open
    connect(mUi->actionOpen, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarFileOpen);

    // Close
    connect(mUi->actionClose, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarFileClose);

    // Save
    connect(mUi->actionSave, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarFileSave);

    // Save As
    // CSV
    connect(mUi->actionSaveAsCsv, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarFileSaveAs);
    // TSV
    connect(mUi->actionSaveAsTsv, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarFileSaveAs);

    /* Menu -> Edit */
    // Undo
    connect(mUi->actionUndo, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarEditUndo);

    // Rename
    connect(mUi->actionRename, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarEditRename);

    // Cut
    connect(mUi->actionCut, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarEditCut);

    // Copy
    connect(mUi->actionCopy, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarEditCopy);

    // Paste
    connect(mUi->actionPaste, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarEditPaste);

    // Clear
    connect(mUi->actionClear, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarEditClear);

    // Clear outside
    connect(mUi->actionClearOutside, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarEditClearOutside);

    // Fill
    connect(mUi->actionFill, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarEditFill);

    // Invert
    connect(mUi->actionInvert, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarEditInvert);


    /* Menu -> Image */
    // Type
    connect(mUi->actionCvt8bit, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarImageType);
    connect(mUi->actionCvt24bit, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarImageType);
    connect(mUi->actionCvtRGBA, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarImageType); 

    // ShowInfo

    // Color
    connect(mUi->actionRGBToGray, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarImageColor);
    connect(mUi->actionGrayToRGB, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarImageColor);
    connect(mUi->actionRGBToHSV, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarImageColor);
    connect(mUi->actionHSVToRGB, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarImageColor);
    connect(mUi->actionRGBToYUV, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarImageColor);
    // connect(mUi->actionYUVToRGB, &QAction::triggered,
    //     mMainWindow, &MainWindow::slotActMenuBarImageColor);

    // Crop
    connect(mUi->actionCrop, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarImageCrop);

    // Duplicate
    connect(mUi->actionDuplicate, &QAction::triggered, 
        mMainWindow, &MainWindow::SlotActMenuBarImageDuplicate);


        
    /* Menu -> Camera */
    connect(mUi->actionCameraGeneral, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarCameraWindow);
    connect(mUi->actionCameraIds, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarCameraWindow);
    connect(mUi->actionCameraOmron, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarCameraWindow);
    connect(mUi->actionCameraBasler, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarCameraWindow);
    connect(mUi->actionCameraCognex, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarCameraWindow);


    /* Menu -> Process */
    // Filter
    connect(mUi->actionFilter, &QAction::triggered,
        mMainWindow, &MainWindow::SlotActMenuBarFilter);
}

void ImageWindow::ToolBarConnection() 
{
    // connect(mUi->actionCrossLine, &QAction::toggled, mScene, &ImageScene::slotToggleCrossLine);

    /* QAction -> ImageScene */

    // Reset DIB Image
    connect(mUi->actionResetImage, &QAction::triggered,
            this, &ImageWindow::SlotResetDibImg);

    // CrossLine
    connect(mUi->actionCrossLine, &QAction::toggled, 
            this, &ImageWindow::SlotToggleCrossLine);

    // Profile-X(R)
    connect(mUi->actionProfileXRed, &QAction::toggled, 
            this, &ImageWindow::SlotToggleProfile);
    // Profile-X(G)
    connect(mUi->actionProfileXGreen, &QAction::toggled, 
            this, &ImageWindow::SlotToggleProfile);
    // Profile-X(B)
    connect(mUi->actionProfileXBlue, &QAction::toggled, 
            this, &ImageWindow::SlotToggleProfile);
    // Profile-Y(R)
    connect(mUi->actionProfileYRed, &QAction::toggled, 
            this, &ImageWindow::SlotToggleProfile);
    // Profile-Y(G)
    connect(mUi->actionProfileYGreen, &QAction::toggled, 
            this, &ImageWindow::SlotToggleProfile);
    // Profile-Y(B)
    connect(mUi->actionProfileYBlue, &QAction::toggled, 
            this, &ImageWindow::SlotToggleProfile);

    // Roi
    connect(mUi->actionRoi, &QAction::toggled, 
            this, &ImageWindow::SlotToggleRoi);

    // Ellipse
    connect(mUi->actionEllipse, &QAction::toggled,
            this, &ImageWindow::SlotToggleEllipse);
}

void ImageWindow::CustomConnection() 
{
    /* ImageWindow -> MainWindow */
    connect(this, &ImageWindow::RemoveImgWin, 
        (MainWindow *)(this->parent()), &MainWindow::SlotRmImgWin);
    connect(this, &ImageWindow::ActiveImgWin, 
        (MainWindow *)(this->parent()), &MainWindow::SlotActiveImgWin);

    /* ImageView -> ImageWindow */
    connect(mUi->graphicsViewImage, &ImageView::EmitShowPosToStatusBar,
            this, &ImageWindow::SlotShowPosToStatusBar);
}

bool ImageWindow::event(QEvent *event) 
{
    /*イベントの基底*/
    // 各イベントが到達する前にフックする.

    if (event->type() == QEvent::WindowActivate)
    {
        emit ActiveImgWin(this);
    }

    return QMainWindow::event(event);
}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////
void ImageWindow::closeEvent(QCloseEvent *event) 
{
    /*登録解除*/
    emit RemoveImgWin(this);
}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

void ImageWindow::SetFilename(const QString& filename) 
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
    mfilename = filename;
}

QString ImageWindow::Filename() const { return mfilename; }
ImageScene *ImageWindow::Scene() const { return mScene; }
Ui::ImageWindow *ImageWindow::Ui() const { return mUi; }


void ImageWindow::ResetDibImg() 
{
    /* 原画像に戻す */
    mScene->ResetRawImg();
}


QImage ImageWindow::GetDibImg() 
{
    /* シーン上の編集画像を取得 */
    return mScene->GetDibImg();
}

bool ImageWindow::SetDibImg(QImage& img, bool isSceneClear, bool isRaw) 
{
    /* シーン上の編集画像に設定 */
  
    int width = img.width();
    int height = img.height();
    int depth = img.depth();
    qsizetype datasize = img.sizeInBytes();

    if (depth == 8) 
    {
        img = img.convertToFormat(QImage::Format_Grayscale8);
        mUi->actionCvt8bit->setChecked(true);
    } 
    else if (depth == 24) 
    {
        img = img.convertToFormat(QImage::Format_RGB888);
        mUi->actionCvt24bit->setChecked(true);
    }
    else if (depth == 32) 
    {
        img = img.convertToFormat(QImage::Format_RGBA8888);
        mUi->actionCvtRGBA->setChecked(true);
    }
    else 
    {
        std::string msg = is::common::format_string(
            "No support image format. Given depth is %d", depth);
        throw std::runtime_error(msg.c_str());
    }

    auto format = GetFormatStr(img);
    
    std::string status = is::common::format_string("%dx%d@%s, %d-bits, %ld[bytes]", 
                                width, height, 
                                format.second.toStdString().c_str(),
                                depth,
                                datasize);

    mUi->lineEditImageStatus->clear();
    mUi->lineEditImageStatus->setText(QString::fromStdString(status));

    if (isSceneClear) 
    {
         mScene->clear();
    }

    return mScene->SetDibImg(img, isRaw);
}



std::map<int, QRectF> ImageWindow::GetRectsOnDibImg() const 
{
    /* シーン上のRoiを取得 */

    std::map<int, QRectF> rects;
    for (auto iter = mUi->graphicsViewImage->GetRoiRect().m_regionFigures.begin(); 
        iter != mUi->graphicsViewImage->GetRoiRect().m_regionFigures.end(); ++iter) 
    {
        rects[iter->first] = iter->second->rect();
    }
    return rects;
}


//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

void ImageWindow::SlotShowPosToStatusBar(
    const QPointF &imgLocalPos,
    const QPointF &scenePos,
    const QPoint &viewPos) 
{
    /* 編集画像上のローカル座標, シーン座標, ビュー座標
       を取得してステータスバーに表示.
    */
   using namespace is::common;

    mPosStatus = format_string("ImageLocalPos(%4.1f, %4.1f), ScenePos(%4.1f, %4.1f), ViewPos(%4d, %4d)",
                               imgLocalPos.x(), imgLocalPos.y(),
                               scenePos.x(), scenePos.y(),
                               viewPos.x(), viewPos.y());
    mStatusBarLabel->setText(QString::fromStdString(mPosStatus));
    this->statusBar()->addPermanentWidget(mStatusBarLabel);
}

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////

void ImageWindow::SlotResetDibImg(bool checked) 
{
    /* 原画像に戻す */
    ResetDibImg();
    IS_DEBUG_LOG("ImageWindow::slotResetDibImg\n");
}


void ImageWindow::SlotToggleCrossLine(bool checked) 
{
    /*十字線の(非)表示*/
    mUi->graphicsViewImage->GetCrossLine().SetChecked(checked);

    if (!mUi->graphicsViewImage->GetCrossLine().GetChecked()) 
    {
        mScene->removeItem(mUi->graphicsViewImage->GetCrossLine().GetLineItemX());
        mScene->removeItem(mUi->graphicsViewImage->GetCrossLine().GetLineItemY());
    }
}

void ImageWindow::SlotToggleProfile(bool checked) 
{
    /*プロファイルの(非)表示*/
    auto p_sender = QObject::sender();
    if (p_sender == mUi->actionProfileXRed) 
    {
        if (!checked) 
        {
            mScene->removeItem(mUi->graphicsViewImage->GetProfile().GetDirectionX().GetItemPathRed());
            mUi->graphicsViewImage->GetProfile().GetDirectionX().SetAddedRedChecked(false);
        }
        mUi->graphicsViewImage->GetProfile().GetDirectionX().SetPathRedChecked(checked);
    }
    else if (p_sender == mUi->actionProfileXGreen) 
    {
        if (!checked) 
        {
            mScene->removeItem(mUi->graphicsViewImage->GetProfile().GetDirectionX().GetItemPathGreen());
            mUi->graphicsViewImage->GetProfile().GetDirectionX().SetAddedGreenChecked(false);
        }
        mUi->graphicsViewImage->GetProfile().GetDirectionX().SetPathGreenChecked(checked);
    }
    else if (p_sender == mUi->actionProfileXBlue) 
    {
        if (!checked) 
        {
            mScene->removeItem(mUi->graphicsViewImage->GetProfile().GetDirectionX().GetItemPathBlue());
            mUi->graphicsViewImage->GetProfile().GetDirectionX().SetAddedBlueChecked(false);
        }
        mUi->graphicsViewImage->GetProfile().GetDirectionX().SetPathBlueChecked(checked);
    }
    else if (p_sender == mUi->actionProfileYRed) 
    {
        if (!checked) 
        {
            mScene->removeItem(mUi->graphicsViewImage->GetProfile().GetDirectionY().GetItemPathRed());
            mUi->graphicsViewImage->GetProfile().GetDirectionY().SetAddedRedChecked(false);
        }
        mUi->graphicsViewImage->GetProfile().GetDirectionY().SetPathRedChecked(checked);
    }
    else if (p_sender == mUi->actionProfileYGreen) 
    {
        if (!checked) 
        {
            mScene->removeItem(mUi->graphicsViewImage->GetProfile().GetDirectionY().GetItemPathGreen());
            mUi->graphicsViewImage->GetProfile().GetDirectionY().SetAddedGreenChecked(false);
        }
        mUi->graphicsViewImage->GetProfile().GetDirectionY().SetPathGreenChecked(checked);
    }
    else if (p_sender == mUi->actionProfileYBlue) 
    {
        if (!checked) 
        {
            mScene->removeItem(mUi->graphicsViewImage->GetProfile().GetDirectionY().GetItemPathBlue());
            mUi->graphicsViewImage->GetProfile().GetDirectionY().SetAddedBlueChecked(false);
        }
        mUi->graphicsViewImage->GetProfile().GetDirectionY().SetPathBlueChecked(checked);
    }
}


void ImageWindow::SlotToggleRoi(bool checked) 
{
    /*矩形領域の(非)表示*/

    mUi->graphicsViewImage->GetRoiRect().m_isRegionFigure = checked;

    if (!checked) 
    {
        size_t num = mUi->graphicsViewImage->GetRoiRect().m_regionFigures.size();
        for (size_t i = 0; i < num; ++i) 
        {
            mUi->graphicsViewImage->GetRoiRect().RemoveRect(mScene, i);
        }
        mUi->graphicsViewImage->GetRoiRect().Release();
    }
}


void ImageWindow::SlotToggleEllipse(bool checked) 
{
    /* 楕円領域の(非)表示 */

    mUi->graphicsViewImage->GetRoiEllipse().m_isRegionFigure = checked;

    if (!checked) 
    {
        size_t num = mUi->graphicsViewImage->GetRoiEllipse().m_regionFigures.size();
        for (size_t i = 0; i < num; ++i) 
        {
            mUi->graphicsViewImage->GetRoiEllipse().RemoveRect(mScene, i);
        }
        mUi->graphicsViewImage->GetRoiEllipse().Release();
    }
}


void ImageWindow::SlotStartCapture() 
{
    /* カメラキャプチャ開始 */

    // CameraController
    std::string maker = "general";
    std::string type = "usb";
    mCamCtrl.setCameraType(maker, type);

    if (mCamCtrl.startCamera(0, 0)) 
    {
        // start worker-thread.

        mCamWidth = mCamCtrl.width();
        mCamHeight = mCamCtrl.height();
        mCamChannels = mCamCtrl.channels();
        mCamMemSizePerLine = mCamCtrl.memSizePerLine();

        if (mCamChannels == 1) 
        {
            mCamFormat = QImage::Format_Grayscale8;
        }
        else if (mCamChannels == 3) 
        {
            mCamFormat = QImage::Format_RGB888;
        }
        else if (mCamChannels == 4) 
        {
            mCamFormat = QImage::Format_RGBA8888;
        }
        else 
        {
            IS_DEBUG_LOG("No support camera format. Given channels is %d\n", mCamChannels);
            mCamCtrl.stopCamera();
            return;
        }

        // WindowTitle
        std::string winTitle = is::common::format_string("%s_%s.bmp", maker.c_str(), type.c_str());
        SetFilename(QString::fromStdString(winTitle));

        // QTimer   
        connect(mCamTimer, &QTimer::timeout, this, &ImageWindow::SlotTimerHandler);
        mCamTimerId = mCamTimer->timerId();

        // https://doc.qt.io/qt-5/qt.html#TimerType-enum
        // Qt::TimerType
        // 0 : Qt::PreciseTimer
        // 1 : Qt::CoarseTimer
        // 2 : Qt::VeryCoarseTimer
        mCamTimerType = mCamTimer->timerType(); // default: Qt::CoarseTimer
        IS_DEBUG_LOG("TimerId: %d, TimerType: %d\n", mCamTimerId, mCamTimerType);

        mCamTimer->start(30);

        IS_DEBUG_LOG("Start draw timer for camera frame.\n");
    }
}


void ImageWindow::SlotStopCapture() 
{
    /* カメラキャプチャ停止 */

    // QTimer
    if (mCamTimer->isActive()) 
    {
        mCamTimer->stop();
        disconnect(mCamTimer, &QTimer::timeout, this, &ImageWindow::SlotTimerHandler);
        IS_DEBUG_LOG("Stop draw timer for camera frame.\n");
    }

    // CameraController
    mCamCtrl.stopCamera();
}


void ImageWindow::SlotTimerHandler() 
{
    /* タイマーハンドラ */

    auto frameDesc = mCamCtrl.fetchFrame();
    auto& frame = std::get<0>(frameDesc);
    auto& fps = std::get<1>(frameDesc);

    IS_DEBUG_LOG("Timer handler: mem-size: %ld, fps: %f\n", 
        frame.size(), fps);

    QImage frameImg(frame.data(), mCamWidth, mCamHeight, mCamMemSizePerLine, mCamFormat);

   SetDibImg(frameImg, false, true);
}