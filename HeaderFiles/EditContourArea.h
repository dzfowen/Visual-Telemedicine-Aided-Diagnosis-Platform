#ifndef EDITCONTOURAREA_H
#define EDITCONTOURAREA_H

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

class EditContourArea :
	public QWidget
{
public:
	bool EditContourOne_isOn;
	bool EditContourPointOrigin_isOn;
	bool EditContourPointEnd_isOn;
	
	bool One_isDone;

	int BrushRadius = 1;
	QColor BrushColor = Qt::yellow;
	QColor BrushOrigin = Qt::yellow;
	QColor BrushEnd = Qt::magenta;
	int contourLoop;
	int numPointOrigin = 0;
	int numPointEnd = 0;

	cv::Mat contourMask, maskTemp, contourImg, contourImg0,contourImg1, contourImg2;

	vector<short>contourOriginPoint_x;
	vector<short>contourOriginPoint_y;
	vector<short>contourEndPoint_x;
	vector<short>contourEndPoint_y;

	EditContourArea();
	void init(int scribble_width, int scribble_height);
	void setImageSize(int scribble_width, int scribble_height);
	QImage image;

	QSize qSize;
	CvSize cSize, oSize;

	double zoomInfactor;

	QImage image_scaled;
	QString numOrigin;
	QString numEnd;

	void scaleImage();

protected:

	Point cOrigin;
	Point cEnd;



	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void paint(QImage& theImage);
	
	QPoint lastPoint, endPoint;
};

#endif