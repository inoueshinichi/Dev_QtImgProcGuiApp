
#include "image_window.h"
#include "main_window.h"

#include <string>
#include <iostream>

ImageWindow::ImageWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_pUi(new Ui::ImageWindow())
    , m_pStatusBarLabel(new QLabel())
{
    // ui
    m_pUi->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // view
    m_pScene = new ImageScene(this);
    m_pUi->graphicsViewImage->setScene(m_pScene);

    // statusbar

    m_pStatusBarLabel->setText(tr("SceneRect (0, 0, 0, 0)"));
    m_pUi->statusbar->addPermanentWidget(m_pStatusBarLabel);

    /*Singal/Slot*/
    customConnection();

}

ImageWindow::~ImageWindow()
{
    if (m_pUi) delete m_pUi;
    if (m_pScene) delete m_pScene;
}

void ImageWindow::customConnection()
{
    /* ImageWindow -> MainWindow */
    connect(this, &ImageWindow::rmImgWin, 
        (MainWindow *)(this->parent()), &MainWindow::slotRmImgWin);
    // connect(this, &ImageWindow::activeImgWin, 
    //     (MainWindow *)(this->parent()), &MainWindow::slotActiveImgWin);
}

void ImageWindow::closeEvent(QCloseEvent *event)
{
    /*登録解除*/
    emit rmImgWin(this);
}


bool ImageWindow::event(QEvent *event)
{
    /*イベントの基底*/
    // 各イベントが到達する前にフックする.

    if (event->type() == QEvent::WindowActivate)
    {
        // emit activeImgWin(this);
    }

    return QMainWindow::event(event);
}