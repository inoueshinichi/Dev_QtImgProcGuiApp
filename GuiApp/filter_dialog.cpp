#include "ui_FilterDialog.h"
#include "filter_dialog.h"

#include "image_window.h"

// ComputerVision
#include <IsComputerVision/filter/blur/average.hpp>

#include <Qt>


//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////
FilterDialog::FilterDialog(QWidget* parent)
    : QDialog(parent)
    , m_pUi(new Ui::FilterDialog()) 
{
    // UI
    m_pUi->setupUi(this);

    // ImageWindow
    m_pImgWin =  qobject_cast<ImageWindow *>(parentWidget());

    setAttribute(Qt::WA_DeleteOnClose); // Closeされたときに自動でメモリ削除


    // Signal/Slot
    MenuBarConnection();
    ToolBarConnection();
    UiConnection();
    CustomConnection();
}


FilterDialog::~FilterDialog() 
{
    if (m_pUi) 
    {
        delete m_pUi;
        m_pUi = nullptr;
    }
}


//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////
void FilterDialog::MenuBarConnection() {}
void FilterDialog::ToolBarConnection() {}
void FilterDialog::UiConnection() 
{
    // Average Filter
    connect(m_pUi->pushButtonAverageFilter, &QPushButton::clicked,
        this, &FilterDialog::SlotAverageFilter);
}

void FilterDialog::CustomConnection() {}


//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// public slot method
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// private slot method
//////////////////////////////////////////////////////////
void FilterDialog::SlotAverageFilter() 
{
    IS_DEBUG_STREAM("SlotAverageFilter\n");

    using namespace is::nbla;
    using namespace is::imgproc;
    using ubyte = unsigned char;
    const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();

    int ksize_x = 15;
    int ksize_y = 15;
 
    auto func = [&](NdArrayPtr img) -> NdArrayPtr {
        return average(img, Size(ksize_x, ksize_y));
    };

    auto qimg = m_pImgWin->GetDibImg();
    auto src = QImage2NdArray(qimg);
    auto dst = is::common::invoke_tm_chrono_ms_ret(func, src);
    qimg = NdArray2QImage(dst);
    m_pImgWin->SetDibImg(qimg);
}