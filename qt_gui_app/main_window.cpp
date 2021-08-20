

#include "ui_MainWindow.h"
#include "main_window.h"

#include <iostream>
#include <cstdio>

/**
 * @brief Construct a new Main Window:: Main Window object
 * 
 * @param parent 
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_pUi(new Ui::MainWindow())
    , m_pStatusBarLabel(new QLabel())
    , m_pLastActiveImgWin(nullptr)
{
    // UI
    m_pUi->setupUi(this);

    /* Signal & Slot */
    menubarConnection();
}

/**
 * @brief Destroy the Main Window:: Main Window object
 * 
 */
MainWindow::~MainWindow() 
{
    if (m_pUi) delete m_pUi;
}


MainWindow::ImgWinRegistory_t& MainWindow::getImgWinRegistory()
{
    static ImgWinRegistory_t imgWindowBacket;
    return imgWindowBacket;
}


/*public slot*/
void MainWindow::slotRmImgWin(ImageWindow *ptr)
{
    /*指定のImageWindowの登録を解除*/

    getImgWinRegistory().erase(ptr);
    size_t count = getImgWinRegistory().size();
    m_pStatusBarLabel->setText(QString::number(count));
    m_pUi->statusBar->addPermanentWidget(m_pStatusBarLabel);
    std::printf("Erase a image window. Given is %p.\n", ptr);

    if (m_pLastActiveImgWin == ptr)
    {
        m_pLastActiveImgWin = nullptr;
    }
}

// /*public slot*/
// void MainWindow::slotActiveImgWin(ImageWindow *ptr)
// {
//     m_pLastActiveImgWin = ptr;
// }


/**
 * @brief メニューバーアクションの接続
 * 
 */
void MainWindow::menubarConnection()
{
    /* File */
    // New
    connect(m_pUi->actionNew, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileNew()));  
    // Open   
    connect(m_pUi->actionOpen, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileOpen()));   
    // Close
    connect(m_pUi->actionClose, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileClose())); 
    // Close All
    connect(m_pUi->actionClose_All, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileCloseAll())); 
    // Save
    connect(m_pUi->actionSave, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSave()));
    // SaveAs
    connect(m_pUi->actionBMP, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    connect(m_pUi->actionJPEG, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    connect(m_pUi->actionJPG, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    connect(m_pUi->actionPNG, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    connect(m_pUi->actionCSV, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    // Print
    connect(m_pUi->actionPrint, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFilePrint())); 
    // Quit
    connect(m_pUi->actionQuit, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileQuit())); 

}

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

    m_pStatusBarLabel->setText(QString::number(getImgWinRegistory().size()));
    m_pUi->statusBar->addPermanentWidget(m_pStatusBarLabel);
}

/**
 * @brief Menu -> File -> Open
 * 
 */
void MainWindow::slotActMenubarFileOpen()
{

}

/**
 * @brief Menu -> File -> Close
 * 
 */
void MainWindow::slotActMenubarFileClose()
{

}

/**
 * @brief Menu -> File -> Close all
 * 
 */
void MainWindow::slotActMenubarFileCloseAll()
{

}

/**
 * @brief Menu -> File -> Save
 * 
 */
void MainWindow::slotActMenubarFileSave()
{

}

/**
 * @brief Menu -> File -> Save as
 * 
 */
void MainWindow::slotActMenubarFileSaveAs()
{

}

/**
 * @brief Menu -> File -> Print
 * 
 */
void MainWindow::slotActMenubarFilePrint()
{

}

/**
 * @brief Menu -> File -> Quit
 * 
 */
void MainWindow::slotActMenubarFileQuit()
{

}


