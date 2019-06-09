#ifndef EDITMASK_H
#define EDITMASK_H

#pragma once
#include "ui_editmask.h"
#include "EditContourArea.h"
#include "EditArea.h"
#include "qwidget.h"
#include <QDialog>
#include <QColorDialog>
#include <DataFile.h>
#include <Windows.h> 

#include <QtWidgets/QMainWindow>
#include <qdebug.h>
#include <QFileDialog.h>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp>  


#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <sstream>
#include <direct.h>
#include <io.h>
#include <string>  
#include <iomanip> 
#include <stdio.h>
#include <math.h>
//#include <tchar.h>

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include <itkRescaleIntensityImageFilter.h>
#include <itkMetaImageIOFactory.h>
#include <itkJPEGImageIOFactory.h>
#include <itkGDCMImageIOFactory.h>

#include "itkImageSeriesReader.h"
#include "itkNumericSeriesFileNames.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkGDCMImageIO.h"


using namespace std;
using namespace cv;

namespace Ui {
	class Dialog_EditMask;
}

class EditMask :public QDialog
{
	Q_OBJECT
public:
	explicit EditMask(QWidget *parent = 0);
	~EditMask();
	char* oriMhd;
	char* maskMhd;
	char* maskNew="maskNew.mhd";
	char* maskEdit = "maskEdit.mhd";
	char* maskOri = "maskOri.mhd";
	char * DICOMtoMHD = "test.mhd";
	QColor fgOverlayColor = Qt::red;
	QColor bgOverlayColor = Qt::blue;
	QColor fgOverlayColor1 = QColor(0, 255, 255, 255);
	QColor fgOverlayColor2 = QColor(255, 0, 255, 255);
	QColor contourOverlayColor = Qt::green;
	QColor contourOverlayColor1 = QColor(0, 255, 255, 255);
	QColor contourOverlayColor2 = QColor(255, 0, 255, 255);

	int fgOverlayOpacity = 20;
	int bgOverlayOpacity = 20;
	int fgOverlayOpacity1 = 20;
	int fgOverlayOpacity2 = 20;
	int contourOverlayOpacity = 80;
	int contourOverlayOpacity1 = 80;
	int contourOverlayOpacity2 = 80;

	


	int str_index=0;
	int imageType=1;
	std::vector<short> vStrImg;
	char * imgFileName = "output.jpg";
	QPixmap P_inputImage;
	QPixmap PM_fgMaskOverlay, PM_fgMaskOverlay1, PM_fgMaskOverlay2, PM_bgMaskOverlay, PM_contourOverlay, PM_segMaskImg, PM_segMaskImgfg, PM_segMaskImgfg1, PM_segMaskImgfg2;
	QSize qSize, oSize;
	int width, height, depth;
	double index_x, index_y, index_z, spacing_x, spacing_y, spacing_z, origin_x, origin_y, origin_z;
	short pixel_max = 0;
	short pixel_min = 0;
	//int window_width = 475, window_height = 560;

	QImage QScribbleImg;
	QImage QfgMaskOverlay;
	QImage QfgMaskOverlay1;
	QImage QfgMaskOverlay2;
	QImage QbgMaskOverlay;
	QImage QcontourOverlay;
	QImage QsegMaskImg, QsegMaskImgfg, QsegMaskImgfg1, QsegMaskImgfg2;
	QImage QScribbleImgScaled, QfgMaskOverlayScaled, QfgMaskOverlay1Scaled, QfgMaskOverlay2Scaled, QbgMaskOverlayScaled, QcontourOverlayScaled, QsegMaskImgScaled, QsegMaskImgfgScaled, QsegMaskImgfg1Scaled, QsegMaskImgfg2Scaled;
	// images
	cv::Mat inputImg, showImg, segShowImg;
	// mask
	cv::Mat fgMask, fgMask1, fgMask2, bgMask, segMask, contourSeg0, contourSeg1, contourSeg2, segMaskfg, segMaskfg1, segMaskfg2;
	cv::Mat fgMaskScaled, fgMask1Scaled, fgMask2Scaled, bgMaskScaled, segMaskScaled, contourSeg0Scaled, contourSeg1Scaled, contourSeg2Scaled, segMaskfgScaled, segMaskfg1Scaled, segMaskfg2Scaled;

	char* fgMaskOverlay = "fgMaskOverlay.png";
	char* bgMaskOverlay = "bgMaskOverlay.png";
	char* fgMaskOverlay1 = "fgMaskOverlay1.png";
	char* fgMaskOverlay2 = "fgMaskOverlay2.png";
	char* contourOverlay = "contourOverlay.png";
	char* maskImg = "maskImg.jpg";
	char* maskImgfg = "maskImgfg.jpg";
	char* maskImgfg1 = "maskImgfg1.jpg";
	char* maskImgfg2 = "maskImgfg2.jpg";

	EditArea *area0;
	EditContourArea *contourArea0;

	std::vector<short> vImage;
	double zoomInfactor;
	

	public slots:
	void setTitle(QString);
	void show(QColor obj1,QColor obj2,QColor obj3,QColor bkg,QColor cnt1,QColor cnt2,QColor cnt3,int obj1o, int obj2o,int obj3o,int bkgo,int cnt1o,int cnt2o,int cnt3o, char* oriFile,char* maskFile, int index);

	void loadData();
	void InputDisplay();
	int loadOriginal3DImage(char * imgName, int str_index);
	int img3D_2D(vector<short> img3D, int str_index, char*img2D);
	int init(char * imgFileName);
	void copyMhdFile(char* file1, char* file2);
	void OverlayDisplay();
	void readMask(char* file);
	void writeMask(char* file);
	void saveMask(char* file);
	void ReloadMask();
	void ResetMask();
	void displayOverlays();
	void changeStartIndex();
	void readImage();
	void ClearContourPoints();
	void ClearPainting();

	void pushButton_cnt1_onclick();
	void pushButton_cnt2_onclick();
	//void pushButton_cnt3_onclick();
	void pushButton_bkg_onclick();
	void pushButton_obj1_onclick();
	void pushButton_obj2_onclick();
	//void pushButton_obj3_onclick();
	
	void changeSize_obj1();
	void changeSize_obj2();
	//void changeSize_obj3();
	void changeSize_bkg();
	void setSize_obj1();
	void setSize_obj2();
	//void setSize_obj3();
	void setSize_bkg();

	void EditContour_one();
	void EditContour_PointOrigin();
	void EditContour_PointEnd();
	void EditContour();
	void EditPainting();
	void morphing(int Feat_num, double Div_x, double Div_y);

	void SaveChanges();
	void SaveResult();

	void closeEvent(QCloseEvent *event);

	void fit_Image();
	void originalSize();
	void zoom();

protected:

private:

	Ui::Dialog_EditMask *ui;
};

#endif




