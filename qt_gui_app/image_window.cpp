
#include "image_window.h"
#include "main_window.h"

#include <string>

ImageWindow::ImageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageWindow())
    , permanentStatusBar(new QLabel())
{
    ui->setupUi(this);

    // カウント
    permanentStatusBar->setText(QString::number(MainWindow::getImgWinRegistory().size()));
    ui->statusbar->addWidget(permanentStatusBar);
}

ImageWindow::~ImageWindow()
{
    if (ui) delete ui;
}

void ImageWindow::closeEvent(QCloseEvent *event)
{
    MainWindow::getImgWinRegistory().erase(reinterpret_cast<uintptr_t>(this)); // 削除
}