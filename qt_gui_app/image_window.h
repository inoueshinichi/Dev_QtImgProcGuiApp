#pragma once

#include "ui_ImageWindow.h"
#include "image_view.h"
#include "image_scene.h"

#include <QMainWindow>
#include <QEvent>
#include <QString>
#include <QLabel>
#include <Qt>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageWindow; }
QT_END_NAMESPACE

class ImageWindow : public QMainWindow
{
    Q_OBJECT

    Ui::ImageWindow *ui;
    ImageScene* scene;
    QLabel *permanentStatusBar;
    QString filename;

    void customConnection();

public:
    explicit ImageWindow(QWidget *parent = nullptr);
    virtual ~ImageWindow();

protected:
    // virtual bool event(QEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void eraseImageWindow(ImageWindow *ptr);

};