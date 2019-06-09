#pragma once

#include "server.h"
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
#include "vtkImagePlaneWidget.h"
#include <vtkResliceCursorWidget.h>
#include "vtkResliceCursor.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include <vtkImageData.h>
#include <QObject>
#include <vtkTextMapper.h>
#include "vtkTextRenderer.h"

//占淦	3D引入文件
#include <vtkOpenGLGPUVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeMapper.h>

using namespace std;


class mainSocketThread;

class DicomReader : public QObject
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


protected:
	vtkSmartPointer< vtkResliceImageViewer > riw[4];
	vtkSmartPointer< vtkImagePlaneWidget > planeWidget[4];
	vtkSmartPointer< vtkDistanceWidget > DistanceWidget[4];
	vtkSmartPointer< vtkTextMapper > sliceTextMapper[4];
	vtkSmartPointer< vtkResliceImageViewerMeasurements > ResliceMeasurements;

	vtkSmartPointer<vtkDICOMImageReader> reader;	//The dicom reader
	vtkSmartPointer<vtkDICOMImageReader> Reader3D;	//The dicom reader

	
	
public:
	mainSocketThread * mainSThread;				//The TCP server mainSockThread


	DicomReader();
	~DicomReader();
	void Read_Display(string path, Ui::ServerClass ui);
	void SetMainSocketThread(mainSocketThread * mainSockThread);
	void DicomRead_3D(string path, Ui::ServerClass ui); //占淦 2016-11-14

private slots:
	void slider_movedAll(int);
	void slider_x_moved(int);
	void slider_y_moved(int);
	void slider_z_moved(int);
	void SaveImg();

	//void btnSegmentClicked();
	



};

