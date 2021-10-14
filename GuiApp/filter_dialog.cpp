#include "ui_FilterDialog.h"
#include "filter_dialog.h"

#include "image_window.h"

#include <IsNdArray/nd_array_extra.hpp>
#include <IsComputerVision/filter/blur.hpp>

#include <Qt>


//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////
FilterDialog::FilterDialog(QWidget* parent)
    : QDialog(parent)
    , m_pUi(new Ui::FilterDialog()) {

    // UI
    m_pUi->setupUi(this);

    // ImageWindow
    m_pImgWin =  qobject_cast<ImageWindow *>(parentWidget());

    setAttribute(Qt::WA_DeleteOnClose); // Closeされたときに自動でメモリ削除


    // Signal/Slot
    menuBarConnection();
    toolBarConnection();
    uiConnection();
    customConnection();
}


FilterDialog::~FilterDialog() {
    if (m_pUi) {
        delete m_pUi;
        m_pUi = nullptr;
    }
}


//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////
void FilterDialog::menuBarConnection() {

}

void FilterDialog::toolBarConnection() {

}

void FilterDialog::uiConnection() {
    // Average Filter
    connect(m_pUi->pushButtonAverageFilter, &QPushButton::clicked,
        this, &FilterDialog::slotAverageFilter);
}

void FilterDialog::customConnection() {

}


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
void FilterDialog::slotAverageFilter() {
    IS_DEBUG_STREAM("slotAverageFilter\n");

    using namespace is::nbla;
    using namespace is::imgproc;
    using ubyte = unsigned char;
    const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();


    int ksize_x = 15;
    int ksize_y = 15;
 
    auto func = [&](NdArrayPtr img) -> NdArrayPtr {
        return avg_filter(img, Size(ksize_x, ksize_y));
    };


    auto qimg = m_pImgWin->getDibImg();
    int width = qimg.width();
    int height = qimg.height();
    int mem_channels = qimg.depth() / 8;
    int channels = mem_channels > 3 ? 3 : mem_channels;
    IS_DEBUG_STREAM("w: %d, h: %d, c: %d\n", width, height, channels);

    int mem_width = qimg.bytesPerLine();
    ubyte* ptr = qimg.bits();

    auto src = zeros<ubyte>({channels, height, width});
    ubyte* data_src = src->cast_data_and_get_pointer<ubyte>(ctx);
    auto sh = src->shape();
    auto st = src->strides();
    for (int c = 0; c < sh[0]; ++c) {
        for (int y = 0; y < sh[1]; ++y) {
            for (int x = 0; x < sh[2]; ++x) {
                data_src[c*st[0]+y*st[1]+x*st[2]] = ptr[y*mem_width+mem_channels*x+c];
            }
        }
    }

    auto start = high_resolution_clock::now();
    auto dst = func(src);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    IS_DEBUG_STREAM("Elapsed time: %d[ms]\n", duration);

    ubyte* data_dst = dst->cast_data_and_get_pointer<ubyte>(ctx);

    for (int c = 0; c < sh[0]; ++c) {
        for (int y = 0; y < sh[1]; ++y) {
            for (int x = 0; x < sh[2]; ++x) {
                ptr[y*mem_width+mem_channels*x+c] = data_dst[c*st[0]+y*st[1]+x*st[2]];
            }
        }
    }

    m_pImgWin->setDibImg(qimg);
}