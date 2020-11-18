/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../image_table_view.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCross_Line;
    QAction *actionProfile;
    QAction *actionROI;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionClose_All;
    QAction *actionSave;
    QAction *actionBMP;
    QAction *actionJPEG;
    QAction *actionPNG;
    QAction *actionCSV;
    QAction *actionPrint;
    QAction *actionQuit;
    QAction *actionUndo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClear;
    QAction *actionClear_Outside;
    QAction *actionFill;
    QAction *actionInvert;
    QAction *action8_bit;
    QAction *actionRGB_Color;
    QAction *actionShow_Info;
    QAction *actionSplit_Channels;
    QAction *actionCrop;
    QAction *actionDuplicate;
    QAction *actionRename;
    QAction *actionScale;
    QAction *actionVertical_Flip;
    QAction *actionHorizontal_Flip;
    QAction *actionRotate_90_Degree_Right;
    QAction *actionRotate_90_Degree_Left;
    QAction *actionRotate;
    QAction *actionTranslate;
    QAction *actionBin;
    QAction *actionHSV2RGB;
    QAction *actionRGB2HSV;
    QAction *actionRGB2Gray;
    QAction *actionMerge_Channels;
    QAction *actionEdge_Detector;
    QAction *actionBlur;
    QAction *actionFFT;
    QAction *actionReset_Image;
    QAction *actionLine_Measure;
    QAction *actionAngle_Measure;
    QAction *actionTime_Squence;
    QAction *actionFeatures;
    QAction *actionSimple_Classifier_Model;
    QAction *actionObject_Detection_Model;
    QAction *actionGAN;
    QAction *actionDataset;
    QAction *actionUSB_Camera;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionOriginal_Scale;
    QAction *actionFit_View;
    QAction *actionIndicator;
    QAction *actionJPG;
    QAction *actionXLSX;
    QAction *actionHarris_Corner;
    QAction *actionFAST_Corner;
    QAction *actionAGAST_Corner;
    QAction *actionMSER_Region;
    QAction *actionStar_Detector;
    QAction *actionBRIEF_Descriptor;
    QAction *actionFREAK_Descriptor;
    QAction *actionLATCH_Descriptor;
    QAction *actionLUCID_Descriptor;
    QAction *actionDAISY_Descriptor;
    QAction *actionMSD_Detector;
    QAction *actionORB;
    QAction *actionKAZE;
    QAction *actionAKAZE;
    QAction *actionBRISK;
    QAction *actionSIFT;
    QAction *actionSURF;
    QAction *actionHOG_Descriptor;
    QAction *actionHarrLike_Descriptor;
    QAction *actionLBP_Descriptor;
    QAction *actionMatching;
    QAction *actionKLT_Corner;
    QAction *actionHough_Line;
    QAction *actionHough_Circle;
    QAction *actionOptical_Flow;
    QAction *actionMeanshift;
    QAction *actionCAMshift;
    QAction *actionLinear_Kalman_Filter;
    QAction *actionNonLinear_Kalman_Filter;
    QAction *actionUnscented_Kalman_Filter;
    QAction *actionParticle_Filter;
    QAction *actionSurface_Plot;
    QAction *actionWavelet;
    QAction *actionLabeling;
    QAction *actionBinarize;
    QAction *actionMorphology;
    QAction *actionLogistic_Regression;
    QAction *actionkNN;
    QAction *actionLinear_Regression;
    QAction *actionRidge_Regression;
    QAction *actionLasso_Regression;
    QAction *actionElastic_Net_Regression;
    QAction *actionPolinominal_Linear_Regression;
    QAction *actionDecision_Tree_Regression;
    QAction *actionRandom_Foreset_Regression;
    QAction *actionSVM_Regression;
    QAction *actionGradient_Boost_Regression;
    QAction *actionGradient_Boost;
    QAction *actionDecision_Tree;
    QAction *actionRandom_Forest;
    QAction *actionAdaBoost;
    QAction *actionK_Means;
    QAction *actionHierarchical_Clustering;
    QAction *actionDBSCAN;
    QAction *actionPCA;
    QAction *actionLDA;
    QAction *actionSBS;
    QAction *actionIP_Address_Camera;
    QAction *action24_bit;
    QAction *actionGray2RGB;
    QAction *actionIDS_Camera;
    QAction *actionOMRON_Camera;
    QAction *actionBASLER_Camera;
    QAction *actionCOGNEX_Camera;
    QAction *actionMask;
    QAction *actionMask_Import;
    QAction *actionMask_Export;
    QAction *actionMapping;
    QAction *actionNoise_Denoise;
    QAction *actionHistogram;
    QAction *actionUnsharp_Masking;
    QAction *actionShow_Histogram;
    QAction *actionBoarder;
    QAction *actionEllipse;
    QAction *actionTM_SSD;
    QAction *actionTM_NSSD;
    QAction *action_TM_CCORR;
    QAction *actionTM_NCCORR;
    QAction *actionTM_CCOEFF;
    QAction *actionTM_NCCOEFF;
    QAction *actionLine;
    QAction *actionSVM;
    QAction *actionSimple_Annotation;
    QAction *actionROI_Annotation;
    QAction *actionRegressior;
    QAction *actionFeature_Vector;
    QAction *actionImage;
    QAction *actionObject_Detection;
    QAction *actionLanguage;
    QAction *actionGenerative;
    QAction *actionVideo_Make;
    QAction *actionVideo_Open;
    QAction *actionFitting_Line;
    QAction *actionFitting_Curve;
    QAction *actionFitting_Ellipse;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *rBtn_View_Mode;
    QRadioButton *rBtn_File_Mode;
    ImageTableView *tView_ImageTable;
    QGridLayout *gridLayout;
    QLineEdit *lEdit_Input_Dir;
    QToolButton *tBtn_Input_Dir;
    QLineEdit *lEdit_Output_Dir;
    QToolButton *tBtn_Output_Dir;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pBtn_ImageTable_Review;
    QPushButton *pBtn_ImageTable_All_Check;
    QPushButton *pBtn_ImageTable_All_Uncheck;
    QLineEdit *lEdit_ImageTable_Search_Recode;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbl_ImageTable_Target_Count;
    QLineEdit *lEdit_ImageTable_Target_Count;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSave_As;
    QMenu *menuEdit;
    QMenu *menuImage;
    QMenu *menuType;
    QMenu *menuColor;
    QMenu *menuTransform;
    QMenu *menuZoom;
    QMenu *menuMask;
    QMenu *menuProcess;
    QMenu *menuAnalyze;
    QMenu *menuML_DL;
    QMenu *menu;
    QMenu *menuFeature_Extraction;
    QMenu *menuML;
    QMenu *menuClassification;
    QMenu *menuRegressor;
    QMenu *menuClustering;
    QMenu *menuDL;
    QMenu *menuClassification_2;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QMenu *menuCamera;
    QMenu *menuVideo;
    QMenu *menuLocal_Feature;
    QMenu *menuKeyPoint;
    QMenu *menuDescriptor;
    QMenu *menuKeyPoint_Descriptor;
    QMenu *menuDetector;
    QMenu *menuHough;
    QMenu *menuTemplate_Matching;
    QMenu *menuFitting;
    QMenu *menuMition;
    QMenu *menuKalman_Filter;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(811, 257);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setAcceptDrops(true);
        MainWindow->setDockNestingEnabled(false);
        actionCross_Line = new QAction(MainWindow);
        actionCross_Line->setObjectName(QString::fromUtf8("actionCross_Line"));
        actionCross_Line->setCheckable(true);
        actionProfile = new QAction(MainWindow);
        actionProfile->setObjectName(QString::fromUtf8("actionProfile"));
        actionProfile->setCheckable(true);
        actionROI = new QAction(MainWindow);
        actionROI->setObjectName(QString::fromUtf8("actionROI"));
        actionROI->setCheckable(true);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClose_All = new QAction(MainWindow);
        actionClose_All->setObjectName(QString::fromUtf8("actionClose_All"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionBMP = new QAction(MainWindow);
        actionBMP->setObjectName(QString::fromUtf8("actionBMP"));
        actionJPEG = new QAction(MainWindow);
        actionJPEG->setObjectName(QString::fromUtf8("actionJPEG"));
        actionPNG = new QAction(MainWindow);
        actionPNG->setObjectName(QString::fromUtf8("actionPNG"));
        actionCSV = new QAction(MainWindow);
        actionCSV->setObjectName(QString::fromUtf8("actionCSV"));
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionClear_Outside = new QAction(MainWindow);
        actionClear_Outside->setObjectName(QString::fromUtf8("actionClear_Outside"));
        actionFill = new QAction(MainWindow);
        actionFill->setObjectName(QString::fromUtf8("actionFill"));
        actionInvert = new QAction(MainWindow);
        actionInvert->setObjectName(QString::fromUtf8("actionInvert"));
        action8_bit = new QAction(MainWindow);
        action8_bit->setObjectName(QString::fromUtf8("action8_bit"));
        action8_bit->setCheckable(true);
        actionRGB_Color = new QAction(MainWindow);
        actionRGB_Color->setObjectName(QString::fromUtf8("actionRGB_Color"));
        actionRGB_Color->setCheckable(true);
        actionShow_Info = new QAction(MainWindow);
        actionShow_Info->setObjectName(QString::fromUtf8("actionShow_Info"));
        actionSplit_Channels = new QAction(MainWindow);
        actionSplit_Channels->setObjectName(QString::fromUtf8("actionSplit_Channels"));
        actionCrop = new QAction(MainWindow);
        actionCrop->setObjectName(QString::fromUtf8("actionCrop"));
        actionDuplicate = new QAction(MainWindow);
        actionDuplicate->setObjectName(QString::fromUtf8("actionDuplicate"));
        actionRename = new QAction(MainWindow);
        actionRename->setObjectName(QString::fromUtf8("actionRename"));
        actionScale = new QAction(MainWindow);
        actionScale->setObjectName(QString::fromUtf8("actionScale"));
        actionVertical_Flip = new QAction(MainWindow);
        actionVertical_Flip->setObjectName(QString::fromUtf8("actionVertical_Flip"));
        actionHorizontal_Flip = new QAction(MainWindow);
        actionHorizontal_Flip->setObjectName(QString::fromUtf8("actionHorizontal_Flip"));
        actionRotate_90_Degree_Right = new QAction(MainWindow);
        actionRotate_90_Degree_Right->setObjectName(QString::fromUtf8("actionRotate_90_Degree_Right"));
        actionRotate_90_Degree_Left = new QAction(MainWindow);
        actionRotate_90_Degree_Left->setObjectName(QString::fromUtf8("actionRotate_90_Degree_Left"));
        actionRotate = new QAction(MainWindow);
        actionRotate->setObjectName(QString::fromUtf8("actionRotate"));
        actionTranslate = new QAction(MainWindow);
        actionTranslate->setObjectName(QString::fromUtf8("actionTranslate"));
        actionBin = new QAction(MainWindow);
        actionBin->setObjectName(QString::fromUtf8("actionBin"));
        actionHSV2RGB = new QAction(MainWindow);
        actionHSV2RGB->setObjectName(QString::fromUtf8("actionHSV2RGB"));
        actionRGB2HSV = new QAction(MainWindow);
        actionRGB2HSV->setObjectName(QString::fromUtf8("actionRGB2HSV"));
        actionRGB2Gray = new QAction(MainWindow);
        actionRGB2Gray->setObjectName(QString::fromUtf8("actionRGB2Gray"));
        actionMerge_Channels = new QAction(MainWindow);
        actionMerge_Channels->setObjectName(QString::fromUtf8("actionMerge_Channels"));
        actionEdge_Detector = new QAction(MainWindow);
        actionEdge_Detector->setObjectName(QString::fromUtf8("actionEdge_Detector"));
        actionBlur = new QAction(MainWindow);
        actionBlur->setObjectName(QString::fromUtf8("actionBlur"));
        actionFFT = new QAction(MainWindow);
        actionFFT->setObjectName(QString::fromUtf8("actionFFT"));
        actionReset_Image = new QAction(MainWindow);
        actionReset_Image->setObjectName(QString::fromUtf8("actionReset_Image"));
        actionLine_Measure = new QAction(MainWindow);
        actionLine_Measure->setObjectName(QString::fromUtf8("actionLine_Measure"));
        actionLine_Measure->setCheckable(true);
        actionAngle_Measure = new QAction(MainWindow);
        actionAngle_Measure->setObjectName(QString::fromUtf8("actionAngle_Measure"));
        actionAngle_Measure->setCheckable(true);
        actionTime_Squence = new QAction(MainWindow);
        actionTime_Squence->setObjectName(QString::fromUtf8("actionTime_Squence"));
        actionFeatures = new QAction(MainWindow);
        actionFeatures->setObjectName(QString::fromUtf8("actionFeatures"));
        actionSimple_Classifier_Model = new QAction(MainWindow);
        actionSimple_Classifier_Model->setObjectName(QString::fromUtf8("actionSimple_Classifier_Model"));
        actionObject_Detection_Model = new QAction(MainWindow);
        actionObject_Detection_Model->setObjectName(QString::fromUtf8("actionObject_Detection_Model"));
        actionGAN = new QAction(MainWindow);
        actionGAN->setObjectName(QString::fromUtf8("actionGAN"));
        actionDataset = new QAction(MainWindow);
        actionDataset->setObjectName(QString::fromUtf8("actionDataset"));
        actionUSB_Camera = new QAction(MainWindow);
        actionUSB_Camera->setObjectName(QString::fromUtf8("actionUSB_Camera"));
        actionZoomIn = new QAction(MainWindow);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        actionZoomOut = new QAction(MainWindow);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        actionOriginal_Scale = new QAction(MainWindow);
        actionOriginal_Scale->setObjectName(QString::fromUtf8("actionOriginal_Scale"));
        actionFit_View = new QAction(MainWindow);
        actionFit_View->setObjectName(QString::fromUtf8("actionFit_View"));
        actionIndicator = new QAction(MainWindow);
        actionIndicator->setObjectName(QString::fromUtf8("actionIndicator"));
        actionIndicator->setCheckable(true);
        actionJPG = new QAction(MainWindow);
        actionJPG->setObjectName(QString::fromUtf8("actionJPG"));
        actionXLSX = new QAction(MainWindow);
        actionXLSX->setObjectName(QString::fromUtf8("actionXLSX"));
        actionHarris_Corner = new QAction(MainWindow);
        actionHarris_Corner->setObjectName(QString::fromUtf8("actionHarris_Corner"));
        actionFAST_Corner = new QAction(MainWindow);
        actionFAST_Corner->setObjectName(QString::fromUtf8("actionFAST_Corner"));
        actionAGAST_Corner = new QAction(MainWindow);
        actionAGAST_Corner->setObjectName(QString::fromUtf8("actionAGAST_Corner"));
        actionMSER_Region = new QAction(MainWindow);
        actionMSER_Region->setObjectName(QString::fromUtf8("actionMSER_Region"));
        actionStar_Detector = new QAction(MainWindow);
        actionStar_Detector->setObjectName(QString::fromUtf8("actionStar_Detector"));
        actionBRIEF_Descriptor = new QAction(MainWindow);
        actionBRIEF_Descriptor->setObjectName(QString::fromUtf8("actionBRIEF_Descriptor"));
        actionFREAK_Descriptor = new QAction(MainWindow);
        actionFREAK_Descriptor->setObjectName(QString::fromUtf8("actionFREAK_Descriptor"));
        actionLATCH_Descriptor = new QAction(MainWindow);
        actionLATCH_Descriptor->setObjectName(QString::fromUtf8("actionLATCH_Descriptor"));
        actionLUCID_Descriptor = new QAction(MainWindow);
        actionLUCID_Descriptor->setObjectName(QString::fromUtf8("actionLUCID_Descriptor"));
        actionDAISY_Descriptor = new QAction(MainWindow);
        actionDAISY_Descriptor->setObjectName(QString::fromUtf8("actionDAISY_Descriptor"));
        actionMSD_Detector = new QAction(MainWindow);
        actionMSD_Detector->setObjectName(QString::fromUtf8("actionMSD_Detector"));
        actionORB = new QAction(MainWindow);
        actionORB->setObjectName(QString::fromUtf8("actionORB"));
        actionKAZE = new QAction(MainWindow);
        actionKAZE->setObjectName(QString::fromUtf8("actionKAZE"));
        actionAKAZE = new QAction(MainWindow);
        actionAKAZE->setObjectName(QString::fromUtf8("actionAKAZE"));
        actionBRISK = new QAction(MainWindow);
        actionBRISK->setObjectName(QString::fromUtf8("actionBRISK"));
        actionSIFT = new QAction(MainWindow);
        actionSIFT->setObjectName(QString::fromUtf8("actionSIFT"));
        actionSURF = new QAction(MainWindow);
        actionSURF->setObjectName(QString::fromUtf8("actionSURF"));
        actionHOG_Descriptor = new QAction(MainWindow);
        actionHOG_Descriptor->setObjectName(QString::fromUtf8("actionHOG_Descriptor"));
        actionHarrLike_Descriptor = new QAction(MainWindow);
        actionHarrLike_Descriptor->setObjectName(QString::fromUtf8("actionHarrLike_Descriptor"));
        actionLBP_Descriptor = new QAction(MainWindow);
        actionLBP_Descriptor->setObjectName(QString::fromUtf8("actionLBP_Descriptor"));
        actionMatching = new QAction(MainWindow);
        actionMatching->setObjectName(QString::fromUtf8("actionMatching"));
        actionKLT_Corner = new QAction(MainWindow);
        actionKLT_Corner->setObjectName(QString::fromUtf8("actionKLT_Corner"));
        actionHough_Line = new QAction(MainWindow);
        actionHough_Line->setObjectName(QString::fromUtf8("actionHough_Line"));
        actionHough_Circle = new QAction(MainWindow);
        actionHough_Circle->setObjectName(QString::fromUtf8("actionHough_Circle"));
        actionOptical_Flow = new QAction(MainWindow);
        actionOptical_Flow->setObjectName(QString::fromUtf8("actionOptical_Flow"));
        actionMeanshift = new QAction(MainWindow);
        actionMeanshift->setObjectName(QString::fromUtf8("actionMeanshift"));
        actionCAMshift = new QAction(MainWindow);
        actionCAMshift->setObjectName(QString::fromUtf8("actionCAMshift"));
        actionLinear_Kalman_Filter = new QAction(MainWindow);
        actionLinear_Kalman_Filter->setObjectName(QString::fromUtf8("actionLinear_Kalman_Filter"));
        actionNonLinear_Kalman_Filter = new QAction(MainWindow);
        actionNonLinear_Kalman_Filter->setObjectName(QString::fromUtf8("actionNonLinear_Kalman_Filter"));
        actionUnscented_Kalman_Filter = new QAction(MainWindow);
        actionUnscented_Kalman_Filter->setObjectName(QString::fromUtf8("actionUnscented_Kalman_Filter"));
        actionParticle_Filter = new QAction(MainWindow);
        actionParticle_Filter->setObjectName(QString::fromUtf8("actionParticle_Filter"));
        actionSurface_Plot = new QAction(MainWindow);
        actionSurface_Plot->setObjectName(QString::fromUtf8("actionSurface_Plot"));
        actionWavelet = new QAction(MainWindow);
        actionWavelet->setObjectName(QString::fromUtf8("actionWavelet"));
        actionLabeling = new QAction(MainWindow);
        actionLabeling->setObjectName(QString::fromUtf8("actionLabeling"));
        actionBinarize = new QAction(MainWindow);
        actionBinarize->setObjectName(QString::fromUtf8("actionBinarize"));
        actionMorphology = new QAction(MainWindow);
        actionMorphology->setObjectName(QString::fromUtf8("actionMorphology"));
        actionLogistic_Regression = new QAction(MainWindow);
        actionLogistic_Regression->setObjectName(QString::fromUtf8("actionLogistic_Regression"));
        actionkNN = new QAction(MainWindow);
        actionkNN->setObjectName(QString::fromUtf8("actionkNN"));
        actionLinear_Regression = new QAction(MainWindow);
        actionLinear_Regression->setObjectName(QString::fromUtf8("actionLinear_Regression"));
        actionRidge_Regression = new QAction(MainWindow);
        actionRidge_Regression->setObjectName(QString::fromUtf8("actionRidge_Regression"));
        actionLasso_Regression = new QAction(MainWindow);
        actionLasso_Regression->setObjectName(QString::fromUtf8("actionLasso_Regression"));
        actionElastic_Net_Regression = new QAction(MainWindow);
        actionElastic_Net_Regression->setObjectName(QString::fromUtf8("actionElastic_Net_Regression"));
        actionPolinominal_Linear_Regression = new QAction(MainWindow);
        actionPolinominal_Linear_Regression->setObjectName(QString::fromUtf8("actionPolinominal_Linear_Regression"));
        actionDecision_Tree_Regression = new QAction(MainWindow);
        actionDecision_Tree_Regression->setObjectName(QString::fromUtf8("actionDecision_Tree_Regression"));
        actionRandom_Foreset_Regression = new QAction(MainWindow);
        actionRandom_Foreset_Regression->setObjectName(QString::fromUtf8("actionRandom_Foreset_Regression"));
        actionSVM_Regression = new QAction(MainWindow);
        actionSVM_Regression->setObjectName(QString::fromUtf8("actionSVM_Regression"));
        actionGradient_Boost_Regression = new QAction(MainWindow);
        actionGradient_Boost_Regression->setObjectName(QString::fromUtf8("actionGradient_Boost_Regression"));
        actionGradient_Boost = new QAction(MainWindow);
        actionGradient_Boost->setObjectName(QString::fromUtf8("actionGradient_Boost"));
        actionDecision_Tree = new QAction(MainWindow);
        actionDecision_Tree->setObjectName(QString::fromUtf8("actionDecision_Tree"));
        actionRandom_Forest = new QAction(MainWindow);
        actionRandom_Forest->setObjectName(QString::fromUtf8("actionRandom_Forest"));
        actionAdaBoost = new QAction(MainWindow);
        actionAdaBoost->setObjectName(QString::fromUtf8("actionAdaBoost"));
        actionK_Means = new QAction(MainWindow);
        actionK_Means->setObjectName(QString::fromUtf8("actionK_Means"));
        actionHierarchical_Clustering = new QAction(MainWindow);
        actionHierarchical_Clustering->setObjectName(QString::fromUtf8("actionHierarchical_Clustering"));
        actionDBSCAN = new QAction(MainWindow);
        actionDBSCAN->setObjectName(QString::fromUtf8("actionDBSCAN"));
        actionPCA = new QAction(MainWindow);
        actionPCA->setObjectName(QString::fromUtf8("actionPCA"));
        actionLDA = new QAction(MainWindow);
        actionLDA->setObjectName(QString::fromUtf8("actionLDA"));
        actionSBS = new QAction(MainWindow);
        actionSBS->setObjectName(QString::fromUtf8("actionSBS"));
        actionIP_Address_Camera = new QAction(MainWindow);
        actionIP_Address_Camera->setObjectName(QString::fromUtf8("actionIP_Address_Camera"));
        action24_bit = new QAction(MainWindow);
        action24_bit->setObjectName(QString::fromUtf8("action24_bit"));
        action24_bit->setCheckable(true);
        actionGray2RGB = new QAction(MainWindow);
        actionGray2RGB->setObjectName(QString::fromUtf8("actionGray2RGB"));
        actionIDS_Camera = new QAction(MainWindow);
        actionIDS_Camera->setObjectName(QString::fromUtf8("actionIDS_Camera"));
        actionOMRON_Camera = new QAction(MainWindow);
        actionOMRON_Camera->setObjectName(QString::fromUtf8("actionOMRON_Camera"));
        actionBASLER_Camera = new QAction(MainWindow);
        actionBASLER_Camera->setObjectName(QString::fromUtf8("actionBASLER_Camera"));
        actionCOGNEX_Camera = new QAction(MainWindow);
        actionCOGNEX_Camera->setObjectName(QString::fromUtf8("actionCOGNEX_Camera"));
        actionMask = new QAction(MainWindow);
        actionMask->setObjectName(QString::fromUtf8("actionMask"));
        actionMask->setCheckable(true);
        actionMask_Import = new QAction(MainWindow);
        actionMask_Import->setObjectName(QString::fromUtf8("actionMask_Import"));
        actionMask_Export = new QAction(MainWindow);
        actionMask_Export->setObjectName(QString::fromUtf8("actionMask_Export"));
        actionMapping = new QAction(MainWindow);
        actionMapping->setObjectName(QString::fromUtf8("actionMapping"));
        actionNoise_Denoise = new QAction(MainWindow);
        actionNoise_Denoise->setObjectName(QString::fromUtf8("actionNoise_Denoise"));
        actionHistogram = new QAction(MainWindow);
        actionHistogram->setObjectName(QString::fromUtf8("actionHistogram"));
        actionUnsharp_Masking = new QAction(MainWindow);
        actionUnsharp_Masking->setObjectName(QString::fromUtf8("actionUnsharp_Masking"));
        actionShow_Histogram = new QAction(MainWindow);
        actionShow_Histogram->setObjectName(QString::fromUtf8("actionShow_Histogram"));
        actionBoarder = new QAction(MainWindow);
        actionBoarder->setObjectName(QString::fromUtf8("actionBoarder"));
        actionEllipse = new QAction(MainWindow);
        actionEllipse->setObjectName(QString::fromUtf8("actionEllipse"));
        actionEllipse->setCheckable(true);
        actionTM_SSD = new QAction(MainWindow);
        actionTM_SSD->setObjectName(QString::fromUtf8("actionTM_SSD"));
        actionTM_NSSD = new QAction(MainWindow);
        actionTM_NSSD->setObjectName(QString::fromUtf8("actionTM_NSSD"));
        action_TM_CCORR = new QAction(MainWindow);
        action_TM_CCORR->setObjectName(QString::fromUtf8("action_TM_CCORR"));
        actionTM_NCCORR = new QAction(MainWindow);
        actionTM_NCCORR->setObjectName(QString::fromUtf8("actionTM_NCCORR"));
        actionTM_CCOEFF = new QAction(MainWindow);
        actionTM_CCOEFF->setObjectName(QString::fromUtf8("actionTM_CCOEFF"));
        actionTM_NCCOEFF = new QAction(MainWindow);
        actionTM_NCCOEFF->setObjectName(QString::fromUtf8("actionTM_NCCOEFF"));
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QString::fromUtf8("actionLine"));
        actionLine->setCheckable(true);
        actionSVM = new QAction(MainWindow);
        actionSVM->setObjectName(QString::fromUtf8("actionSVM"));
        actionSimple_Annotation = new QAction(MainWindow);
        actionSimple_Annotation->setObjectName(QString::fromUtf8("actionSimple_Annotation"));
        actionROI_Annotation = new QAction(MainWindow);
        actionROI_Annotation->setObjectName(QString::fromUtf8("actionROI_Annotation"));
        actionRegressior = new QAction(MainWindow);
        actionRegressior->setObjectName(QString::fromUtf8("actionRegressior"));
        actionFeature_Vector = new QAction(MainWindow);
        actionFeature_Vector->setObjectName(QString::fromUtf8("actionFeature_Vector"));
        actionImage = new QAction(MainWindow);
        actionImage->setObjectName(QString::fromUtf8("actionImage"));
        actionObject_Detection = new QAction(MainWindow);
        actionObject_Detection->setObjectName(QString::fromUtf8("actionObject_Detection"));
        actionLanguage = new QAction(MainWindow);
        actionLanguage->setObjectName(QString::fromUtf8("actionLanguage"));
        actionGenerative = new QAction(MainWindow);
        actionGenerative->setObjectName(QString::fromUtf8("actionGenerative"));
        actionVideo_Make = new QAction(MainWindow);
        actionVideo_Make->setObjectName(QString::fromUtf8("actionVideo_Make"));
        actionVideo_Open = new QAction(MainWindow);
        actionVideo_Open->setObjectName(QString::fromUtf8("actionVideo_Open"));
        actionFitting_Line = new QAction(MainWindow);
        actionFitting_Line->setObjectName(QString::fromUtf8("actionFitting_Line"));
        actionFitting_Curve = new QAction(MainWindow);
        actionFitting_Curve->setObjectName(QString::fromUtf8("actionFitting_Curve"));
        actionFitting_Ellipse = new QAction(MainWindow);
        actionFitting_Ellipse->setObjectName(QString::fromUtf8("actionFitting_Ellipse"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rBtn_View_Mode = new QRadioButton(centralWidget);
        rBtn_View_Mode->setObjectName(QString::fromUtf8("rBtn_View_Mode"));
        rBtn_View_Mode->setChecked(true);

        verticalLayout->addWidget(rBtn_View_Mode);

        rBtn_File_Mode = new QRadioButton(centralWidget);
        rBtn_File_Mode->setObjectName(QString::fromUtf8("rBtn_File_Mode"));

        verticalLayout->addWidget(rBtn_File_Mode);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        tView_ImageTable = new ImageTableView(centralWidget);
        tView_ImageTable->setObjectName(QString::fromUtf8("tView_ImageTable"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tView_ImageTable->sizePolicy().hasHeightForWidth());
        tView_ImageTable->setSizePolicy(sizePolicy2);
        tView_ImageTable->setAcceptDrops(true);

        gridLayout_2->addWidget(tView_ImageTable, 2, 0, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        lEdit_Input_Dir = new QLineEdit(centralWidget);
        lEdit_Input_Dir->setObjectName(QString::fromUtf8("lEdit_Input_Dir"));
        lEdit_Input_Dir->setEnabled(false);

        gridLayout->addWidget(lEdit_Input_Dir, 0, 0, 1, 1);

        tBtn_Input_Dir = new QToolButton(centralWidget);
        tBtn_Input_Dir->setObjectName(QString::fromUtf8("tBtn_Input_Dir"));
        tBtn_Input_Dir->setPopupMode(QToolButton::DelayedPopup);
        tBtn_Input_Dir->setAutoRaise(false);
        tBtn_Input_Dir->setArrowType(Qt::NoArrow);

        gridLayout->addWidget(tBtn_Input_Dir, 0, 1, 1, 1);

        lEdit_Output_Dir = new QLineEdit(centralWidget);
        lEdit_Output_Dir->setObjectName(QString::fromUtf8("lEdit_Output_Dir"));
        lEdit_Output_Dir->setEnabled(false);

        gridLayout->addWidget(lEdit_Output_Dir, 1, 0, 1, 1);

        tBtn_Output_Dir = new QToolButton(centralWidget);
        tBtn_Output_Dir->setObjectName(QString::fromUtf8("tBtn_Output_Dir"));

        gridLayout->addWidget(tBtn_Output_Dir, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pBtn_ImageTable_Review = new QPushButton(centralWidget);
        pBtn_ImageTable_Review->setObjectName(QString::fromUtf8("pBtn_ImageTable_Review"));

        horizontalLayout_3->addWidget(pBtn_ImageTable_Review);

        pBtn_ImageTable_All_Check = new QPushButton(centralWidget);
        pBtn_ImageTable_All_Check->setObjectName(QString::fromUtf8("pBtn_ImageTable_All_Check"));

        horizontalLayout_3->addWidget(pBtn_ImageTable_All_Check);

        pBtn_ImageTable_All_Uncheck = new QPushButton(centralWidget);
        pBtn_ImageTable_All_Uncheck->setObjectName(QString::fromUtf8("pBtn_ImageTable_All_Uncheck"));

        horizontalLayout_3->addWidget(pBtn_ImageTable_All_Uncheck);

        lEdit_ImageTable_Search_Recode = new QLineEdit(centralWidget);
        lEdit_ImageTable_Search_Recode->setObjectName(QString::fromUtf8("lEdit_ImageTable_Search_Recode"));

        horizontalLayout_3->addWidget(lEdit_ImageTable_Search_Recode);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lbl_ImageTable_Target_Count = new QLabel(centralWidget);
        lbl_ImageTable_Target_Count->setObjectName(QString::fromUtf8("lbl_ImageTable_Target_Count"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lbl_ImageTable_Target_Count->sizePolicy().hasHeightForWidth());
        lbl_ImageTable_Target_Count->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(lbl_ImageTable_Target_Count);

        lEdit_ImageTable_Target_Count = new QLineEdit(centralWidget);
        lEdit_ImageTable_Target_Count->setObjectName(QString::fromUtf8("lEdit_ImageTable_Target_Count"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lEdit_ImageTable_Target_Count->sizePolicy().hasHeightForWidth());
        lEdit_ImageTable_Target_Count->setSizePolicy(sizePolicy4);
        lEdit_ImageTable_Target_Count->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(lEdit_ImageTable_Target_Count);


        horizontalLayout_3->addLayout(horizontalLayout_4);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 811, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSave_As = new QMenu(menuFile);
        menuSave_As->setObjectName(QString::fromUtf8("menuSave_As"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuImage = new QMenu(menuBar);
        menuImage->setObjectName(QString::fromUtf8("menuImage"));
        menuType = new QMenu(menuImage);
        menuType->setObjectName(QString::fromUtf8("menuType"));
        menuColor = new QMenu(menuImage);
        menuColor->setObjectName(QString::fromUtf8("menuColor"));
        menuTransform = new QMenu(menuImage);
        menuTransform->setObjectName(QString::fromUtf8("menuTransform"));
        menuZoom = new QMenu(menuImage);
        menuZoom->setObjectName(QString::fromUtf8("menuZoom"));
        menuMask = new QMenu(menuImage);
        menuMask->setObjectName(QString::fromUtf8("menuMask"));
        menuProcess = new QMenu(menuBar);
        menuProcess->setObjectName(QString::fromUtf8("menuProcess"));
        menuAnalyze = new QMenu(menuBar);
        menuAnalyze->setObjectName(QString::fromUtf8("menuAnalyze"));
        menuML_DL = new QMenu(menuBar);
        menuML_DL->setObjectName(QString::fromUtf8("menuML_DL"));
        menu = new QMenu(menuML_DL);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuFeature_Extraction = new QMenu(menuML_DL);
        menuFeature_Extraction->setObjectName(QString::fromUtf8("menuFeature_Extraction"));
        menuML = new QMenu(menuML_DL);
        menuML->setObjectName(QString::fromUtf8("menuML"));
        menuClassification = new QMenu(menuML);
        menuClassification->setObjectName(QString::fromUtf8("menuClassification"));
        menuRegressor = new QMenu(menuML);
        menuRegressor->setObjectName(QString::fromUtf8("menuRegressor"));
        menuClustering = new QMenu(menuML);
        menuClustering->setObjectName(QString::fromUtf8("menuClustering"));
        menuDL = new QMenu(menuML_DL);
        menuDL->setObjectName(QString::fromUtf8("menuDL"));
        menuClassification_2 = new QMenu(menuDL);
        menuClassification_2->setObjectName(QString::fromUtf8("menuClassification_2"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QString::fromUtf8("menuCamera"));
        menuVideo = new QMenu(menuBar);
        menuVideo->setObjectName(QString::fromUtf8("menuVideo"));
        menuLocal_Feature = new QMenu(menuBar);
        menuLocal_Feature->setObjectName(QString::fromUtf8("menuLocal_Feature"));
        menuKeyPoint = new QMenu(menuLocal_Feature);
        menuKeyPoint->setObjectName(QString::fromUtf8("menuKeyPoint"));
        menuDescriptor = new QMenu(menuLocal_Feature);
        menuDescriptor->setObjectName(QString::fromUtf8("menuDescriptor"));
        menuKeyPoint_Descriptor = new QMenu(menuLocal_Feature);
        menuKeyPoint_Descriptor->setObjectName(QString::fromUtf8("menuKeyPoint_Descriptor"));
        menuDetector = new QMenu(menuBar);
        menuDetector->setObjectName(QString::fromUtf8("menuDetector"));
        menuHough = new QMenu(menuDetector);
        menuHough->setObjectName(QString::fromUtf8("menuHough"));
        menuTemplate_Matching = new QMenu(menuDetector);
        menuTemplate_Matching->setObjectName(QString::fromUtf8("menuTemplate_Matching"));
        menuFitting = new QMenu(menuDetector);
        menuFitting->setObjectName(QString::fromUtf8("menuFitting"));
        menuMition = new QMenu(menuBar);
        menuMition->setObjectName(QString::fromUtf8("menuMition"));
        menuKalman_Filter = new QMenu(menuMition);
        menuKalman_Filter->setObjectName(QString::fromUtf8("menuKalman_Filter"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuImage->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuBar->addAction(menuVideo->menuAction());
        menuBar->addAction(menuProcess->menuAction());
        menuBar->addAction(menuAnalyze->menuAction());
        menuBar->addAction(menuLocal_Feature->menuAction());
        menuBar->addAction(menuDetector->menuAction());
        menuBar->addAction(menuMition->menuAction());
        menuBar->addAction(menuML_DL->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addAction(actionClose_All);
        menuFile->addAction(actionSave);
        menuFile->addAction(menuSave_As->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuSave_As->addAction(actionBMP);
        menuSave_As->addAction(actionJPG);
        menuSave_As->addAction(actionJPEG);
        menuSave_As->addAction(actionPNG);
        menuSave_As->addSeparator();
        menuSave_As->addAction(actionCSV);
        menuSave_As->addAction(actionXLSX);
        menuEdit->addAction(actionUndo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionClear);
        menuEdit->addAction(actionClear_Outside);
        menuEdit->addAction(actionFill);
        menuEdit->addAction(actionInvert);
        menuImage->addAction(menuType->menuAction());
        menuImage->addSeparator();
        menuImage->addAction(actionShow_Info);
        menuImage->addAction(menuColor->menuAction());
        menuImage->addAction(menuMask->menuAction());
        menuImage->addSeparator();
        menuImage->addAction(actionBoarder);
        menuImage->addAction(actionCrop);
        menuImage->addAction(actionDuplicate);
        menuImage->addAction(actionRename);
        menuImage->addAction(actionScale);
        menuImage->addAction(menuTransform->menuAction());
        menuImage->addSeparator();
        menuImage->addAction(menuZoom->menuAction());
        menuType->addAction(action8_bit);
        menuType->addAction(action24_bit);
        menuType->addAction(actionRGB_Color);
        menuColor->addAction(actionRGB2Gray);
        menuColor->addAction(actionGray2RGB);
        menuColor->addAction(actionRGB2HSV);
        menuColor->addAction(actionHSV2RGB);
        menuColor->addSeparator();
        menuColor->addAction(actionSplit_Channels);
        menuColor->addAction(actionMerge_Channels);
        menuTransform->addAction(actionVertical_Flip);
        menuTransform->addAction(actionHorizontal_Flip);
        menuTransform->addAction(actionRotate_90_Degree_Right);
        menuTransform->addAction(actionRotate_90_Degree_Left);
        menuTransform->addAction(actionRotate);
        menuTransform->addAction(actionTranslate);
        menuTransform->addAction(actionBin);
        menuZoom->addAction(actionZoomIn);
        menuZoom->addAction(actionZoomOut);
        menuZoom->addAction(actionOriginal_Scale);
        menuZoom->addAction(actionFit_View);
        menuMask->addAction(actionMask_Import);
        menuMask->addAction(actionMask_Export);
        menuProcess->addAction(actionBlur);
        menuProcess->addAction(actionUnsharp_Masking);
        menuProcess->addAction(actionEdge_Detector);
        menuProcess->addAction(actionMapping);
        menuProcess->addAction(actionBinarize);
        menuProcess->addAction(actionMorphology);
        menuProcess->addAction(actionNoise_Denoise);
        menuProcess->addAction(actionHistogram);
        menuAnalyze->addAction(actionLabeling);
        menuAnalyze->addSeparator();
        menuAnalyze->addAction(actionShow_Histogram);
        menuAnalyze->addAction(actionSurface_Plot);
        menuAnalyze->addSeparator();
        menuAnalyze->addAction(actionFFT);
        menuAnalyze->addAction(actionWavelet);
        menuML_DL->addAction(menu->menuAction());
        menuML_DL->addSeparator();
        menuML_DL->addAction(actionDataset);
        menuML_DL->addSeparator();
        menuML_DL->addAction(menuDL->menuAction());
        menuML_DL->addAction(menuML->menuAction());
        menuML_DL->addSeparator();
        menuML_DL->addAction(menuFeature_Extraction->menuAction());
        menu->addAction(actionSimple_Annotation);
        menu->addSeparator();
        menu->addAction(actionROI_Annotation);
        menuFeature_Extraction->addAction(actionPCA);
        menuFeature_Extraction->addAction(actionLDA);
        menuFeature_Extraction->addAction(actionSBS);
        menuML->addAction(menuClassification->menuAction());
        menuML->addAction(menuRegressor->menuAction());
        menuML->addAction(menuClustering->menuAction());
        menuClassification->addAction(actionSVM);
        menuClassification->addAction(actionLogistic_Regression);
        menuClassification->addAction(actionkNN);
        menuClassification->addSeparator();
        menuClassification->addAction(actionDecision_Tree);
        menuClassification->addAction(actionRandom_Forest);
        menuClassification->addSeparator();
        menuClassification->addAction(actionAdaBoost);
        menuClassification->addAction(actionGradient_Boost);
        menuRegressor->addAction(actionLinear_Regression);
        menuRegressor->addAction(actionPolinominal_Linear_Regression);
        menuRegressor->addSeparator();
        menuRegressor->addAction(actionRidge_Regression);
        menuRegressor->addAction(actionLasso_Regression);
        menuRegressor->addAction(actionElastic_Net_Regression);
        menuRegressor->addSeparator();
        menuRegressor->addAction(actionDecision_Tree_Regression);
        menuRegressor->addAction(actionRandom_Foreset_Regression);
        menuRegressor->addSeparator();
        menuRegressor->addAction(actionSVM_Regression);
        menuRegressor->addSeparator();
        menuRegressor->addAction(actionGradient_Boost_Regression);
        menuClustering->addAction(actionK_Means);
        menuClustering->addAction(actionHierarchical_Clustering);
        menuClustering->addAction(actionDBSCAN);
        menuDL->addAction(menuClassification_2->menuAction());
        menuDL->addAction(actionRegressior);
        menuDL->addAction(actionGenerative);
        menuClassification_2->addAction(actionFeature_Vector);
        menuClassification_2->addAction(actionImage);
        menuClassification_2->addSeparator();
        menuClassification_2->addAction(actionObject_Detection);
        menuClassification_2->addSeparator();
        menuClassification_2->addAction(actionLanguage);
        menuCamera->addAction(actionUSB_Camera);
        menuCamera->addAction(actionIP_Address_Camera);
        menuCamera->addSeparator();
        menuCamera->addAction(actionIDS_Camera);
        menuCamera->addAction(actionOMRON_Camera);
        menuCamera->addAction(actionBASLER_Camera);
        menuCamera->addAction(actionCOGNEX_Camera);
        menuVideo->addAction(actionVideo_Make);
        menuVideo->addAction(actionVideo_Open);
        menuLocal_Feature->addAction(menuKeyPoint_Descriptor->menuAction());
        menuLocal_Feature->addAction(menuKeyPoint->menuAction());
        menuLocal_Feature->addAction(menuDescriptor->menuAction());
        menuLocal_Feature->addSeparator();
        menuLocal_Feature->addAction(actionMatching);
        menuKeyPoint->addAction(actionKLT_Corner);
        menuKeyPoint->addAction(actionHarris_Corner);
        menuKeyPoint->addAction(actionFAST_Corner);
        menuKeyPoint->addAction(actionAGAST_Corner);
        menuKeyPoint->addSeparator();
        menuKeyPoint->addAction(actionMSER_Region);
        menuKeyPoint->addSeparator();
        menuKeyPoint->addAction(actionStar_Detector);
        menuKeyPoint->addAction(actionMSD_Detector);
        menuDescriptor->addAction(actionBRIEF_Descriptor);
        menuDescriptor->addAction(actionFREAK_Descriptor);
        menuDescriptor->addAction(actionLATCH_Descriptor);
        menuDescriptor->addAction(actionLUCID_Descriptor);
        menuDescriptor->addAction(actionDAISY_Descriptor);
        menuDescriptor->addSeparator();
        menuDescriptor->addAction(actionHOG_Descriptor);
        menuDescriptor->addAction(actionHarrLike_Descriptor);
        menuDescriptor->addAction(actionLBP_Descriptor);
        menuKeyPoint_Descriptor->addAction(actionORB);
        menuKeyPoint_Descriptor->addAction(actionBRISK);
        menuKeyPoint_Descriptor->addAction(actionKAZE);
        menuKeyPoint_Descriptor->addAction(actionAKAZE);
        menuKeyPoint_Descriptor->addSeparator();
        menuKeyPoint_Descriptor->addAction(actionSIFT);
        menuKeyPoint_Descriptor->addAction(actionSURF);
        menuDetector->addAction(menuHough->menuAction());
        menuDetector->addAction(menuTemplate_Matching->menuAction());
        menuDetector->addAction(menuFitting->menuAction());
        menuHough->addAction(actionHough_Line);
        menuHough->addAction(actionHough_Circle);
        menuTemplate_Matching->addAction(actionTM_SSD);
        menuTemplate_Matching->addAction(actionTM_NSSD);
        menuTemplate_Matching->addSeparator();
        menuTemplate_Matching->addAction(action_TM_CCORR);
        menuTemplate_Matching->addAction(actionTM_NCCORR);
        menuTemplate_Matching->addSeparator();
        menuTemplate_Matching->addAction(actionTM_CCOEFF);
        menuTemplate_Matching->addAction(actionTM_NCCOEFF);
        menuFitting->addAction(actionFitting_Line);
        menuFitting->addAction(actionFitting_Curve);
        menuFitting->addAction(actionFitting_Ellipse);
        menuMition->addAction(actionOptical_Flow);
        menuMition->addAction(actionMeanshift);
        menuMition->addAction(actionCAMshift);
        menuMition->addAction(menuKalman_Filter->menuAction());
        menuMition->addAction(actionParticle_Filter);
        menuKalman_Filter->addAction(actionLinear_Kalman_Filter);
        menuKalman_Filter->addSeparator();
        menuKalman_Filter->addAction(actionNonLinear_Kalman_Filter);
        menuKalman_Filter->addAction(actionUnscented_Kalman_Filter);
        toolBar->addAction(actionReset_Image);
        toolBar->addSeparator();
        toolBar->addAction(actionIndicator);
        toolBar->addAction(actionMask);
        toolBar->addAction(actionCross_Line);
        toolBar->addAction(actionProfile);
        toolBar->addSeparator();
        toolBar->addAction(actionROI);
        toolBar->addAction(actionLine);
        toolBar->addAction(actionEllipse);
        toolBar->addSeparator();
        toolBar->addAction(actionLine_Measure);
        toolBar->addAction(actionAngle_Measure);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionCross_Line->setText(QCoreApplication::translate("MainWindow", "Cross Line", nullptr));
#if QT_CONFIG(tooltip)
        actionCross_Line->setToolTip(QCoreApplication::translate("MainWindow", "Cross Line", nullptr));
#endif // QT_CONFIG(tooltip)
        actionProfile->setText(QCoreApplication::translate("MainWindow", "Profile", nullptr));
        actionROI->setText(QCoreApplication::translate("MainWindow", "ROI", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("MainWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
#if QT_CONFIG(shortcut)
        actionClose->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose_All->setText(QCoreApplication::translate("MainWindow", "Close All", nullptr));
#if QT_CONFIG(shortcut)
        actionClose_All->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBMP->setText(QCoreApplication::translate("MainWindow", "BMP", nullptr));
        actionJPEG->setText(QCoreApplication::translate("MainWindow", "JPEG", nullptr));
        actionPNG->setText(QCoreApplication::translate("MainWindow", "PNG", nullptr));
        actionCSV->setText(QCoreApplication::translate("MainWindow", "CSV", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
#if QT_CONFIG(shortcut)
        actionPrint->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        actionClear_Outside->setText(QCoreApplication::translate("MainWindow", "Clear outside", nullptr));
#if QT_CONFIG(tooltip)
        actionClear_Outside->setToolTip(QCoreApplication::translate("MainWindow", "Clear Outside", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFill->setText(QCoreApplication::translate("MainWindow", "Fill", nullptr));
        actionInvert->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        action8_bit->setText(QCoreApplication::translate("MainWindow", "8-bit", nullptr));
        actionRGB_Color->setText(QCoreApplication::translate("MainWindow", "RGB Color", nullptr));
        actionShow_Info->setText(QCoreApplication::translate("MainWindow", "Show Info", nullptr));
        actionSplit_Channels->setText(QCoreApplication::translate("MainWindow", "Split Channels", nullptr));
        actionCrop->setText(QCoreApplication::translate("MainWindow", "Crop", nullptr));
#if QT_CONFIG(shortcut)
        actionCrop->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDuplicate->setText(QCoreApplication::translate("MainWindow", "Duplicate", nullptr));
#if QT_CONFIG(shortcut)
        actionDuplicate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRename->setText(QCoreApplication::translate("MainWindow", "Rename", nullptr));
        actionScale->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
#if QT_CONFIG(shortcut)
        actionScale->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionVertical_Flip->setText(QCoreApplication::translate("MainWindow", "Vertical Flip", nullptr));
        actionHorizontal_Flip->setText(QCoreApplication::translate("MainWindow", "Horizontal Flip", nullptr));
        actionRotate_90_Degree_Right->setText(QCoreApplication::translate("MainWindow", "Rotate 90 Degree Right", nullptr));
        actionRotate_90_Degree_Left->setText(QCoreApplication::translate("MainWindow", "Rotate 90 Degree Left", nullptr));
        actionRotate->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
        actionTranslate->setText(QCoreApplication::translate("MainWindow", "Translate", nullptr));
        actionBin->setText(QCoreApplication::translate("MainWindow", "Bin", nullptr));
        actionHSV2RGB->setText(QCoreApplication::translate("MainWindow", "HSV -> RGB", nullptr));
#if QT_CONFIG(tooltip)
        actionHSV2RGB->setToolTip(QCoreApplication::translate("MainWindow", "HSV -> RGB", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRGB2HSV->setText(QCoreApplication::translate("MainWindow", "RGB -> HSV", nullptr));
#if QT_CONFIG(tooltip)
        actionRGB2HSV->setToolTip(QCoreApplication::translate("MainWindow", "RGB -> HSV", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRGB2Gray->setText(QCoreApplication::translate("MainWindow", "RGB -> Gray", nullptr));
#if QT_CONFIG(tooltip)
        actionRGB2Gray->setToolTip(QCoreApplication::translate("MainWindow", "RGB -> Gray", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMerge_Channels->setText(QCoreApplication::translate("MainWindow", "Merge Channels", nullptr));
        actionEdge_Detector->setText(QCoreApplication::translate("MainWindow", "Edge Detector", nullptr));
#if QT_CONFIG(tooltip)
        actionEdge_Detector->setToolTip(QCoreApplication::translate("MainWindow", "Detect Edge", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBlur->setText(QCoreApplication::translate("MainWindow", "Blur", nullptr));
#if QT_CONFIG(tooltip)
        actionBlur->setToolTip(QCoreApplication::translate("MainWindow", "Blur Filter", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFFT->setText(QCoreApplication::translate("MainWindow", "FFT", nullptr));
        actionReset_Image->setText(QCoreApplication::translate("MainWindow", "Reset Image", nullptr));
        actionLine_Measure->setText(QCoreApplication::translate("MainWindow", "Line Measure", nullptr));
        actionAngle_Measure->setText(QCoreApplication::translate("MainWindow", "Angle Measure", nullptr));
        actionTime_Squence->setText(QCoreApplication::translate("MainWindow", "Time Squence", nullptr));
        actionFeatures->setText(QCoreApplication::translate("MainWindow", "Features", nullptr));
        actionSimple_Classifier_Model->setText(QCoreApplication::translate("MainWindow", "Simple Classifier Model", nullptr));
        actionObject_Detection_Model->setText(QCoreApplication::translate("MainWindow", "Object Detection Model", nullptr));
        actionGAN->setText(QCoreApplication::translate("MainWindow", "GAN", nullptr));
#if QT_CONFIG(tooltip)
        actionGAN->setToolTip(QCoreApplication::translate("MainWindow", "Generate Model", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDataset->setText(QCoreApplication::translate("MainWindow", "Dataset", nullptr));
        actionUSB_Camera->setText(QCoreApplication::translate("MainWindow", "USB", nullptr));
        actionZoomIn->setText(QCoreApplication::translate("MainWindow", "In [+]", nullptr));
        actionZoomOut->setText(QCoreApplication::translate("MainWindow", "Out [-]", nullptr));
#if QT_CONFIG(tooltip)
        actionZoomOut->setToolTip(QCoreApplication::translate("MainWindow", "Out [-]", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOriginal_Scale->setText(QCoreApplication::translate("MainWindow", "Original Scale", nullptr));
        actionFit_View->setText(QCoreApplication::translate("MainWindow", "Fit View", nullptr));
        actionIndicator->setText(QCoreApplication::translate("MainWindow", "Indicator", nullptr));
        actionJPG->setText(QCoreApplication::translate("MainWindow", "JPG", nullptr));
        actionXLSX->setText(QCoreApplication::translate("MainWindow", "XLSX", nullptr));
        actionHarris_Corner->setText(QCoreApplication::translate("MainWindow", "Harris Corner", nullptr));
#if QT_CONFIG(tooltip)
        actionHarris_Corner->setToolTip(QCoreApplication::translate("MainWindow", "Harris Corner", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFAST_Corner->setText(QCoreApplication::translate("MainWindow", "FAST Corner", nullptr));
        actionAGAST_Corner->setText(QCoreApplication::translate("MainWindow", "AGAST Corner", nullptr));
        actionMSER_Region->setText(QCoreApplication::translate("MainWindow", "MSER Region", nullptr));
#if QT_CONFIG(tooltip)
        actionMSER_Region->setToolTip(QCoreApplication::translate("MainWindow", "MSER Region", nullptr));
#endif // QT_CONFIG(tooltip)
        actionStar_Detector->setText(QCoreApplication::translate("MainWindow", "Star Detector", nullptr));
        actionBRIEF_Descriptor->setText(QCoreApplication::translate("MainWindow", "BRIEF Descriptor", nullptr));
        actionFREAK_Descriptor->setText(QCoreApplication::translate("MainWindow", "FREAK Descriptor", nullptr));
        actionLATCH_Descriptor->setText(QCoreApplication::translate("MainWindow", "LATCH Descriptor", nullptr));
        actionLUCID_Descriptor->setText(QCoreApplication::translate("MainWindow", "LUCID Descriptor", nullptr));
        actionDAISY_Descriptor->setText(QCoreApplication::translate("MainWindow", "DAISY Descriptor", nullptr));
        actionMSD_Detector->setText(QCoreApplication::translate("MainWindow", "MSD Detector", nullptr));
        actionORB->setText(QCoreApplication::translate("MainWindow", "ORB", nullptr));
        actionKAZE->setText(QCoreApplication::translate("MainWindow", "KAZE", nullptr));
        actionAKAZE->setText(QCoreApplication::translate("MainWindow", "AKAZE", nullptr));
        actionBRISK->setText(QCoreApplication::translate("MainWindow", "BRISK", nullptr));
        actionSIFT->setText(QCoreApplication::translate("MainWindow", "SIFT", nullptr));
        actionSURF->setText(QCoreApplication::translate("MainWindow", "SURF", nullptr));
        actionHOG_Descriptor->setText(QCoreApplication::translate("MainWindow", "HOG Descriptor", nullptr));
        actionHarrLike_Descriptor->setText(QCoreApplication::translate("MainWindow", "HarrLike Descriptor", nullptr));
        actionLBP_Descriptor->setText(QCoreApplication::translate("MainWindow", "LBP Descriptor", nullptr));
        actionMatching->setText(QCoreApplication::translate("MainWindow", "Matching", nullptr));
        actionKLT_Corner->setText(QCoreApplication::translate("MainWindow", "KLT Corner", nullptr));
        actionHough_Line->setText(QCoreApplication::translate("MainWindow", "Hough Line", nullptr));
        actionHough_Circle->setText(QCoreApplication::translate("MainWindow", "Hough Circle", nullptr));
        actionOptical_Flow->setText(QCoreApplication::translate("MainWindow", "Optical Flow", nullptr));
        actionMeanshift->setText(QCoreApplication::translate("MainWindow", "Meanshift", nullptr));
        actionCAMshift->setText(QCoreApplication::translate("MainWindow", "CAMshift", nullptr));
        actionLinear_Kalman_Filter->setText(QCoreApplication::translate("MainWindow", "Linear Kalman Filter", nullptr));
        actionNonLinear_Kalman_Filter->setText(QCoreApplication::translate("MainWindow", "NonLinear Kalman Filter", nullptr));
        actionUnscented_Kalman_Filter->setText(QCoreApplication::translate("MainWindow", "Unscented Kalman Filter", nullptr));
        actionParticle_Filter->setText(QCoreApplication::translate("MainWindow", "Particle Filter", nullptr));
        actionSurface_Plot->setText(QCoreApplication::translate("MainWindow", "Surface Plot", nullptr));
        actionWavelet->setText(QCoreApplication::translate("MainWindow", "Wavelet", nullptr));
        actionLabeling->setText(QCoreApplication::translate("MainWindow", "Labeling", nullptr));
        actionBinarize->setText(QCoreApplication::translate("MainWindow", "Binarize", nullptr));
        actionMorphology->setText(QCoreApplication::translate("MainWindow", "Morphology", nullptr));
        actionLogistic_Regression->setText(QCoreApplication::translate("MainWindow", "Logistic Regression", nullptr));
        actionkNN->setText(QCoreApplication::translate("MainWindow", "kNN", nullptr));
        actionLinear_Regression->setText(QCoreApplication::translate("MainWindow", "Linear Regression", nullptr));
        actionRidge_Regression->setText(QCoreApplication::translate("MainWindow", "Ridge Regression", nullptr));
        actionLasso_Regression->setText(QCoreApplication::translate("MainWindow", "Lasso Regression", nullptr));
        actionElastic_Net_Regression->setText(QCoreApplication::translate("MainWindow", "Elastic Net Regression", nullptr));
        actionPolinominal_Linear_Regression->setText(QCoreApplication::translate("MainWindow", "Polinominal Linear Regression", nullptr));
        actionDecision_Tree_Regression->setText(QCoreApplication::translate("MainWindow", "Decision Tree Regression", nullptr));
        actionRandom_Foreset_Regression->setText(QCoreApplication::translate("MainWindow", "Random Foreset Regression", nullptr));
        actionSVM_Regression->setText(QCoreApplication::translate("MainWindow", "SVM Regression", nullptr));
        actionGradient_Boost_Regression->setText(QCoreApplication::translate("MainWindow", "Gradient Boost Regression", nullptr));
        actionGradient_Boost->setText(QCoreApplication::translate("MainWindow", "Gradient Boost", nullptr));
        actionDecision_Tree->setText(QCoreApplication::translate("MainWindow", "Decision Tree", nullptr));
        actionRandom_Forest->setText(QCoreApplication::translate("MainWindow", "Random Forest", nullptr));
        actionAdaBoost->setText(QCoreApplication::translate("MainWindow", "AdaBoost", nullptr));
        actionK_Means->setText(QCoreApplication::translate("MainWindow", "K Means", nullptr));
        actionHierarchical_Clustering->setText(QCoreApplication::translate("MainWindow", "Hierarchical Clustering", nullptr));
        actionDBSCAN->setText(QCoreApplication::translate("MainWindow", "DBSCAN", nullptr));
        actionPCA->setText(QCoreApplication::translate("MainWindow", "PCA", nullptr));
        actionLDA->setText(QCoreApplication::translate("MainWindow", "LDA", nullptr));
        actionSBS->setText(QCoreApplication::translate("MainWindow", "SBS", nullptr));
        actionIP_Address_Camera->setText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        action24_bit->setText(QCoreApplication::translate("MainWindow", "24-bit", nullptr));
        actionGray2RGB->setText(QCoreApplication::translate("MainWindow", "Gray -> RGB", nullptr));
#if QT_CONFIG(tooltip)
        actionGray2RGB->setToolTip(QCoreApplication::translate("MainWindow", "Gray -> RGB", nullptr));
#endif // QT_CONFIG(tooltip)
        actionIDS_Camera->setText(QCoreApplication::translate("MainWindow", "IDS", nullptr));
#if QT_CONFIG(tooltip)
        actionIDS_Camera->setToolTip(QCoreApplication::translate("MainWindow", "IDS Camera USB or GigE Interface", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOMRON_Camera->setText(QCoreApplication::translate("MainWindow", "OMRON", nullptr));
#if QT_CONFIG(tooltip)
        actionOMRON_Camera->setToolTip(QCoreApplication::translate("MainWindow", "Omron sentech camera USB or GigE Interface", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBASLER_Camera->setText(QCoreApplication::translate("MainWindow", "BASLER", nullptr));
#if QT_CONFIG(tooltip)
        actionBASLER_Camera->setToolTip(QCoreApplication::translate("MainWindow", "BALSER Camera USB or GigE Interface", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCOGNEX_Camera->setText(QCoreApplication::translate("MainWindow", "COGNEX", nullptr));
#if QT_CONFIG(tooltip)
        actionCOGNEX_Camera->setToolTip(QCoreApplication::translate("MainWindow", "COGNEX Camera USB or GigE Interface", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMask->setText(QCoreApplication::translate("MainWindow", "Mask", nullptr));
#if QT_CONFIG(tooltip)
        actionMask->setToolTip(QCoreApplication::translate("MainWindow", "Show or Hide Mask", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMask_Import->setText(QCoreApplication::translate("MainWindow", "Import Mask", nullptr));
        actionMask_Export->setText(QCoreApplication::translate("MainWindow", "Export Mask", nullptr));
        actionMapping->setText(QCoreApplication::translate("MainWindow", "Mapping", nullptr));
#if QT_CONFIG(tooltip)
        actionMapping->setToolTip(QCoreApplication::translate("MainWindow", "Mapping image color", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNoise_Denoise->setText(QCoreApplication::translate("MainWindow", "Noise/Denoise", nullptr));
        actionHistogram->setText(QCoreApplication::translate("MainWindow", "Histogram", nullptr));
        actionUnsharp_Masking->setText(QCoreApplication::translate("MainWindow", "Unsharp Masking", nullptr));
        actionShow_Histogram->setText(QCoreApplication::translate("MainWindow", "Show Histogram", nullptr));
#if QT_CONFIG(tooltip)
        actionShow_Histogram->setToolTip(QCoreApplication::translate("MainWindow", "Show Histogram", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBoarder->setText(QCoreApplication::translate("MainWindow", "Boarder", nullptr));
        actionEllipse->setText(QCoreApplication::translate("MainWindow", "Ellipse", nullptr));
        actionTM_SSD->setText(QCoreApplication::translate("MainWindow", "SSD", nullptr));
#if QT_CONFIG(tooltip)
        actionTM_SSD->setToolTip(QCoreApplication::translate("MainWindow", "Sum of Square Difference", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTM_NSSD->setText(QCoreApplication::translate("MainWindow", "NSSD", nullptr));
#if QT_CONFIG(tooltip)
        actionTM_NSSD->setToolTip(QCoreApplication::translate("MainWindow", "Normalized Sum of Square Difference", nullptr));
#endif // QT_CONFIG(tooltip)
        action_TM_CCORR->setText(QCoreApplication::translate("MainWindow", "CCORR", nullptr));
#if QT_CONFIG(tooltip)
        action_TM_CCORR->setToolTip(QCoreApplication::translate("MainWindow", "Cross Correlation", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTM_NCCORR->setText(QCoreApplication::translate("MainWindow", "NCCORR", nullptr));
#if QT_CONFIG(tooltip)
        actionTM_NCCORR->setToolTip(QCoreApplication::translate("MainWindow", "Normalized Cross Correlation", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTM_CCOEFF->setText(QCoreApplication::translate("MainWindow", "CCOEFF", nullptr));
#if QT_CONFIG(tooltip)
        actionTM_CCOEFF->setToolTip(QCoreApplication::translate("MainWindow", "Cross Coefficient", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTM_NCCOEFF->setText(QCoreApplication::translate("MainWindow", "NCCOEFF", nullptr));
#if QT_CONFIG(tooltip)
        actionTM_NCCOEFF->setToolTip(QCoreApplication::translate("MainWindow", "Normalized Cross Coefficient", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLine->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        actionSVM->setText(QCoreApplication::translate("MainWindow", "SVM", nullptr));
        actionSimple_Annotation->setText(QCoreApplication::translate("MainWindow", "Simple Annotation", nullptr));
        actionROI_Annotation->setText(QCoreApplication::translate("MainWindow", "ROI Annotation", nullptr));
        actionRegressior->setText(QCoreApplication::translate("MainWindow", "Regressior", nullptr));
        actionFeature_Vector->setText(QCoreApplication::translate("MainWindow", "Feature Vector", nullptr));
        actionImage->setText(QCoreApplication::translate("MainWindow", "Image", nullptr));
        actionObject_Detection->setText(QCoreApplication::translate("MainWindow", "Object Detection", nullptr));
        actionLanguage->setText(QCoreApplication::translate("MainWindow", "Language", nullptr));
#if QT_CONFIG(tooltip)
        actionLanguage->setToolTip(QCoreApplication::translate("MainWindow", "Language", nullptr));
#endif // QT_CONFIG(tooltip)
        actionGenerative->setText(QCoreApplication::translate("MainWindow", "Generative", nullptr));
        actionVideo_Make->setText(QCoreApplication::translate("MainWindow", "Video Make", nullptr));
        actionVideo_Open->setText(QCoreApplication::translate("MainWindow", "Video Open", nullptr));
        actionFitting_Line->setText(QCoreApplication::translate("MainWindow", "Fitting Line", nullptr));
        actionFitting_Curve->setText(QCoreApplication::translate("MainWindow", "Fitting Curve", nullptr));
        actionFitting_Ellipse->setText(QCoreApplication::translate("MainWindow", "Fitting Ellipse", nullptr));
        rBtn_View_Mode->setText(QCoreApplication::translate("MainWindow", "View", nullptr));
        rBtn_File_Mode->setText(QCoreApplication::translate("MainWindow", "File", nullptr));
        lEdit_Input_Dir->setPlaceholderText(QCoreApplication::translate("MainWindow", "Input Directory", nullptr));
        tBtn_Input_Dir->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        lEdit_Output_Dir->setPlaceholderText(QCoreApplication::translate("MainWindow", "Output Directory", nullptr));
        tBtn_Output_Dir->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        pBtn_ImageTable_Review->setText(QCoreApplication::translate("MainWindow", "Review", nullptr));
        pBtn_ImageTable_All_Check->setText(QCoreApplication::translate("MainWindow", "All Check", nullptr));
        pBtn_ImageTable_All_Uncheck->setText(QCoreApplication::translate("MainWindow", "All Uncheck", nullptr));
        lEdit_ImageTable_Search_Recode->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search Name", nullptr));
        lbl_ImageTable_Target_Count->setText(QCoreApplication::translate("MainWindow", "Target Count", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSave_As->setTitle(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuImage->setTitle(QCoreApplication::translate("MainWindow", "Image", nullptr));
        menuType->setTitle(QCoreApplication::translate("MainWindow", "Type", nullptr));
        menuColor->setTitle(QCoreApplication::translate("MainWindow", "Color", nullptr));
        menuTransform->setTitle(QCoreApplication::translate("MainWindow", "Transform", nullptr));
        menuZoom->setTitle(QCoreApplication::translate("MainWindow", "Zoom", nullptr));
        menuMask->setTitle(QCoreApplication::translate("MainWindow", "Mask", nullptr));
        menuProcess->setTitle(QCoreApplication::translate("MainWindow", "Process", nullptr));
        menuAnalyze->setTitle(QCoreApplication::translate("MainWindow", "Analyze", nullptr));
        menuML_DL->setTitle(QCoreApplication::translate("MainWindow", "ML/DL", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "Annotation", nullptr));
        menuFeature_Extraction->setTitle(QCoreApplication::translate("MainWindow", "Feature Extraction", nullptr));
        menuML->setTitle(QCoreApplication::translate("MainWindow", "ML", nullptr));
        menuClassification->setTitle(QCoreApplication::translate("MainWindow", "Classification", nullptr));
        menuRegressor->setTitle(QCoreApplication::translate("MainWindow", "Regressor", nullptr));
        menuClustering->setTitle(QCoreApplication::translate("MainWindow", "Clustering", nullptr));
        menuDL->setTitle(QCoreApplication::translate("MainWindow", "DL", nullptr));
        menuClassification_2->setTitle(QCoreApplication::translate("MainWindow", "Classification", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("MainWindow", "Window", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuCamera->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        menuVideo->setTitle(QCoreApplication::translate("MainWindow", "Video", nullptr));
        menuLocal_Feature->setTitle(QCoreApplication::translate("MainWindow", "Local Feature", nullptr));
        menuKeyPoint->setTitle(QCoreApplication::translate("MainWindow", "KeyPoint", nullptr));
        menuDescriptor->setTitle(QCoreApplication::translate("MainWindow", "Descriptor", nullptr));
        menuKeyPoint_Descriptor->setTitle(QCoreApplication::translate("MainWindow", "KeyPoint&Descriptor", nullptr));
        menuDetector->setTitle(QCoreApplication::translate("MainWindow", "Detector", nullptr));
        menuHough->setTitle(QCoreApplication::translate("MainWindow", "Hough", nullptr));
        menuTemplate_Matching->setTitle(QCoreApplication::translate("MainWindow", "Template Matching", nullptr));
        menuFitting->setTitle(QCoreApplication::translate("MainWindow", "Fitting", nullptr));
        menuMition->setTitle(QCoreApplication::translate("MainWindow", "Motion Tracking", nullptr));
        menuKalman_Filter->setTitle(QCoreApplication::translate("MainWindow", "Kalman Filter", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
