/**
 * @file main_window.cpp
 * @author your name (you@domain.com)
 * @brief Qt 自作MainWindowのSourceファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ui_MainWindow.h"
#include "main_window.h"

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QImage>

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <filesystem>
namespace fs = std::filesystem;
#include <chrono>
using namespace std::chrono;


//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_pUi(new Ui::MainWindow())
    , m_pStatusBarLabel(new QLabel())
    , m_pLastActiveImgWin(nullptr) {
    // UI
    m_pUi->setupUi(this);

    /* Signal & Slot */
    menuBarConnection();
}

MainWindow::~MainWindow() {
    if (m_pUi) {
        delete m_pUi;
        m_pUi = nullptr;
    }
}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

/**
 * @brief MenuBarのSignal/Slot接続
 * 
 */
void MainWindow::menuBarConnection() {
    /* Menu -> File */
    // New
    connect(m_pUi->actionNew, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileNew);

    // Open
    connect(m_pUi->actionOpen, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileOpen);

    // Close All
    connect(m_pUi->actionCloseAll, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileCloseAll);

    // Print
    connect(m_pUi->actionPrint, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFilePrint);
    // Quit
    connect(m_pUi->actionQuit, &QAction::triggered,
            this, &MainWindow::slotActMenuBarFileQuit);
    
}

/**
 * @brief ToolBarに関するSignal/Slot接続
 * 
 */
void MainWindow::toolBarConnection() {
//    // 右クリックでToolBarを非表示にできないようにする
//     m_pUi->toolBar->toggleViewAction()->setEnabled(false);
}

void MainWindow::uiConnection() {

}

void MainWindow::customConnection() {

}

/**
 * @brief ドラッグ開始時の処理
 * 
 */
void MainWindow::startDragProcess(Qt::DropActions *dropActions, QMouseEvent *event) {

}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////

/**
 * @brief ドラッグ状態でWindowにカーソルが侵入した際のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{}


/**
 * @brief ドラッグ状態でWindowからカーソルが外れた際のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{}

    /**
 * @brief ドラッグ移動中のイベント処理
 * 
 * @param event 
 */
    void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{}

/**
 * @brief ドロップイベント時の処理
 * 
 * @param event 
 */
    void MainWindow::dropEvent(QDropEvent *event)
{}

/**
 * @brief マウス移動時のイベント処理
 * 
 * @param event 
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

MainWindow::ImgWinRegistry_t &MainWindow::getImgWinRegistry() {
    static ImgWinRegistry_t imgWindowBacket;
    return imgWindowBacket;
}

/**
 * @brief 新規でImageWindowを生成
 * 
 * @param filename 
 * @return ImageWindow* 
 */
ImageWindow* MainWindow::genImgWin(const QString &filename) {
    ImageWindow *p_imgWin = new ImageWindow(this);
    p_imgWin->setFilename(filename);
    getImgWinRegistry().insert(p_imgWin);
    p_imgWin->show();
    p_imgWin->activateWindow();

    m_pStatusBarLabel->setText(QString::number(getImgWinRegistry().size()));
    m_pUi->statusBar->addPermanentWidget(m_pStatusBarLabel);

    return p_imgWin;
}

//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

/**
 * @brief 指定のImageWindowの登録を解除
 * 
 * @param ptr 
 */
void MainWindow::slotRmImgWin(ImageWindow *ptr) {
    getImgWinRegistry().erase(ptr);
    size_t count = getImgWinRegistry().size();
    m_pStatusBarLabel->setText(QString::number(count));
    m_pUi->statusBar->addPermanentWidget(m_pStatusBarLabel);

    IS_DEBUG_STREAM("Erase a image window. Given is %p.\n", (void *)ptr);

    if (m_pLastActiveImgWin == ptr) {
        m_pLastActiveImgWin = nullptr;
    }
}


/**
 * @brief アクティブウィンドウの更新
 * 
 * @param ptr 
 */
void MainWindow::slotActiveImgWin(ImageWindow *ptr)
{
    m_pLastActiveImgWin = ptr;
}

/**
 * @brief Menu -> File -> New
 * 
 */
void MainWindow::slotActMenuBarFileNew() {
    genImgWin(tr("New Empty"));
}

/**
 * @brief Menu -> File -> Open
 * 
 */
void MainWindow::slotActMenuBarFileOpen() {
    QString cwdPath = QString::fromStdString(fs::current_path().string());
    QString fileFilter = tr("画像(*.bmp *.jpg *.jpeg *.png *.tiff)");
    auto fileList = QFileDialog::getOpenFileNames(this,
                                                  tr("画像ファイルを開く"), 
                                                  cwdPath, 
                                                  fileFilter);

    std::set<std::string> currImgWinFilenames;
    for (const auto &p_imgWin : getImgWinRegistry()) {
        currImgWinFilenames.insert(p_imgWin->filename().toStdString());
    }

    foreach (QString path, fileList) {
        if (!path.isEmpty()) {
            QImage img(path);
            int depth = img.bitPlaneCount();
            bool isGray = img.isGrayscale();
            if (isGray && depth == 8) {
                img = img.convertToFormat(QImage::Format_Grayscale8);
            } else if (depth == 24 || depth == 32) {
                
                img = img.convertToFormat(QImage::Format_RGB888); // 透明度は破棄
            }
            else {
                throw std::runtime_error("No support image format.");
            }

            auto tokens = path.split(tr("/"));
            QString filename = tokens[tokens.size() - 1];

            IS_DEBUG_STREAM("%s\n", filename.toStdString().c_str());

            std::string newFilename = getNewSerialNo(filename.toStdString(),
                                                     currImgWinFilenames);
            ImageWindow *p_newImgWin = genImgWin(QString::fromStdString(newFilename));

            if (isGray && depth == 8) {
              p_newImgWin->ui()->actionCvt8bit->setChecked(true);
            }
            else if (isGray && depth == 24) {
              p_newImgWin->ui()->actionCvt24bit->setChecked(true);
            }
            else {
              p_newImgWin->ui()->actionCvtRGB->setChecked(true);
            }

            p_newImgWin->scene()->clear();
            p_newImgWin->scene()->setDibImg(img);
        }
    }
}

/**
 * @brief Menu -> File -> Close
 * 
 */
void MainWindow::slotActMenuBarFileClose() {
    auto &registry = getImgWinRegistry();
    if (m_pLastActiveImgWin) {
        m_pLastActiveImgWin->close();
        registry.erase(m_pLastActiveImgWin);
        m_pLastActiveImgWin = nullptr;
    }
}

/**
 * @brief Menu -> File -> Close all
 * 
 */
void MainWindow::slotActMenuBarFileCloseAll() {
    auto &registry = getImgWinRegistry();
    std::vector<ImageWindow *> tmpWins;
    for (auto iter = registry.begin(); iter != registry.end(); ++iter) {
        tmpWins.push_back(*iter);
    }
    registry.clear();

    for (size_t i = 0; i < tmpWins.size(); ++i) {
        tmpWins[i]->close();
        tmpWins[i] = nullptr;
    }
}

/**
 * @brief Menu -> File -> Save
 * 
 */
void MainWindow::slotActMenuBarFileSave() {
    auto qimg = m_pLastActiveImgWin->scene()->getDibImg();
    if (!qimg.isNull()) {
        auto filename = m_pLastActiveImgWin->filename();
        QString cwd = QString::fromStdString(fs::current_path().string());
        auto path = cwd + tr("/") + filename;

        auto savepath = QFileDialog::getSaveFileName(
            nullptr, 
            tr("画像の保存"), 
            path,
            tr("画像(*.bmp *.jpeg *.jpg *.png *.tiff)"));

        if (!savepath.isNull()) {
          IS_DEBUG_STREAM("%s\n", savepath.toStdString().c_str());
          qimg.save(savepath);
        }
    }
    else {
      QMessageBox::warning(m_pLastActiveImgWin, 
                            tr("画像の保存"),
                            tr("画像がありません."));
    }
}

/**
 * @brief Menu -> File -> Save as
 * 
 */
void MainWindow::slotActMenuBarFileSaveAs() {
   if (sender() == m_pLastActiveImgWin->ui()->actionSaveAsCsv) {
    IS_DEBUG_STREAM("Save As Csv\n");
   } else if (sender() == m_pLastActiveImgWin->ui()->actionSaveAsTsv) {
     IS_DEBUG_STREAM("Save As Tsv\n");
   }
}

/**
 * @brief Menu -> File -> Print
 * 
 */
void MainWindow::slotActMenuBarFilePrint() {
  QMessageBox::warning(m_pLastActiveImgWin, tr("画像の印刷"), tr("工事中..."));
}

/**
 * @brief Menu -> File -> Quit
 * 
 */
void MainWindow::slotActMenuBarFileQuit() {
    
    QApplication::closeAllWindows();
}

/**
 * @brief Menu -> Edit -> Undo
 * 
 */
void MainWindow::slotActMenuBarEditUndo() {
    QMessageBox::warning(m_pLastActiveImgWin, tr("Undo"), tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Rename
 * 
 */
void MainWindow::slotActMenuBarEditRename() {
    auto new_name = QInputDialog::getText(m_pLastActiveImgWin, 
                                        tr("画像ファイル名の変更"),
                                        tr("新しいファイル名"));
    m_pLastActiveImgWin->setFilename(new_name);

}

/**
 * @brief Menu -> Edit -> Cut
 * 
 */
void MainWindow::slotActMenuBarEditCut() {
  QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域のカット"), 
                       tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Copy
 *
 */
void MainWindow::slotActMenuBarEditCopy() {
  QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域のコピー"),
                       tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Paste
 * 
 */
void MainWindow::slotActMenuBarEditPaste() {
  QMessageBox::warning(m_pLastActiveImgWin, tr("指定ポイントを中心する貼り付け"),
                      tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Clear
 * 
 */
void MainWindow::slotActMenuBarEditClear() {
  QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域のクリア"),
                      tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Clear outside
 * 
 */
void MainWindow::slotActMenuBarEditClearOutside() {
  QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域以外のクリア"),
                      tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Fill
 * 
 */
void MainWindow::slotActMenuBarEditFill() {
  QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域の色指定"),
                      tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Invert
 * 
 */
void MainWindow::slotActMenuBarEditInvert() {
  QMessageBox::warning(m_pLastActiveImgWin, tr("色反転"),
                      tr("工事中..."));
}

/**
 * @brief Menu -> Image -> Type
 * 
 */
void MainWindow::slotActMenuBarImageType() {
    auto p_ui = m_pLastActiveImgWin->ui();

    p_ui->actionCvt8bit->setChecked(false);
    p_ui->actionCvt24bit->setChecked(false);
    p_ui->actionCvtRGB->setChecked(false);

    QImage::Format format;

    if (sender() == p_ui->actionCvt8bit) {
        p_ui->actionCvt8bit->setChecked(true);
        format = QImage::Format_Grayscale8;
    } 
    else if (sender() == p_ui->actionCvt24bit) {
        p_ui->actionCvt24bit->setChecked(true);
        format = QImage::Format_RGB888;
    }
    else if (sender() == p_ui->actionCvtRGB) {
        p_ui->actionCvtRGB->setChecked(true);
        format = QImage::Format_RGB32;
    }

    auto tp_start = high_resolution_clock::now();

    auto qimg = m_pLastActiveImgWin->scene()->getDibImg();
    m_pLastActiveImgWin->scene()->setDibImg(qimg.convertToFormat(format).copy());

    auto tp_end = high_resolution_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(tp_end - tp_start).count();

    m_pUi->statusBar->clearMessage();
    QString msg = QString::fromStdString(
        is::common::format_string("Type response: %.3f[ms]", elapsedTime));
    m_pUi->statusBar->showMessage(msg);
}


//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////

void
MainWindow::slotSelectInputDir() {}

void MainWindow::slotSelectOutputDir()
{}

