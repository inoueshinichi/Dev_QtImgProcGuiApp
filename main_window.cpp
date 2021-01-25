
// 自作
#include "ui_MainWindow.h"
#include "main_window.h"

// Standard

// Qt


/**
 * @brief Construct a new Main Window:: Main Window object
 * 
 * @param parent 
 */
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

/**
 * @brief Destroy the Main Window:: Main Window object
 * 
 */
MainWindow::~MainWindow() 
{}

/**
 * @brief メニューバーアクションの接続
 * 
 */
void MainWindow::_menubar_connection()
{
    /* File */
    // New
    connect(ui_->actionNew, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_new()));  
    // Open   
    connect(ui_->actionOpen, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_open()));   
    // Close
    connect(ui_->actionClose, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_close())); 
    // Close All
    connect(ui_->actionClose_All, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_close_all())); 
    // Save
    connect(ui_->actionSave, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_save()));
    // SaveAs
    connect(ui_->actionBMP, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_save_as()));
    connect(ui_->actionJPEG, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_save_as()));
    connect(ui_->actionJPG, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_save_as()));
    connect(ui_->actionPNG, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_save_as()));
    connect(ui_->actionCSV, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_save_as()));
    // Print
    connect(ui_->actionPrint, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_print())); 
    // Quit
    connect(ui_->actionQuit, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_file_quit())); 


    /* Edit */
    // Undo
    connect(ui_->actionUndo, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_edit_undo()));
    // Cut
    connect(ui_->actionCut, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_edit_cut()));
    // Copy
    connect(ui_->actionCopy, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_edit_copy()));
    // Paste
    connect(ui_->actionPaste, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_edit_paste()));
    // Clear
    connect(ui_->actionClear, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_edit_clear()));
    // Claer Outside
    connect(ui_->actionClear_Outside, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_edit_clear_outside()));
    // Fill
    connect(ui_->actionFill, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_edit_fill()));
    // Invert
    connect(ui_->actionInvert, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_edit_invert()));


    /* Image */
    // Type
    connect(ui_->action8_bit, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_type()));
    connect(ui_->action24_bit, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_type()));
    connect(ui_->actionRGB_Color, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_type()));
    // Show Info
    connect(ui_->actionShow_Info, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_show_info()));
    // Color
    connect(ui_->actionRGB2Gray, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_color()));
    connect(ui_->actionGray2RGB, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_color()));
    connect(ui_->actionRGB2HSV, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_color()));
    connect(ui_->actionHSV2RGB, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_color()));
    connect(ui_->actionSplit_Channels, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_color()));
    connect(ui_->actionMerge_Channels, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_color()));
    // Maks
    connect(ui_->actionMask_Import, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_mask()));
    connect(ui_->actionMask_Export, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_mask()));
    // Boarder
    connect(ui_->actionBoarder, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_boarder()));
    // Crop
    connect(ui_->actionCrop, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_crop()));
    // Dupulicate
    connect(ui_->actionDuplicate, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_duplicate()));
    // Rename
    connect(ui_->actionRename, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_rename()));
    // Scale
    connect(ui_->actionScale, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_scale()));
    // Transform
    connect(ui_->actionVertical_Flip, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_transform()));
    connect(ui_->actionHorizontal_Flip, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_transform()));
    connect(ui_->actionRotate_90_Degree_Right, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_transform()));
    connect(ui_->actionRotate_90_Degree_Left, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_transform()));
    connect(ui_->actionRotate, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_transform()));
    connect(ui_->actionTranslate, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_transform()));
    connect(ui_->actionBin, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_transform()));
    // Zoom
    connect(ui_->actionZoomIn, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_zoom()));
    connect(ui_->actionZoomOut, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_zoom()));
    connect(ui_->actionOriginal_Scale, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_zoom()));
    connect(ui_->actionFit_View, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_zoom()));

    /* Camera */
    connect(ui_->actionUSB_Camera, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_camera())); // USB
    connect(ui_->actionIP_Address_Camera, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_camera())); // IP_Address
    connect(ui_->actionIDS_Camera, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_camera()));    // IDS Camera
    connect(ui_->actionOMRON_Camera, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_camera()));  // OMRON Camera
    connect(ui_->actionBASLER_Camera, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_camera())); // BASLER Camera
    connect(ui_->actionCOGNEX_Camera, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_camera())); // COGNEX Camera

    /* Video */
    connect(ui_->actionVideo_Generate, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_video()));
    connect(ui_->actionVideo_Show, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_video()));

    /* Image Process */
    connect(ui_->actionBlur, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    connect(ui_->actionUnsharp_Masking, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    connect(ui_->actionEdge_Detector, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    connect(ui_->actionMapping, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    connect(ui_->actionBinarize, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    connect(ui_->actionMorphology, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    connect(ui_->actionNoise_Denoise, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    connect(ui_->actionHistogram, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    // connect(ui_->, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    // connect(ui_->, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    // connect(ui_->, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));
    // connect(ui_->, SIGNAL(triggered()), this, SLOT(_slot_act_menubar_image_process()));

    /* Image Analyze */


}

/**
 * @brief Menu -> File -> New
 * 
 */
void MainWindow::_slot_act_menubar_file_new()
{

}

/**
 * @brief Menu -> File -> Open
 * 
 */
void MainWindow::_slot_act_menubar_file_open()
{

}

/**
 * @brief Menu -> File -> Close
 * 
 */
void MainWindow::_slot_act_menubar_file_close()
{

}

/**
 * @brief Menu -> File -> Close all
 * 
 */
void MainWindow::_slot_act_menubar_file_close_all()
{

}

/**
 * @brief Menu -> File -> Save
 * 
 */
void MainWindow::_slot_act_menubar_file_save()
{

}

/**
 * @brief Menu -> File -> Save as
 * 
 */
void MainWindow::_slot_act_menubar_file_save_as()
{

}

/**
 * @brief Menu -> File -> Print
 * 
 */
void MainWindow::_slot_act_menubar_file_print()
{

}

/**
 * @brief Menu -> File -> Quit
 * 
 */
void MainWindow::_slot_act_menubar_file_quit()
{

}

/**
 * @brief Menu -> Edit -> Undo
 * 
 */
void MainWindow::_slot_act_menubar_edit_undo()
{

}

/**
 * @brief Menu -> Edit -> Cut
 * 
 */
void MainWindow::_slot_act_menubar_edit_cut()
{

}

/**
 * @brief Menu -> Edit -> Copy
 * 
 */
void MainWindow::_slot_act_menubar_edit_copy()
{

}

/**
 * @brief Menu -> Edit -> Paste
 * 
 */
void MainWindow::_slot_act_menubar_edit_paste()
{

}

/**
 * @brief Menu -> Edit -> Clear
 * 
 */
void MainWindow::_slot_act_menubar_edit_clear()
{

}

/**
 * @brief Menu -> Edit -> Clear outside
 * 
 */
void MainWindow::_slot_act_menubar_edit_clear_outside()
{

}

/**
 * @brief Menu -> Edit -> Fill
 * 
 */
void MainWindow::_slot_act_menubar_edit_fill()
{

}

/**
 * @brief Menu -> Edit -> Invert
 * 
 */
void MainWindow::_slot_act_menubar_edit_invert()
{

}

/**
 * @brief Menu -> Image -> Type
 * 
 */
void MainWindow::_slot_act_menubar_image_type()
{

}

/**
 * @brief Menu -> Image -> Show Info
 * 
 */
void MainWindow::_slot_act_menubar_image_show_info()
{

}

/**
 * @brief Menu -> Image -> Color
 * 
 */
void MainWindow::_slot_act_menubar_image_color()
{

}

/**
 * @brief Menu -> Image -> Mask
 * 
 */
void MainWindow::_slot_act_menubar_image_mask()
{

}

/**
 * @brief Menu -> Image -> Boarder
 * 
 */
void MainWindow::_slot_act_menubar_image_boarder()
{

}

/**
 * @brief Menu -> Image -> Crop
 * 
 */
void MainWindow::_slot_act_menubar_image_crop()
{

}

/**
 * @brief Menu -> Image -> Duplicate
 * 
 */
void MainWindow::_slot_act_menubar_image_duplicate()
{

}


/**
 * Menu -> Image -> Rename
 * */
void MainWindow::_slot_act_menubar_image_rename()
{

}


/**
 * Menu -> Image -> Scale
 * */
void MainWindow::_slot_act_menubar_image_scale()
{

}


/**
 * Menu -> Image -> Transform
 * */
void MainWindow::_slot_act_menubar_image_transform()
{

}


/**
 * Menu -> Image -> Zoom
 * */
void MainWindow::_slot_act_menubar_image_zoom()
{

}


/**
 * Menu -> Camera
 * */
void MainWindow::_slot_act_menubar_camera()
{

}

/**
 * Menu -> Video -> Make
 * */
void MainWindow::_slot_act_menubar_video()
{

}

/**
 * Menu -> Image Process
 * */
void MainWindow::_slot_act_menubar_image_process()
{
    // Blur
    // Unsharp Masking
    // Edge Detector
    // Luminance Mapping
    // Binarize
    // Morphology
    // Noise/Denoise
    // Histogram
}

/**
 * Menu -> Image Analyze
 * */
void MainWindow::_slot_act_menubar_analyze()
{
    // Labeling
    // Show Histogram
    // Surface Plot
    // FFT
    // Wavelet
}

/**
 * Menu -> Local Features
 * */
void MainWindow::_slot_act_menubar_local_features()
{
    // Keypoint/Descriptor
    // Keypoint
    // Descriptor
    // Matching
}

/**
 * Menu -> Detector -> Hough
 * */
void MainWindow::_slot_act_menubar_detector_hough()
{

}


/**
 * Menu -> Detector -> Template Matching
 * */
void MainWindow::_slot_act_menubar_detector_template_matching()
{

}


/**
 * Menu -> Detector -> Fitting
 * */
void MainWindow::_slot_act_menubar_detector_fitting()
{

}


/**
 * Menu -> Motion Tracking -> Optical Flow
 * */
void MainWindow::_slot_act_menubar_motion_tracking_optical_flow()
{

}


/**
 * Menu -> Motion Tracking -> MeanShift
 * */
void MainWindow::_slot_act_menubar_motion_tracking_mean_shift()
{

}


/**
 * Menu -> Motion Tracking -> CamShift
 * */
void MainWindow::_slot_act_menubar_motion_tracking_cam_shift()
{

}


/**
 * Menu -> Motion Tracking -> Kalman Filter
 * */
void MainWindow::_slot_act_menubar_motion_tracking_kalman_filter()
{

}


/**
 * Menu -> Motion Tracking -> Particle Filter
 * */
void MainWindow::_slot_act_menubar_motion_tracking_particle_filter()
{

}

/**
 * Menu -> ML/DL -> Annotation
 * */
void MainWindow::_slot_act_menubar_annotation()
{

}

/**
 * Menu -> ML/DL -> Dataset
 */
void MainWindow::_slot_act_menubar_dataset()
{

}

/**
 * @brief Menu -> MD/DL -> Image Classification
 * 
 */
void MainWindow::_slot_act_menubar_dl_image_classification()
{

}

/**
 * @brief Menu -> MD/DL -> Object Detection
 * 
 */
void MainWindow::_slot_act_menubar_dl_object_detection()
{

}
