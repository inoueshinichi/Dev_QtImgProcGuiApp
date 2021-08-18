#pragma once

#include "ui_ImageWindow.h"

#include <QMainWindow>
#include <QEvent>
#include <QString>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageWindow; }
QT_END_NAMESPACE

class ImageWindow : public QMainWindow
{
    Q_OBJECT

    Ui::ImageWindow *ui;
    QLabel *permanentStatusBar;

public:
    ImageWindow(QWidget *parent = nullptr);
    virtual ~ImageWindow();

protected:
    // virtual bool event(QEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

};