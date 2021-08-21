

#include "ui_MainWindow.h"
#include "main_window.h"

#include <iostream>
#include <cstdio>

//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *p_parent)
    : QMainWindow(p_parent)
    , m_pUi(new Ui::MainWindow())
    , m_pStatusBarLabel(new QLabel())
    , m_pLastActiveImgWin(nullptr)
{
    // UI
    m_pUi->setupUi(this);

    /* Signal & Slot */
    menuBarConnection();
}

MainWindow::~MainWindow() 
{
    if (m_pUi) delete m_pUi;
}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

void MainWindow::menuBarConnection()
{
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

void MainWindow::toolBarConnection()
{
    /* ToolBarに関するSignal/Slot接続
    */

   // 右クリックでToolBarを非表示にできないようにする
    m_pUi->toolBar->toggleViewAction()->setEnabled(false);


}

void MainWindow::uiConnection()
{

}

void MainWindow::customConnection()
{

}

/**
 * @brief ドラッグ開始時の処理
 * 
 */
void MainWindow::startDragProcess()
{

}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////

/**
 * @brief ドラッグ状態でWindowにカーソルが侵入した際のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragEnterEvent(QtGui::QDragEnterEvent *event)
{}


/**
 * @brief ドラッグ状態でWindowからカーソルが外れた際のイベント処理
 * 
 * @param event 
 */
void dragLeaveEvent(QtGui::QDragLeaveEvent *event)
{}

    /**
 * @brief ドラッグ移動中のイベント処理
 * 
 * @param event 
 */
    void MainWindow::dragMoveEvent(QtGui::QDragMoveEvent *event)
{}

/**
 * @brief ドロップイベント時の処理
 * 
 * @param event 
 */
    void MainWindow::dropEvent(QtGui::QDropEvent *event)
{}

/**
 * @brief マウス移動時のイベント処理
 * 
 * @param event 
 */
void mouseMoveEvent(QtGui::QMouseEvent *event)
{}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

MainWindow::ImgWinRegistory_t &MainWindow::getImgWinRegistory()
{
    static ImgWinRegistory_t imgWindowBacket;
    return imgWindowBacket;
}

//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

/*public slot*/
void MainWindow::slotRmImgWin(ImageWindow *ptr)
{
    /*指定のImageWindowの登録を解除*/

    getImgWinRegistory().erase(ptr);
    size_t count = getImgWinRegistory().size();
    m_pStatusBarLabel->setText(QString::number(count));
    m_pUi->statusBar->addPermanentWidget(m_pStatusBarLabel);
    std::printf("Erase a image window. Given is %p.\n", (void *)ptr);

    if (m_pLastActiveImgWin == ptr)
    {
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
void MainWindow::slotActMenubarFileNew()
{
    // テスト ImageWindowの生成
    ImageWindow* pImgWin = new ImageWindow(this);
    getImgWinRegistory().insert(pImgWin);
    pImgWin->show();
    pImgWin->activateWindow();
    pImgWin->setFilename(tr("New Empty"));

    m_pStatusBarLabel->setText(QString::number(getImgWinRegistory().size()));
    m_pUi->statusBar->addPermanentWidget(m_pStatusBarLabel);
}

/**
 * @brief Menu -> File -> Open
 * 
 */
void MainWindow::slotActMenubarFileOpen()
{}

/**
 * @brief Menu -> File -> Close
 * 
 */
void MainWindow::slotActMenubarFileClose()
{}

/**
 * @brief Menu -> File -> Close all
 * 
 */
void MainWindow::slotActMenubarFileCloseAll()
{}

/**
 * @brief Menu -> File -> Save
 * 
 */
void MainWindow::slotActMenubarFileSave()
{}

/**
 * @brief Menu -> File -> Save as
 * 
 */
void MainWindow::slotActMenubarFileSaveAs()
{}

/**
 * @brief Menu -> File -> Print
 * 
 */
void MainWindow::slotActMenubarFilePrint()
{}

/**
 * @brief Menu -> File -> Quit
 * 
 */
void MainWindow::slotActMenubarFileQuit()
{}

/**
 * @brief Menu -> Edit -> Undo
 * 
 */
void MainWindow::slotActMenuBarEditUndo()
{}

/**
 * @brief Menu -> Edit -> Cut
 * 
 */
void MainWindow::slotActMenuBarEditCut()
{}

/**
 * @brief Menu -> Edit -> Copy
 * 
 */
void MainWindow::slotActMenuBarEditCopy()
{}

