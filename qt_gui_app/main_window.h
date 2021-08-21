#pragma once


#include "image_window.h"

#include <QMainWindow>
#include <QImage>
#include <QString>
#include <QLabel>

#include <set>


QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
    Ui::MainWindow *m_pUi;
    QLabel* m_pStatusBarLabel;
    ImageWindow* m_pLastActiveImgWin;

private:
    
    void menubarConnection();
    // void toolbarConnection();
    // void uiConnection();
    // void customConnection();
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    /*ImageWindow*/
    using ImgWinRegistory_t = std::set<ImageWindow*>;
    static ImgWinRegistory_t& getImgWinRegistory();

signals:
    
public slots:
    void slotRmImgWin(ImageWindow *ptr);
    void slotActiveImgWin(ImageWindow *ptr);

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
