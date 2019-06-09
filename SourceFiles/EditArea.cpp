#include "EditArea.h"
#include <QPainter>




using namespace std;
using namespace cv;



EditArea::EditArea()
{

	imageObj = QImage(10, 10, QImage::Format_ARGB32);
	imageObj.fill(0);

	imageBkg = QImage(10, 10, QImage::Format_ARGB32);
	imageBkg.fill(0);

	imageObj1 = QImage(10, 10, QImage::Format_ARGB32);
	imageObj1.fill(0);

	imageObj2 = QImage(10, 10, QImage::Format_ARGB32);
	imageObj2.fill(0);

	imageNotes = QImage(10, 10, QImage::Format_ARGB32);
	imageNotes.fill(0);

	imageROI = QImage(10, 10, QImage::Format_ARGB32);
	imageROI.fill(0);
}

void EditArea::scaleImage()
{

	//imageROI_scaled = imageROI;
	//imageObj_scaled = imageObj;
	//imageBkg_scaled = imageBkg;
	//imageNotes_scaled = imageNotes;

	imageROI_scaled = imageROI.scaled(qSize, Qt::IgnoreAspectRatio);
	imageObj_scaled = imageObj.scaled(qSize, Qt::IgnoreAspectRatio);
	imageBkg_scaled = imageBkg.scaled(qSize, Qt::IgnoreAspectRatio);
	imageObj1_scaled = imageObj1.scaled(qSize, Qt::IgnoreAspectRatio);
	imageObj2_scaled = imageObj2.scaled(qSize, Qt::IgnoreAspectRatio);
	imageNotes_scaled = imageNotes.scaled(qSize, Qt::IgnoreAspectRatio);

	imageROI =imageROI_scaled;
	imageObj = imageObj_scaled;
	imageBkg = imageBkg_scaled;
	imageObj1 = imageObj1_scaled;
	imageObj2 = imageObj2_scaled;
	imageNotes = imageNotes_scaled;

	cv::resize(fgScribbleMask, fgScribbleMask, cSize);
	cv::resize(bgScribbleMask, bgScribbleMask, cSize);
	cv::resize(fgScribbleMask1, fgScribbleMask1, cSize);
	cv::resize(fgScribbleMask2, fgScribbleMask2, cSize);
	cv::resize(eraserMask, eraserMask, cSize);
	cv::resize(notesScribbleMask, notesScribbleMask, cSize);
	//imshow("fg mask", fgScribbleMask);
	//imshow("bg mask", bgScribbleMask);
}

void EditArea::setImageSize(int scribble_width, int scribble_height)
{
	QImage newImage(scribble_width, scribble_height, QImage::Format_ARGB32);
	newImage.fill(0);
	imageObj = newImage;
	imageBkg = newImage;
	imageObj1 = newImage;
	imageObj2 = newImage;
	imageNotes = newImage;
	imageROI = newImage;
	width = scribble_width;
	height = scribble_height;
	oSize = cvSize(scribble_width, scribble_height);
	update();
}

void EditArea::clearNotes()
{
	imageNotes.fill(0);
	notesScribbleMask = 0;
	update();
}

void EditArea::clearObj()
{
	imageObj.fill(0);
	imageObj1.fill(0);
	imageObj2.fill(0);
	fgScribbleMask = 0;
	fgScribbleMask1 = 0;
	fgScribbleMask2 = 0;
	update();
	//imshow("fg mask", fgScribbleMask);
}

void EditArea::clearBkg()
{
	imageBkg.fill(0);
	bgScribbleMask = 0;
	update();
	//imshow("bg mask", bgScribbleMask);
}

void EditArea::init(int scribble_width, int scribble_height)
{
	objLabel.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	objLabel = 0;
	bkgLabel.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	bkgLabel = 0;
	objLabel1.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	objLabel1 = 0;
	objLabel2.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	objLabel2 = 0;
	fgScribbleMask.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	fgScribbleMask = 0;
	bgScribbleMask.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	bgScribbleMask = 0;
	fgScribbleMask1.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	fgScribbleMask1 = 0;
	fgScribbleMask2.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	fgScribbleMask2 = 0;
	notesScribbleMask.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	notesScribbleMask = 0;
	eraserMask.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	eraserMask = 0;
	




	//namedWindow("fg mask", CV_WINDOW_AUTOSIZE);
	//namedWindow("bg mask", CV_WINDOW_AUTOSIZE);
	

	//imshow("fg mask", fgScribbleMask);
	//imshow("bg mask", bgScribbleMask);

}

void EditArea::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawImage(0, 0, imageObj);
	painter.drawImage(0, 0, imageBkg);
	painter.drawImage(0, 0, imageObj1);
	painter.drawImage(0, 0, imageObj2);
	painter.drawImage(0, 0, imageNotes);
	painter.drawImage(0, 0, imageROI);
}

void EditArea::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		selectPoint = event->pos();
		index_x = selectPoint.x();
		index_y = selectPoint.y();

		lastPoint = event->pos();
		int x = lastPoint.x();
		int y = lastPoint.y();

		setLabels = 1;

		if (pushButton_Select_isOn)
		{
			endPoint = lastPoint;
		}
		else if (pushButton_ROI_isOn)
		{
			setROI = 0;
			testPoint = event->pos();
			x = x / zoomInfactor;
			y = y / zoomInfactor;
			select_flag = true;
			pOrigin = Point(x, y);
			select = Rect(x, y, 0, 0);
		}
		//else if (pushButton_obj_isOn)
		//{
		//	////imageObj.fill(0);
		//	//imageObj1.fill(0);
		//	//imageObj2.fill(0);
		//	//imageBkg.fill(0);
		//	//update();
		//	paint(imageObj);
		//	circle(fgScribbleMask, Point(x, y), objBrushRadius, 255, -1);
		//	circle(bgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
		//	circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
		//	circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
		//	//imshow("fg mask", fgScribbleMask);

		//}
		//else if (pushButton_bkg_isOn)
		//{
		//	//imageObj.fill(0);
		//	//imageObj1.fill(0);
		//	//imageObj2.fill(0);
		//	////imageBkg.fill(0);
		//	//update();
		//	paint(imageBkg);
		//	circle(bgScribbleMask, Point(x, y), bkgBrushRadius, 255, -1);
		//	circle(fgScribbleMask, Point(x, y), bkgBrushRadius, 0, -1);
		//	circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
		//	circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
		//	//imshow("bg mask", bgScribbleMask);

		//}
		//else if (pushButton_obj1_isOn)
		//{
		//	//imageObj.fill(0);
		//	////imageObj1.fill(0);
		//	//imageObj2.fill(0);
		//	//imageBkg.fill(0);
		//	//update();
		//	paint(imageObj1);
		//	circle(fgScribbleMask1, Point(x, y), obj1BrushRadius, 255, -1);
		//	circle(bgScribbleMask, Point(x, y), obj1BrushRadius, 0, -1);
		//	circle(fgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
		//	circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
		//	//imshow("fg mask", fgScribbleMask);


		//}
		//else if (pushButton_obj2_isOn)
		//{
		//	//imageObj.fill(0);
		//	//imageObj1.fill(0);
		//	////imageObj2.fill(0);
		//	//imageBkg.fill(0);
		//	//update();
		//	paint(imageObj2);
		//	circle(fgScribbleMask2, Point(x, y), obj2BrushRadius, 255, -1);
		//	circle(bgScribbleMask, Point(x, y), obj2BrushRadius, 0, -1);
		//	circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
		//	circle(fgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
		//	//imshow("fg mask", fgScribbleMask);

		//}
		//else if (pushButton_Notes_isOn)
		//{
		//	paint(imageNotes);
		//}
		//else if (pushButton_Eraser_isOn)
		//{
		//	circle(fgScribbleMask, Point(x, y), eraserBrushRadius, 0, -1);
		//	//imshow("fg mask", fgScribbleMask);
		//	circle(bgScribbleMask, Point(x, y), eraserBrushRadius, 0, -1);
		//	//imshow("bg mask", bgScribbleMask);
		//	circle(fgScribbleMask1, Point(x, y), eraserBrushRadius, 0, -1);
		//	circle(fgScribbleMask2, Point(x, y), eraserBrushRadius, 0, -1);
		//	circle(eraserMask, Point(x, y), eraserBrushRadius, 255, -1);
		//	paint(imageObj);
		//	paint(imageBkg);
		//	paint(imageObj1);
		//	paint(imageObj2);
		//	paint(imageNotes);
		//	circle(eraserMask, Point(x, y), eraserBrushRadius, 0, -1);
		//}

	}
}

void EditArea::mouseMoveEvent(QMouseEvent *event)
{



	if (event->buttons()&Qt::LeftButton)
	{
		selectPoint = event->pos();
		index_x = selectPoint.x();
		index_y = selectPoint.y();

		endPoint = event->pos();
		int x = endPoint.x();
		int y = endPoint.y();

		if (pushButton_ROI_isOn)
		{	
			paint(imageROI);
			x = x / zoomInfactor;
			y = y / zoomInfactor;
			select.x = MIN(pOrigin.x, x);
			select.y = MIN(pOrigin.y, y);
			select.width = abs(x - pOrigin.x);
			select.height = abs(y - pOrigin.y);
			select &= Rect(0, 0, width, height);		
			
		}
		else if (pushButton_obj_isOn)
		{	
			paint(imageObj);	
			circle(fgScribbleMask, Point(x, y), objBrushRadius, 255, -1);
			circle(bgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
			//imshow("fg mask", fgScribbleMask);
		}
		else if (pushButton_bkg_isOn)
		{
			paint(imageBkg);
			circle(bgScribbleMask, Point(x, y), bkgBrushRadius, 255, -1);
			circle(fgScribbleMask, Point(x, y), bkgBrushRadius, 0, -1);
			circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
			//imshow("bg mask", bgScribbleMask);
		}
		else if (pushButton_obj1_isOn)
		{
			paint(imageObj1);
			circle(fgScribbleMask1, Point(x, y), obj1BrushRadius, 255, -1);
			circle(bgScribbleMask, Point(x, y), obj1BrushRadius, 0, -1);
			circle(fgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
			//imshow("fg mask", fgScribbleMask);
		}
		else if (pushButton_obj2_isOn)
		{
			paint(imageObj2);
			circle(fgScribbleMask2, Point(x, y), obj2BrushRadius, 255, -1);
			circle(bgScribbleMask, Point(x, y), obj2BrushRadius, 0, -1);
			circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
			//imshow("fg mask", fgScribbleMask);
		}
		else if (pushButton_Notes_isOn)
		{ 
			paint(imageNotes);
			circle(notesScribbleMask, Point(x, y), notesBrushRadius, 255, -1);
		}
		else if (pushButton_Eraser_isOn)
		{
			circle(fgScribbleMask, Point(x, y), eraserBrushRadius, 0, -1);
			//imshow("fg mask", fgScribbleMask);
			circle(bgScribbleMask, Point(x, y), eraserBrushRadius, 0, -1);
			//imshow("bg mask", bgScribbleMask);
			circle(fgScribbleMask1, Point(x, y), eraserBrushRadius, 0, -1);
			circle(fgScribbleMask2, Point(x, y), eraserBrushRadius, 0, -1);
			circle(eraserMask, Point(x, y), eraserBrushRadius, 255, -1);
			circle(notesScribbleMask, Point(x, y), eraserBrushRadius, 0, -1);
			paint(imageNotes);
			paint(imageObj);
			paint(imageBkg);
			paint(imageObj1);
			paint(imageObj2);
			circle(eraserMask, Point(x, y), eraserBrushRadius, 0, -1);
		}
	}
}

void EditArea::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		selectPoint = event->pos();
		index_x = selectPoint.x();
		index_y = selectPoint.y();

		endPoint = event->pos();
		int x = endPoint.x();
		int y = endPoint.y();

		if (pushButton_ROI_isOn)
		{
			select_flag = false;              
			paint(imageROI);
			setROI = 1;
			update();
		}
		else if (pushButton_obj_isOn)
		{
			////imageObj.fill(0);
			//imageObj1.fill(0);
			//imageObj2.fill(0);
			//imageBkg.fill(0);
			//update();
			paint(imageObj);			
			circle(fgScribbleMask, Point(x, y), objBrushRadius, 255, -1);	
			circle(bgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
			//imshow("fg mask", fgScribbleMask);
			
			resetDisplay(fgScribbleMask, imageObj, objBrushColor, objBrushOpacity);
			resetDisplay(fgScribbleMask1, imageObj1, obj1BrushColor, obj1BrushOpacity);
			resetDisplay(fgScribbleMask2, imageObj2, obj2BrushColor, obj2BrushOpacity);
			resetDisplay(bgScribbleMask, imageBkg, bkgBrushColor, bkgBrushOpacity);
		}
		else if (pushButton_bkg_isOn)
		{
			//imageObj.fill(0);
			//imageObj1.fill(0);
			//imageObj2.fill(0);
			////imageBkg.fill(0);
			//update();
			paint(imageBkg);
			circle(bgScribbleMask, Point(x, y), bkgBrushRadius, 255, -1);
			circle(fgScribbleMask, Point(x, y), bkgBrushRadius, 0, -1);
			circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
			//imshow("bg mask", bgScribbleMask);
			resetDisplay(fgScribbleMask, imageObj, objBrushColor, objBrushOpacity);
			resetDisplay(fgScribbleMask1, imageObj1, obj1BrushColor, obj1BrushOpacity);
			resetDisplay(fgScribbleMask2, imageObj2, obj2BrushColor, obj2BrushOpacity);
			resetDisplay(bgScribbleMask, imageBkg, bkgBrushColor, bkgBrushOpacity);
		}
		else if (pushButton_obj1_isOn)
		{
			//imageObj.fill(0);
			////imageObj1.fill(0);
			//imageObj2.fill(0);
			//imageBkg.fill(0);
			//update();
			paint(imageObj1);
			circle(fgScribbleMask1, Point(x, y), obj1BrushRadius, 255, -1);
			circle(bgScribbleMask, Point(x, y), obj1BrushRadius, 0, -1);
			circle(fgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask2, Point(x, y), objBrushRadius, 0, -1);
			//imshow("fg mask", fgScribbleMask);
			resetDisplay(fgScribbleMask, imageObj, objBrushColor, objBrushOpacity);
			resetDisplay(fgScribbleMask1, imageObj1, obj1BrushColor, obj1BrushOpacity);
			resetDisplay(fgScribbleMask2, imageObj2, obj2BrushColor, obj2BrushOpacity);
			resetDisplay(bgScribbleMask, imageBkg, bkgBrushColor, bkgBrushOpacity);

		}
		else if (pushButton_obj2_isOn)
		{
			//imageObj.fill(0);
			//imageObj1.fill(0);
			////imageObj2.fill(0);
			//imageBkg.fill(0);
			//update();
			paint(imageObj2);
			circle(fgScribbleMask2, Point(x, y), obj2BrushRadius, 255, -1);
			circle(bgScribbleMask, Point(x, y), obj2BrushRadius, 0, -1);
			circle(fgScribbleMask1, Point(x, y), objBrushRadius, 0, -1);
			circle(fgScribbleMask, Point(x, y), objBrushRadius, 0, -1);
			//imshow("fg mask", fgScribbleMask);
			resetDisplay(fgScribbleMask, imageObj, objBrushColor, objBrushOpacity);
			resetDisplay(fgScribbleMask1, imageObj1, obj1BrushColor, obj1BrushOpacity);
			resetDisplay(fgScribbleMask2, imageObj2, obj2BrushColor, obj2BrushOpacity);
			resetDisplay(bgScribbleMask, imageBkg, bkgBrushColor, bkgBrushOpacity);
		}
		else if (pushButton_Notes_isOn)
		{
			paint(imageNotes);
		}
		else if (pushButton_Eraser_isOn)
		{			
			circle(fgScribbleMask, Point(x, y), eraserBrushRadius, 0, -1);
			//imshow("fg mask", fgScribbleMask);
			circle(bgScribbleMask, Point(x, y), eraserBrushRadius, 0, -1);
			//imshow("bg mask", bgScribbleMask);
			circle(fgScribbleMask1, Point(x, y), eraserBrushRadius, 0, -1);
			circle(fgScribbleMask2, Point(x, y), eraserBrushRadius, 0, -1);
			circle(eraserMask, Point(x, y), eraserBrushRadius, 255, -1);
			paint(imageObj);
			paint(imageBkg);
			paint(imageObj1);
			paint(imageObj2);
			paint(imageNotes);
			circle(eraserMask, Point(x, y), eraserBrushRadius, 0, -1);
		}
	}
}

void EditArea::resetDisplay(Mat image, QImage &theImage, QColor Color, int Opacity)
{

	int x = 255;
	x = x*Opacity*0.01;
	theImage.fill(0);
	
	for (int j = 0; j < cSize.height; j++)
	{
		for (int i = 0; i < cSize.width; i++)
		{
			if (image.at<uchar>(j, i) == 255)
				theImage.setPixel(i, j, qRgba(Color.red(), Color.green(), Color.blue(), x));
		}
	}
	
	/*for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (image.at<uchar>(y, x) == 255)
			pp.drawEllipse(QPoint(x,y), 1, 1);
		}
	}*/
}

void EditArea::resetDisplayROI(QImage &theImage, QColor Color, int Opacity)
{
	int x = Color.alpha();
	x = x*Opacity*0.01;
	Color.setAlpha(x);
	for (int j = 0; j < cSize.height; j++)
	{
		for (int i = 0; i < cSize.width; i++)
		{
			if (theImage.pixel(i, j) == 0)
			{

			}
			else
			theImage.setPixel(i, j, qRgba(Color.red(), Color.green(), Color.blue(), Color.alpha()));
		}
	}

}

void EditArea::paint(QImage &theImage)
{
	QPainter pp(&theImage);
	if (pushButton_ROI_isOn)
	{
		imageROI.fill(0);
		QColor brushColor;
		brushColor = roiBrushColor;
		int x = brushColor.alpha();
		x = x*roiBrushOpacity*0.01;
		brushColor.setAlpha(x);

		pp.setPen(QPen(brushColor, 0));
		QRect rect = QRect(testPoint, endPoint);
		pp.drawRect(rect);
	}
	else if (pushButton_obj_isOn)
	{
		QColor brushColor;
		brushColor = objBrushColor;
		int x = brushColor.alpha();
		x = x*objBrushOpacity*0.01;
		brushColor.setAlpha(x);

		pp.setPen(QPen(brushColor, 0));
		pp.setBrush(brushColor);
		pp.drawEllipse(lastPoint, objBrushRadius, objBrushRadius);
	}
	else if (pushButton_bkg_isOn)
	{
		QColor brushColor;
		brushColor = bkgBrushColor;		
		int x = brushColor.alpha();
		x = x*bkgBrushOpacity*0.01;
		brushColor.setAlpha(x);

		pp.setPen(QPen(brushColor, 0));
		pp.setBrush(brushColor);
		pp.drawEllipse(lastPoint, bkgBrushRadius, bkgBrushRadius);
	}
	else if (pushButton_obj1_isOn)
	{
		QColor brushColor;
		brushColor = obj1BrushColor;
		int x = brushColor.alpha();
		x = x*obj1BrushOpacity*0.01;
		brushColor.setAlpha(x);

		pp.setPen(QPen(brushColor, 0));
		pp.setBrush(brushColor);
		pp.drawEllipse(lastPoint, obj1BrushRadius, obj1BrushRadius);
	}
	else if (pushButton_obj2_isOn)
	{
		QColor brushColor;
		brushColor = obj2BrushColor;
		int x = brushColor.alpha();
		x = x*obj2BrushOpacity*0.01;
		brushColor.setAlpha(x);

		pp.setPen(QPen(brushColor, 0));
		pp.setBrush(brushColor);
		pp.drawEllipse(lastPoint, obj2BrushRadius, obj2BrushRadius);
	}
	else if (pushButton_Notes_isOn)
	{
		QColor brushColor;
		brushColor = notesBrushColor;
		int x = brushColor.alpha();
		x = x*notesBrushOpacity*0.01;
		brushColor.setAlpha(x);

		pp.setPen(QPen(brushColor, 0));
		pp.setBrush(brushColor);
		pp.drawEllipse(lastPoint, notesBrushRadius, notesBrushRadius);
	}
	else if (pushButton_Eraser_isOn)
	{
		for (int j = 0; j < cSize.height; j++)
		{
			for (int i = 0; i < cSize.width; i++)
			{
				if (eraserMask.at<uchar>(j, i) == 255)
					theImage.setPixel(i, j, qRgba(0,0,0,0));
			}
		}
		/*pp.setPen(QPen(eraserBrushColor, 0));
		pp.setBrush(eraserBrushColor);
		pp.drawEllipse(lastPoint, eraserBrushRadius, eraserBrushRadius);*/
	/*	QRect rect;
		rect = QRect(lastPoint, QPoint(lastPoint.x() + eraserBrushRadius, lastPoint.y() + eraserBrushRadius));  
		pp.eraseRect(rect);*/
	}

	lastPoint = endPoint;
	update();
}

