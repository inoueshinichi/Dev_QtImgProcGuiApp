
// 自作
#include "common.hpp"
#include "image_window.hpp"

// Standard

// Qt

namespace Is
{
    ImageWindow::ImageWindow(QWidget* parent)
        : QMainWindow(parent)
    {
        ui_ = make_shared<Ui::MakeWindow>();
        ui_->setUp(this);

        scene_ = make_shared<ImageDrawScene>(this);
    }


    void ImageWindow::_custom_connection()
    {
        /* ImageDrawScene -> ImageWindow */
        // Show scene rect
        connect(scene_.get(), &ImageDrawScene::signal_show_scene_rect, this, &ImageWindow::slot_show_scene_rect);
    }

// ==============================================
// private slots [START]
// ==============================================


// ==============================================
// private slots [END]
// ==============================================

// ==============================================
// public slots [START]
// ==============================================

// public slot from ImageDrawScene
void ImageWindow::slot_show_scene_rect(const QRectF& scene_rect)
{
    rect = scene_rect.toRect();
    int x = rect.x();
    int y = rect.y();
    int width = rect.width();
    int height = rect.height();
    permanent_status_->setText(format_string("SceneRect (%4d,%4d,%4d,%4d)"s, x, y, width, height));
    ui_->statusbar.addPermanentWidget(permanent_status_);
}

// ==============================================
// public slots [END]
// ==============================================

}