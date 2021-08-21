
#include "image_window.h"
#include "main_window.h"

#include <cstring>
#include <ctime>
#include <string>
#include <iostream>

ImageWindow::ImageWindow(QWidget *p_parent)
    : QMainWindow(p_parent)
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

void ImageWindow::setFilename(const QString& filename)
{
    /*ファイル名 + 時間*/

    // 時間取得
    char timeString[256];
    std::memset((void *)&timeString, '\0', sizeof(timeString));
    time_t theTime = time(nullptr);
    struct tm *stm = localtime(&theTime);
    if (theTime == -1 || stm == nullptr)
    {
        std::snprintf(timeString, 256, "Unknown");
    }
    else
    {
        strftime(timeString, 256, "%Y-%m-%d %H:%M ", stm);
    }
    QString timeNow(timeString);
    this->setWindowTitle(timeNow + filename);
    m_filename = filename;
}

QString ImageWindow::filename() const { return m_filename; }


// void ImageWindow::toggleCrossLine(bool isShow)
// {
//     /*マウスの十字線の表示切り替え*/
//     m_pScene->> toggleCrossLine(isShow);
// }


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