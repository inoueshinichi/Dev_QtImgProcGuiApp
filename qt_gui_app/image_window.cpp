
#include "image_window.h"
#include "main_window.h"

#include <string>
#include <iostream>

ImageWindow::ImageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageWindow())
    , permanentStatusBar(new QLabel())
{
    // ui
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // view
    scene = new ImageScene(this);
    ui->graphicsViewImage->setScene(scene);

    // statusbar
    permanentStatusBar->setText("SceneRect (0, 0, 0, 0)");
    ui->statusbar->addPermanentWidget(permanentStatusBar);

    /*Singal/Slot*/
    customConnection();

}

ImageWindow::~ImageWindow()
{
    if (ui) delete ui;
    if (scene) delete scene;
}

void ImageWindow::customConnection()
{
    /* ImageWindow -> MainWindow */
    connect(this, &ImageWindow::eraseImageWindow, (MainWindow *)(this->parent()), &MainWindow::slotEraseImageWindow);
}

void ImageWindow::closeEvent(QCloseEvent *event)
{
    /*登録解除*/
    emit eraseImageWindow(this);
}