#ifndef MHDREADER_H
#define MHDREADER_H

#pragma once
using namespace std;
#include <string>
#include <string.h>
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkDICOMImageReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "server.h"
#include "vtkImagePlaneWidget.h"
#include <vtkResliceCursorWidget.h>
#include "vtkResliceCursor.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include <vtkImageData.h>
#include <QObject>
#include <vtkMetaImageReader.h>
#include <vtkImageShiftScale.h>
#include <vtkImageBlend.h>
#include <vtkImageFlip.h>

#include "mainSocketThread.h"
#include "editmask.h"

class mhdReader : public QObject
{
	Q_OBJECT
private:
	vtkSmartPointer<vtkImagePlaneWidget>   m_ImagePlaneWidget;
	vtkSmartPointer<vtkResliceCursorWidget> m_ResliceCursorWidget;
	vtkSmartPointer<vtkResliceCursor>      m_ResliceCursor;
	vtkSmartPointer<vtkResliceCursorThickLineRepresentation> m_ResliceCursorRep;
	Ui::ServerClass currentui;
	char filepath[100];
	std::vector<short> vStrImg;
	char* liverConstraintFile = "F:\\Program in japan\\TrainingCase49_LIverMask_RAI.mhd";

	/////YY/////
	EditMask *edition;
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
	/////2017.5.28////

	float originalPoints[10];
	float editPoints[10];

protected:
	vtkSmartPointer< vtkResliceImageViewer > riw[3];
	vtkSmartPointer< vtkImagePlaneWidget > planeWidget[3];
	vtkSmartPointer< vtkDistanceWidget > DistanceWidget[3];
	vtkSmartPointer< vtkResliceImageViewerMeasurements > ResliceMeasurements;
	vtkSmartPointer< vtkMetaImageReader > reader;

	vtkSmartPointer< vtkRenderer > renderForWidgetX;
	vtkSmartPointer< vtkRenderer > renderForVolume;
	vtkSmartPointer< vtkImageShiftScale > shiftScaleFilter;
	vtkSmartPointer<vtkImageFlip> filpYFilter;

public:
	mhdReader();
	~mhdReader();
	void Read_Display(string path, Ui::ServerClass ui);
	////YY////
	QString QInputfile;
	////2016.12.23////
	mainSocketThread * mainSockTread;

	private slots:
	void slider_x_moved(int);
	void slider_y_moved(int);
	void slider_z_moved(int);
	void Saveimg();

	void openVolumeRendering();
	///YY///
	void test();
	void Edit();
	///2017.5.28///
	//change brightness and contrast
	void changeBrighteness(int);
	void changeContrast(int);

	void overlap();

	void editMask();
	void origianlPoint();
	void newPoint();

	//void server_GetRequestForOriginalPoint();
	//void server_GetRequestForNewPoint();
	//void server_GetRequestForEditMask();
};

#endif // MHDREADER_H