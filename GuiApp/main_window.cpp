/**
 * @file main_window.cpp
 * @author your name (you@domain.com)
 * @brief Qt 自作MainWindowのSourceファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "utility.h"

#include "ui_MainWindow.h"
#include "main_window.h"

#include <QApplication>

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <filesystem>
namespace fs = std::filesystem;


//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_pUi(new Ui::MainWindow())
    , m_pStatusBarLabel(new QLabel())
    , m_pLastActiveImgWin(nullptr) {
    // UI
    m_pUi->setupUi(this);

    /* Signal & Slot */
    menuBarConnection();
}

MainWindow::~MainWindow() {
    if (m_pUi) {
        delete m_pUi;
        m_pUi = nullptr;
    }
}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void MainWindow::menuBarConnection() {
    /*MenuBarのSignal/Slot接続
    */

    ///////////////
    // File
    ///////////////
    // New
    connect(m_pUi->actionNew, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileNew);

    // Open
    connect(m_pUi->actionOpen, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileOpen);

    // Close
    connect(m_pUi->actionClose, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileClose);

    // Close All
    connect(m_pUi->actionCloseAll, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileCloseAll);

    // Save
    connect(m_pUi->actionSave, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileSave);

    // SaveAs
    connect(m_pUi->actionSaveAsBmp, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileSaveAs);
    connect(m_pUi->actionSaveAsJpg, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileSaveAs);
    connect(m_pUi->actionSaveAsJpeg, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileSaveAs);
    connect(m_pUi->actionSaveAsPng, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileSaveAs);
    connect(m_pUi->actionSaveAsCsv, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileSaveAs);

    // Print
    connect(m_pUi->actionPrint, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFilePrint);
    // Quit
    connect(m_pUi->actionQuit, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileQuit);


    ///////////////
    // Edit
    ///////////////
}

void MainWindow::toolBarConnection() {
    /* ToolBarに関するSignal/Slot接続
    */

//    // 右クリックでToolBarを非表示にできないようにする
//     m_pUi->toolBar->toggleViewAction()->setEnabled(false);


}

void MainWindow::uiConnection() {

}

void MainWindow::customConnection() {

}

/**
 * @brief ドラッグ開始時の処理
 * 
 */
void MainWindow::startDragProcess(Qt::DropActions *dropActions, QMouseEvent *event) {

}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////

/**
 * @brief ドラッグ状態でWindowにカーソルが侵入した際のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{}


/**
 * @brief ドラッグ状態でWindowからカーソルが外れた際のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{}

    /**
 * @brief ドラッグ移動中のイベント処理
 * 
 * @param event 
 */
    void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{}

/**
 * @brief ドロップイベント時の処理
 * 
 * @param event 
 */
    void MainWindow::dropEvent(QDropEvent *event)
{}

/**
 * @brief マウス移動時のイベント処理
 * 
 * @param event 
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

MainWindow::ImgWinRegistry_t &MainWindow::getImgWinRegistry() {
    static ImgWinRegistry_t imgWindowBacket;
    return imgWindowBacket;
}

ImageWindow* MainWindow::genImgWin(const QString &filename) {
    /* 新規でImageWindowを生成
    */
    ImageWindow *p_imgWin = new ImageWindow(this);
    p_imgWin->setFilename(filename);
    getImgWinRegistry().insert(p_imgWin);
    p_imgWin->show();
    p_imgWin->activateWindow();

    m_pStatusBarLabel->setText(QString::number(getImgWinRegistry().size()));
    m_pUi->statusBar->addPermanentWidget(m_pStatusBarLabel);

    return p_imgWin;
}

//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

/*public slot*/
void MainWindow::slotRmImgWin(ImageWindow *ptr) {
    /* 指定のImageWindowの登録を解除
    */

    getImgWinRegistry().erase(ptr);
    size_t count = getImgWinRegistry().size();
    m_pStatusBarLabel->setText(QString::number(count));
    m_pUi->statusBar->addPermanentWidget(m_pStatusBarLabel);

    DEBUG_STREAM("Erase a image window. Given is %p.\n", (void *)ptr);

    if (m_pLastActiveImgWin == ptr) {
        m_pLastActiveImgWin = nullptr;
    }
}

/*public slot*/
void MainWindow::slotActiveImgWin(ImageWindow *ptr)
{
    m_pLastActiveImgWin = ptr;
}

//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////

void MainWindow::slotSelectInputDir()
{}

void MainWindow::slotSelectOutputDir()
{}

/**
 * @brief Menu -> File -> New
 * 
 */
void MainWindow::slotActMenuBarFileNew() {
    /* ImageWindowの生成
    */
    genImgWin(tr("New Empty"));
}

/**
 * @brief Menu -> File -> Open
 * 
 */
void MainWindow::slotActMenuBarFileOpen() {
    /* 画像を読み込む */

    QString cwdPath = QString::fromStdString(fs::current_path().string());
    QString fileFilter = tr("画像(*.bmp *.jpg *.jpeg *.png *.tiff)");
    auto fileList = QFileDialog::getOpenFileNames(this, tr("画像ファイルを開く"), cwdPath, fileFilter);

    std::set<std::string> currImgWinFilenames;
    for (const auto &p_imgWin : getImgWinRegistry()) {
        currImgWinFilenames.insert(p_imgWin->filename().toStdString());
    }

    foreach(QString path, fileList) {
        if (!path.isEmpty()) {
            QImage img(path);
            int depth = img.bitPlaneCount();
            bool isGray = img.isGrayscale();
            if (isGray && depth == 8) {
                img = img.convertToFormat(QImage::Format_Grayscale8);
            }
            else {
                img = img.convertToFormat(QImage::Format_RGB888);
            }
            auto tokens = path.split(tr("/"));
            QString filename = tokens[tokens.size() - 1];
            
            DEBUG_STREAM("%s\n", filename.toStdString().c_str());

            std::string newFilename = getNewSerialNoFilename(filename.toStdString(), currImgWinFilenames);
            ImageWindow *p_newImgWin = genImgWin(QString::fromStdString(newFilename));

            p_newImgWin->scene()->clear();
            p_newImgWin->scene()->setDibImgOnScreen(img);

            // test gen view
            // ImageView* view = new ImageView();
            // view->setScene(p_newImgWin->scene());
            // view->show();
        }
    }
}

/**
 * @brief Menu -> File -> Close
 * 
 */
void MainWindow::slotActMenuBarFileClose()
{
    /* アクティブなImageWindowを閉じる
    */
   if (m_pLastActiveImgWin) {
       m_pLastActiveImgWin->close();
       m_pLastActiveImgWin = nullptr;
   }
}

/**
 * @brief Menu -> File -> Close all
 * 
 */
void MainWindow::slotActMenuBarFileCloseAll() 
{
    /* 開いているすべてのImageWindowを閉じる
    */
    // auto &registry = getImgWinRegistry();
    // for (auto iter = registry.begin(); iter != registry.end(); ++iter) {
    //     slotRmImgWin(*iter);
    // }
}

/**
 * @brief Menu -> File -> Save
 * 
 */
void MainWindow::slotActMenuBarFileSave()
{}

/**
 * @brief Menu -> File -> Save as
 * 
 */
void MainWindow::slotActMenuBarFileSaveAs()
{}

/**
 * @brief Menu -> File -> Print
 * 
 */
void MainWindow::slotActMenuBarFilePrint()
{}

/**
 * @brief Menu -> File -> Quit
 * 
 */
void MainWindow::slotActMenuBarFileQuit() {
    /*アプリケーションの終了*/
    QApplication::closeAllWindows();
}

// /**
//  * @brief Menu -> Edit -> Undo
//  * 
//  */
// void MainWindow::slotActMenuBarEditUndo()
// {}

// /**
//  * @brief Menu -> Edit -> Cut
//  * 
//  */
// void MainWindow::slotActMenuBarEditCut()
// {}

// /**
//  * @brief Menu -> Edit -> Copy
//  * 
//  */
// void MainWindow::slotActMenuBarEditCopy()
// {}

