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
#include "filter_dialog.h"



#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QImage>
#include <QRect>
#include <QMimeData>
#include <QUrl>

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

    // WA
    setAttribute(Qt::WA_AcceptTouchEvents);

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




void MainWindow::helperImgProc(const QString &process, 
                               std::function<void(QImage &)> func) {
    /* ヘルパー関数 */
    auto tp_start = high_resolution_clock::now();

    QImage img = m_pLastActiveImgWin->getDibImg();

    // 画像処理タスク
    func(img);

    m_pLastActiveImgWin->setDibImg(img);

    auto tp_end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(tp_end - tp_start).count();
    IS_DEBUG_STREAM("%s: %ld[ms]\n", process.toStdString().c_str(), duration);

    std::string status = is::common::format_string("%s: %ld[ms]", 
                                    process.toStdString().c_str(), duration);
    m_pUi->statusBar->clearMessage();
    m_pUi->statusBar->showMessage(QString::fromStdString(status));
}


//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////

/**
 * @brief ドラッグ状態でWidgetにカーソルが侵入した際のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    /*
        よく使用するMIMEタイプ
        Tester      Getter      Setter         MIME Types
        -----------------------------------------------------
        hasText()   text()      setText()      text/plain
        hasHtml()   html()      setHtml()      text/html
        hasUrls()   urls()      setUrls()      text/uri-text
        hasImages() imageData() setImageData() image/*
        hasColor()  colorData() setColorData() application/x-color
        image/* で受け付けるファイル拡張子
        bmp, fif, gif, ifm, ief, jpe, jpg, jpeg, png, svg, tif, tiff,
        mcf, rp, wbmp, ras, fh, fh4, fh5, fh7, fhc, ico, jps, pnm, pbm,
        ppm, rgb, xbm, xpm, swx, xwd
        QImageで受け付けるファイル拡張子
        bmp(R/W), gif(R), jpg(R/W), jpeg(R/W), png(R/W), pbm(R), pgm(R),
        ppm(R/W), xbm(R/W), xpm(R/W) 
    */

    IS_DEBUG_STREAM("dragEnterEvent\n");

    // mimeDataの種類を調べてドラッグ受付許可
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
        IS_DEBUG_STREAM("Accept Urls\n");
    }

    QMainWindow::dragEnterEvent(event);
}


/**
 * @brief ドラッグ状態でWindowからカーソルが外れた際のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragLeaveEvent(QDragLeaveEvent *event) {
    QMainWindow::dragLeaveEvent(event);
}

/**
 * @brief ドラッグ移動中のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragMoveEvent(QDragMoveEvent *event) {
    QMainWindow::dragMoveEvent(event);
}

/**
 * @brief ドロップイベント時の処理
 * 
 * @param event 
 */
void MainWindow::dropEvent(QDropEvent *event) {

    if (event->mimeData()->hasUrls()) {

        std::set<std::string> currImgWinFilenames;
        for (const auto& p_imgWin : getImgWinRegistry()) {
            currImgWinFilenames.insert(p_imgWin->filename().toStdString());
        }

        foreach(QUrl url, event->mimeData()->urls()) {
            if (!url.isValid()) {
                auto qStr = url.toString();
                IS_DEBUG_STREAM("Invalid URL. Given is %s\n", qStr.toStdString().c_str());
                continue;
            }

            // URLがローカルPCに存在する場合
            if (url.isLocalFile()) {
                auto qStr = url.toString();
                IS_DEBUG_STREAM("Recieve URL: %s\n", qStr.toStdString().c_str());

                auto localUrl = url.toLocalFile();
                // IS_DEBUG_STREAM("Recieve local file: %s\n", localUrl.toStdString().c_str());

                // ImageWindowを生成
                QImage img;
                if (!img.load(localUrl)) continue;

                auto tokens = localUrl.split(tr("/"));
                QString filename = tokens[tokens.size() - 1];
                std::string newFilename = 
                    getNewSerialNo(filename.toStdString(), currImgWinFilenames);
                ImageWindow *p_newImgWin = genImgWin(QString::fromStdString(newFilename));

                p_newImgWin->setDibImg(img, true, true);
            }
        }
    }

    // MainWindow::dropEvent(event);
}



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
void MainWindow::slotActiveImgWin(ImageWindow *ptr) {
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
    for (const auto& p_imgWin : getImgWinRegistry()) {
        currImgWinFilenames.insert(p_imgWin->filename().toStdString());
    }

    foreach (QString path, fileList) {
        if (!path.isEmpty()) {
            QImage img(path);
           
            auto tokens = path.split(tr("/"));
            QString filename = tokens[tokens.size() - 1];

            IS_DEBUG_STREAM("%s\n", filename.toStdString().c_str());

            std::string newFilename = getNewSerialNo(filename.toStdString(),
                                                     currImgWinFilenames);
            ImageWindow *p_newImgWin = genImgWin(QString::fromStdString(newFilename));

            p_newImgWin->setDibImg(img, true, true);
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
    
    if (new_name.isEmpty())
        return;

    auto qname = m_pLastActiveImgWin->filename();
    std::string name = qname.toStdString();
    IS_DEBUG_STREAM("Before %s\n", name.c_str());
    auto tokens = is::common::split_string(name, ".");
    QString filename = new_name + QString(".") + 
        QString::fromStdString(tokens[tokens.size() - 1]);

    IS_DEBUG_STREAM("After %s\n", filename.toStdString().c_str());
    
    m_pLastActiveImgWin->setFilename(filename);

}

/**
 * @brief Menu -> Edit -> Cut
 * 
 */
void MainWindow::slotActMenuBarEditCut() {
    // QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域のカット"), 
    //                     tr("工事中..."));

    std::map<int, QRectF> localRects = m_pLastActiveImgWin->getRectsOnDibImg();

    auto func = [&](QImage& img) -> void {

        int last = -1;

        // 最大値を取得
        for (auto iter = localRects.begin(); iter != localRects.end(); ++iter) {
            if (last < iter->first) {
                last = iter->first;
            }
        }

        if (last < 0) {
            return;
        }

        // 指定領域をコピー
        QRect roi = localRects[last].toRect();
        m_copyImg = img.copy(roi);

        // 指定領域をクリア
        int l, t, r, b;
        l = roi.x();
        t = roi.y();
        r = l + roi.width();
        b = t + roi.height();
        using byte = uchar;
        int memWidth = img.bytesPerLine();
        int memChannels = img.depth() / 8;
        int channels = (memChannels > 3) ? 3 : memChannels;
        byte *imgPtr = img.bits();
        for (int c = 0; c < channels; ++c) {
            for (int y = t; y < b; ++y) {
                for (int x = l; x < r; ++x) {
                    imgPtr[y*memWidth + memChannels*x + c] = 0; // 黒
                }
            }
        }
    };

    helperImgProc(QString("Cut"), func);
}

/**
 * @brief Menu -> Edit -> Copy
 *
 */
void MainWindow::slotActMenuBarEditCopy() {
    // QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域のコピー"),
    //                     tr("工事中..."));

    std::map<int, QRectF> localRects = m_pLastActiveImgWin->getRectsOnDibImg();

    auto func = [&](QImage& img) -> void {

        int last = -1;

        // 最大値を取得
        for (auto iter = localRects.begin(); iter != localRects.end(); ++iter) {
            if (last < iter->first) {
                last = iter->first;
            }
        }

        if (last < 0) {
            return;
        }

        // 指定領域をコピー
        QRect roi = localRects[last].toRect();
        m_copyImg = img.copy(roi);
    };

    helperImgProc(QString("Copy"), func);
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
    // QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域のクリア"),
    //                   tr("工事中..."));

    std::map<int, QRectF> localRects = m_pLastActiveImgWin->getRectsOnDibImg();

    auto func = [&](QImage &img) -> void {
        using byte = uchar;
        int l, t, r, b;
        int memWidth = img.bytesPerLine();
        int memChannels = img.depth() / 8;
        int channels = (memChannels > 3) ? 3 : memChannels;
        byte *imgPtr = img.bits();

        if (localRects.size() > 0) {
            for (const auto &roi : localRects) {
                l = roi.second.x();
                t = roi.second.y();
                r = int(l + roi.second.width());
                b = int(t + roi.second.height());
                for (int c = 0; c < channels; ++c) {
                    for (int y = t; y < b; ++y) {
                        for (int x = l; x < r; ++x) {
                            imgPtr[y*memWidth + memChannels*x + c] = 0; // 黒
                        }
                    }
                }
            }
        }
        else {
            l = 0;
            t = 0;
            r = img.width();
            b = img.height();
            for (int c = 0; c < channels; ++c) {
                for (int y = t; y < b; ++y) {
                    for (int x = l; x < r; ++x) {
                        imgPtr[y*memWidth + memChannels*x + c] = 0; // 黒
                    }
                }
            }
        }
    };

    helperImgProc(QString("Clear"), func);
}

/**
 * @brief Menu -> Edit -> Clear outside
 * 
 */
void MainWindow::slotActMenuBarEditClearOutside() {
    // QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域以外のクリア"),
    //                   tr("工事中..."));

    std::map<int, QRectF> localRects = m_pLastActiveImgWin->getRectsOnDibImg();

    auto func = [&](QImage &img) -> void {
        if (localRects.size() > 0) {
            using byte = uchar;
            int l, t, r, b;
            int memWidth = img.bytesPerLine();
            int memChannels = img.depth() / 8;
            int channels = (memChannels > 3) ? 3 : memChannels;
            byte *srcPtr = img.bits();

            QImage blackImg = img.copy();
            blackImg.fill(Qt::black);
            byte *dstPtr = blackImg.bits();

            for (const auto &roi : localRects) {
                l = roi.second.x();
                t = roi.second.y();
                r = int(l + roi.second.width());
                b = int(t + roi.second.height());

                for (int c = 0; c < channels; ++c) {
                    for (int y = t; y < b; ++y) {
                        for (int x = l; x < r; ++x) {
                            dstPtr[y*memWidth + memChannels*x + c] = 
                            srcPtr[y*memWidth + memChannels*x + c];
                        }
                    }
                }
            }

            blackImg.swap(img);
        }
    };

    helperImgProc(QString("Clear Outside"), func);
}

/**
 * @brief Menu -> Edit -> Fill
 * 
 */
void MainWindow::slotActMenuBarEditFill() {
    QMessageBox::warning(m_pLastActiveImgWin, tr("ROI領域の色指定"),
                          tr("工事中..."));

    auto color = QColorDialog::getColor();
}

/**
 * @brief Menu -> Edit -> Invert
 * 
 */
void MainWindow::slotActMenuBarEditInvert() {
    // QMessageBox::warning(m_pLastActiveImgWin, tr("色反転"), 
    //                         tr("工事中..."));

    std::map<int, QRectF> localRects = m_pLastActiveImgWin->getRectsOnDibImg();

    auto func = [&](QImage &img) -> void {

        if (localRects.size() > 0) {
            using byte = uchar;
            int l, t, r, b;
            int memWidth = img.bytesPerLine();
            int memChannels = img.depth() / 8;
            int channels = (memChannels > 3) ? 3 : memChannels;
            byte *imgPtr = img.bits();
            for (const auto &roi : localRects) {
                l = roi.second.x();
                t = roi.second.y();
                r = int(l + roi.second.width());
                b = int(t + roi.second.height());

                for (int c = 0; c < channels; ++c) {
                    for (int y = t; y < b; ++y) {
                        for (int x = l; x < r; ++x) {
                            byte& v = imgPtr[y*memWidth + memChannels*x + c];
                            v = 255 - v;
                        }
                    }
                }
            }
        }
        else {
            img.invertPixels();
        }
    };

    helperImgProc(QString("Clear"), func);
}

/**
 * @brief Menu -> Image -> Type
 * 
 */
void MainWindow::slotActMenuBarImageType() {
    auto p_ui = m_pLastActiveImgWin->ui();

    p_ui->actionCvt8bit->setChecked(false);
    p_ui->actionCvt24bit->setChecked(false);
    p_ui->actionCvtRGBA->setChecked(false);

    QImage::Format format;

    if (sender() == p_ui->actionCvt8bit) {
        p_ui->actionCvt8bit->setChecked(true);
        format = QImage::Format_Grayscale8;
    } 
    else if (sender() == p_ui->actionCvt24bit) {
        p_ui->actionCvt24bit->setChecked(true);
        format = QImage::Format_RGB888;
    }
    else if (sender() == p_ui->actionCvtRGBA) {
        p_ui->actionCvtRGBA->setChecked(true);
        format = QImage::Format_RGBA8888;
    }

    auto func = [&](QImage &img) -> void {
        img = img.convertToFormat(format);
    };

    helperImgProc(QString("Type"), func);
}


/**
 * @brief Menu -> Image -> ShowInfo
 * 
 */
void MainWindow::slotActMenuBarImageShowInfo() {

}


/**
 * @brief Menu -> Image -> Color
 * 
 */
void MainWindow::slotActMenuBarImageColor() {

    auto sender = this->sender();
    if (sender == m_pLastActiveImgWin->ui()->actionRGBToGray) {
        IS_DEBUG_STREAM("RGB -> Gray\n");
    }
    else if (sender == m_pLastActiveImgWin->ui()->actionGrayToRGB) {
        IS_DEBUG_STREAM("Gray -> RGB\n");
    }
    else if (sender == m_pLastActiveImgWin->ui()->actionRGBToHSV) {
        IS_DEBUG_STREAM("RGB -> HSV\n");
    }
    else if (sender == m_pLastActiveImgWin->ui()->actionHSVToRGB) {
        IS_DEBUG_STREAM("HSV -> RGB\n");
    }
    else if (sender == m_pLastActiveImgWin->ui()->actionRGBToYUV) {
        IS_DEBUG_STREAM("RGB -> YUV\n");
    }
    // else if (sender == m_pLastActiveImgWin->ui()->actionYUVToRGB) {
        
    // }
}

/**
 * @brief Menu -> Image -> Border
 * 
 */
void MainWindow::slotActMenuBarImageBorder() {

}


/**
 * @brief 
 * 
 */
void MainWindow::slotActMenuBarImageTransform() {

}


/**
 * @brief Menu -> Image -> Crop
 * 
 */
void MainWindow::slotActMenuBarImageCrop() {
    std::map<int, QRectF> localRects = m_pLastActiveImgWin->getRectsOnDibImg();
    QImage img = m_pLastActiveImgWin->getDibImg();

    for (const auto& roi : localRects) {
        auto filename = m_pLastActiveImgWin->filename();
        int pos = filename.lastIndexOf(tr("."));
        auto name = filename.left(pos);
        auto ext = filename.mid(pos + 1);
        filename = name + tr("_crop.") + ext;

        ImageWindow *p_newImgWin = genImgWin(filename);

        QImage cropedImg = img.copy(roi.second.toRect());

        p_newImgWin->setDibImg(cropedImg, true, true);
    }
}


/**
 * @brief Menu -> Image -> Duplicate
 * 
 */
void MainWindow::slotActMenuBarImageDuplicate() {
    std::set<std::string> currImgWinFilenames;
    for (const auto &p_imgWin : getImgWinRegistry()) {
        currImgWinFilenames.insert(p_imgWin->filename().toStdString());
    }

    auto filename = m_pLastActiveImgWin->filename();
    int pos = filename.lastIndexOf(tr("."));
    auto name = filename.left(pos);
    auto ext = filename.mid(pos + 1);

    pos = name.indexOf(tr("-"));
    if (pos > 0) {
        name = name.left(pos);
    }
    IS_DEBUG_STREAM("Duplicate %s.%s\n", 
                    name.toStdString().c_str(),
                    ext.toStdString().c_str());

    QImage img = m_pLastActiveImgWin->getDibImg().copy();

    filename = name + tr(".") + ext;
    std::string newFilename = getNewSerialNo(filename.toStdString(), currImgWinFilenames);
    ImageWindow *p_newImgWin = genImgWin(QString::fromStdString(newFilename));

    p_newImgWin->setDibImg(img, true, true);
}


/**
 * @brief Menu -> Process -> Filter
 * 
 */
void MainWindow::slotActMenuBarFilter() {
    auto p_filter_dlg = new FilterDialog(m_pLastActiveImgWin);
    p_filter_dlg->show();
    p_filter_dlg->activateWindow();
}


//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////

/**
 * @brief Menu -> Camera
 * 
 */
void MainWindow::slotActMenuBarCameraWindow() {
    QMessageBox::warning(m_pLastActiveImgWin, tr("Camera"), 
                        tr("工事中..."));
}