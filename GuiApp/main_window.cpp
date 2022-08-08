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
#include "image_window.h"
#include "filter_dialog.h"
#include "image_scene.h"



#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QImage>
#include <QRect>
#include <QMimeData>
#include <QUrl>

#include <Qt>
#include <QLabel>
#include <QString>
#include <QDrag>
#include <QEvent>
#include <QMessageBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QDialog>
#include <QInputDialog>
#include <QColorDialog>

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
    , mUi(new Ui::MainWindow())
    , mStatusBarLabel(new QLabel())
    , mLastActiveImgWin(nullptr) 
{
    // UI
    mUi->setupUi(this);

    // WA
    setAttribute(Qt::WA_AcceptTouchEvents);

    /* Signal & Slot */
    MenuBarConnection();
}

MainWindow::~MainWindow() 
{
    if (mUi) 
    {
        delete mUi;
        mUi = nullptr;
    }
}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////

/**
 * @brief MenuBarのSignal/Slot接続
 * 
 */
void MainWindow::MenuBarConnection() 
{
    /* Menu -> File */

    // New
    connect(mUi->actionNew, &QAction::triggered,
            this, &MainWindow::SlotActMenuBarFileNew);

    // Open
    connect(mUi->actionOpen, &QAction::triggered,
            this, &MainWindow::SlotActMenuBarFileOpen);

    // Close All
    connect(mUi->actionCloseAll, &QAction::triggered,
            this, &MainWindow::SlotActMenuBarFileCloseAll);

    // Print
    connect(mUi->actionPrint, &QAction::triggered,
            this, &MainWindow::SlotActMenuBarFilePrint);

    // Quit
    connect(mUi->actionQuit, &QAction::triggered,
            this, &MainWindow::SlotActMenuBarFileQuit);

}

/**
 * @brief ToolBarに関するSignal/Slot接続
 * 
 */
void MainWindow::ToolBarConnection() 
{
//    // 右クリックでToolBarを非表示にできないようにする
//     mUi->toolBar->toggleViewAction()->setEnabled(false);
}

void MainWindow::UiConnection() {}

void MainWindow::CustomConnection() {}


void MainWindow::HelperImgProc(const QString& process, 
                               std::function<void(QImage &)> func) 
{
    /* ヘルパー関数 */
    auto tp_start = high_resolution_clock::now();

    QImage img = mLastActiveImgWin->GetDibImg();

    // 画像処理タスク
    func(img);

    mLastActiveImgWin->SetDibImg(img);

    auto tp_end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(tp_end - tp_start).count();
    IS_DEBUG_STREAM("%s: %ld[ms]\n", process.toStdString().c_str(), duration);

    std::string status = is::common::format_string("%s: %ld[ms]", 
                                    process.toStdString().c_str(), duration);
    mUi->statusBar->clearMessage();
    mUi->statusBar->showMessage(QString::fromStdString(status));
}


//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////

/**
 * @brief ドラッグ状態でWidgetにカーソルが侵入した際のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragEnterEvent(QDragEnterEvent *event) 
{
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
    if (event->mimeData()->hasUrls()) 
    {
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
void MainWindow::dragLeaveEvent(QDragLeaveEvent *event) 
{
    QMainWindow::dragLeaveEvent(event);
}

/**
 * @brief ドラッグ移動中のイベント処理
 * 
 * @param event 
 */
void MainWindow::dragMoveEvent(QDragMoveEvent *event) 
{
    QMainWindow::dragMoveEvent(event);
}

/**
 * @brief ドロップイベント時の処理
 * 
 * @param event 
 */
void MainWindow::dropEvent(QDropEvent *event) 
{
    if (event->mimeData()->hasUrls()) 
    {
        std::set<std::string> currImgWinFilenames;
        for (const auto& imgWin : GetImgWinRegistry()) 
        {
            currImgWinFilenames.insert(imgWin->Filename().toStdString());
        }

        foreach(QUrl url, event->mimeData()->urls()) 
        {
            if (!url.isValid()) 
            {
                auto qStr = url.toString();
                IS_DEBUG_STREAM("Invalid URL. Given is %s\n", qStr.toStdString().c_str());
                continue;
            }

            // URLがローカルPCに存在する場合
            if (url.isLocalFile()) 
            {
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
                    GetNewSerialNo(filename.toStdString(), currImgWinFilenames);
                ImageWindow *p_newImgWin = GenImgWin(QString::fromStdString(newFilename));

                p_newImgWin->SetDibImg(img, true, true);
            }
        }
    }

    // MainWindow::dropEvent(event);
}



//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

MainWindow::ImgWinRegistry_t &MainWindow::GetImgWinRegistry() 
{
    static ImgWinRegistry_t imgWindowBacket;
    return imgWindowBacket;
}

/**
 * @brief 新規でImageWindowを生成
 * 
 * @param filename 
 * @return ImageWindow* 
 */
ImageWindow* MainWindow::GenImgWin(const QString &filename) 
{
    ImageWindow *imgWin = new ImageWindow(this);
    imgWin->SetFilename(filename);
    GetImgWinRegistry().insert(imgWin);
    imgWin->show();
    imgWin->activateWindow();

    mStatusBarLabel->setText(QString::number(GetImgWinRegistry().size()));
    mUi->statusBar->addPermanentWidget(mStatusBarLabel);

    return imgWin;
}

//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////

/**
 * @brief 指定のImageWindowの登録を解除
 * 
 * @param ptr 
 */
void MainWindow::SlotRmImgWin(ImageWindow *ptr) 
{
    GetImgWinRegistry().erase(ptr);
    size_t count = GetImgWinRegistry().size();
    mStatusBarLabel->setText(QString::number(count));
    mUi->statusBar->addPermanentWidget(mStatusBarLabel);

    IS_DEBUG_STREAM("Erase a image window. Given is %p.\n", (void *)ptr);

    if (mLastActiveImgWin == ptr) 
    {
        mLastActiveImgWin = nullptr;
    }
}


/**
 * @brief アクティブウィンドウの更新
 * 
 * @param ptr 
 */
void MainWindow::SlotActiveImgWin(ImageWindow *ptr) 
{
    mLastActiveImgWin = ptr;
}

/**
 * @brief Menu -> File -> New
 * 
 */
void MainWindow::SlotActMenuBarFileNew() 
{
    GenImgWin(tr("New Empty"));
}

/**
 * @brief Menu -> File -> Open
 * 
 */
void MainWindow::SlotActMenuBarFileOpen() 
{
    QString cwdPath = QString::fromStdString(fs::current_path().string());
    QString fileFilter = tr("画像(*.bmp *.jpg *.jpeg *.png *.tiff)");
    auto fileList = QFileDialog::getOpenFileNames(this,
                                                  tr("画像ファイルを開く"), 
                                                  cwdPath, 
                                                  fileFilter);

    std::set<std::string> currImgWinFilenames;
    for (const auto& imgWin : GetImgWinRegistry()) 
    {
        currImgWinFilenames.insert(imgWin->Filename().toStdString());
    }

    foreach (QString path, fileList) 
    {
        if (!path.isEmpty()) 
        {
            QImage img(path);
           
            auto tokens = path.split(tr("/"));
            QString filename = tokens[tokens.size() - 1];

            IS_DEBUG_STREAM("%s\n", filename.toStdString().c_str());

            std::string newFilename = GetNewSerialNo(filename.toStdString(),
                                                     currImgWinFilenames);
            ImageWindow *newImgWin = GenImgWin(QString::fromStdString(newFilename));

            newImgWin->SetDibImg(img, true, true);
        }
    }
}

/**
 * @brief Menu -> File -> Close
 * 
 */
void MainWindow::SlotActMenuBarFileClose() 
{
    auto &registry = GetImgWinRegistry();
    if (mLastActiveImgWin) 
    {
        mLastActiveImgWin->close();
        registry.erase(mLastActiveImgWin);
        mLastActiveImgWin = nullptr;
    }
}

/**
 * @brief Menu -> File -> Close all
 * 
 */
void MainWindow::SlotActMenuBarFileCloseAll() 
{
    auto &registry = GetImgWinRegistry();
    std::vector<ImageWindow *> tmpWins;
    for (auto iter = registry.begin(); iter != registry.end(); ++iter) 
    {
        tmpWins.push_back(*iter);
    }
    registry.clear();

    for (size_t i = 0; i < tmpWins.size(); ++i) 
    {
        tmpWins[i]->close();
        tmpWins[i] = nullptr;
    }
}

/**
 * @brief Menu -> File -> Save
 * 
 */
void MainWindow::SlotActMenuBarFileSave() 
{
    auto qimg = mLastActiveImgWin->Scene()->GetDibImg();
    if (!qimg.isNull()) 
    {
        auto filename = mLastActiveImgWin->Filename();
        QString cwd = QString::fromStdString(fs::current_path().string());
        auto path = cwd + tr("/") + filename;

        auto savepath = QFileDialog::getSaveFileName(
            nullptr, 
            tr("画像の保存"), 
            path,
            tr("画像(*.bmp *.jpeg *.jpg *.png *.tiff)"));

        if (!savepath.isNull()) 
        {
          IS_DEBUG_STREAM("%s\n", savepath.toStdString().c_str());
          qimg.save(savepath);
        }
    }
    else 
    {
      QMessageBox::warning(mLastActiveImgWin, 
                            tr("画像の保存"),
                            tr("画像がありません."));
    }
}

/**
 * @brief Menu -> File -> Save as
 * 
 */
void MainWindow::SlotActMenuBarFileSaveAs() 
{
   if (sender() == mLastActiveImgWin->Ui()->actionSaveAsCsv) 
   {
      IS_DEBUG_STREAM("Save As Csv\n");
   } else if (sender() == mLastActiveImgWin->Ui()->actionSaveAsTsv) 
   {
      IS_DEBUG_STREAM("Save As Tsv\n");
   }
}

/**
 * @brief Menu -> File -> Print
 * 
 */
void MainWindow::SlotActMenuBarFilePrint() 
{
  QMessageBox::warning(mLastActiveImgWin, tr("画像の印刷"), tr("工事中..."));
}

/**
 * @brief Menu -> File -> Quit
 * 
 */
void MainWindow::SlotActMenuBarFileQuit() 
{    
    QApplication::closeAllWindows();
}

/**
 * @brief Menu -> Edit -> Undo
 * 
 */
void MainWindow::SlotActMenuBarEditUndo() 
{
    QMessageBox::warning(mLastActiveImgWin, tr("Undo"), tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Rename
 * 
 */
void MainWindow::SlotActMenuBarEditRename() 
{
    auto new_name = QInputDialog::getText(mLastActiveImgWin, 
                                        tr("画像ファイル名の変更"),
                                        tr("新しいファイル名"));
    
    if (new_name.isEmpty())
        return;

    auto qname = mLastActiveImgWin->Filename();
    std::string name = qname.toStdString();
    IS_DEBUG_STREAM("Before %s\n", name.c_str());
    auto tokens = is::common::split_string(name, ".");
    QString filename = new_name + QString(".") + 
        QString::fromStdString(tokens[tokens.size() - 1]);

    IS_DEBUG_STREAM("After %s\n", filename.toStdString().c_str());
    
    mLastActiveImgWin->SetFilename(filename);

}

/**
 * @brief Menu -> Edit -> Cut
 * 
 */
void MainWindow::SlotActMenuBarEditCut() 
{
    // QMessageBox::warning(mLastActiveImgWin, tr("ROI領域のカット"), 
    //                     tr("工事中..."));

    std::map<int, QRectF> localRects = mLastActiveImgWin->GetRectsOnDibImg();

    auto func = [&](QImage& img) -> void {

        int last = -1;

        // 最大値を取得
        for (auto iter = localRects.begin(); iter != localRects.end(); ++iter) 
        {
            if (last < iter->first) 
            {
                last = iter->first;
            }
        }

        if (last < 0) return;

        // 指定領域をコピー
        QRect roi = localRects[last].toRect();
        mCopyImg = img.copy(roi);

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
        for (int c = 0; c < channels; ++c) 
        {
            for (int y = t; y < b; ++y) 
            {
                for (int x = l; x < r; ++x) 
                {
                    imgPtr[y*memWidth + memChannels*x + c] = 0; // 黒
                }
            }
        }
    };

    HelperImgProc(QString("Cut"), func);
}

/**
 * @brief Menu -> Edit -> Copy
 *
 */
void MainWindow::SlotActMenuBarEditCopy() 
{
    // QMessageBox::warning(mLastActiveImgWin, tr("ROI領域のコピー"),
    //                     tr("工事中..."));

    std::map<int, QRectF> localRects = mLastActiveImgWin->GetRectsOnDibImg();

    auto func = [&](QImage& img) -> void {

        int last = -1;

        // 最大値を取得
        for (auto iter = localRects.begin(); iter != localRects.end(); ++iter) 
        {
            if (last < iter->first) last = iter->first;
        }

        if (last < 0) return;

        // 指定領域をコピー
        QRect roi = localRects[last].toRect();
        mCopyImg = img.copy(roi);
    };

    HelperImgProc(QString("Copy"), func);
}

/**
 * @brief Menu -> Edit -> Paste
 * 
 */
void MainWindow::SlotActMenuBarEditPaste() 
{
  QMessageBox::warning(mLastActiveImgWin, tr("指定ポイントを中心する貼り付け"),
                      tr("工事中..."));
}

/**
 * @brief Menu -> Edit -> Clear
 * 
 */
void MainWindow::SlotActMenuBarEditClear() 
{
    // QMessageBox::warning(mLastActiveImgWin, tr("ROI領域のクリア"),
    //                   tr("工事中..."));

    std::map<int, QRectF> localRects = mLastActiveImgWin->GetRectsOnDibImg();

    auto func = [&](QImage &img) -> void {
        using byte = uchar;
        int l, t, r, b;
        int memWidth = img.bytesPerLine();
        int memChannels = img.depth() / 8;
        int channels = (memChannels > 3) ? 3 : memChannels;
        byte *imgPtr = img.bits();

        if (localRects.size() > 0) 
        {
            for (const auto &roi : localRects) 
            {
                l = roi.second.x();
                t = roi.second.y();
                r = int(l + roi.second.width());
                b = int(t + roi.second.height());
                for (int c = 0; c < channels; ++c) 
                {
                    for (int y = t; y < b; ++y) 
                    {
                        for (int x = l; x < r; ++x) 
                        {
                            imgPtr[y*memWidth + memChannels*x + c] = 0; // 黒
                        }
                    }
                }
            }
        }
        else 
        {
            l = 0;
            t = 0;
            r = img.width();
            b = img.height();
            for (int c = 0; c < channels; ++c) 
            {
                for (int y = t; y < b; ++y) 
                {
                    for (int x = l; x < r; ++x) 
                    {
                        imgPtr[y*memWidth + memChannels*x + c] = 0; // 黒
                    }
                }
            }
        }
    };

    HelperImgProc(QString("Clear"), func);
}

/**
 * @brief Menu -> Edit -> Clear outside
 * 
 */
void MainWindow::SlotActMenuBarEditClearOutside() 
{
    // QMessageBox::warning(mLastActiveImgWin, tr("ROI領域以外のクリア"),
    //                   tr("工事中..."));

    std::map<int, QRectF> localRects = mLastActiveImgWin->GetRectsOnDibImg();

    auto func = [&](QImage &img) -> void {
        if (localRects.size() > 0) 
        {
            using byte = uchar;
            int l, t, r, b;
            int memWidth = img.bytesPerLine();
            int memChannels = img.depth() / 8;
            int channels = (memChannels > 3) ? 3 : memChannels;
            byte *srcPtr = img.bits();

            QImage blackImg = img.copy();
            blackImg.fill(Qt::black);
            byte *dstPtr = blackImg.bits();

            for (const auto &roi : localRects) 
            {
                l = roi.second.x();
                t = roi.second.y();
                r = int(l + roi.second.width());
                b = int(t + roi.second.height());

                for (int c = 0; c < channels; ++c) 
                {
                    for (int y = t; y < b; ++y) 
                    {
                        for (int x = l; x < r; ++x) 
                        {
                            dstPtr[y*memWidth + memChannels*x + c] = 
                            srcPtr[y*memWidth + memChannels*x + c];
                        }
                    }
                }
            }

            blackImg.swap(img);
        }
    };

    HelperImgProc(QString("Clear Outside"), func);
}

/**
 * @brief Menu -> Edit -> Fill
 * 
 */
void MainWindow::SlotActMenuBarEditFill() 
{
    QMessageBox::warning(mLastActiveImgWin, tr("ROI領域の色指定"),
                          tr("工事中..."));

    auto color = QColorDialog::getColor();
}

/**
 * @brief Menu -> Edit -> Invert
 * 
 */
void MainWindow::SlotActMenuBarEditInvert() 
{
    // QMessageBox::warning(mLastActiveImgWin, tr("色反転"), 
    //                         tr("工事中..."));

    std::map<int, QRectF> localRects = mLastActiveImgWin->GetRectsOnDibImg();

    auto func = [&](QImage &img) -> void {

        if (localRects.size() > 0) 
        {
            using byte = uchar;
            int l, t, r, b;
            int memWidth = img.bytesPerLine();
            int memChannels = img.depth() / 8;
            int channels = (memChannels > 3) ? 3 : memChannels;
            byte *imgPtr = img.bits();
            for (const auto &roi : localRects) 
            {
                l = roi.second.x();
                t = roi.second.y();
                r = int(l + roi.second.width());
                b = int(t + roi.second.height());

                for (int c = 0; c < channels; ++c) 
                {
                    for (int y = t; y < b; ++y) 
                    {
                        for (int x = l; x < r; ++x) 
                        {
                            byte& v = imgPtr[y*memWidth + memChannels*x + c];
                            v = 255 - v;
                        }
                    }
                }
            }
        }
        else 
        {
            img.invertPixels();
        }
    };

    HelperImgProc(QString("Clear"), func);
}

/**
 * @brief Menu -> Image -> Type
 * 
 */
void MainWindow::SlotActMenuBarImageType() 
{
    auto p_ui = mLastActiveImgWin->Ui();

    p_ui->actionCvt8bit->setChecked(false);
    p_ui->actionCvt24bit->setChecked(false);
    p_ui->actionCvtRGBA->setChecked(false);

    QImage::Format format;

    if (sender() == p_ui->actionCvt8bit) 
    {
        p_ui->actionCvt8bit->setChecked(true);
        format = QImage::Format_Grayscale8;
    } 
    else if (sender() == p_ui->actionCvt24bit) 
    {
        p_ui->actionCvt24bit->setChecked(true);
        format = QImage::Format_RGB888;
    }
    else if (sender() == p_ui->actionCvtRGBA) 
    {
        p_ui->actionCvtRGBA->setChecked(true);
        format = QImage::Format_RGBA8888;
    }

    auto func = [&](QImage &img) -> void {
        img = img.convertToFormat(format);
    };

    HelperImgProc(QString("Type"), func);
}


/**
 * @brief Menu -> Image -> ShowInfo
 * 
 */
void MainWindow::SlotActMenuBarImageShowInfo() {}


/**
 * @brief Menu -> Image -> Color
 * 
 */
void MainWindow::SlotActMenuBarImageColor() 
{
    auto sender = this->sender();
    if (sender == mLastActiveImgWin->Ui()->actionRGBToGray) 
    {
        IS_DEBUG_STREAM("RGB -> Gray\n");
    }
    else if (sender == mLastActiveImgWin->Ui()->actionGrayToRGB) 
    {
        IS_DEBUG_STREAM("Gray -> RGB\n");
    }
    else if (sender == mLastActiveImgWin->Ui()->actionRGBToHSV) 
    {
        IS_DEBUG_STREAM("RGB -> HSV\n");
    }
    else if (sender == mLastActiveImgWin->Ui()->actionHSVToRGB) 
    {
        IS_DEBUG_STREAM("HSV -> RGB\n");
    }
    else if (sender == mLastActiveImgWin->Ui()->actionRGBToYUV) 
    {
        IS_DEBUG_STREAM("RGB -> YUV\n");
    }
    // else if (sender == mLastActiveImgWin->ui()->actionYUVToRGB) {
        
    // }
}

/**
 * @brief Menu -> Image -> Border
 * 
 */
void MainWindow::SlotActMenuBarImageBorder() {}


/**
 * @brief 
 * 
 */
void MainWindow::SlotActMenuBarImageTransform() {}


/**
 * @brief Menu -> Image -> Crop
 * 
 */
void MainWindow::SlotActMenuBarImageCrop() 
{
    std::map<int, QRectF> localRects = mLastActiveImgWin->GetRectsOnDibImg();
    QImage img = mLastActiveImgWin->GetDibImg();

    for (const auto& roi : localRects) 
    {
        auto filename = mLastActiveImgWin->Filename();
        int pos = filename.lastIndexOf(tr("."));
        auto name = filename.left(pos);
        auto ext = filename.mid(pos + 1);
        filename = name + tr("_crop.") + ext;

        ImageWindow *p_newImgWin = GenImgWin(filename);

        QImage cropedImg = img.copy(roi.second.toRect());

        p_newImgWin->SetDibImg(cropedImg, true, true);
    }
}


/**
 * @brief Menu -> Image -> Duplicate
 * 
 */
void MainWindow::SlotActMenuBarImageDuplicate() 
{
    std::set<std::string> currImgWinFilenames;
    for (const auto &imgWin : GetImgWinRegistry()) 
    {
        currImgWinFilenames.insert(imgWin->Filename().toStdString());
    }

    auto filename = mLastActiveImgWin->Filename();
    int pos = filename.lastIndexOf(tr("."));
    auto name = filename.left(pos);
    auto ext = filename.mid(pos + 1);

    pos = name.indexOf(tr("-"));

    if (pos > 0) name = name.left(pos);

    IS_DEBUG_STREAM("Duplicate %s.%s\n", 
                    name.toStdString().c_str(),
                    ext.toStdString().c_str());

    QImage img = mLastActiveImgWin->GetDibImg().copy();

    filename = name + tr(".") + ext;
    std::string newFilename = GetNewSerialNo(filename.toStdString(), currImgWinFilenames);
    ImageWindow *p_newImgWin = GenImgWin(QString::fromStdString(newFilename));

    p_newImgWin->SetDibImg(img, true, true);
}


/**
 * @brief Menu -> Process -> Filter
 * 
 */
void MainWindow::SlotActMenuBarFilter() 
{
    auto p_filter_dlg = new FilterDialog(mLastActiveImgWin);
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
void MainWindow::SlotActMenuBarCameraWindow() 
{
    QMessageBox::warning(mLastActiveImgWin, tr("Camera"), 
                        tr("工事中..."));
}