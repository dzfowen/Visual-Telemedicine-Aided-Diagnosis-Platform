#include "EditContourArea.h"
#include <QPainter>

using namespace std;
using namespace cv;



EditContourArea::EditContourArea()
{
	image = QImage(10, 10, QImage::Format_ARGB32);
	image.fill(0);
}

void EditContourArea::setImageSize(int scribble_width, int scribble_height)
{
	QImage newImage(scribble_width, scribble_height, QImage::Format_ARGB32);
	newImage.fill(0);
	image = newImage;
	oSize = cvSize(scribble_width, scribble_height);
	update();
}

void EditContourArea::init(int scribble_width, int scribble_height)
{

	contourMask.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	contourMask = 0;
	maskTemp.create(cvSize(scribble_width, scribble_height), CV_8UC1);
	maskTemp = 0;
	contourImg.create(cvSize(scribble_width, scribble_height), CV_8UC4);
	contourImg = (0, 0, 0, 0);
	contourImg0.create(cvSize(scribble_width, scribble_height), CV_8UC4);
	contourImg0 = (0, 0, 0, 0);
	contourImg1.create(cvSize(scribble_width, scribble_height), CV_8UC4);
	contourImg1 = (0, 0, 0, 0);
	contourImg2.create(cvSize(scribble_width, scribble_height), CV_8UC4);
	contourImg2 = (0, 0, 0, 0);
    
	//namedWindow("Contour Mask", CV_WINDOW_AUTOSIZE);
	//namedWindow("Contour Image", CV_WINDOW_AUTOSIZE);

	/*imshow("Contour Mask", contourMask);
	imshow("Contour Image", contourImg);*/

}

void EditContourArea::scaleImage()
{
	image_scaled = image.scaled(qSize, Qt::IgnoreAspectRatio);
	
	image = image_scaled;

	//cv::resize(contourImg, contourImg, cSize);
	
	//imshow("Contour Image", contourImg);
}

void EditContourArea::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawImage(0, 0, image);
}

void EditContourArea::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		lastPoint = event->pos();
		int x = lastPoint.x();
		int y = lastPoint.y();
		x = x/zoomInfactor;
		y = y/zoomInfactor;
		cOrigin = Point(x, y);	

		if (EditContourOne_isOn)
		{	
			contourOriginPoint_x.push_back(x);
			contourOriginPoint_y.push_back(y);	
		}
		if (EditContourPointOrigin_isOn)
		{
			numPointOrigin++;
			contourOriginPoint_x.push_back(x);
			contourOriginPoint_y.push_back(y);
			numOrigin = QString::number(numPointOrigin);
			paint(image);
		}
		if (EditContourPointEnd_isOn)
		{
			numPointEnd++;
			contourEndPoint_x.push_back(x);
			contourEndPoint_y.push_back(y);
			numEnd = QString::number(numPointEnd);
			paint(image);
		}
	}
}

void EditContourArea::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons()&Qt::LeftButton)
	{
		endPoint = event->pos();
		//paint(image);
		//image.fill(0);
	}
}

void EditContourArea::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		endPoint = event->pos();
		if (EditContourOne_isOn)
		{
			paint(image);
			int x = endPoint.x();
			int y = endPoint.y();
			x = x/zoomInfactor;
			y = y/zoomInfactor;
			cEnd = Point(x, y);
			contourLoop ++;
			One_isDone = true;
			contourEndPoint_x.push_back(x);
			contourEndPoint_y.push_back(y);
			line(contourImg, cOrigin, cEnd, Scalar(127, 255, 255));
			//imshow("Contour Image", contourImg);
		}
	}
}

 

void EditContourArea::paint(QImage &theImage)
{
	QPainter pp(&theImage);
	if (EditContourOne_isOn)
	{
		pp.setPen(QPen(BrushColor, 0));
		pp.setBrush(BrushColor);
		pp.drawLine(lastPoint, endPoint);
	}
	if (EditContourPointOrigin_isOn)
	{
		pp.setPen(QPen(BrushOrigin, 0));
		pp.setBrush(BrushColor);
		pp.drawEllipse(lastPoint, 1, 1);
		pp.drawText(lastPoint.x()+3,lastPoint.y()+3, numOrigin);
	}
	if (EditContourPointEnd_isOn)
	{
		pp.setPen(QPen(BrushEnd, 0));
		pp.setBrush(BrushColor);
		pp.drawEllipse(lastPoint, 1, 1);
		pp.drawText(lastPoint.x() + 3, lastPoint.y() + 3, numEnd);
	}
	
	update();
}

