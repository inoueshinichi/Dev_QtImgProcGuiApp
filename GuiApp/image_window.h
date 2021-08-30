/**
 * @file image_window.cpp
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief Qt 自作ImageWindowのHeaderファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
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

    Ui::ImageWindow *m_pUi;
    ImageScene *m_pScene;
    QLabel *m_pStatusBarLabel;
    QString m_filename;
    std::string m_posStatus;

    void uiConnection();
    void memuBarConnection();
    void toolBarConnection();
    void customConnection();


public:
    explicit ImageWindow(QWidget *parent = nullptr);
    virtual ~ImageWindow();

    void setFilename(const QString& filename);
    QString filename() const;
    ImageScene* scene() const;

    // void toggleCrossLine(bool isShow);
    // void toggleProfile(bool isShow);
    // void toggleRoi(bool isShow);
    // void toggleLine(bool isShow);
    // void toggleEllipse(bool isShow);
    // void toggleMask(bool isShow);

protected:
    virtual bool event(QEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void rmImgWin(ImageWindow* ptr);
    void activeImgWin(ImageWindow* ptr);

public slots:
    void slotShowPosToStatusBar(const QPointF &imgLocalPos,
                                const QPointF &scenePos,
                                const QPoint &viewPos);

private slots:
    void slotToggleCrossLine(bool checked);
    void slotToggleProfile(bool checked);
    void slotToggleRoi(bool checked);
};