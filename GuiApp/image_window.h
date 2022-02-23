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
#include "image_scene.h"

#include <IsComputerVision/camera/camera_controller.hpp>

#include <QMainWindow>
#include <QEvent>
#include <QString>
#include <QLabel>
#include <Qt>
#include <QTimer>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageWindow; }
QT_END_NAMESPACE

class MainWindow;

class ImageWindow : public QMainWindow 
{    
    Q_OBJECT
    
    MainWindow*      m_pMainWindow;
    Ui::ImageWindow* m_pUi;
    ImageScene*      m_pScene;
    QLabel*          m_pStatusBarLabel;
    QString          m_filename;
    std::string      m_posStatus;

    // Camera
    QTimer*          m_pCamTimer;
    int m_camTimerId {0};
    Qt::TimerType m_camTimerType;
    is::imgproc::CameraController m_camCtrl;
    QImage::Format m_camFormat;
    int m_camWidth {0};
    int m_camHeight {0};
    int m_camChannels {0};
    size_t m_camMemSizePerLine {0};

    void UiConnection();
    void MemuBarConnection();
    void ToolBarConnection();
    void CustomConnection();

public:
    explicit ImageWindow(QWidget *parent = nullptr);
    virtual ~ImageWindow();

    void SetFilename(const QString& filename);
    QString Filename() const;
    ImageScene* Scene() const;
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
    void RemoveImgWin(ImageWindow *ptr);
    void ActiveImgWin(ImageWindow *ptr);

public slots:
    void SlotShowPosToStatusBar(const QPointF &imgLocalPos,
                                const QPointF &scenePos,
                                const QPoint &viewPos);

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