#ifndef EDITAREA_H
#define EDITAREA_H

#pragma once
#include "qwidget.h"
#include <QMouseEvent>
#include <QPoint>
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


using namespace std;
using namespace cv;


class EditArea :public QWidget
{
public:	
	
	bool pushButton_Select_isOn;
	bool pushButton_ROI_isOn;
	bool pushButton_obj_isOn;
	bool pushButton_bkg_isOn;
	bool pushButton_Notes_isOn;
	bool pushButton_Eraser_isOn;
	bool pushButton_obj1_isOn;
	bool pushButton_obj2_isOn;

	bool setROI=0;

	bool setLabels = 0;

	void setImageSize(int scribble_width, int scribble_height);	

	int objBrushRadius = 10;
	int bkgBrushRadius = 10;
	int notesBrushRadius = 2;
	int eraserBrushRadius = 10;
	int obj1BrushRadius = 10;
	int obj2BrushRadius = 10;
	//int roiBrushRadius = 1;

	QColor objBrushColor = Qt::red;
	QColor bkgBrushColor = Qt::blue;
	QColor notesBrushColor = Qt::green;
	QColor roiBrushColor = Qt::yellow;
	QColor obj1BrushColor = QColor(0, 255, 255, 255);
	QColor obj2BrushColor = QColor(255, 0, 255, 255);

	int objBrushOpacity = 80;
	int bkgBrushOpacity = 80;
	int notesBrushOpacity = 80;
	int roiBrushOpacity = 100;
	int obj1BrushOpacity = 80;
	int obj2BrushOpacity = 80;

	cv::Mat fgScribbleMask, bgScribbleMask, fgScribbleMask1, fgScribbleMask2, eraserMask, objLabel, bkgLabel, objLabel1, objLabel2, notesScribbleMask;
	void init(int scribble_width, int scribble_height);
	void clearNotes();
	void clearObj();
	void clearBkg();
	

	EditArea();

	int width, height;

	Rect select;



	int index_x, index_y;
	int intensity;
	//QString indexLabel;

	QPoint lastPoint, endPoint, selectPoint, testPoint;
	QSize qSize;
	CvSize cSize, oSize;

	double zoomInfactor;

	QImage imageROI, imageObj, imageBkg, imageObj1, imageObj2, imageNotes;
	QImage imageROI_scaled, imageObj_scaled, imageBkg_scaled, imageObj1_scaled, imageObj2_scaled, imageNotes_scaled;

	
	void scaleImage();
	void resetDisplay(Mat image, QImage &theImage, QColor Color, int Opacity);
	void resetDisplayROI(QImage &theImage, QColor Color, int Opacity);


protected:

	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void paint(QImage& theImage);

	Point pOrigin;
	bool select_flag = false;

};

#endif
