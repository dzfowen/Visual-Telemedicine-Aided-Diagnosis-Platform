/********************************************************************************
** Form generated from reading UI file 'editmask.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMASK_H
#define UI_EDITMASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_EditMask
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QLabel *label_EditContour;
    QPushButton *pushButton_cnt1;
    QPushButton *pushButton_cnt2;
    QFrame *frame_EditContour;
    QPushButton *pushButton_ContourOverlay_Edit_PointOrigin;
    QPushButton *pushButton_ContourOverlay_Edit_PointEnd;
    QPushButton *pushButton_ContourOverlay_Edit;
    QFrame *line_7;
    QPushButton *pushButton_ContourOverlay_Edit_Clear;
    QFrame *line_SideBar1;
    QLabel *label_EditObjects;
    QPushButton *pushButton_obj1;
    QLabel *label_px1;
    QLineEdit *lineEdit_obj1;
    QPushButton *pushButton_obj2;
    QSlider *horizontalSlider_obj1;
    QSlider *horizontalSlider_obj2;
    QLineEdit *lineEdit_obj2;
    QLabel *label_px2;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_SideBar2;
    QSlider *horizontalSlider_bkg;
    QPushButton *pushButton_bkg;
    QLineEdit *lineEdit_bkg;
    QLabel *label_px4;
    QPushButton *pushButton_ReloadMask;
    QPushButton *pushButton_SaveMaskAs;
    QFrame *line_5;
    QPushButton *pushButton_SaveChanges;
    QFrame *line_6;
    QPushButton *pushButton_Reset;
    QPushButton *pushButton_MaskOverlay_Edit_Clear;
    QPushButton *pushButton_MaskOverlay_Edit;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea_ContourOverlay;
    QWidget *scrollAreaWidgetContents_ContourOverlay;
    QLabel *label_MaskDisplay;
    QLabel *label_ContourOverlay;
    QLabel *label_MaskOverlay_fg;
    QScrollArea *scrollArea_EditContourArea;
    QWidget *scrollAreaWidgetContents_2;
    QLabel *label_MaskOverlay_bg;
    QLabel *label_ScibbleImage_ValueOfSliceNumber;
    QLabel *label_ScribbleImage_ValueOfSliceNumber_Value;
    QLabel *label_ScibbleImage_ValueOfSliceNumber_2;
    QLabel *label_OriginalDisplay;
    QLabel *label_ContourOverlayTitle;
    QLabel *label_MaskOverlay_fg1;
    QLabel *label_MaskOverlay_fg2;
    QScrollArea *scrollArea_ScribbleArea;
    QWidget *scrollAreaWidgetContents_4;
    QScrollBar *verticalScrollBar_ScribbleImage;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_OriginalSize;
    QSlider *horizontalSlider_zoom;
    QLabel *label_ZoomValue;
    QPushButton *pushButton_FitTheScreen;

    void setupUi(QDialog *Dialog_EditMask)
    {
        if (Dialog_EditMask->objectName().isEmpty())
            Dialog_EditMask->setObjectName(QStringLiteral("Dialog_EditMask"));
        Dialog_EditMask->resize(931, 649);
        Dialog_EditMask->setMinimumSize(QSize(910, 620));
        Dialog_EditMask->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        horizontalLayout = new QHBoxLayout(Dialog_EditMask);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(Dialog_EditMask);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(361, 580));
        frame->setMaximumSize(QSize(361, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_EditContour = new QLabel(frame);
        label_EditContour->setObjectName(QStringLiteral("label_EditContour"));
        label_EditContour->setGeometry(QRect(20, 20, 111, 16));
        label_EditContour->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font-family: \"Arial\";\n"
"font-size: 12px;\n"
"   "));
        pushButton_cnt1 = new QPushButton(frame);
        pushButton_cnt1->setObjectName(QStringLiteral("pushButton_cnt1"));
        pushButton_cnt1->setGeometry(QRect(30, 40, 50, 50));
        pushButton_cnt1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(255,255,255);\n"
"    background-color: rgb(80, 80, 80);\n"
"    border-radius:5px;\n"
"    border:1px solid rgb(100,100,100);\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(40, 40, 40);\n"
"    border: 1px solid rgb(120,120,120);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(20,20, 20);\n"
"    border:2px solid white;\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/myImage/Resources/Interface/images/icons_obj1Cnt.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cnt1->setIcon(icon);
        pushButton_cnt1->setIconSize(QSize(45, 45));
        pushButton_cnt1->setCheckable(true);
        pushButton_cnt1->setAutoExclusive(false);
        pushButton_cnt2 = new QPushButton(frame);
        pushButton_cnt2->setObjectName(QStringLiteral("pushButton_cnt2"));
        pushButton_cnt2->setGeometry(QRect(30, 100, 50, 50));
        pushButton_cnt2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(255,255,255);\n"
"    background-color: rgb(80, 80, 80);\n"
"    border-radius:5px;\n"
"    border:1px solid rgb(100,100,100);\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(40, 40, 40);\n"
"    border: 1px solid rgb(120,120,120);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(20,20, 20);\n"
"    border:2px solid white;\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/myImage/Resources/Interface/images/icons_obj2Cnt.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cnt2->setIcon(icon1);
        pushButton_cnt2->setIconSize(QSize(45, 45));
        pushButton_cnt2->setCheckable(true);
        pushButton_cnt2->setAutoExclusive(false);
        frame_EditContour = new QFrame(frame);
        frame_EditContour->setObjectName(QStringLiteral("frame_EditContour"));
        frame_EditContour->setGeometry(QRect(90, 40, 251, 161));
        frame_EditContour->setFrameShape(QFrame::StyledPanel);
        frame_EditContour->setFrameShadow(QFrame::Raised);
        pushButton_ContourOverlay_Edit_PointOrigin = new QPushButton(frame_EditContour);
        pushButton_ContourOverlay_Edit_PointOrigin->setObjectName(QStringLiteral("pushButton_ContourOverlay_Edit_PointOrigin"));
        pushButton_ContourOverlay_Edit_PointOrigin->setEnabled(true);
        pushButton_ContourOverlay_Edit_PointOrigin->setGeometry(QRect(0, 0, 121, 40));
        pushButton_ContourOverlay_Edit_PointOrigin->setMinimumSize(QSize(60, 25));
        pushButton_ContourOverlay_Edit_PointOrigin->setMaximumSize(QSize(500, 500));
        pushButton_ContourOverlay_Edit_PointOrigin->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(255, 255, 0);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"          background-color: rgb(20,20, 20);\n"
"   color: rgb(255,255,255);\n"
"    border:1px solid white;\n"
"}\n"
""));
        pushButton_ContourOverlay_Edit_PointOrigin->setCheckable(true);
        pushButton_ContourOverlay_Edit_PointOrigin->setAutoExclusive(false);
        pushButton_ContourOverlay_Edit_PointEnd = new QPushButton(frame_EditContour);
        pushButton_ContourOverlay_Edit_PointEnd->setObjectName(QStringLiteral("pushButton_ContourOverlay_Edit_PointEnd"));
        pushButton_ContourOverlay_Edit_PointEnd->setGeometry(QRect(130, 0, 121, 40));
        pushButton_ContourOverlay_Edit_PointEnd->setMinimumSize(QSize(60, 25));
        pushButton_ContourOverlay_Edit_PointEnd->setMaximumSize(QSize(500, 500));
        pushButton_ContourOverlay_Edit_PointEnd->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(255,0, 255);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"           background-color: rgb(20,20, 20);\n"
"   color: rgb(255,255,255);\n"
"    border:1px solid white;\n"
"}\n"
""));
        pushButton_ContourOverlay_Edit_PointEnd->setCheckable(true);
        pushButton_ContourOverlay_Edit_PointEnd->setAutoExclusive(false);
        pushButton_ContourOverlay_Edit = new QPushButton(frame_EditContour);
        pushButton_ContourOverlay_Edit->setObjectName(QStringLiteral("pushButton_ContourOverlay_Edit"));
        pushButton_ContourOverlay_Edit->setGeometry(QRect(70, 70, 181, 40));
        pushButton_ContourOverlay_Edit->setMinimumSize(QSize(60, 25));
        pushButton_ContourOverlay_Edit->setMaximumSize(QSize(500, 60));
        pushButton_ContourOverlay_Edit->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));
        line_7 = new QFrame(frame_EditContour);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(0, 55, 251, 1));
        line_7->setStyleSheet(QStringLiteral("background-color: rgb(80, 80, 80);"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        pushButton_ContourOverlay_Edit_Clear = new QPushButton(frame_EditContour);
        pushButton_ContourOverlay_Edit_Clear->setObjectName(QStringLiteral("pushButton_ContourOverlay_Edit_Clear"));
        pushButton_ContourOverlay_Edit_Clear->setGeometry(QRect(0, 70, 61, 40));
        pushButton_ContourOverlay_Edit_Clear->setMinimumSize(QSize(0, 25));
        pushButton_ContourOverlay_Edit_Clear->setMaximumSize(QSize(500, 60));
        pushButton_ContourOverlay_Edit_Clear->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));
        pushButton_ContourOverlay_Edit_Clear->setCheckable(false);
        pushButton_ContourOverlay_Edit_Clear->setAutoExclusive(false);
        line_SideBar1 = new QFrame(frame);
        line_SideBar1->setObjectName(QStringLiteral("line_SideBar1"));
        line_SideBar1->setGeometry(QRect(10, 160, 350, 1));
        line_SideBar1->setStyleSheet(QStringLiteral("background-color: rgb(160, 160, 160);"));
        line_SideBar1->setFrameShape(QFrame::HLine);
        line_SideBar1->setFrameShadow(QFrame::Sunken);
        label_EditObjects = new QLabel(frame);
        label_EditObjects->setObjectName(QStringLiteral("label_EditObjects"));
        label_EditObjects->setGeometry(QRect(20, 175, 111, 16));
        label_EditObjects->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font-family: \"Arial\";\n"
"font-size: 12px;\n"
"   "));
        pushButton_obj1 = new QPushButton(frame);
        pushButton_obj1->setObjectName(QStringLiteral("pushButton_obj1"));
        pushButton_obj1->setGeometry(QRect(30, 200, 201, 40));
        pushButton_obj1->setMinimumSize(QSize(60, 25));
        pushButton_obj1->setMaximumSize(QSize(500, 60));
        pushButton_obj1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"        background-color: rgb(20,20, 20);\n"
"   color: rgb(255,255,255);\n"
"    border:1px solid white;\n"
"}\n"
""));
        pushButton_obj1->setCheckable(true);
        pushButton_obj1->setAutoExclusive(false);
        label_px1 = new QLabel(frame);
        label_px1->setObjectName(QStringLiteral("label_px1"));
        label_px1->setGeometry(QRect(320, 215, 32, 31));
        label_px1->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font-family: \"Arial\";\n"
"font-size: 16px;"));
        lineEdit_obj1 = new QLineEdit(frame);
        lineEdit_obj1->setObjectName(QStringLiteral("lineEdit_obj1"));
        lineEdit_obj1->setGeometry(QRect(250, 220, 61, 21));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(14);
        lineEdit_obj1->setFont(font);
        lineEdit_obj1->setAcceptDrops(true);
        lineEdit_obj1->setAutoFillBackground(false);
        lineEdit_obj1->setStyleSheet(QLatin1String("background-image: url(:/Segmentation/Resources/Interface/images/Brush_49.png);\n"
"color: rgb(255, 255, 255);\n"
"border-image: url(:/Segmentation/Resources/Interface/images/Brush_49.png);\n"
""));
        lineEdit_obj1->setFrame(false);
        pushButton_obj2 = new QPushButton(frame);
        pushButton_obj2->setObjectName(QStringLiteral("pushButton_obj2"));
        pushButton_obj2->setGeometry(QRect(30, 290, 201, 40));
        pushButton_obj2->setMinimumSize(QSize(60, 25));
        pushButton_obj2->setMaximumSize(QSize(500, 60));
        pushButton_obj2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"        background-color: rgb(20,20, 20);\n"
"    border:1px solid white;\n"
"color: rgb(255,255,255);\n"
"}\n"
""));
        pushButton_obj2->setCheckable(true);
        pushButton_obj2->setAutoExclusive(false);
        horizontalSlider_obj1 = new QSlider(frame);
        horizontalSlider_obj1->setObjectName(QStringLiteral("horizontalSlider_obj1"));
        horizontalSlider_obj1->setGeometry(QRect(30, 250, 311, 20));
        horizontalSlider_obj1->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0, 0);"));
        horizontalSlider_obj1->setMinimum(1);
        horizontalSlider_obj1->setMaximum(20);
        horizontalSlider_obj1->setPageStep(5);
        horizontalSlider_obj1->setValue(10);
        horizontalSlider_obj1->setOrientation(Qt::Horizontal);
        horizontalSlider_obj2 = new QSlider(frame);
        horizontalSlider_obj2->setObjectName(QStringLiteral("horizontalSlider_obj2"));
        horizontalSlider_obj2->setGeometry(QRect(30, 340, 311, 20));
        horizontalSlider_obj2->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0, 0);"));
        horizontalSlider_obj2->setMinimum(1);
        horizontalSlider_obj2->setMaximum(20);
        horizontalSlider_obj2->setPageStep(5);
        horizontalSlider_obj2->setValue(10);
        horizontalSlider_obj2->setOrientation(Qt::Horizontal);
        lineEdit_obj2 = new QLineEdit(frame);
        lineEdit_obj2->setObjectName(QStringLiteral("lineEdit_obj2"));
        lineEdit_obj2->setGeometry(QRect(250, 310, 61, 21));
        lineEdit_obj2->setFont(font);
        lineEdit_obj2->setAcceptDrops(true);
        lineEdit_obj2->setAutoFillBackground(false);
        lineEdit_obj2->setStyleSheet(QLatin1String("background-image: url(:/Segmentation/Resources/Interface/images/Brush_49.png);\n"
"color: rgb(255, 255, 255);\n"
"border-image: url(:/Segmentation/Resources/Interface/images/Brush_49.png);\n"
""));
        lineEdit_obj2->setFrame(false);
        label_px2 = new QLabel(frame);
        label_px2->setObjectName(QStringLiteral("label_px2"));
        label_px2->setGeometry(QRect(320, 305, 32, 31));
        label_px2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font-family: \"Arial\";\n"
"font-size: 16px;"));
        line_2 = new QFrame(frame);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(30, 280, 310, 1));
        line_2->setStyleSheet(QStringLiteral("background-color: rgb(80, 80, 80);"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(frame);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(30, 370, 310, 1));
        line_3->setStyleSheet(QStringLiteral("background-color: rgb(80, 80, 80);"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_SideBar2 = new QFrame(frame);
        line_SideBar2->setObjectName(QStringLiteral("line_SideBar2"));
        line_SideBar2->setGeometry(QRect(10, 520, 350, 1));
        line_SideBar2->setStyleSheet(QStringLiteral("background-color: rgb(160, 160, 160);"));
        line_SideBar2->setFrameShape(QFrame::HLine);
        line_SideBar2->setFrameShadow(QFrame::Sunken);
        horizontalSlider_bkg = new QSlider(frame);
        horizontalSlider_bkg->setObjectName(QStringLiteral("horizontalSlider_bkg"));
        horizontalSlider_bkg->setGeometry(QRect(30, 430, 311, 20));
        horizontalSlider_bkg->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0, 0);"));
        horizontalSlider_bkg->setMinimum(1);
        horizontalSlider_bkg->setMaximum(20);
        horizontalSlider_bkg->setPageStep(5);
        horizontalSlider_bkg->setValue(10);
        horizontalSlider_bkg->setOrientation(Qt::Horizontal);
        pushButton_bkg = new QPushButton(frame);
        pushButton_bkg->setObjectName(QStringLiteral("pushButton_bkg"));
        pushButton_bkg->setGeometry(QRect(30, 380, 201, 40));
        pushButton_bkg->setMinimumSize(QSize(60, 25));
        pushButton_bkg->setMaximumSize(QSize(500, 60));
        pushButton_bkg->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"           background-color: rgb(20,20, 20);\n"
"    border:1px solid white;\n"
"color: rgb(255,255,255);\n"
"}\n"
""));
        pushButton_bkg->setCheckable(true);
        pushButton_bkg->setAutoExclusive(false);
        lineEdit_bkg = new QLineEdit(frame);
        lineEdit_bkg->setObjectName(QStringLiteral("lineEdit_bkg"));
        lineEdit_bkg->setGeometry(QRect(250, 400, 61, 21));
        lineEdit_bkg->setFont(font);
        lineEdit_bkg->setAcceptDrops(true);
        lineEdit_bkg->setAutoFillBackground(false);
        lineEdit_bkg->setStyleSheet(QLatin1String("background-image: url(:/Segmentation/Resources/Interface/images/Brush_49.png);\n"
"color: rgb(255, 255, 255);\n"
"border-image: url(:/Segmentation/Resources/Interface/images/Brush_49.png);\n"
""));
        lineEdit_bkg->setFrame(false);
        label_px4 = new QLabel(frame);
        label_px4->setObjectName(QStringLiteral("label_px4"));
        label_px4->setGeometry(QRect(320, 395, 32, 31));
        label_px4->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font-family: \"Arial\";\n"
"font-size: 16px;"));
        pushButton_ReloadMask = new QPushButton(frame);
        pushButton_ReloadMask->setObjectName(QStringLiteral("pushButton_ReloadMask"));
        pushButton_ReloadMask->setGeometry(QRect(30, 580, 151, 31));
        pushButton_ReloadMask->setMinimumSize(QSize(60, 25));
        pushButton_ReloadMask->setMaximumSize(QSize(500, 60));
        pushButton_ReloadMask->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));
        pushButton_SaveMaskAs = new QPushButton(frame);
        pushButton_SaveMaskAs->setObjectName(QStringLiteral("pushButton_SaveMaskAs"));
        pushButton_SaveMaskAs->setGeometry(QRect(190, 580, 151, 31));
        pushButton_SaveMaskAs->setMinimumSize(QSize(60, 25));
        pushButton_SaveMaskAs->setMaximumSize(QSize(500, 60));
        pushButton_SaveMaskAs->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));
        line_5 = new QFrame(frame);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(30, 455, 310, 1));
        line_5->setStyleSheet(QStringLiteral("background-color: rgb(80, 80, 80);"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        pushButton_SaveChanges = new QPushButton(frame);
        pushButton_SaveChanges->setObjectName(QStringLiteral("pushButton_SaveChanges"));
        pushButton_SaveChanges->setGeometry(QRect(120, 530, 221, 41));
        pushButton_SaveChanges->setMinimumSize(QSize(60, 25));
        pushButton_SaveChanges->setMaximumSize(QSize(500, 60));
        pushButton_SaveChanges->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));
        line_6 = new QFrame(frame);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(85, 40, 1, 110));
        line_6->setStyleSheet(QStringLiteral("background-color: rgb(180, 180, 180);"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        pushButton_Reset = new QPushButton(frame);
        pushButton_Reset->setObjectName(QStringLiteral("pushButton_Reset"));
        pushButton_Reset->setGeometry(QRect(30, 530, 81, 41));
        pushButton_Reset->setMinimumSize(QSize(60, 25));
        pushButton_Reset->setMaximumSize(QSize(500, 60));
        pushButton_Reset->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));
        pushButton_MaskOverlay_Edit_Clear = new QPushButton(frame);
        pushButton_MaskOverlay_Edit_Clear->setObjectName(QStringLiteral("pushButton_MaskOverlay_Edit_Clear"));
        pushButton_MaskOverlay_Edit_Clear->setGeometry(QRect(30, 467, 81, 41));
        pushButton_MaskOverlay_Edit_Clear->setMinimumSize(QSize(60, 25));
        pushButton_MaskOverlay_Edit_Clear->setMaximumSize(QSize(500, 60));
        pushButton_MaskOverlay_Edit_Clear->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));
        pushButton_MaskOverlay_Edit = new QPushButton(frame);
        pushButton_MaskOverlay_Edit->setObjectName(QStringLiteral("pushButton_MaskOverlay_Edit"));
        pushButton_MaskOverlay_Edit->setGeometry(QRect(120, 467, 221, 41));
        pushButton_MaskOverlay_Edit->setMinimumSize(QSize(60, 25));
        pushButton_MaskOverlay_Edit->setMaximumSize(QSize(500, 60));
        pushButton_MaskOverlay_Edit->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));

        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(Dialog_EditMask);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMinimumSize(QSize(500, 560));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        scrollArea_ContourOverlay = new QScrollArea(frame_3);
        scrollArea_ContourOverlay->setObjectName(QStringLiteral("scrollArea_ContourOverlay"));
        scrollArea_ContourOverlay->setMinimumSize(QSize(475, 560));
        scrollArea_ContourOverlay->setWidgetResizable(true);
        scrollAreaWidgetContents_ContourOverlay = new QWidget();
        scrollAreaWidgetContents_ContourOverlay->setObjectName(QStringLiteral("scrollAreaWidgetContents_ContourOverlay"));
        scrollAreaWidgetContents_ContourOverlay->setGeometry(QRect(0, 0, 473, 558));
        scrollAreaWidgetContents_ContourOverlay->setMinimumSize(QSize(0, 0));
        label_MaskDisplay = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_MaskDisplay->setObjectName(QStringLiteral("label_MaskDisplay"));
        label_MaskDisplay->setGeometry(QRect(0, 0, 475, 560));
        label_MaskDisplay->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        label_MaskDisplay->setAlignment(Qt::AlignCenter);
        label_ContourOverlay = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_ContourOverlay->setObjectName(QStringLiteral("label_ContourOverlay"));
        label_ContourOverlay->setGeometry(QRect(0, 0, 475, 560));
        label_ContourOverlay->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        label_ContourOverlay->setAlignment(Qt::AlignCenter);
        label_MaskOverlay_fg = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_MaskOverlay_fg->setObjectName(QStringLiteral("label_MaskOverlay_fg"));
        label_MaskOverlay_fg->setGeometry(QRect(0, 0, 475, 560));
        label_MaskOverlay_fg->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        label_MaskOverlay_fg->setAlignment(Qt::AlignCenter);
        scrollArea_EditContourArea = new QScrollArea(scrollAreaWidgetContents_ContourOverlay);
        scrollArea_EditContourArea->setObjectName(QStringLiteral("scrollArea_EditContourArea"));
        scrollArea_EditContourArea->setGeometry(QRect(0, 0, 475, 560));
        scrollArea_EditContourArea->setMaximumSize(QSize(16777215, 16777215));
        scrollArea_EditContourArea->setAutoFillBackground(false);
        scrollArea_EditContourArea->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        scrollArea_EditContourArea->setFrameShadow(QFrame::Raised);
        scrollArea_EditContourArea->setLineWidth(0);
        scrollArea_EditContourArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea_EditContourArea->setWidgetResizable(true);
        scrollArea_EditContourArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 473, 558));
        scrollArea_EditContourArea->setWidget(scrollAreaWidgetContents_2);
        label_MaskOverlay_bg = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_MaskOverlay_bg->setObjectName(QStringLiteral("label_MaskOverlay_bg"));
        label_MaskOverlay_bg->setGeometry(QRect(0, 0, 475, 560));
        label_MaskOverlay_bg->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        label_MaskOverlay_bg->setAlignment(Qt::AlignCenter);
        label_ScibbleImage_ValueOfSliceNumber = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_ScibbleImage_ValueOfSliceNumber->setObjectName(QStringLiteral("label_ScibbleImage_ValueOfSliceNumber"));
        label_ScibbleImage_ValueOfSliceNumber->setGeometry(QRect(50, 530, 41, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        label_ScibbleImage_ValueOfSliceNumber->setFont(font1);
        label_ScibbleImage_ValueOfSliceNumber->setCursor(QCursor(Qt::IBeamCursor));
        label_ScibbleImage_ValueOfSliceNumber->setLayoutDirection(Qt::LeftToRight);
        label_ScibbleImage_ValueOfSliceNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255, 0);"));
        label_ScibbleImage_ValueOfSliceNumber->setTextFormat(Qt::AutoText);
        label_ScibbleImage_ValueOfSliceNumber->setScaledContents(false);
        label_ScibbleImage_ValueOfSliceNumber->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_ScibbleImage_ValueOfSliceNumber->setTextInteractionFlags(Qt::TextSelectableByMouse);
        label_ScribbleImage_ValueOfSliceNumber_Value = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_ScribbleImage_ValueOfSliceNumber_Value->setObjectName(QStringLiteral("label_ScribbleImage_ValueOfSliceNumber_Value"));
        label_ScribbleImage_ValueOfSliceNumber_Value->setGeometry(QRect(5, 530, 31, 21));
        label_ScribbleImage_ValueOfSliceNumber_Value->setFont(font1);
        label_ScribbleImage_ValueOfSliceNumber_Value->setCursor(QCursor(Qt::IBeamCursor));
        label_ScribbleImage_ValueOfSliceNumber_Value->setLayoutDirection(Qt::LeftToRight);
        label_ScribbleImage_ValueOfSliceNumber_Value->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255, 0);"));
        label_ScribbleImage_ValueOfSliceNumber_Value->setTextFormat(Qt::AutoText);
        label_ScribbleImage_ValueOfSliceNumber_Value->setScaledContents(false);
        label_ScribbleImage_ValueOfSliceNumber_Value->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_ScribbleImage_ValueOfSliceNumber_Value->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextEditable|Qt::TextEditorInteraction|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        label_ScibbleImage_ValueOfSliceNumber_2 = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_ScibbleImage_ValueOfSliceNumber_2->setObjectName(QStringLiteral("label_ScibbleImage_ValueOfSliceNumber_2"));
        label_ScibbleImage_ValueOfSliceNumber_2->setGeometry(QRect(25, 530, 21, 21));
        label_ScibbleImage_ValueOfSliceNumber_2->setFont(font1);
        label_ScibbleImage_ValueOfSliceNumber_2->setCursor(QCursor(Qt::IBeamCursor));
        label_ScibbleImage_ValueOfSliceNumber_2->setLayoutDirection(Qt::LeftToRight);
        label_ScibbleImage_ValueOfSliceNumber_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255, 0);"));
        label_ScibbleImage_ValueOfSliceNumber_2->setTextFormat(Qt::AutoText);
        label_ScibbleImage_ValueOfSliceNumber_2->setScaledContents(false);
        label_ScibbleImage_ValueOfSliceNumber_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_ScibbleImage_ValueOfSliceNumber_2->setTextInteractionFlags(Qt::TextSelectableByMouse);
        label_OriginalDisplay = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_OriginalDisplay->setObjectName(QStringLiteral("label_OriginalDisplay"));
        label_OriginalDisplay->setGeometry(QRect(0, 0, 475, 560));
        label_OriginalDisplay->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        label_OriginalDisplay->setAlignment(Qt::AlignCenter);
        label_ContourOverlayTitle = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_ContourOverlayTitle->setObjectName(QStringLiteral("label_ContourOverlayTitle"));
        label_ContourOverlayTitle->setGeometry(QRect(10, 10, 91, 25));
        label_ContourOverlayTitle->setFont(font1);
        label_ContourOverlayTitle->setLayoutDirection(Qt::LeftToRight);
        label_ContourOverlayTitle->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255, 0);"));
        label_MaskOverlay_fg1 = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_MaskOverlay_fg1->setObjectName(QStringLiteral("label_MaskOverlay_fg1"));
        label_MaskOverlay_fg1->setGeometry(QRect(0, 0, 475, 560));
        label_MaskOverlay_fg1->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        label_MaskOverlay_fg1->setAlignment(Qt::AlignCenter);
        label_MaskOverlay_fg2 = new QLabel(scrollAreaWidgetContents_ContourOverlay);
        label_MaskOverlay_fg2->setObjectName(QStringLiteral("label_MaskOverlay_fg2"));
        label_MaskOverlay_fg2->setGeometry(QRect(0, 0, 475, 560));
        label_MaskOverlay_fg2->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        label_MaskOverlay_fg2->setAlignment(Qt::AlignCenter);
        scrollArea_ScribbleArea = new QScrollArea(scrollAreaWidgetContents_ContourOverlay);
        scrollArea_ScribbleArea->setObjectName(QStringLiteral("scrollArea_ScribbleArea"));
        scrollArea_ScribbleArea->setGeometry(QRect(0, 0, 475, 560));
        scrollArea_ScribbleArea->setMaximumSize(QSize(16777215, 16777215));
        scrollArea_ScribbleArea->setAutoFillBackground(false);
        scrollArea_ScribbleArea->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        scrollArea_ScribbleArea->setFrameShadow(QFrame::Raised);
        scrollArea_ScribbleArea->setLineWidth(0);
        scrollArea_ScribbleArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea_ScribbleArea->setWidgetResizable(true);
        scrollArea_ScribbleArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 473, 558));
        scrollArea_ScribbleArea->setWidget(scrollAreaWidgetContents_4);
        scrollArea_ContourOverlay->setWidget(scrollAreaWidgetContents_ContourOverlay);
        label_OriginalDisplay->raise();
        label_MaskOverlay_fg->raise();
        label_MaskOverlay_bg->raise();
        label_MaskDisplay->raise();
        label_MaskOverlay_fg1->raise();
        label_MaskOverlay_fg2->raise();
        label_ContourOverlay->raise();
        scrollArea_EditContourArea->raise();
        label_ContourOverlayTitle->raise();
        scrollArea_ScribbleArea->raise();
        label_ScibbleImage_ValueOfSliceNumber_2->raise();
        label_ScibbleImage_ValueOfSliceNumber->raise();
        label_ScribbleImage_ValueOfSliceNumber_Value->raise();

        horizontalLayout_2->addWidget(scrollArea_ContourOverlay);

        verticalScrollBar_ScribbleImage = new QScrollBar(frame_3);
        verticalScrollBar_ScribbleImage->setObjectName(QStringLiteral("verticalScrollBar_ScribbleImage"));
        verticalScrollBar_ScribbleImage->setMinimumSize(QSize(20, 560));
        verticalScrollBar_ScribbleImage->setMinimum(1);
        verticalScrollBar_ScribbleImage->setPageStep(5);
        verticalScrollBar_ScribbleImage->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(verticalScrollBar_ScribbleImage);


        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_4);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_OriginalSize = new QPushButton(frame_4);
        pushButton_OriginalSize->setObjectName(QStringLiteral("pushButton_OriginalSize"));
        pushButton_OriginalSize->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));

        horizontalLayout_3->addWidget(pushButton_OriginalSize);

        horizontalSlider_zoom = new QSlider(frame_4);
        horizontalSlider_zoom->setObjectName(QStringLiteral("horizontalSlider_zoom"));
        horizontalSlider_zoom->setMinimumSize(QSize(0, 20));
        horizontalSlider_zoom->setMaximumSize(QSize(16777215, 20));
        horizontalSlider_zoom->setMaximum(200);
        horizontalSlider_zoom->setValue(100);
        horizontalSlider_zoom->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_zoom);

        label_ZoomValue = new QLabel(frame_4);
        label_ZoomValue->setObjectName(QStringLiteral("label_ZoomValue"));
        label_ZoomValue->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font-family: \"Arial\";\n"
"font-size: 12px;"));

        horizontalLayout_3->addWidget(label_ZoomValue);

        pushButton_FitTheScreen = new QPushButton(frame_4);
        pushButton_FitTheScreen->setObjectName(QStringLiteral("pushButton_FitTheScreen"));
        pushButton_FitTheScreen->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    color: rgb(20,20,20);\n"
"    background-color: rgb(240, 240, 240);\n"
"    border-radius:5px;\n"
"    padding: 3px;\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color: rgb(220, 220, 220);\n"
"}\n"
"QPushButton:pressed, QPushButton:checked\n"
"{\n"
"    background-color: rgb(200,200, 200);\n"
"}\n"
""));

        horizontalLayout_3->addWidget(pushButton_FitTheScreen);


        verticalLayout->addWidget(frame_4);


        horizontalLayout->addWidget(frame_2);


        retranslateUi(Dialog_EditMask);

        QMetaObject::connectSlotsByName(Dialog_EditMask);
    } // setupUi

    void retranslateUi(QDialog *Dialog_EditMask)
    {
        Dialog_EditMask->setWindowTitle(QApplication::translate("Dialog_EditMask", "Dialog", 0));
        label_EditContour->setText(QApplication::translate("Dialog_EditMask", "Edit Contour:", 0));
        pushButton_cnt1->setText(QString());
        pushButton_cnt2->setText(QString());
        pushButton_ContourOverlay_Edit_PointOrigin->setText(QApplication::translate("Dialog_EditMask", "Original Points", 0));
        pushButton_ContourOverlay_Edit_PointEnd->setText(QApplication::translate("Dialog_EditMask", "New Points", 0));
        pushButton_ContourOverlay_Edit->setText(QApplication::translate("Dialog_EditMask", "Edit", 0));
        pushButton_ContourOverlay_Edit_Clear->setText(QApplication::translate("Dialog_EditMask", "Clear", 0));
        label_EditObjects->setText(QApplication::translate("Dialog_EditMask", "Edit Objects:", 0));
        pushButton_obj1->setText(QApplication::translate("Dialog_EditMask", "Paint Object1", 0));
        label_px1->setText(QApplication::translate("Dialog_EditMask", "px", 0));
        lineEdit_obj1->setText(QApplication::translate("Dialog_EditMask", " 10", 0));
        pushButton_obj2->setText(QApplication::translate("Dialog_EditMask", "Paint Object2", 0));
        lineEdit_obj2->setText(QApplication::translate("Dialog_EditMask", " 10", 0));
        label_px2->setText(QApplication::translate("Dialog_EditMask", "px", 0));
        pushButton_bkg->setText(QApplication::translate("Dialog_EditMask", "Paint Background", 0));
        lineEdit_bkg->setText(QApplication::translate("Dialog_EditMask", " 10", 0));
        label_px4->setText(QApplication::translate("Dialog_EditMask", "px", 0));
        pushButton_ReloadMask->setText(QApplication::translate("Dialog_EditMask", "Reload Mask", 0));
        pushButton_SaveMaskAs->setText(QApplication::translate("Dialog_EditMask", "Save Mask As ...", 0));
        pushButton_SaveChanges->setText(QApplication::translate("Dialog_EditMask", "Save Change", 0));
        pushButton_Reset->setText(QApplication::translate("Dialog_EditMask", "Reset", 0));
        pushButton_MaskOverlay_Edit_Clear->setText(QApplication::translate("Dialog_EditMask", "Clear", 0));
        pushButton_MaskOverlay_Edit->setText(QApplication::translate("Dialog_EditMask", "Edit", 0));
        label_MaskDisplay->setText(QString());
        label_ContourOverlay->setText(QString());
        label_MaskOverlay_fg->setText(QString());
        label_MaskOverlay_bg->setText(QString());
        label_ScibbleImage_ValueOfSliceNumber->setText(QApplication::translate("Dialog_EditMask", "0", 0));
        label_ScribbleImage_ValueOfSliceNumber_Value->setText(QApplication::translate("Dialog_EditMask", "0", 0));
        label_ScibbleImage_ValueOfSliceNumber_2->setText(QApplication::translate("Dialog_EditMask", "/", 0));
        label_OriginalDisplay->setText(QString());
        label_ContourOverlayTitle->setText(QApplication::translate("Dialog_EditMask", "Display", 0));
        label_MaskOverlay_fg1->setText(QString());
        label_MaskOverlay_fg2->setText(QString());
        pushButton_OriginalSize->setText(QApplication::translate("Dialog_EditMask", "Original Size", 0));
        label_ZoomValue->setText(QApplication::translate("Dialog_EditMask", "100%", 0));
        pushButton_FitTheScreen->setText(QApplication::translate("Dialog_EditMask", "Fit the Screen", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_EditMask: public Ui_Dialog_EditMask {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMASK_H
