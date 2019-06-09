/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ServerClass
{
public:
    QAction *actionAbout;
    QAction *actionServices;
    QAction *actionHide;
    QAction *actionHide_Others;
    QAction *actionShow_All;
    QAction *actionQuit;
    QAction *actionService;
    QAction *actionAuthority;
    QAction *actionMessages;
    QAction *actionVideo;
    QAction *actionAudio;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionFilt_on_Screen;
    QAction *action100;
    QAction *action200;
    QAction *actionScreen_Mode;
    QAction *actionRulers;
    QAction *actionHide_2;
    QAction *actionShow;
    QAction *actionConnectin_Editor;
    QAction *actionExtension_Manager;
    QAction *actionModule_Panel;
    QAction *actionToolbars;
    QAction *actionLayout;
    QAction *actionError_Log;
    QAction *actionGeneral_Editor;
    QAction *actionOutliner;
    QAction *actionWorkspace;
    QAction *actionSearch;
    QAction *actionKeyboard_Shortcuts;
    QAction *actionServices_and_Support;
    QAction *actionTutorials;
    QAction *actionReport_a_Problem;
    QAction *actionCheck_for_Upadates;
    QAction *actionSystem_info;
    QAction *actionHome_Page;
    QAction *actionNew_Scence;
    QAction *actionOpen_Scence;
    QAction *actionSave_Scence;
    QAction *actionSave_Scence_As;
    QAction *actionClose;
    QAction *actionClose_All;
    QAction *actionAdd_Data;
    QAction *actionDownload_Sample_Data;
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionView_Image;
    QAction *actionView_Sequence;
    QAction *actionProject_Window;
    QAction *actionSet_Project;
    QAction *actionRecent_Files;
    QAction *actionRecent_Increments;
    QAction *actionRecent_Projects;
    QAction *actionPrint;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionRepeat;
    QAction *actionRecent_Command_List;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionDelete;
    QAction *actionDelete_All_by_Type;
    QAction *actionSelect_Tool;
    QAction *action_4;
    QAction *actionSelect_All;
    QAction *actionDeselect_All;
    QAction *actionInvert_Selection;
    QAction *actionSelect_All_by_Type;
    QAction *actionDuplicate;
    QAction *actionEdit_mask;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame;
    QPushButton *button_LoadData;
    QPushButton *toolButton_21;
    QPushButton *toolButton_19;
    QPushButton *overlap_button;
    QPushButton *toolButton_26;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QPushButton *toolButton_22;
    QPushButton *toolButton_23;
    QPushButton *toolButton_24;
    QPushButton *toolButton_25;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_5;
    QPushButton *btn_brush;
    QFrame *line_6;
    QPushButton *btn_clear;
    QComboBox *comboBox_brush;
    QSlider *horizontalSlider_size;
    QLabel *label_size;
    QLabel *label_px;
    QPushButton *btn_volume;
    QPushButton *btn_screenshot;
    QPushButton *btn_audio;
    QComboBox *comboBox_screenshotWin;
    QPushButton *btn_3D;
    QSlider *horizontalSlider_brightness;
    QLabel *label_brightness;
    QLabel *label_contrast;
    QSlider *horizontalSlider_contrast;
    QWidget *plugin_widget;
    QPushButton *but_seg;
    QPushButton *btn_save;
    QPushButton *button_EditMask;
    QPushButton *button_OriginalPoints;
    QPushButton *button_NewPoints;
    QFrame *line_4;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_1;
    QVTKWidget *qvtkWidget_y;
    QFrame *line_10;
    QScrollBar *horizontalScrollBar_x;
    QVTKWidget *qvtkWidget_x;
    QScrollBar *horizontalScrollBar_z;
    QVTKWidget *qvtkWidget_xyz;
    QVTKWidget *qvtkWidget_z;
    QScrollBar *horizontalScrollBar_0;
    QFrame *line_11;
    QScrollBar *horizontalScrollBar_y;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit_mask;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ServerClass)
    {
        if (ServerClass->objectName().isEmpty())
            ServerClass->setObjectName(QStringLiteral("ServerClass"));
        ServerClass->resize(1118, 1025);
        actionAbout = new QAction(ServerClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionServices = new QAction(ServerClass);
        actionServices->setObjectName(QStringLiteral("actionServices"));
        actionHide = new QAction(ServerClass);
        actionHide->setObjectName(QStringLiteral("actionHide"));
        actionHide_Others = new QAction(ServerClass);
        actionHide_Others->setObjectName(QStringLiteral("actionHide_Others"));
        actionShow_All = new QAction(ServerClass);
        actionShow_All->setObjectName(QStringLiteral("actionShow_All"));
        actionShow_All->setEnabled(false);
        actionQuit = new QAction(ServerClass);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionService = new QAction(ServerClass);
        actionService->setObjectName(QStringLiteral("actionService"));
        actionAuthority = new QAction(ServerClass);
        actionAuthority->setObjectName(QStringLiteral("actionAuthority"));
        actionMessages = new QAction(ServerClass);
        actionMessages->setObjectName(QStringLiteral("actionMessages"));
        actionVideo = new QAction(ServerClass);
        actionVideo->setObjectName(QStringLiteral("actionVideo"));
        actionAudio = new QAction(ServerClass);
        actionAudio->setObjectName(QStringLiteral("actionAudio"));
        actionZoom_In = new QAction(ServerClass);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        actionZoom_Out = new QAction(ServerClass);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        actionFilt_on_Screen = new QAction(ServerClass);
        actionFilt_on_Screen->setObjectName(QStringLiteral("actionFilt_on_Screen"));
        action100 = new QAction(ServerClass);
        action100->setObjectName(QStringLiteral("action100"));
        action200 = new QAction(ServerClass);
        action200->setObjectName(QStringLiteral("action200"));
        actionScreen_Mode = new QAction(ServerClass);
        actionScreen_Mode->setObjectName(QStringLiteral("actionScreen_Mode"));
        actionRulers = new QAction(ServerClass);
        actionRulers->setObjectName(QStringLiteral("actionRulers"));
        actionHide_2 = new QAction(ServerClass);
        actionHide_2->setObjectName(QStringLiteral("actionHide_2"));
        actionHide_2->setCheckable(false);
        actionShow = new QAction(ServerClass);
        actionShow->setObjectName(QStringLiteral("actionShow"));
        actionConnectin_Editor = new QAction(ServerClass);
        actionConnectin_Editor->setObjectName(QStringLiteral("actionConnectin_Editor"));
        actionExtension_Manager = new QAction(ServerClass);
        actionExtension_Manager->setObjectName(QStringLiteral("actionExtension_Manager"));
        actionModule_Panel = new QAction(ServerClass);
        actionModule_Panel->setObjectName(QStringLiteral("actionModule_Panel"));
        actionToolbars = new QAction(ServerClass);
        actionToolbars->setObjectName(QStringLiteral("actionToolbars"));
        actionLayout = new QAction(ServerClass);
        actionLayout->setObjectName(QStringLiteral("actionLayout"));
        actionError_Log = new QAction(ServerClass);
        actionError_Log->setObjectName(QStringLiteral("actionError_Log"));
        actionGeneral_Editor = new QAction(ServerClass);
        actionGeneral_Editor->setObjectName(QStringLiteral("actionGeneral_Editor"));
        actionOutliner = new QAction(ServerClass);
        actionOutliner->setObjectName(QStringLiteral("actionOutliner"));
        actionWorkspace = new QAction(ServerClass);
        actionWorkspace->setObjectName(QStringLiteral("actionWorkspace"));
        actionSearch = new QAction(ServerClass);
        actionSearch->setObjectName(QStringLiteral("actionSearch"));
        actionKeyboard_Shortcuts = new QAction(ServerClass);
        actionKeyboard_Shortcuts->setObjectName(QStringLiteral("actionKeyboard_Shortcuts"));
        actionServices_and_Support = new QAction(ServerClass);
        actionServices_and_Support->setObjectName(QStringLiteral("actionServices_and_Support"));
        actionTutorials = new QAction(ServerClass);
        actionTutorials->setObjectName(QStringLiteral("actionTutorials"));
        actionReport_a_Problem = new QAction(ServerClass);
        actionReport_a_Problem->setObjectName(QStringLiteral("actionReport_a_Problem"));
        actionCheck_for_Upadates = new QAction(ServerClass);
        actionCheck_for_Upadates->setObjectName(QStringLiteral("actionCheck_for_Upadates"));
        actionSystem_info = new QAction(ServerClass);
        actionSystem_info->setObjectName(QStringLiteral("actionSystem_info"));
        actionHome_Page = new QAction(ServerClass);
        actionHome_Page->setObjectName(QStringLiteral("actionHome_Page"));
        actionNew_Scence = new QAction(ServerClass);
        actionNew_Scence->setObjectName(QStringLiteral("actionNew_Scence"));
        actionOpen_Scence = new QAction(ServerClass);
        actionOpen_Scence->setObjectName(QStringLiteral("actionOpen_Scence"));
        actionSave_Scence = new QAction(ServerClass);
        actionSave_Scence->setObjectName(QStringLiteral("actionSave_Scence"));
        actionSave_Scence_As = new QAction(ServerClass);
        actionSave_Scence_As->setObjectName(QStringLiteral("actionSave_Scence_As"));
        actionClose = new QAction(ServerClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionClose_All = new QAction(ServerClass);
        actionClose_All->setObjectName(QStringLiteral("actionClose_All"));
        actionAdd_Data = new QAction(ServerClass);
        actionAdd_Data->setObjectName(QStringLiteral("actionAdd_Data"));
        actionDownload_Sample_Data = new QAction(ServerClass);
        actionDownload_Sample_Data->setObjectName(QStringLiteral("actionDownload_Sample_Data"));
        actionImport = new QAction(ServerClass);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        actionExport = new QAction(ServerClass);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        actionView_Image = new QAction(ServerClass);
        actionView_Image->setObjectName(QStringLiteral("actionView_Image"));
        actionView_Sequence = new QAction(ServerClass);
        actionView_Sequence->setObjectName(QStringLiteral("actionView_Sequence"));
        actionProject_Window = new QAction(ServerClass);
        actionProject_Window->setObjectName(QStringLiteral("actionProject_Window"));
        actionSet_Project = new QAction(ServerClass);
        actionSet_Project->setObjectName(QStringLiteral("actionSet_Project"));
        actionRecent_Files = new QAction(ServerClass);
        actionRecent_Files->setObjectName(QStringLiteral("actionRecent_Files"));
        actionRecent_Increments = new QAction(ServerClass);
        actionRecent_Increments->setObjectName(QStringLiteral("actionRecent_Increments"));
        actionRecent_Increments->setEnabled(false);
        actionRecent_Projects = new QAction(ServerClass);
        actionRecent_Projects->setObjectName(QStringLiteral("actionRecent_Projects"));
        actionPrint = new QAction(ServerClass);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        actionUndo = new QAction(ServerClass);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(ServerClass);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionRepeat = new QAction(ServerClass);
        actionRepeat->setObjectName(QStringLiteral("actionRepeat"));
        actionRecent_Command_List = new QAction(ServerClass);
        actionRecent_Command_List->setObjectName(QStringLiteral("actionRecent_Command_List"));
        actionCut = new QAction(ServerClass);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(ServerClass);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(ServerClass);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionDelete = new QAction(ServerClass);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        actionDelete_All_by_Type = new QAction(ServerClass);
        actionDelete_All_by_Type->setObjectName(QStringLiteral("actionDelete_All_by_Type"));
        actionSelect_Tool = new QAction(ServerClass);
        actionSelect_Tool->setObjectName(QStringLiteral("actionSelect_Tool"));
        action_4 = new QAction(ServerClass);
        action_4->setObjectName(QStringLiteral("action_4"));
        actionSelect_All = new QAction(ServerClass);
        actionSelect_All->setObjectName(QStringLiteral("actionSelect_All"));
        actionDeselect_All = new QAction(ServerClass);
        actionDeselect_All->setObjectName(QStringLiteral("actionDeselect_All"));
        actionInvert_Selection = new QAction(ServerClass);
        actionInvert_Selection->setObjectName(QStringLiteral("actionInvert_Selection"));
        actionSelect_All_by_Type = new QAction(ServerClass);
        actionSelect_All_by_Type->setObjectName(QStringLiteral("actionSelect_All_by_Type"));
        actionDuplicate = new QAction(ServerClass);
        actionDuplicate->setObjectName(QStringLiteral("actionDuplicate"));
        actionEdit_mask = new QAction(ServerClass);
        actionEdit_mask->setObjectName(QStringLiteral("actionEdit_mask"));
        centralWidget = new QWidget(ServerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(20, 20, 20);"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(220, 0));
        frame->setMaximumSize(QSize(220, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        button_LoadData = new QPushButton(frame);
        button_LoadData->setObjectName(QStringLiteral("button_LoadData"));
        button_LoadData->setGeometry(QRect(10, 20, 95, 40));
        button_LoadData->setMinimumSize(QSize(95, 40));
        button_LoadData->setMaximumSize(QSize(95, 40));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        button_LoadData->setFont(font);
        button_LoadData->setAutoFillBackground(false);
        button_LoadData->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        button_LoadData->setAutoDefault(false);
        button_LoadData->setDefault(false);
        button_LoadData->setFlat(false);
        toolButton_21 = new QPushButton(frame);
        toolButton_21->setObjectName(QStringLiteral("toolButton_21"));
        toolButton_21->setGeometry(QRect(110, 20, 100, 40));
        toolButton_21->setMinimumSize(QSize(100, 40));
        toolButton_21->setMaximumSize(QSize(100, 40));
        toolButton_21->setFont(font);
        toolButton_21->setAutoFillBackground(false);
        toolButton_21->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        toolButton_21->setAutoDefault(false);
        toolButton_21->setDefault(false);
        toolButton_21->setFlat(false);
        toolButton_19 = new QPushButton(frame);
        toolButton_19->setObjectName(QStringLiteral("toolButton_19"));
        toolButton_19->setGeometry(QRect(10, 140, 95, 40));
        toolButton_19->setMinimumSize(QSize(95, 40));
        toolButton_19->setMaximumSize(QSize(95, 40));
        toolButton_19->setFont(font);
        toolButton_19->setAutoFillBackground(false);
        toolButton_19->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        toolButton_19->setAutoDefault(false);
        toolButton_19->setDefault(false);
        toolButton_19->setFlat(false);
        overlap_button = new QPushButton(frame);
        overlap_button->setObjectName(QStringLiteral("overlap_button"));
        overlap_button->setGeometry(QRect(10, 210, 95, 40));
        overlap_button->setMinimumSize(QSize(95, 40));
        overlap_button->setMaximumSize(QSize(95, 40));
        overlap_button->setFont(font);
        overlap_button->setAutoFillBackground(false);
        overlap_button->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        overlap_button->setAutoDefault(false);
        overlap_button->setDefault(false);
        overlap_button->setFlat(false);
        toolButton_26 = new QPushButton(frame);
        toolButton_26->setObjectName(QStringLiteral("toolButton_26"));
        toolButton_26->setGeometry(QRect(15, 425, 190, 40));
        toolButton_26->setMinimumSize(QSize(190, 40));
        toolButton_26->setMaximumSize(QSize(190, 40));
        toolButton_26->setFont(font);
        toolButton_26->setAutoFillBackground(false);
        toolButton_26->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        toolButton_26->setAutoDefault(false);
        toolButton_26->setDefault(false);
        toolButton_26->setFlat(false);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 465, 200, 120));
        frame_2->setMinimumSize(QSize(200, 120));
        frame_2->setMaximumSize(QSize(200, 120));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setSpacing(5);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        toolButton_22 = new QPushButton(frame_2);
        toolButton_22->setObjectName(QStringLiteral("toolButton_22"));
        toolButton_22->setMinimumSize(QSize(90, 40));
        toolButton_22->setMaximumSize(QSize(90, 40));
        toolButton_22->setStyleSheet(QLatin1String("\n"
"                        QPushButton\n"
"                        {\n"
"                        color: rgb(255,255,255);\n"
"                        background-color: rgb(20, 20, 20);\n"
"                        border-radius:5px;\n"
"                        border:1px solid grey;\n"
"                        padding: 3px;\n"
"                        font-family: \"Arial\";\n"
"                        font-size: 14px;\n"
"                        text-align: center;\n"
"                        }\n"
"\n"
"                        QPushButton:hover\n"
"                        {\n"
"                        background-color: rgb(50, 50, 50);\n"
"                        }\n"
"                        QPushButton:pressed, QPushButton:checked\n"
"                        {\n"
"                        background-color: rgb(0,0, 0);\n"
"                        }\n"
"                       PluginButton\n"
"                        {\n"
"                        color: rgb(255,255,255);\n"
"                        background"
                        "-color: rgb(20, 20, 20);\n"
"                        border-radius:5px;\n"
"                        border:1px solid grey;\n"
"                        padding: 3px;\n"
"                        font-family: \"Arial\";\n"
"                        font-size: 14px;\n"
"                        text-align: center;\n"
"                        }\n"
""));

        gridLayout->addWidget(toolButton_22, 0, 0, 1, 2);

        toolButton_23 = new QPushButton(frame_2);
        toolButton_23->setObjectName(QStringLiteral("toolButton_23"));
        toolButton_23->setMinimumSize(QSize(90, 40));
        toolButton_23->setMaximumSize(QSize(90, 40));
        toolButton_23->setStyleSheet(QLatin1String("\n"
"                        QPushButton\n"
"                        {\n"
"                        color: rgb(255,255,255);\n"
"                        background-color: rgb(20, 20, 20);\n"
"                        border-radius:5px;\n"
"                        border:1px solid grey;\n"
"                        padding: 3px;\n"
"                        font-family: \"Arial\";\n"
"                        font-size: 14px;\n"
"                        text-align: center;\n"
"                        }\n"
"\n"
"                        QPushButton:hover\n"
"                        {\n"
"                        background-color: rgb(50, 50, 50);\n"
"                        }\n"
"                        QPushButton:pressed, QPushButton:checked\n"
"                        {\n"
"                        background-color: rgb(0,0, 0);\n"
"                        }\n"
"                      "));

        gridLayout->addWidget(toolButton_23, 1, 0, 1, 1);

        toolButton_24 = new QPushButton(frame_2);
        toolButton_24->setObjectName(QStringLiteral("toolButton_24"));
        toolButton_24->setMinimumSize(QSize(90, 40));
        toolButton_24->setMaximumSize(QSize(90, 40));
        toolButton_24->setStyleSheet(QLatin1String("\n"
"                        QPushButton\n"
"                        {\n"
"                        color: rgb(255,255,255);\n"
"                        background-color: rgb(20, 20, 20);\n"
"                        border-radius:5px;\n"
"                        border:1px solid grey;\n"
"                        padding: 3px;\n"
"                        font-family: \"Arial\";\n"
"                        font-size: 14px;\n"
"                        text-align: center;\n"
"                        }\n"
"\n"
"                        QPushButton:hover\n"
"                        {\n"
"                        background-color: rgb(50, 50, 50);\n"
"                        }\n"
"                        QPushButton:pressed, QPushButton:checked\n"
"                        {\n"
"                        background-color: rgb(0,0, 0);\n"
"                        }\n"
"                      "));

        gridLayout->addWidget(toolButton_24, 1, 2, 1, 1);

        toolButton_25 = new QPushButton(frame_2);
        toolButton_25->setObjectName(QStringLiteral("toolButton_25"));
        toolButton_25->setMinimumSize(QSize(90, 40));
        toolButton_25->setMaximumSize(QSize(90, 40));
        toolButton_25->setStyleSheet(QLatin1String("\n"
"                        QPushButton\n"
"                        {\n"
"                        color: rgb(255,255,255);\n"
"                        background-color: rgb(20, 20, 20);\n"
"                        border-radius:5px;\n"
"                        border:1px solid grey;\n"
"                        padding: 3px;\n"
"                        font-family: \"Arial\";\n"
"                        font-size: 14px;\n"
"                        text-align: center;\n"
"                        }\n"
"\n"
"                        QPushButton:hover\n"
"                        {\n"
"                        background-color: rgb(50, 50, 50);\n"
"                        }\n"
"                        QPushButton:pressed, QPushButton:checked\n"
"                        {\n"
"                        background-color: rgb(0,0, 0);\n"
"                        }\n"
"                      "));

        gridLayout->addWidget(toolButton_25, 0, 2, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        line = new QFrame(frame);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 125, 200, 1));
        line->setStyleSheet(QStringLiteral("background-color: rgb(160, 160, 160);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(frame);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 195, 200, 1));
        line_2->setStyleSheet(QStringLiteral("background-color: rgb(160, 160, 160);"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(frame);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 315, 200, 1));
        line_3->setStyleSheet(QStringLiteral("background-color: rgb(160, 160, 160);"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(frame);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(10, 410, 200, 1));
        line_5->setStyleSheet(QStringLiteral("background-color: rgb(160, 160, 160);"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        btn_brush = new QPushButton(frame);
        btn_brush->setObjectName(QStringLiteral("btn_brush"));
        btn_brush->setGeometry(QRect(0, 600, 51, 40));
        btn_brush->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        btn_brush->setCheckable(true);
        line_6 = new QFrame(frame);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(10, 585, 200, 1));
        line_6->setStyleSheet(QStringLiteral("background-color: rgb(160, 160, 160);"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        btn_clear = new QPushButton(frame);
        btn_clear->setObjectName(QStringLiteral("btn_clear"));
        btn_clear->setGeometry(QRect(120, 600, 41, 40));
        btn_clear->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        comboBox_brush = new QComboBox(frame);
        comboBox_brush->setObjectName(QStringLiteral("comboBox_brush"));
        comboBox_brush->setGeometry(QRect(60, 600, 51, 41));
        comboBox_brush->setStyleSheet(QLatin1String("\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                "));
        horizontalSlider_size = new QSlider(frame);
        horizontalSlider_size->setObjectName(QStringLiteral("horizontalSlider_size"));
        horizontalSlider_size->setGeometry(QRect(10, 650, 151, 22));
        horizontalSlider_size->setMinimum(1);
        horizontalSlider_size->setMaximum(20);
        horizontalSlider_size->setPageStep(5);
        horizontalSlider_size->setValue(3);
        horizontalSlider_size->setOrientation(Qt::Horizontal);
        label_size = new QLabel(frame);
        label_size->setObjectName(QStringLiteral("label_size"));
        label_size->setGeometry(QRect(170, 650, 21, 18));
        label_size->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_px = new QLabel(frame);
        label_px->setObjectName(QStringLiteral("label_px"));
        label_px->setGeometry(QRect(180, 650, 21, 18));
        label_px->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btn_volume = new QPushButton(frame);
        btn_volume->setObjectName(QStringLiteral("btn_volume"));
        btn_volume->setGeometry(QRect(10, 260, 200, 40));
        btn_volume->setMinimumSize(QSize(200, 40));
        btn_volume->setMaximumSize(QSize(200, 40));
        btn_volume->setFont(font);
        btn_volume->setAutoFillBackground(false);
        btn_volume->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        btn_volume->setCheckable(true);
        btn_volume->setAutoDefault(false);
        btn_volume->setDefault(false);
        btn_volume->setFlat(false);
        btn_screenshot = new QPushButton(frame);
        btn_screenshot->setObjectName(QStringLiteral("btn_screenshot"));
        btn_screenshot->setGeometry(QRect(10, 70, 95, 40));
        btn_screenshot->setMinimumSize(QSize(95, 40));
        btn_screenshot->setMaximumSize(QSize(95, 40));
        btn_screenshot->setFont(font);
        btn_screenshot->setAutoFillBackground(false);
        btn_screenshot->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        btn_screenshot->setCheckable(true);
        btn_screenshot->setAutoDefault(false);
        btn_screenshot->setDefault(false);
        btn_screenshot->setFlat(false);
        btn_audio = new QPushButton(frame);
        btn_audio->setObjectName(QStringLiteral("btn_audio"));
        btn_audio->setGeometry(QRect(110, 140, 100, 40));
        btn_audio->setMinimumSize(QSize(100, 40));
        btn_audio->setMaximumSize(QSize(100, 40));
        btn_audio->setFont(font);
        btn_audio->setAutoFillBackground(false);
        btn_audio->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        btn_audio->setCheckable(true);
        btn_audio->setAutoDefault(false);
        btn_audio->setDefault(false);
        btn_audio->setFlat(false);
        comboBox_screenshotWin = new QComboBox(frame);
        comboBox_screenshotWin->setObjectName(QStringLiteral("comboBox_screenshotWin"));
        comboBox_screenshotWin->setGeometry(QRect(110, 70, 100, 40));
        comboBox_screenshotWin->setStyleSheet(QLatin1String("\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                "));
        btn_3D = new QPushButton(frame);
        btn_3D->setObjectName(QStringLiteral("btn_3D"));
        btn_3D->setGeometry(QRect(110, 210, 100, 40));
        btn_3D->setMinimumSize(QSize(100, 40));
        btn_3D->setMaximumSize(QSize(100, 40));
        btn_3D->setFont(font);
        btn_3D->setAutoFillBackground(false);
        btn_3D->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        btn_3D->setAutoDefault(false);
        btn_3D->setDefault(false);
        btn_3D->setFlat(false);
        horizontalSlider_brightness = new QSlider(frame);
        horizontalSlider_brightness->setObjectName(QStringLiteral("horizontalSlider_brightness"));
        horizontalSlider_brightness->setGeometry(QRect(20, 340, 181, 21));
        horizontalSlider_brightness->setOrientation(Qt::Horizontal);
        label_brightness = new QLabel(frame);
        label_brightness->setObjectName(QStringLiteral("label_brightness"));
        label_brightness->setGeometry(QRect(50, 320, 111, 21));
        label_brightness->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_brightness->setAlignment(Qt::AlignCenter);
        label_contrast = new QLabel(frame);
        label_contrast->setObjectName(QStringLiteral("label_contrast"));
        label_contrast->setGeometry(QRect(50, 360, 111, 21));
        label_contrast->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_contrast->setAlignment(Qt::AlignCenter);
        horizontalSlider_contrast = new QSlider(frame);
        horizontalSlider_contrast->setObjectName(QStringLiteral("horizontalSlider_contrast"));
        horizontalSlider_contrast->setGeometry(QRect(20, 380, 181, 21));
        horizontalSlider_contrast->setOrientation(Qt::Horizontal);
        plugin_widget = new QWidget(frame);
        plugin_widget->setObjectName(QStringLiteral("plugin_widget"));
        plugin_widget->setGeometry(QRect(0, 730, 221, 191));
        plugin_widget->setStyleSheet(QLatin1String("QWidget{\n"
"	\n"
"	\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        but_seg = new QPushButton(plugin_widget);
        but_seg->setObjectName(QStringLiteral("but_seg"));
        but_seg->setGeometry(QRect(10, 10, 200, 40));
        but_seg->setMinimumSize(QSize(95, 40));
        but_seg->setMaximumSize(QSize(200, 40));
        but_seg->setFont(font);
        but_seg->setAutoFillBackground(false);
        but_seg->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        but_seg->setAutoDefault(false);
        but_seg->setDefault(false);
        but_seg->setFlat(false);
        btn_save = new QPushButton(frame);
        btn_save->setObjectName(QStringLiteral("btn_save"));
        btn_save->setGeometry(QRect(170, 600, 41, 40));
        btn_save->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        button_EditMask = new QPushButton(frame);
        button_EditMask->setObjectName(QStringLiteral("button_EditMask"));
        button_EditMask->setGeometry(QRect(150, 680, 60, 40));
        button_EditMask->setMinimumSize(QSize(60, 40));
        button_EditMask->setMaximumSize(QSize(200, 40));
        button_EditMask->setFont(font);
        button_EditMask->setAutoFillBackground(false);
        button_EditMask->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        button_EditMask->setAutoDefault(false);
        button_EditMask->setDefault(false);
        button_EditMask->setFlat(false);
        button_OriginalPoints = new QPushButton(frame);
        button_OriginalPoints->setObjectName(QStringLiteral("button_OriginalPoints"));
        button_OriginalPoints->setGeometry(QRect(10, 680, 60, 40));
        button_OriginalPoints->setMinimumSize(QSize(60, 40));
        button_OriginalPoints->setMaximumSize(QSize(200, 40));
        button_OriginalPoints->setFont(font);
        button_OriginalPoints->setAutoFillBackground(false);
        button_OriginalPoints->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        button_OriginalPoints->setAutoDefault(false);
        button_OriginalPoints->setDefault(false);
        button_OriginalPoints->setFlat(false);
        button_NewPoints = new QPushButton(frame);
        button_NewPoints->setObjectName(QStringLiteral("button_NewPoints"));
        button_NewPoints->setGeometry(QRect(80, 680, 60, 40));
        button_NewPoints->setMinimumSize(QSize(60, 40));
        button_NewPoints->setMaximumSize(QSize(200, 40));
        button_NewPoints->setFont(font);
        button_NewPoints->setAutoFillBackground(false);
        button_NewPoints->setStyleSheet(QLatin1String("\n"
"                  QPushButton\n"
"                  {\n"
"                  color: rgb(255,255,255);\n"
"                  background-color: rgb(20, 20, 20);\n"
"                  border-radius:5px;\n"
"                  border:1px solid grey;\n"
"                  padding: 3px;\n"
"                  font-family: \"Arial\";\n"
"                  font-size: 14px;\n"
"                  text-align: center;\n"
"                  }\n"
"\n"
"                  QPushButton:hover\n"
"                  {\n"
"                  background-color: rgb(50, 50, 50);\n"
"                  }\n"
"                  QPushButton:pressed, QPushButton:checked\n"
"                  {\n"
"                  background-color: rgb(0,0, 0);\n"
"                  }\n"
"                "));
        button_NewPoints->setAutoDefault(false);
        button_NewPoints->setDefault(false);
        button_NewPoints->setFlat(false);
        label_contrast->raise();
        button_LoadData->raise();
        toolButton_21->raise();
        toolButton_19->raise();
        overlap_button->raise();
        toolButton_26->raise();
        frame_2->raise();
        line->raise();
        line_2->raise();
        line_3->raise();
        line_5->raise();
        btn_brush->raise();
        line_6->raise();
        btn_clear->raise();
        comboBox_brush->raise();
        horizontalSlider_size->raise();
        label_size->raise();
        label_px->raise();
        btn_volume->raise();
        btn_screenshot->raise();
        btn_audio->raise();
        comboBox_screenshotWin->raise();
        btn_3D->raise();
        horizontalSlider_brightness->raise();
        label_brightness->raise();
        horizontalSlider_contrast->raise();
        plugin_widget->raise();
        btn_save->raise();
        button_EditMask->raise();
        button_OriginalPoints->raise();
        button_NewPoints->raise();

        horizontalLayout_2->addWidget(frame);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setMinimumSize(QSize(1, 0));
        line_4->setMaximumSize(QSize(1, 16777215));
        line_4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_4);

        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout_1 = new QGridLayout();
        gridLayout_1->setSpacing(0);
        gridLayout_1->setObjectName(QStringLiteral("gridLayout_1"));
        qvtkWidget_y = new QVTKWidget(frame_3);
        qvtkWidget_y->setObjectName(QStringLiteral("qvtkWidget_y"));
        qvtkWidget_y->setMinimumSize(QSize(200, 200));

        gridLayout_1->addWidget(qvtkWidget_y, 3, 0, 1, 1);

        line_10 = new QFrame(frame_3);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setLineWidth(3);
        line_10->setMidLineWidth(1);
        line_10->setFrameShape(QFrame::VLine);
        line_10->setFrameShadow(QFrame::Sunken);

        gridLayout_1->addWidget(line_10, 0, 1, 2, 1);

        horizontalScrollBar_x = new QScrollBar(frame_3);
        horizontalScrollBar_x->setObjectName(QStringLiteral("horizontalScrollBar_x"));
        horizontalScrollBar_x->setMinimumSize(QSize(200, 20));
        horizontalScrollBar_x->setOrientation(Qt::Horizontal);

        gridLayout_1->addWidget(horizontalScrollBar_x, 0, 2, 1, 1);

        qvtkWidget_x = new QVTKWidget(frame_3);
        qvtkWidget_x->setObjectName(QStringLiteral("qvtkWidget_x"));
        qvtkWidget_x->setMinimumSize(QSize(200, 200));

        gridLayout_1->addWidget(qvtkWidget_x, 1, 0, 1, 1);

        horizontalScrollBar_z = new QScrollBar(frame_3);
        horizontalScrollBar_z->setObjectName(QStringLiteral("horizontalScrollBar_z"));
        horizontalScrollBar_z->setMinimumSize(QSize(200, 20));
        horizontalScrollBar_z->setOrientation(Qt::Horizontal);

        gridLayout_1->addWidget(horizontalScrollBar_z, 2, 2, 1, 1);

        qvtkWidget_xyz = new QVTKWidget(frame_3);
        qvtkWidget_xyz->setObjectName(QStringLiteral("qvtkWidget_xyz"));
        qvtkWidget_xyz->setMinimumSize(QSize(200, 200));

        gridLayout_1->addWidget(qvtkWidget_xyz, 1, 2, 1, 1);

        qvtkWidget_z = new QVTKWidget(frame_3);
        qvtkWidget_z->setObjectName(QStringLiteral("qvtkWidget_z"));
        qvtkWidget_z->setMinimumSize(QSize(200, 200));

        gridLayout_1->addWidget(qvtkWidget_z, 3, 2, 1, 1);

        horizontalScrollBar_0 = new QScrollBar(frame_3);
        horizontalScrollBar_0->setObjectName(QStringLiteral("horizontalScrollBar_0"));
        horizontalScrollBar_0->setMinimumSize(QSize(200, 20));
        horizontalScrollBar_0->setOrientation(Qt::Horizontal);

        gridLayout_1->addWidget(horizontalScrollBar_0, 0, 0, 1, 1);

        line_11 = new QFrame(frame_3);
        line_11->setObjectName(QStringLiteral("line_11"));
        line_11->setLineWidth(3);
        line_11->setMidLineWidth(1);
        line_11->setFrameShape(QFrame::VLine);
        line_11->setFrameShadow(QFrame::Sunken);

        gridLayout_1->addWidget(line_11, 2, 1, 2, 1);

        horizontalScrollBar_y = new QScrollBar(frame_3);
        horizontalScrollBar_y->setObjectName(QStringLiteral("horizontalScrollBar_y"));
        horizontalScrollBar_y->setMinimumSize(QSize(200, 20));
        horizontalScrollBar_y->setOrientation(Qt::Horizontal);

        gridLayout_1->addWidget(horizontalScrollBar_y, 2, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_1);


        horizontalLayout_2->addWidget(frame_3);

        ServerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ServerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1118, 30));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit_mask = new QMenu(menuBar);
        menuEdit_mask->setObjectName(QStringLiteral("menuEdit_mask"));
        ServerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ServerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ServerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ServerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ServerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit_mask->menuAction());
        menuEdit_mask->addAction(actionEdit_mask);

        retranslateUi(ServerClass);

        QMetaObject::connectSlotsByName(ServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ServerClass)
    {
        ServerClass->setWindowTitle(QApplication::translate("ServerClass", "Server", 0));
        actionAbout->setText(QApplication::translate("ServerClass", "&About", 0));
        actionServices->setText(QApplication::translate("ServerClass", "&Services", 0));
        actionHide->setText(QApplication::translate("ServerClass", "Hide", 0));
        actionHide_Others->setText(QApplication::translate("ServerClass", "Hide Others", 0));
        actionShow_All->setText(QApplication::translate("ServerClass", "Show All", 0));
        actionQuit->setText(QApplication::translate("ServerClass", "&Quit", 0));
        actionService->setText(QApplication::translate("ServerClass", "Service", 0));
        actionAuthority->setText(QApplication::translate("ServerClass", "Authority", 0));
        actionMessages->setText(QApplication::translate("ServerClass", "Messages", 0));
        actionVideo->setText(QApplication::translate("ServerClass", "Video", 0));
        actionAudio->setText(QApplication::translate("ServerClass", "Audio", 0));
        actionZoom_In->setText(QApplication::translate("ServerClass", "Zoom In", 0));
        actionZoom_Out->setText(QApplication::translate("ServerClass", "Zoom Out", 0));
        actionFilt_on_Screen->setText(QApplication::translate("ServerClass", "Filt on Screen", 0));
        action100->setText(QApplication::translate("ServerClass", "100%", 0));
        action200->setText(QApplication::translate("ServerClass", "200%", 0));
        actionScreen_Mode->setText(QApplication::translate("ServerClass", "Screen Mode", 0));
        actionRulers->setText(QApplication::translate("ServerClass", "Rulers", 0));
        actionHide_2->setText(QApplication::translate("ServerClass", "Hide", 0));
        actionShow->setText(QApplication::translate("ServerClass", "Show", 0));
        actionConnectin_Editor->setText(QApplication::translate("ServerClass", "Connectin Editor", 0));
        actionExtension_Manager->setText(QApplication::translate("ServerClass", "Extension Manager", 0));
        actionModule_Panel->setText(QApplication::translate("ServerClass", "Module Panel", 0));
        actionToolbars->setText(QApplication::translate("ServerClass", "Toolbars", 0));
        actionLayout->setText(QApplication::translate("ServerClass", "Layout", 0));
        actionError_Log->setText(QApplication::translate("ServerClass", "Error Log", 0));
        actionGeneral_Editor->setText(QApplication::translate("ServerClass", "General Editor", 0));
        actionOutliner->setText(QApplication::translate("ServerClass", "Outliner", 0));
        actionWorkspace->setText(QApplication::translate("ServerClass", "Workspace", 0));
        actionSearch->setText(QApplication::translate("ServerClass", "Search", 0));
        actionKeyboard_Shortcuts->setText(QApplication::translate("ServerClass", "Keyboard Shortcuts", 0));
        actionServices_and_Support->setText(QApplication::translate("ServerClass", "Services and Support", 0));
        actionTutorials->setText(QApplication::translate("ServerClass", "Tutorials", 0));
        actionReport_a_Problem->setText(QApplication::translate("ServerClass", "Report a Problem", 0));
        actionCheck_for_Upadates->setText(QApplication::translate("ServerClass", "Check for Upadates", 0));
        actionSystem_info->setText(QApplication::translate("ServerClass", "System info...", 0));
        actionHome_Page->setText(QApplication::translate("ServerClass", "Home Page", 0));
        actionNew_Scence->setText(QApplication::translate("ServerClass", "&New Scene", 0));
        actionOpen_Scence->setText(QApplication::translate("ServerClass", "&Open Scene", 0));
        actionSave_Scence->setText(QApplication::translate("ServerClass", "Save Scene", 0));
        actionSave_Scence_As->setText(QApplication::translate("ServerClass", "Save Scene As", 0));
        actionClose->setText(QApplication::translate("ServerClass", "Close ", 0));
        actionClose_All->setText(QApplication::translate("ServerClass", "Close All", 0));
        actionAdd_Data->setText(QApplication::translate("ServerClass", "&Add Data", 0));
        actionDownload_Sample_Data->setText(QApplication::translate("ServerClass", "&Download Sample Data", 0));
        actionImport->setText(QApplication::translate("ServerClass", "&Import", 0));
        actionExport->setText(QApplication::translate("ServerClass", "&Export", 0));
        actionView_Image->setText(QApplication::translate("ServerClass", "View Image...", 0));
        actionView_Sequence->setText(QApplication::translate("ServerClass", "View &Sequence...", 0));
        actionProject_Window->setText(QApplication::translate("ServerClass", "&Project Window", 0));
        actionSet_Project->setText(QApplication::translate("ServerClass", "Set Project...", 0));
        actionRecent_Files->setText(QApplication::translate("ServerClass", "&Recent Files", 0));
        actionRecent_Increments->setText(QApplication::translate("ServerClass", "Recent Increments", 0));
        actionRecent_Projects->setText(QApplication::translate("ServerClass", "Recent Projects", 0));
        actionPrint->setText(QApplication::translate("ServerClass", "Print", 0));
        actionUndo->setText(QApplication::translate("ServerClass", "Undo", 0));
        actionRedo->setText(QApplication::translate("ServerClass", "Redo", 0));
        actionRepeat->setText(QApplication::translate("ServerClass", "Repeat ", 0));
        actionRecent_Command_List->setText(QApplication::translate("ServerClass", "Recent Command List", 0));
        actionCut->setText(QApplication::translate("ServerClass", "Cut", 0));
        actionCopy->setText(QApplication::translate("ServerClass", "Copy", 0));
        actionPaste->setText(QApplication::translate("ServerClass", "Paste", 0));
        actionDelete->setText(QApplication::translate("ServerClass", "Delete", 0));
        actionDelete_All_by_Type->setText(QApplication::translate("ServerClass", "Delete All by Type", 0));
        actionSelect_Tool->setText(QApplication::translate("ServerClass", "Select Tool", 0));
        action_4->setText(QString());
        actionSelect_All->setText(QApplication::translate("ServerClass", "Select All", 0));
        actionDeselect_All->setText(QApplication::translate("ServerClass", "Deselect All", 0));
        actionInvert_Selection->setText(QApplication::translate("ServerClass", "Invert Selection", 0));
        actionSelect_All_by_Type->setText(QApplication::translate("ServerClass", "Select All by Type", 0));
        actionDuplicate->setText(QApplication::translate("ServerClass", "Duplicate", 0));
        actionEdit_mask->setText(QApplication::translate("ServerClass", "edit mask", 0));
        button_LoadData->setText(QApplication::translate("ServerClass", "Load Data", 0));
        toolButton_21->setText(QApplication::translate("ServerClass", "Set Channel", 0));
        toolButton_19->setText(QApplication::translate("ServerClass", "Authority", 0));
        overlap_button->setText(QApplication::translate("ServerClass", "Overlap", 0));
        toolButton_26->setText(QApplication::translate("ServerClass", "Full View   (4 in 1)", 0));
        toolButton_22->setText(QApplication::translate("ServerClass", "xyz", 0));
        toolButton_23->setText(QApplication::translate("ServerClass", "y", 0));
        toolButton_24->setText(QApplication::translate("ServerClass", "z", 0));
        toolButton_25->setText(QApplication::translate("ServerClass", "x", 0));
        btn_brush->setText(QApplication::translate("ServerClass", "Brush", 0));
        btn_clear->setText(QApplication::translate("ServerClass", "Clear", 0));
        label_size->setText(QApplication::translate("ServerClass", "3", 0));
        label_px->setText(QApplication::translate("ServerClass", "px", 0));
        btn_volume->setText(QApplication::translate("ServerClass", "Volume Rendering", 0));
        btn_screenshot->setText(QApplication::translate("ServerClass", "Screenshot", 0));
        btn_audio->setText(QApplication::translate("ServerClass", "Audio", 0));
        btn_3D->setText(QApplication::translate("ServerClass", "3D", 0));
        label_brightness->setText(QApplication::translate("ServerClass", "brightness", 0));
        label_contrast->setText(QApplication::translate("ServerClass", "contrast", 0));
        but_seg->setText(QApplication::translate("ServerClass", "Plug-ins", 0));
        btn_save->setText(QApplication::translate("ServerClass", "Save", 0));
        button_EditMask->setText(QApplication::translate("ServerClass", "Edit", 0));
        button_OriginalPoints->setText(QApplication::translate("ServerClass", "OrigP", 0));
        button_NewPoints->setText(QApplication::translate("ServerClass", "NewP", 0));
        menuFile->setTitle(QApplication::translate("ServerClass", "file", 0));
        menuEdit_mask->setTitle(QApplication::translate("ServerClass", "mask", 0));
    } // retranslateUi

};

namespace Ui {
    class ServerClass: public Ui_ServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
