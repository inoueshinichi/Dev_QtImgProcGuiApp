#pragma once

#include "GuiApp.h"

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
    namespace Ui { class FilterDialog; }
QT_END_NAMESPACE

class ImageWindow;

class FilterDialog : public QDialog 
{
    Q_OBJECT
    Q_DISABLE_COPY(FilterDialog)

    ImageWindow* m_pImgWin;
    Ui::FilterDialog* m_pUi;

    void MenuBarConnection();
    void ToolBarConnection();
    void UiConnection();
    void CustomConnection();

public:
    FilterDialog(QWidget* parent = nullptr);
    virtual ~FilterDialog();

signals:

public slots:

private slots:
    void SlotAverageFilter();
  
};