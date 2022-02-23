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

#include <functional>



QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow 
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
    
    Ui::MainWindow*  m_pUi;
    QLabel*          m_pStatusBarLabel;
    ImageWindow*     m_pLastActiveImgWin;
    QImage           m_copyImg;

private:
    void MenuBarConnection();
    void ToolBarConnection();
    void UiConnection();
    void CustomConnection();

    void HelperImgProc(const QString &process, std::function<void(QImage&)> func);


public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    /*ImageWindow*/
    using ImgWinRegistry_t = std::set<ImageWindow*>;
    static ImgWinRegistry_t& GetImgWinRegistry();
    ImageWindow* GenImgWin(const QString &filename);

protected:
    /*Drag/Drop*/
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    /*Mouse*/

signals:
    
public slots:
    void SlotRmImgWin(ImageWindow *ptr);
    void SlotActiveImgWin(ImageWindow *ptr);

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
