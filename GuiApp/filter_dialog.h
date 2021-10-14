#pragma once

#include "GuiApp.h"

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
    namespace Ui { class FilterDialog; }
QT_END_NAMESPACE

class ImageWindow;

class FilterDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(FilterDialog)

    ImageWindow* m_pImgWin;

    Ui::FilterDialog* m_pUi;


    void menuBarConnection();
    void toolBarConnection();
    void uiConnection();
    void customConnection();

public:
    FilterDialog(QWidget* parent = nullptr);
    virtual ~FilterDialog();

signals:

public slots:

private slots:
    void slotAverageFilter();

    
};