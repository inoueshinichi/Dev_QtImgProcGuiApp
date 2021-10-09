/**
 * @file main_window.cpp
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief Qt 自作MainWindowのHeaderファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "GuiApp.h"
#include "image_window.h"

#include <functional>

#include <QMainWindow>
#include <Qt>
#include <QDrag>
#include <QMessageBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QDialog>
#include <QInputDialog>
#include <QColorDialog>
#include <QImage>
#include <QString>
#include <QLabel>




QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
    Ui::MainWindow *m_pUi;
    QLabel* m_pStatusBarLabel;
    ImageWindow* m_pLastActiveImgWin;
    QImage m_copyImg;
    QPointF m_pressPosOnScreen;

private:
    void menuBarConnection();
    void toolBarConnection();
    void uiConnection();
    void customConnection();

    void enableViewMode();
    void enableFileMode();
    void startDragProcess(Qt::DropActions *dropActions, QMouseEvent *event);

    void helperImgProc(const QString &process, std::function<void(QImage&)> func);
    void startDrag(Qt::DropAction action, QMouseEvent *event);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    /*ImageWindow*/
    using ImgWinRegistry_t = std::set<ImageWindow*>;
    static ImgWinRegistry_t& getImgWinRegistry();
    ImageWindow* genImgWin(const QString &filename);

protected:
    /*Drag/Drop*/
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    /*Mouse*/
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    
public slots:
    void slotRmImgWin(ImageWindow *ptr);
    void slotActiveImgWin(ImageWindow *ptr);

    /* Menu -> File */
    void slotActMenuBarFileNew();
    void slotActMenuBarFileOpen();
    void slotActMenuBarFileClose();
    void slotActMenuBarFileCloseAll();
    void slotActMenuBarFileSave();
    void slotActMenuBarFileSaveAs();
    void slotActMenuBarFilePrint();
    void slotActMenuBarFileQuit();

    /* Menu -> Edit */
    void slotActMenuBarEditUndo();
    void slotActMenuBarEditRename();
    void slotActMenuBarEditCut();
    void slotActMenuBarEditCopy();
    void slotActMenuBarEditPaste();
    void slotActMenuBarEditClear();
    void slotActMenuBarEditClearOutside();
    void slotActMenuBarEditFill();
    void slotActMenuBarEditInvert();

    /* Menu -> Image */
    void slotActMenuBarImageType();
    void slotActMenuBarImageShowInfo();
    void slotActMenuBarImageColor();
    void slotActMenuBarImageBorder();
    void slotActMenuBarImageCrop();
    void slotActMenuBarImageDuplicate();
    void slotActMenuBarImageTransform();

    /* Menu -> View */
    // void slotActMenuBarViewFitView();
    // void slotActMenuBarViewOriginalScale();

    // /* Menu -> Camera */
    void slotActMenuBarCameraWindow();

    // /* Menu -> Video */
    // void slotActMenuBarVideoWindow();

private slots:
 
    // /* Menu -> Process */
    // void slotActMenuBarProcessBlur();
    // void slotActMenuBarProcessShading();
    // void slotActMenuBarProcessUnsharpMask();
    // void slotActMenuBarProcessEdgeDetector();
    // void slotActMenuBarProcessLut();
    // void slotActMenuBarProcessBinarize();
    // void slotActMenuBarProcessMorphology();
    // void slotActMenuBarProcessNoise();
    // void slotActMenuBarProcessHistogram();

    // /* Menu -> Analyze -> Frequency */
    // void slotActMenuBarAnaFreqFft();
    // void slotActMenuBarAnaFreqWavelet();
    
    // /* Menu -> Analyze -> Luminance */
    // void slotActMenuBarAnaLumHist();
    // void slotActMenuBarAnaLumProfile();

    // /* Menu -> Anayze -> Blob */
    // void slotActMenuBarAnaBlobLabeling();
};
