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

#include <QMainWindow>
#include <QImage>

#include <functional>



QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow 
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
    
    Ui::MainWindow* mUi;
    class QLabel* mStatusBarLabel;
    class ImageWindow* mLastActiveImgWin;
    QImage mCopyImg;

private:
    void MenuBarConnection();
    void ToolBarConnection();
    void UiConnection();
    void CustomConnection();

    void HelperImgProc(const class QString& process, std::function<void(QImage&)> func);


public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

    /*ImageWindow*/
    using ImgWinRegistry_t = std::set<class ImageWindow*>;
    static ImgWinRegistry_t& GetImgWinRegistry();
    class ImageWindow* GenImgWin(const class QString& filename);

protected:
    /*Drag/Drop*/
    void dragEnterEvent(class QDragEnterEvent *event) override;
    void dragLeaveEvent(class QDragLeaveEvent *event) override;
    void dragMoveEvent(class QDragMoveEvent *event) override;
    void dropEvent(class QDropEvent *event) override;

    /*Mouse*/

signals:
    
public slots:
    void SlotRmImgWin(class ImageWindow* ptr);
    void SlotActiveImgWin(class ImageWindow* ptr);

    /* Menu -> File */
    void SlotActMenuBarFileNew();
    void SlotActMenuBarFileOpen();
    void SlotActMenuBarFileClose();
    void SlotActMenuBarFileCloseAll();
    void SlotActMenuBarFileSave();
    void SlotActMenuBarFileSaveAs();
    void SlotActMenuBarFilePrint();
    void SlotActMenuBarFileQuit();

    /* Menu -> Edit */
    void SlotActMenuBarEditUndo();
    void SlotActMenuBarEditRename();
    void SlotActMenuBarEditCut();
    void SlotActMenuBarEditCopy();
    void SlotActMenuBarEditPaste();
    void SlotActMenuBarEditClear();
    void SlotActMenuBarEditClearOutside();
    void SlotActMenuBarEditFill();
    void SlotActMenuBarEditInvert();

    /* Menu -> Image */
    void SlotActMenuBarImageType();
    void SlotActMenuBarImageShowInfo();
    void SlotActMenuBarImageColor();
    void SlotActMenuBarImageBorder();
    void SlotActMenuBarImageCrop();
    void SlotActMenuBarImageDuplicate();
    void SlotActMenuBarImageTransform();

    /* Menu -> View */
    // void slotActMenuBarViewFitView();
    // void slotActMenuBarViewOriginalScale();

    // /* Menu -> Camera */
    void SlotActMenuBarCameraWindow();

    // /* Menu -> Video */
    // void slotActMenuBarVideoWindow();
 
    /* Menu -> Process */
    void SlotActMenuBarFilter();
    // void slotActMenuBarEdgeDetector();
    // void slotActMenuBarLut();
    // void slotActMenuBarBinarize();
    // void slotActMenuBarMorphology();
    // void slotActMenuBarNoise();
    // void slotActMenuBarHistogram();

    // /* Menu -> Analyze -> Frequency */
    // void slotActMenuBarAnaFreqFft();
    // void slotActMenuBarAnaFreqWavelet();
    
    // /* Menu -> Analyze -> Luminance */
    // void slotActMenuBarAnaLumHist();
    // void slotActMenuBarAnaLumProfile();

    // /* Menu -> Anayze -> Blob */
    // void slotActMenuBarAnaBlobLabeling();
};
