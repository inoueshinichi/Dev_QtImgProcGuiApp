#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// 自作
// #include "image_window.h"
#include "ui_MainWindow.h"

// Standard
#include <deque>
#include <memory>

// Qt
#include <QMainWindow>
#include <QImage>
#include <QString>

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using std::deque;
using std::shared_ptr;
using std::make_shared;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // UI
    shared_ptr<Ui::MainWindow> ui_;

    // ImageWindow
    // deque<shared_ptr<ImageWindow>> wins_;
    // shared_ptr<ImageWindow> last_active_win_;

    // QImage
    QImage image_;
    
    // File Mode
    QString current_dir_;

    void _menubar_connection();
    void _toolbar_connection();
    void _ui_connection();
    void _custom_connection();

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    /* Menu -> File */
    void _slot_act_menubar_file_new();
    void _slot_act_menubar_file_open();
    void _slot_act_menubar_file_close();
    void _slot_act_menubar_file_close_all();
    void _slot_act_menubar_file_save();
    void _slot_act_menubar_file_save_as();
    void _slot_act_menubar_file_print();
    void _slot_act_menubar_file_quit();

    /* Menu -> Edit */
    void _slot_act_menubar_edit_undo();
    void _slot_act_menubar_edit_cut();
    void _slot_act_menubar_edit_copy();
    void _slot_act_menubar_edit_paste();
    void _slot_act_menubar_edit_clear();
    void _slot_act_menubar_edit_clear_outside();
    void _slot_act_menubar_edit_fill();
    void _slot_act_menubar_edit_invert();

    /* Menu -> Image */ 
    void _slot_act_menubar_image_type();
    void _slot_act_menubar_image_show_info();
    void _slot_act_menubar_image_color();
    void _slot_act_menubar_image_mask();
    void _slot_act_menubar_image_boarder();
    void _slot_act_menubar_image_crop();
    void _slot_act_menubar_image_duplicate();
    void _slot_act_menubar_image_rename();
    void _slot_act_menubar_image_scale();
    void _slot_act_menubar_image_transform();
    void _slot_act_menubar_image_zoom();

    /* Menu -> Camera */ 
    void _slot_act_menubar_camera();

    /* Menu -> Video */
    void _slot_act_menubar_video();

    /* Menu -> Image Process */
    void _slot_act_menubar_image_process();

    /* Menu -> Image Analyze */
    void _slot_act_menubar_analyze();
    
    /* Menu -> Local Features */
    void _slot_act_menubar_local_features();

    /* Menu -> Detector */
    void _slot_act_menubar_detector_hough();
    void _slot_act_menubar_detector_template_matching();
    void _slot_act_menubar_detector_fitting();

    /* Menu -> Motion Tracking */
    void _slot_act_menubar_motion_tracking_optical_flow();
    void _slot_act_menubar_motion_tracking_mean_shift();
    void _slot_act_menubar_motion_tracking_cam_shift();
    void _slot_act_menubar_motion_tracking_kalman_filter();
    void _slot_act_menubar_motion_tracking_particle_filter();

    /* Menu -> ML/DL */
    void _slot_act_menubar_annotation();
    void _slot_act_menubar_dataset();
    void _slot_act_menubar_dl_image_classification();
    void _slot_act_menubar_dl_object_detection();

    /* Menu -> Window */
    
};
#endif // __MAIN_WINDOW_H__