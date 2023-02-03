/**
 * @file image_window.cpp
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief Qt 自作ImageWindowのHeaderファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "GuiApp.h"

#include "ui_ImageWindow.h"
#include "image_view.h"

#include <QMainWindow>


#include <QEvent>
#include <QString>

#include <Qt>

#include <QImage>

#include <IsComputerVision/camera/camera_controller.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageWindow; }
QT_END_NAMESPACE



class ImageWindow : public QMainWindow 
{    
    Q_OBJECT
    
    class MainWindow* mMainWindow;
    Ui::ImageWindow* mUi;
    class ImageScene* mScene;
    class QLabel* mStatusBarLabel;
    QString          mfilename;
    std::string      mPosStatus;

    // Camera
    class QTimer* mCamTimer;
    int mCamTimerId {0};
    Qt::TimerType mCamTimerType;
    is::cv::CameraController mCamCtrl;
    QImage::Format mCamFormat;
    int mCamWidth {0};
    int mCamHeight {0};
    int mCamChannels {0};
    size_t mCamMemSizePerLine {0};

    void UiConnection();
    void MemuBarConnection();
    void ToolBarConnection();
    void CustomConnection();

public:
    explicit ImageWindow(QWidget *parent = nullptr);
    virtual ~ImageWindow();

    void SetFilename(const QString& filename);
    QString Filename() const;
    class ImageScene* Scene() const;
    Ui::ImageWindow* Ui() const;
    void ResetDibImg();
    QImage GetDibImg();
    bool SetDibImg(QImage& img, bool isSceneClear = false, bool isRaw = false);
    std::map<int, QRectF> GetRectsOnDibImg() const;

protected:
    virtual bool event(QEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    /* --- ImageWindow --- */
    void RemoveImgWin(class ImageWindow* ptr);
    void ActiveImgWin(class ImageWindow* ptr);

public slots:
    void SlotShowPosToStatusBar(const QPointF& imgLocalPos,
                                const QPointF& scenePos,
                                const QPoint& viewPos);

private slots:
    void SlotResetDibImg(bool checked);
    void SlotToggleCrossLine(bool checked);
    void SlotToggleProfile(bool checked);
    void SlotToggleRoi(bool checked);
    void SlotToggleEllipse(bool checked);

    // QTimer
    void SlotStartCapture();
    void SlotStopCapture();
    void SlotTimerHandler();
};