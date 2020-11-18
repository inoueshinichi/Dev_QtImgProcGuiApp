#ifndef __IMAGE_WINDOW_HPP__
#define __IMAGE_WINDOW_HPP__

// #include "pch.hpp"
// #include "ui_image_window.hpp"
// #include <QMainWindow>

// #include <memory>

// QT_BEGIN_NAMESPACE
// namespace Ui { class ImageWindow; }
// QT_END_NAMESPACE

// namespace Is
// {
//     using std::shared_ptr;

//     class MainWindow;
//     class ImageDrawScene;
//     class QLabel;

//     class ImageWindow : public QMainWindow
//     {
//         Q_OBJECT

//         Ui::ImageWindow* ui_;
//         shared_ptr<ImageDrawScene> scene_;
//         shared_ptr<MainWindow> main_win_;
//         shared_ptr<QLabel> permanent_status_;
//         QString filename_;

//         void _menubar_connection();
//         void _toolbar_connection();
//         void _ui_connection();
//         void _custom_connection();

//     protected:
//         virtual bool event(QEvent *event) override;
//         virtual void closeEvent(QCloseEvent *event) override;

//     public:
//         ImageWindow(QWidget* parent = nullptr);
//         virtual ~ImageWindow();

//         void set_filename(const QString& fname);
//         QString filename() const;
//         QImage dib_image_on_scene() const;
//         void switch_visualization_on_scene(VitualType type, bool is_show);

//     signals:
//         void on_update_image_type(shared_ptr<ImageWindow> img_win);

//     public slots:
//         void slot_update_image_status(const QImage& qimg);
//         void slot_update_mouse_position(const QPointF& scene_pos);
        

//     }

// }



#endif // __IMAGE_WINDOW_HPP__