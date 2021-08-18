#pragma once


#include "image_window.h"

#include <QMainWindow>
#include <QImage>
#include <QString>

#include <map>


QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;

private:
    
    void menubarConnection();
    // void toolbarConnection();
    // void uiConnection();
    // void customConnection();
    
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    /*ImageWindow*/
    using ImgWinRegistory_t = std::map<uintptr_t, ImageWindow*>;
    static ImgWinRegistory_t& getImgWinRegistory();

signals:

public slots:

private slots:

    /* Menu -> File */
    void slotActMenubarFileNew();
    void slotActMenubarFileOpen();
    void slotActMenubarFileClose();
    void slotActMenubarFileCloseAll();
    void slotActMenubarFileSave();
    void slotActMenubarFileSaveAs();
    void slotActMenubarFilePrint();
    void slotActMenubarFileQuit();
};
