#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__

#include "pch.hpp"

#include <QMainWindow>
#include <QImage>
#include <QString>

#include <deque>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ImageWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // UI
    Ui::MainWindow *ui_{nullptr};

    // ImageWindow
    std::deque<std::shared_ptr<ImageWindow>> wins_;
    std::shared_ptr<ImageWindow> last_active_win_;

    // QImage
    QImage qimg_;
    
    // File Mode
    QString current_dir_;

    void _menubar_connection();
    // void _toolbar_connection();
    // void _ui_connection();
    // void _custom_connection();

private slots:
    /* Menu -> File */
    void _act_menubar_file_new();
    void _act_menubar_file_open();
    void _act_menubar_file_close();
    void _act_menubar_file_close_all();
    void _act_menubar_file_save();
    void _act_menubar_file_save_as();
    void _act_menubar_file_print();
    void _act_menubar_file_quit();

    /* Menu -> Edit */
    void _act_menubar_edit_undo();
    void _act_menubar_edit_cut();
    void _act_menubar_edit_copy();
    void _act_menubar_edit_paste();
    void _act_menubar_edit_clear();
    void _act_menubar_edit_clear_outside();
    void _act_menubar_edit_fill();
    void _act_menubar_edit_invert();

    /* Menu -> Image */ 
    void _act_menubar_image_type();
    void _act_menubar_image_show_info();
    void _act_menubar_image_color();
    void _act_menubar_image_mask();
    void _act_menubar_image_boarder();
    void _act_menubar_image_crop();
    void _act_menubar_image_duplicate();
    void _act_menubar_image_rename();
    void _act_menubar_image_scale();
    void _act_menubar_image_transform();
    void _act_menubar_image_zoom();

    /* Menu -> Camera */ 
    void _act_menubar_camera();

    /* Menu -> Video */
    void _act_menubar_video_make();
    void _act_menubar_video_open();

    /* Menu -> Image Process */
    void _act_menubar_process_blur();
    void _act_menubar_process_unsharp_masking();
    void _act_menubar_process_edge_detector();
    void _act_menubar_process_luminance_mapping();
    void _act_menubar_process_binarize();
    void _act_menubar_process_morphology();
    void _act_menubar_process_noise_denoise();
    void _act_menubar_process_histogram();

    /* Menu -> Image Analyze */
    void _act_menubar_analyze_labeling();
    void _act_menubar_analyze_show_histogram();
    void _act_menubar_analyze_surface_plot();
    void _act_menubar_analyze_fft();
    void _act_menubar_analyze_wavelet();

    /* Menu -> Local Features */
    void _act_menubar_local_features_keypoint_descriptor();
    void _act_menubar_local_features_keypoint();
    void _act_menubar_local_features_descriptor();
    void _act_menubar_local_features_matching();

    /* Menu -> Detector */
    void _act_menubar_detector_hough();
    void _act_menubar_detector_template_matching();
    void _act_menubar_detector_fitting();

    /* Menu -> Motion Tracking */
    void _act_menubar_motion_tracking_optical_flow();
    void _act_menubar_motion_tracking_mean_shift();
    void _act_menubar_motion_tracking_cam_shift();
    void _act_menubar_motion_tracking_kalman_filter();
    void _act_menubar_motion_tracking_particle_filter();

    /* Menu -> ML/DL */
    void _act_menubar_ml_dl_annotation();
    void _act_menubar_ml_dl_dataset();
    void _act_menubar_ml_dl_dl_classification();
    void _act_menubar_ml_dl_dl_regression();
    void _act_menubar_ml_dl_dl_generative();
    void _act_menubar_ml_dl_ml_classification();
    void _act_menubar_ml_dl_ml_regression();
    void _act_menubar_ml_dl_ml_clusterring();
    void _act_menubar_ml_dl_feature_extraction();

    /* Menu -> Window */
    // void _act_menubar_window_unknown();

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

};


#endif // __MAIN_WINDOW_HPP__