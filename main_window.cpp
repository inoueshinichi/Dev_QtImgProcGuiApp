
// 自作
#include "main_window.h"

// Standard

// Qt


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    // , wins_()
    // , last_active_win_()
{
    // UI
    ui_ = make_shared<Ui::MainWindow>();
    ui_->setupUi(this);

    /* Signal & Slot */
    _menubar_connection();
    // _toolbar_connection();
    // _ui_connection();
    // _custom_connection();
}

MainWindow::~MainWindow() 
{}


/**
 * メニューバーアクションの接続
 * */
void MainWindow::_menubar_connection()
{
    /* File */
    // New
    connect(ui_->actionNew, SIGNAL(triggered()), this, SLOT(_act_menubar_file_new()));  
    // Open   
    connect(ui_->actionOpen, SIGNAL(triggered()), this, SLOT(_act_menubar_file_open()));   
    // Close
    connect(ui_->actionClose, SIGNAL(triggered()), this, SLOT(_act_menubar_file_close())); 
    // Close All
    connect(ui_->actionClose_All, SIGNAL(triggered()), this, SLOT(_act_menubar_file_close_all())); 
    // Save
    connect(ui_->actionSave, SIGNAL(triggered()), this, SLOT(_act_menubar_file_save()));
    // SaveAs
    connect(ui_->actionBMP, SIGNAL(triggered()), this, SLOT(_act_menubar_file_save_as()));
    connect(ui_->actionJPEG, SIGNAL(triggered()), this, SLOT(_act_menubar_file_save_as()));
    connect(ui_->actionJPG, SIGNAL(triggered()), this, SLOT(_act_menubar_file_save_as()));
    connect(ui_->actionPNG, SIGNAL(triggered()), this, SLOT(_act_menubar_file_save_as()));
    connect(ui_->actionCSV, SIGNAL(triggered()), this, SLOT(_act_menubar_file_save_as()));
    // Print
    connect(ui_->actionPrint, SIGNAL(triggered()), this, SLOT(_act_menubar_file_print())); 
    // Quit
    connect(ui_->actionQuit, SIGNAL(triggered()), this, SLOT(_act_menubar_file_quit())); 


    /* Edit */
    // Undo
    connect(ui_->actionUndo, SIGNAL(triggered()), this, SLOT(_act_menubar_edit_undo()));
    // Cut
    connect(ui_->actionCut, SIGNAL(triggered()), this, SLOT(_act_menubar_edit_cut()));
    // Copy
    connect(ui_->actionCopy, SIGNAL(triggered()), this, SLOT(_act_menubar_edit_copy()));
    // Paste
    connect(ui_->actionPaste, SIGNAL(triggered()), this, SLOT(_act_menubar_edit_paste()));
    // Clear
    connect(ui_->actionClear, SIGNAL(triggered()), this, SLOT(_act_menubar_edit_clear()));
    // Claer Outside
    connect(ui_->actionClear_Outside, SIGNAL(triggered()), this, SLOT(_act_menubar_edit_clear_outside()));
    // Fill
    connect(ui_->actionFill, SIGNAL(triggered()), this, SLOT(_act_menubar_edit_fill()));
    // Invert
    connect(ui_->actionInvert, SIGNAL(triggered()), this, SLOT(_act_menubar_edit_invert()));


    /* Image */
    // Type
    connect(ui_->action8_bit, SIGNAL(triggered()), this, SLOT(_act_menubar_image_type()));
    connect(ui_->action24_bit, SIGNAL(triggered()), this, SLOT(_act_menubar_image_type()));
    connect(ui_->actionRGB_Color, SIGNAL(triggered()), this, SLOT(_act_menubar_image_type()));
    // Show Info
    connect(ui_->actionShow_Info, SIGNAL(triggered()), this, SLOT(_act_menubar_image_show_info()));
}


/**
 * Menu -> File -> New
 * */
void MainWindow::_act_menubar_file_new()
{

}


/**
 * Menu -> File -> Open
 * */
void MainWindow::_act_menubar_file_open()
{

}


/**
 * Menu -> File -> Close
 * */
void MainWindow::_act_menubar_file_close()
{

}


/**
 * Menu -> File -> Close all
 * */
void MainWindow::_act_menubar_file_close_all()
{

}


/**
 * Menu -> File -> Save
 * */
void MainWindow::_act_menubar_file_save()
{

}


/**
 * Menu -> File -> Save as
 * */
void MainWindow::_act_menubar_file_save_as()
{

}


/**
 * Menu -> File -> Print
 * */
void MainWindow::_act_menubar_file_print()
{

}


/**
 * Menu -> File -> Quit
 * */
void MainWindow::_act_menubar_file_quit()
{

}


/**
 * Menu -> Edit -> Undo
 * */
void MainWindow::_act_menubar_edit_undo()
{

}


/**
 * Menu -> Edit -> Cut
 * */
void MainWindow::_act_menubar_edit_cut()
{

}


/**
 * Menu -> Edit -> Copy
 * */
void MainWindow::_act_menubar_edit_copy()
{

}


/**
 * Menu -> Edit -> Paste
 * */
void MainWindow::_act_menubar_edit_paste()
{

}


/**
 * Menu -> Edit -> Clear
 * */
void MainWindow::_act_menubar_edit_clear()
{

}


/**
 * Menu -> Edit -> Clear outside
 * */
void MainWindow::_act_menubar_edit_clear_outside()
{

}


/**
 * Menu -> Edit -> Fill
 * */
void MainWindow::_act_menubar_edit_fill()
{

}


/**
 * Menu -> Edit -> Invert
 * */
void MainWindow::_act_menubar_edit_invert()
{

}


/**
 * Menu -> Image -> Type
 * */
void MainWindow::_act_menubar_image_type()
{

}


/**
 * Menu -> Image -> Show Info
 * */
void MainWindow::_act_menubar_image_show_info()
{

}


/**
 * Menu -> Image -> Color
 * */
void MainWindow::_act_menubar_image_color()
{

}


/**
 * Menu -> Image -> Mask
 * */
void MainWindow::_act_menubar_image_mask()
{

}


/**
 * Menu -> Image -> Boarder
 * */
void MainWindow::_act_menubar_image_boarder()
{

}


/**
 * Menu -> Image -> Crop
 * */
void MainWindow::_act_menubar_image_crop()
{

}


/**
 * Menu -> Image -> Duplicate
 * */
void MainWindow::_act_menubar_image_duplicate()
{

}


/**
 * Menu -> Image -> Rename
 * */
void MainWindow::_act_menubar_image_rename()
{

}


/**
 * Menu -> Image -> Scale
 * */
void MainWindow::_act_menubar_image_scale()
{

}


/**
 * Menu -> Image -> Transform
 * */
void MainWindow::_act_menubar_image_transform()
{

}


/**
 * Menu -> Image -> Zoom
 * */
void MainWindow::_act_menubar_image_zoom()
{

}


/**
 * Menu -> Camera -> Dialog
 * */
void MainWindow::_act_menubar_camera()
{

}

/**
 * Menu -> Video -> Make
 * */
void MainWindow::_act_menubar_video_make()
{

}


/**
 * Menu -> Video -> Open
 * */
void MainWindow::_act_menubar_video_open()
{

}


/**
 * Menu -> Image Process -> Blur
 * */
void MainWindow::_act_menubar_process_blur()
{

}


/**
 * Menu -> Image Process -> Unsharp Masking
 * */
void MainWindow::_act_menubar_process_unsharp_masking()
{
    
}


/**
 * Menu -> Image Process -> Edge Detector
 * */
void MainWindow::_act_menubar_process_edge_detector()
{
    
}


/**
 * Menu -> Image Process -> Luminance Mapping
 * */
void MainWindow::_act_menubar_process_luminance_mapping()
{
    
}


/**
 * Menu -> Image Process -> Binarize
 * */
void MainWindow::_act_menubar_process_binarize()
{
    
}


/**
 * Menu -> Image Process -> Morphology
 * */
void MainWindow::_act_menubar_process_morphology()
{
    
}


/**
 * Menu -> Image Process -> Noise/Denoise
 * */
void MainWindow::_act_menubar_process_noise_denoise()
{
    
}


/**
 * Menu -> Image Process -> Histogram
 * */
void MainWindow::_act_menubar_process_histogram()
{
    
}


/**
 * Menu -> Image Analyze -> Labeling
 * */
void MainWindow::_act_menubar_analyze_labeling()
{
    
}


/**
 * Menu -> Image Analyze -> Show Histogram
 * */
void MainWindow::_act_menubar_analyze_show_histogram()
{
    
}


/**
 * Menu -> Image Analyze -> Surface Plot
 * */
void MainWindow::_act_menubar_analyze_surface_plot()
{
    
}


/**
 * Menu -> Image Analyze -> FFT
 * */
void MainWindow::_act_menubar_analyze_fft()
{
    
}


/**
 * Menu -> Image Analyze -> Wavelet
 * */
void MainWindow::_act_menubar_analyze_wavelet()
{
    
}


/**
 * Menu -> Local Features -> Keypoint/Descriptor
 * */
void MainWindow::_act_menubar_local_features_keypoint_descriptor()
{

}


/**
 * Menu -> Local Features -> Keypoint
 * */
void MainWindow::_act_menubar_local_features_keypoint()
{

}


/**
 * Menu -> Local Features -> Descriptor
 * */
void MainWindow::_act_menubar_local_features_descriptor()
{

}


/**
 * Menu -> Local Features -> Matching
 * */
void MainWindow::_act_menubar_local_features_matching()
{

}


/**
 * Menu -> Detector -> Hough
 * */
void MainWindow::_act_menubar_detector_hough()
{

}


/**
 * Menu -> Detector -> Template Matching
 * */
void MainWindow::_act_menubar_detector_template_matching()
{

}


/**
 * Menu -> Detector -> Fitting
 * */
void MainWindow::_act_menubar_detector_fitting()
{

}


/**
 * Menu -> Motion Tracking -> Optical Flow
 * */
void MainWindow::_act_menubar_motion_tracking_optical_flow()
{

}


/**
 * Menu -> Motion Tracking -> MeanShift
 * */
void MainWindow::_act_menubar_motion_tracking_mean_shift()
{

}


/**
 * Menu -> Motion Tracking -> CamShift
 * */
void MainWindow::_act_menubar_motion_tracking_cam_shift()
{

}


/**
 * Menu -> Motion Tracking -> Kalman Filter
 * */
void MainWindow::_act_menubar_motion_tracking_kalman_filter()
{

}


/**
 * Menu -> Motion Tracking -> Particle Filter
 * */
void MainWindow::_act_menubar_motion_tracking_particle_filter()
{

}


void MainWindow::_act_menubar_ml_dl_annotation()
{

}


void MainWindow::_act_menubar_ml_dl_dataset()
{

}


void MainWindow::_act_menubar_ml_dl_dl_classification()
{

}


void MainWindow::_act_menubar_ml_dl_dl_regression()
{

}


void MainWindow::_act_menubar_ml_dl_dl_generative()
{

}


void MainWindow::_act_menubar_ml_dl_ml_classification()
{

}


void MainWindow::_act_menubar_ml_dl_ml_regression()
{

}


void MainWindow::_act_menubar_ml_dl_ml_clusterring()
{

}


void MainWindow::_act_menubar_ml_dl_feature_extraction()
{

}
