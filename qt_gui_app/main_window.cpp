

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
    , ui(new Ui::MainWindow())
    , permanentStatusBar(new QLabel())
    , lastActiveImgWin(nullptr)
{
    // UI
    ui->setupUi(this);

    /* Signal & Slot */
    menubarConnection();
}

/**
 * @brief Destroy the Main Window:: Main Window object
 * 
 */
MainWindow::~MainWindow() 
{
    if (ui) delete ui;
}


MainWindow::ImgWinRegistory_t& MainWindow::getImgWinRegistory()
{
    static ImgWinRegistory_t imgWindowBacket;
    return imgWindowBacket;
}


/*public slot*/
void MainWindow::slotEraseImageWindow(ImageWindow *ptr)
{
    /*指定のImageWindowの登録を解除*/

    getImgWinRegistory().erase(reinterpret_cast<uintptr_t>(ptr));
    size_t count = getImgWinRegistory().size();
    permanentStatusBar->setText(QString::number(count));
    ui->statusBar->addPermanentWidget(permanentStatusBar);
    std::printf("Erase a image window. Given is %p.\n", ptr);

    if (lastActiveImgWin == ptr)
    {
        lastActiveImgWin = nullptr;
    }
}

/*public slot*/
void MainWindow::slotActiveImageWindow(ImageWindow *ptr)
{
    lastActiveImgWin = ptr;
}


/**
 * @brief メニューバーアクションの接続
 * 
 */
void MainWindow::menubarConnection()
{
    /* File */
    // New
    connect(ui->actionNew, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileNew()));  
    // Open   
    connect(ui->actionOpen, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileOpen()));   
    // Close
    connect(ui->actionClose, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileClose())); 
    // Close All
    connect(ui->actionClose_All, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileCloseAll())); 
    // Save
    connect(ui->actionSave, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSave()));
    // SaveAs
    connect(ui->actionBMP, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    connect(ui->actionJPEG, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    connect(ui->actionJPG, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    connect(ui->actionPNG, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    connect(ui->actionCSV, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileSaveAs()));
    // Print
    connect(ui->actionPrint, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFilePrint())); 
    // Quit
    connect(ui->actionQuit, SIGNAL(triggered()), 
        this, SLOT(slotActMenubarFileQuit())); 

}

/**
 * @brief Menu -> File -> New
 * 
 */
void MainWindow::slotActMenubarFileNew()
{
    // テスト ImageWindowの生成
    ImageWindow* tmpImgWin = new ImageWindow(this);
    getImgWinRegistory()[reinterpret_cast<uintptr_t>(tmpImgWin)] =  tmpImgWin;
    tmpImgWin->show();
    tmpImgWin->activateWindow();

    permanentStatusBar->setText(QString::number(getImgWinRegistory().size()));
    ui->statusBar->addPermanentWidget(permanentStatusBar);
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


