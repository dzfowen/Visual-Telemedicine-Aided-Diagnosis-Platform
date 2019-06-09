#include "DicomReader.h"
#include "vtkPlanes.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkXMLImageDataReader.h"
#include "vtkContourFilter.h"
#include "vtkSmartPointer.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkOutlineFilter.h"
#include "vtkStripper.h"
#include "vtkResliceCursorCallback.h"
#include "vtkResliceImageViewer.h"
#include "vtkCellPicker.h"
#include "vtkInteractorStyleImage.h"
#include "vtkImageMapToColors.h"

#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkTextMapper.h"
#include "vtkLineSource.h"
#include "vtkCallbackCommand.h"

#include "vtkMetaImageWriter.h"
#include "vtkImageCast.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkPolyDataToImageStencil.h"
#include "vtkImageStencil.h"
#include "vtkCoordinate.h"
#include "vtkMath.h"

#include "vtkImageMagnify.h"
#include "vtkImageActor.h"
//2016-11-17
#include "vtkVolumeRayCastCompositeFunction.h" 

#include <sstream>

#include <string>
using namespace std;
#include <qdebug.h>
#include <QDebug>
#include <vtkWidgetEvent.h>
#include <vtkCallbackCommand.h>
#include <vtkWidgetEventTranslator.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkProperty.h>
#include <vtkDICOMImageReader.h>
#include <vtkPiecewiseFunction.h> 
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkBoxWidget.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
extern float slice_x;
extern float slice_y;
extern float slice_z;
extern float slice_0;
extern int recv_mask;


//11-15  加入滑动条参数
class vtkVolumeSliderCallbackOpacity1 : public vtkCommand
{
public:
	static vtkVolumeSliderCallbackOpacity1 *New()
	{
		return new vtkVolumeSliderCallbackOpacity1;
	}

	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkSliderWidget *sliderWidget1 = reinterpret_cast<vtkSliderWidget*>(caller);

		double node1[] = { 0, 0, 0, 0 };
		double node2[] = { 0, 0, 0, 0 };
		double node3[] = { 0, 0, 0, 0 };
		double node4[] = { 0, 0, 0, 0 };
		this->opaFun->GetNodeValue(0, node1);
		this->opaFun->GetNodeValue(1, node2);
		this->opaFun->GetNodeValue(2, node3);
		this->opaFun->GetNodeValue(3, node4);
		double sliderpoint = static_cast<vtkSliderRepresentation *>(sliderWidget1->GetRepresentation())->GetValue();
		double slider2point = node3[0];


		this->opaFun->RemoveAllPoints();
		this->opaFun->AddPoint(0, 0, 0.49, 0.61);
		this->opaFun->AddPoint(sliderpoint, 0.71, 0.5, 0.0);
		this->opaFun->AddPoint(slider2point, 0.3, 0.5, 0.0);
		this->opaFun->AddPoint(1000, 0.0, 0.5, 0.0);

		this->UpdateEvent;
		this->opaFun->GetNodeValue(1, node2);
		std::cout << "第一个点的坐标是：" << node1[0] << "透明度是" << node1[1];
		std::cout << "第二个点的坐标是：" << node2[0] << "透明度是" << node2[1];
		std::cout << "第三个点的坐标是：" << node3[0] << "透明度是" << node3[1];
		std::cout << "第四个点的坐标是：" << node4[0] << "透明度是" << node4[1] << "\n";

	}

	vtkVolumeSliderCallbackOpacity1() :opaFun(0){}
	vtkPiecewiseFunction *opaFun;
};



class vtkVolumeSliderCallbackOpacity2 : public vtkCommand
{
public:
	static vtkVolumeSliderCallbackOpacity2 *New()
	{
		return new vtkVolumeSliderCallbackOpacity2;
	}

	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkSliderWidget *sliderWidget2 = reinterpret_cast<vtkSliderWidget*>(caller);

		double node1[] = { 0, 0, 0, 0 };
		double node2[] = { 0, 0, 0, 0 };
		double node3[] = { 0, 0, 0, 0 };
		double node4[] = { 0, 0, 0, 0 };
		this->opaFun->GetNodeValue(0, node1);
		this->opaFun->GetNodeValue(1, node2);
		this->opaFun->GetNodeValue(2, node3);
		this->opaFun->GetNodeValue(3, node4);
		double sliderpoint = static_cast<vtkSliderRepresentation *>(sliderWidget2->GetRepresentation())->GetValue();
		double sliderpoint2 = node2[0];

		this->opaFun->RemoveAllPoints();
		this->opaFun->AddPoint(0, 0, 0.49, 0.61);
		this->opaFun->AddPoint(sliderpoint2, 0.71, 0.5, 0.0);
		this->opaFun->AddPoint(sliderpoint, 0.3, 0.5, 0.0);
		this->opaFun->AddPoint(1000, 0, 0.5, 0);


		this->UpdateEvent;

		this->opaFun->GetNodeValue(2, node3);
		std::cout << "第一个点的坐标是：" << node1[0] << "透明度是" << node1[1];
		std::cout << "第二个点的坐标是：" << node2[0] << "透明度是" << node2[1];
		std::cout << "第三个点的坐标是：" << node3[0] << "透明度是" << node3[1];
		std::cout << "第四个点的坐标是：" << node4[0] << "透明度是" << node4[1] << "\n";

	}

	vtkVolumeSliderCallbackOpacity2() :opaFun(0){}
	vtkPiecewiseFunction *opaFun;
};



DicomReader::DicomReader()
{
}

DicomReader::~DicomReader()
{

}

void DicomReader::Read_Display(string path,Ui::ServerClass ui)
{
	currentui = ui;
	strcpy_s(filepath, strlen(path.c_str()) + 1, path.c_str());
	reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	string path1 = path.substr(0,path.find_last_of("/"));
	reader->SetDirectoryName(path1.data());
	reader->Update();

	int imageDims[3];
	reader->GetOutput()->GetDimensions(imageDims);

	ui.horizontalScrollBar_0->setMaximum(imageDims[2]);
	ui.horizontalScrollBar_x->setMaximum(imageDims[2]);
	ui.horizontalScrollBar_y->setMaximum(imageDims[2]);
	ui.horizontalScrollBar_z->setMaximum(imageDims[2]);
	for (int i = 0; i < 4; i++)
	{
		riw[i] = vtkSmartPointer< vtkResliceImageViewer >::New();
	}

	ui.qvtkWidget_z->SetRenderWindow(riw[0]->GetRenderWindow());
	riw[0]->SetupInteractor(ui.qvtkWidget_z->GetRenderWindow()->GetInteractor());
	ui.qvtkWidget_y->SetRenderWindow(riw[1]->GetRenderWindow());
	riw[1]->SetupInteractor(ui.qvtkWidget_y->GetRenderWindow()->GetInteractor());
	ui.qvtkWidget_xyz->SetRenderWindow(riw[2]->GetRenderWindow());
	riw[2]->SetupInteractor(ui.qvtkWidget_xyz->GetRenderWindow()->GetInteractor());
	ui.qvtkWidget_x->SetRenderWindow(riw[3]->GetRenderWindow());
	riw[3]->SetupInteractor(ui.qvtkWidget_x->GetRenderWindow()->GetInteractor());

	for (int i = 0; i < 4; i++)
	{
		// make them all share the same re slice cursor object.
		vtkResliceCursorLineRepresentation *rep =vtkResliceCursorLineRepresentation::SafeDownCast(riw[i]->GetResliceCursorWidget()->GetRepresentation());
		riw[i]->SetResliceCursor(riw[0]->GetResliceCursor());
		rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(2);
		riw[i]->SetInputData(reader->GetOutput());
		riw[i]->SetSliceOrientationToXY();
		riw[i]->SetResliceModeToAxisAligned();
	}
	double * Xrange = riw[3]->GetImageActor()->GetXRange();


	//write the Text Table
	//write the Patient information
	vtkSmartPointer<vtkTextProperty> vtkTxtProperty = vtkSmartPointer<vtkTextProperty>::New();
	vtkTxtProperty->SetFontFamilyToCourier();
	vtkTxtProperty->SetFontSize(13);
	vtkTxtProperty->SetColor(0,1,0);
	vtkTxtProperty->SetVerticalJustificationToTop();
	vtkTxtProperty->SetJustificationToLeft();

	char * infoTxt = new char[50]; infoTxt[0] = '\0';
	strcat(infoTxt, "PatientID:\t");strcat(infoTxt, reader->GetPatientName());strcat(infoTxt, "\n");
	strcat(infoTxt, "StudyID:\t"); strcat(infoTxt, reader->GetStudyID()); strcat(infoTxt, "\n");

	vtkSmartPointer<vtkTextMapper> usageTextMapper = vtkSmartPointer<vtkTextMapper>::New();
	usageTextMapper->SetInput(infoTxt);
	usageTextMapper->SetTextProperty(vtkTxtProperty);

	vtkSmartPointer<vtkActor2D> usageTextActor = vtkSmartPointer<vtkActor2D>::New();
	usageTextActor->SetMapper(usageTextMapper);
	usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
	usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

	//Change the maxslice from int to string
	char maxSlice[10];
	itoa(riw[0]->GetSliceMax(), maxSlice, 10);
	//write the slice information
	for (int i = 0; i < 4; i++)
	{
		char * sliceInfoTxt = new char[100]; sliceInfoTxt[0] = '\0';
		stringstream sstream;
		sstream << riw[i]->GetSlice(); 

		strcat(sliceInfoTxt, sstream.str().c_str()); 
		strcat(sliceInfoTxt, " / "); 
		strcat(sliceInfoTxt, maxSlice);

		sliceTextMapper[i] = vtkSmartPointer<vtkTextMapper>::New();
		sliceTextMapper[i]->SetInput(sliceInfoTxt);
		sliceTextMapper[i]->SetTextProperty(vtkTxtProperty);

		vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
		sliceTextActor->SetMapper(sliceTextMapper[i]);
		sliceTextActor->SetPosition(10, 15);

		riw[i]->GetRenderer()->AddActor2D(sliceTextActor);
		riw[i]->GetRenderer()->AddActor2D(usageTextActor);
	}
	
	vtkSmartPointer<vtkCellPicker> picker =vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkProperty> ipwProp =vtkSmartPointer<vtkProperty>::New();

	vtkSmartPointer< vtkRenderer > ren = vtkSmartPointer< vtkRenderer >::New();

	vtkRenderWindowInteractor *iren = ui.qvtkWidget_x->GetInteractor();

	vtkSmartPointer<vtkResliceCursorCallback> cbk =
		vtkSmartPointer<vtkResliceCursorCallback>::New();

	for (int i = 0; i < 4; i++)
	{
		
		// Make them all share the same color map.
		riw[i]->SetLookupTable(riw[0]->GetLookupTable());
	}
	ui.qvtkWidget_x->show();
	ui.qvtkWidget_xyz->show();
	ui.qvtkWidget_y->show();
	ui.qvtkWidget_z->show();

	ui.horizontalScrollBar_0->setValue(riw[3]->GetSlice());
	ui.horizontalScrollBar_x->setValue(riw[2]->GetSlice());
	ui.horizontalScrollBar_y->setValue(riw[1]->GetSlice());
	ui.horizontalScrollBar_z->setValue(riw[0] ->GetSlice());
	
	slice_0 = ui.horizontalScrollBar_0->value();
	slice_z = ui.horizontalScrollBar_x->value();
	slice_y = ui.horizontalScrollBar_y->value();
	slice_x = ui.horizontalScrollBar_z->value();


	connect(ui.horizontalScrollBar_0, SIGNAL(valueChanged(int)), this, SLOT(slider_movedAll(int)));
	connect(ui.horizontalScrollBar_x, SIGNAL(valueChanged(int)), this, SLOT(slider_x_moved(int)));
	connect(ui.horizontalScrollBar_y, SIGNAL(valueChanged(int)), this, SLOT(slider_y_moved(int)));
	connect(ui.horizontalScrollBar_z, SIGNAL(valueChanged(int)), this, SLOT(slider_z_moved(int)));
	/*
		Update by YaoTaihang	2015-12-08
		This Sentence is old Segment, connect to function:SaveImg()
		Now, it's useless;
	*/
	/*
		Update by YaoTaihang	2015-12-02
		Using this part to do something for segmmentition
	*/
}

void DicomReader::SetMainSocketThread(mainSocketThread * mainSockThread)
{
	this->mainSThread = mainSockThread;
};
//
//void DicomReader::btnSegmentClicked()
//{
//	/*
//		Update by YaoTaihang	2015-12-08
//		Save Mark line into mhd file for segment
//	*/
//	//Get information from the reader;
//	double * Spacing = reader->GetPixelSpacing();
//	int Dims[3];
//	reader->GetOutput()->GetDimensions(Dims);
//	double * Origin = reader->GetDataOrigin();
//
//	//Create ImageData
//	vtkSmartPointer<vtkImageData> whiteImage = vtkSmartPointer<vtkImageData>::New();
//	whiteImage->SetSpacing(Spacing);
//	whiteImage->SetDimensions(Dims);
//	whiteImage->SetExtent(0, Dims[0] - 1, 0, Dims[1] - 1, 0, Dims[2] - 1);
//	whiteImage->SetOrigin(Origin);
//	whiteImage->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
//
//	//Fill the image with foreground voxels:
//	unsigned char backgroundValue = 0;
//	unsigned char outval = 255;
//	unsigned char obj1 = 0;
//	unsigned char obj2 = 2;
//	vtkIdType count = whiteImage->GetNumberOfPoints();
//	for (vtkIdType i = 0; i < count; ++i)
//	{
//		whiteImage->GetPointData()->GetScalars()->SetTuple1(i, 255);
//	}
//
//	//Create new Points and Lines for saving transport polygonal lines
//	vtkSmartPointer<vtkPoints> Points = vtkSmartPointer<vtkPoints>::New();
//	vtkSmartPointer<vtkCellArray> Lines = vtkSmartPointer<vtkCellArray>::New();
//	
//	int Pianshu = 12;
//	int LineSize = 6;
//	int TotalPointsNumber = 0;
//	//Transport points from old coordinate to the new coordinate
//	for (int i = 0; i < this->markCallback[0]->GetAllPolygonalLines().size(); i++)
//	{
//		vtkPoints * pointsForThisLine = this->markCallback[0]->GetAllPolygonalLines()[i]->GetPoints();
//		for (int j = 0; j < pointsForThisLine->GetNumberOfPoints(); j++)
//		{
//			//get every point in this line
//			double* thisPoint = pointsForThisLine->GetPoint(j);
//
//			//坐标变换
//			double newPoint[3];
//			qDebug("oldPoint---------------------%f---%f---%f", thisPoint[0], thisPoint[1], thisPoint[2]);
//			double oldSize[2];
//			qDebug("size-------------------------%d---%d-----", riw[0]->GetSize()[0], riw[0]->GetSize()[1]);
//
//
//
//			//insert this new  transport point into points
//			Points->InsertNextPoint(thisPoint[0], thisPoint[1], Pianshu);
//		}
//		//Draw the line use the points for this polygonalLine
//		for (int j = 1; j < pointsForThisLine->GetNumberOfPoints(); j++)
//		{
//			double Point0[3], Point1[3];
//			Points->GetPoint(TotalPointsNumber + j - 1, Point0);
//			Points->GetPoint(TotalPointsNumber + j, Point1);
//
//			qDebug("%d----%f-%f--	%d--%f-%f-----", TotalPointsNumber + j - 1,Point0[0], Point0[1], TotalPointsNumber + j,Point1[0], Point1[1]);
//
//			int PointBegin[3], PointEnd[3],CurrentZ;
//			for (int i = 0; i < 3; i++)
//			{
//				PointBegin[i] = Point0[i];
//				PointEnd[i] = Point1[i];
//			}
//			CurrentZ = PointEnd[2];
//			//draw the point into imagedata
//			whiteImage->GetPointData()->GetScalars()->SetTuple1(
//				PointBegin[2] * Dims[0] * Dims[1] + PointBegin[1] * Dims[0] + PointBegin[0], obj1);
//			whiteImage->GetPointData()->GetScalars()->SetTuple1(
//				CurrentZ * Dims[0] * Dims[1] + PointEnd[1] * Dims[0] + PointEnd[0], obj1);
//			//draw the size for the line //PointBegin
//			for (int sizePointX = PointBegin[0] - LineSize / 2; sizePointX < PointBegin[0] + LineSize / 2; sizePointX++)
//			{
//				for (int sizePointY = PointBegin[1] - LineSize / 2; sizePointY < PointBegin[1] + LineSize / 2; sizePointY++)
//				{
//					whiteImage->GetPointData()->GetScalars()->SetTuple1(
//						CurrentZ * Dims[0] * Dims[1] + sizePointY * Dims[0] + sizePointX, obj1);
//				}
//			}
//
//			for (int sizePointX = PointEnd[0] - LineSize / 2; sizePointX < PointEnd[0] + LineSize / 2; sizePointX++)
//			{
//				for (int sizePointY = PointEnd[1] - LineSize / 2; sizePointY < PointEnd[1] + LineSize / 2; sizePointY++)
//				{
//					whiteImage->GetPointData()->GetScalars()->SetTuple1(
//						CurrentZ * Dims[0] * Dims[1] + sizePointY * Dims[0] + sizePointX, obj1);
//				}
//			}
//
//			qDebug("begin---%d----%d---", PointBegin[0], PointBegin[1]);
//			
//			//Compute all points on this line ,对两点间线性插值
//			if (PointEnd[0] - PointBegin[0] != 0)
//			{
//				double grad = (PointEnd[1] - PointBegin[1]) *1.0 / (PointEnd[0] - PointBegin[0])*1.0;
//				for (int k = PointBegin[0]; k != PointEnd[0]; k = PointEnd[0] - PointBegin[0]>0 ? k + 1 : k - 1)
//				{
//					int newX = k;
//					int newY = grad*(k - PointBegin[0]) + PointBegin[1];
//					qDebug("---%d----%d---", newX, newY);
//
//					//draw the point into imagedata
//					whiteImage->GetPointData()->GetScalars()->SetTuple1(
//						CurrentZ * Dims[0] * Dims[1] + newY * Dims[0] + newX, obj1);
//
//					for (int sizePointX = newX - LineSize / 2; sizePointX < newX + LineSize / 2; sizePointX++)
//					{
//						for (int sizePointY = newY - LineSize / 2; sizePointY < newY + LineSize / 2; sizePointY++)
//						{
//							whiteImage->GetPointData()->GetScalars()->SetTuple1(
//								CurrentZ * Dims[0] * Dims[1] + sizePointY * Dims[0] + sizePointX, obj1);
//						}
//					}
//
//				}
//			}
//			else
//			{
//				for (int k = PointBegin[1]; k != PointEnd[1]; k = PointEnd[1] - PointBegin[1] > 0 ? k + 1 : k - 1)
//				{
//					int newX = PointBegin[0];
//					int newY = k;
//					qDebug("---%d----%d---", newX, newY);
//
//
//					//draw the point into imagedata
//					whiteImage->GetPointData()->GetScalars()->SetTuple1(
//						CurrentZ * Dims[0] * Dims[1] + newY * Dims[0] + newX, obj1);
//
//					for (int sizePointX = newX - LineSize / 2; sizePointX < newX + LineSize / 2; sizePointX++)
//					{
//						for (int sizePointY = newY - LineSize / 2; sizePointY < newY + LineSize / 2; sizePointY++)
//						{
//							whiteImage->GetPointData()->GetScalars()->SetTuple1(
//								CurrentZ * Dims[0] * Dims[1] + sizePointY * Dims[0] + sizePointX, obj1);
//						}
//					}
//				}
//			}
//			
//			qDebug("end---%d----%d---", PointEnd[0], PointEnd[1]);
//			/*vtkSmartPointer<vtkLine> singleLine = vtkSmartPointer<vtkLine>::New();
//			singleLine->GetPointIds()->SetId(0, TotalPointsNumber + j - 1);
//			singleLine->GetPointIds()->SetId(1, TotalPointsNumber + j);
//			Lines->InsertNextCell(singleLine);*/
//		}
//		//Points Number of already add in.
//		TotalPointsNumber += pointsForThisLine->GetNumberOfPoints();
//	}
//	qDebug("TotalPointsNumber-----------------%d", TotalPointsNumber);
//	//Create polydatda for lines
//	vtkSmartPointer<vtkPolyData> polyLines = vtkSmartPointer<vtkPolyData>::New();
//	polyLines->SetPoints(Points);
//	polyLines->SetLines(Lines);
//
//	
//	//draw every point to the imagedata
//
//	//vtkIdType count_PolyData = polyLines->;
//
//	//qDebug("count_PolyData-------------%d",count_PolyData);
//
//
//	//Create image stencil
//	/*vtkSmartPointer<vtkPolyDataToImageStencil> pol2stenc = vtkSmartPointer<vtkPolyDataToImageStencil>::New();
//	pol2stenc->SetInputData(polyLines);
//	pol2stenc->SetOutputOrigin(Origin);
//	pol2stenc->SetOutputSpacing(Spacing);
//	pol2stenc->SetOutputWholeExtent(whiteImage->GetExtent());
//	pol2stenc->Update();*/
//
//	// cut the corresponding white image and set the background:
//	/*vtkSmartPointer<vtkImageStencil> imgstenc = vtkSmartPointer<vtkImageStencil>::New();
//	imgstenc->SetInputData(whiteImage);
//	imgstenc->SetStencilConnection(pol2stenc->GetOutputPort());
//	imgstenc->ReverseStencilOff();
//	imgstenc->SetBackgroundValue(outval);
//	imgstenc->Update();*/
//
//	//Save it into file
//	char * filePath = "C:\\mhdSegment.mhd";
//	char * filePathRaw = "C:\\mhdSegment.raw";
//	vtkSmartPointer<vtkMetaImageWriter> writer = vtkSmartPointer<vtkMetaImageWriter>::New();
//	writer->SetInputData(whiteImage);
//	writer->SetFileName(filePath);
//	writer->SetRAWFileName(filePathRaw);
//	writer->Write();
//
//}
void DicomReader::slider_movedAll(int n)
{
	char maxSlice[10];
	itoa(riw[0]->GetSliceMax(), maxSlice, 10);
	for (int i = 0; i < 4; i++)
	{
		//Refresh Slice
		riw[i]->SetSlice(n + 3 - i);
		//Refresh SliceText
		char * sliceInfoTxt = new char[100]; sliceInfoTxt[0] = '\0';
		stringstream sstream;sstream << riw[i]->GetSlice();
		strcat(sliceInfoTxt, sstream.str().c_str());strcat(sliceInfoTxt, " / ");strcat(sliceInfoTxt, maxSlice);
		sliceTextMapper[i]->SetInput(sliceInfoTxt);
	}

	riw[0]->SetSlice(n + 3);
	riw[1]->SetSlice(n + 2);
	riw[2]->SetSlice(n + 1);
	riw[3]->SetSlice(n + 0);

	currentui.horizontalScrollBar_z->setValue(n+3);
	currentui.horizontalScrollBar_y->setValue(n+2);
	currentui.horizontalScrollBar_x->setValue(n+1);
	currentui.horizontalScrollBar_0->setValue(n);

	slice_0 = n;
	slice_x = n + 1;
	slice_y = n + 2;
	slice_z = n + 3;
}

void DicomReader::slider_x_moved(int n)
{
	riw[2]->SetSlice(n);
	slice_z = n;
	//Refresh SliceText
	char maxSlice[10];
	itoa(riw[0]->GetSliceMax(), maxSlice, 10);
	char * sliceInfoTxt = new char[100]; sliceInfoTxt[0] = '\0';
	stringstream sstream; sstream << riw[2]->GetSlice();
	strcat(sliceInfoTxt, sstream.str().c_str()); strcat(sliceInfoTxt, " / "); strcat(sliceInfoTxt, maxSlice);
	sliceTextMapper[2]->SetInput(sliceInfoTxt);
}

void DicomReader::slider_y_moved(int n)
{
	riw[1]->SetSlice(n);
	slice_y = n;
	//Refresh SliceText
	char maxSlice[10];
	itoa(riw[0]->GetSliceMax(), maxSlice, 10);
	char * sliceInfoTxt = new char[100]; sliceInfoTxt[0] = '\0';
	stringstream sstream; sstream << riw[1]->GetSlice();
	strcat(sliceInfoTxt, sstream.str().c_str()); strcat(sliceInfoTxt, " / "); strcat(sliceInfoTxt, maxSlice);
	sliceTextMapper[1]->SetInput(sliceInfoTxt);
}

void DicomReader::slider_z_moved(int n)
{

	riw[0]->SetSlice(n);
	slice_x = n;
	//Refresh SliceText
	char maxSlice[10];
	itoa(riw[0]->GetSliceMax(), maxSlice, 10);
	char * sliceInfoTxt = new char[100]; sliceInfoTxt[0] = '\0';
	stringstream sstream; sstream << riw[0]->GetSlice();
	strcat(sliceInfoTxt, sstream.str().c_str()); strcat(sliceInfoTxt, " / "); strcat(sliceInfoTxt, maxSlice);
	sliceTextMapper[0]->SetInput(sliceInfoTxt);
}

void DicomReader::SaveImg()
{
	vStrImg.swap(vector<short>());
	qDebug() << "currentui.horizontalScrollBar_x->value() = " << currentui.horizontalScrollBar_x->value();
}

//2016-11-14 占淦
void DicomReader::DicomRead_3D(string path, Ui::ServerClass ui){
	//取到UI和解析出dicom文件目录
	currentui = ui;
	strcpy_s(filepath, strlen(path.c_str()) + 1, path.c_str());
	Reader3D = vtkSmartPointer<vtkDICOMImageReader>::New();
	string path1 = path.substr(0, path.find_last_of("/"));
	/*qDebug("%s", path.c_str());
	qDebug("%s", filepath);
	qDebug("%s",path1.c_str());*/
	
	//设置渲染器和渲染窗口
	vtkRenderer *renderer = vtkRenderer::New();
	vtkRenderWindow *renderWindow = vtkRenderWindow::New();
	renderWindow->AddRenderer(renderer);
	

	ui.qvtkWidget_x->SetRenderWindow(renderWindow);

	//将交互器与渲染窗口绑定
	vtkRenderWindowInteractor *renderWindowInteractor = vtkRenderWindowInteractor::New();
	//vtkRenderWindowInteractor *renderWindowInteractor = ui.qvtkWidget_x->GetRenderWindow()->GetInteractor();
	vtkInteractorStyleTrackballCamera *mInteractorStyle = vtkInteractorStyleTrackballCamera::New();
	renderWindowInteractor->SetInteractorStyle(mInteractorStyle);
	ui.qvtkWidget_x->GetRenderWindow()->SetInteractor(renderWindowInteractor);
	renderWindowInteractor->SetInteractorStyle(mInteractorStyle);
	//ui.qvtkWidget_x->GetRenderWindow()->SetInteractor(renderWindowInteractor);
	

	vtkAlgorithm *Areader = 0;
	vtkImageData *input = 0;
	
	//开始读入dicom数据
	Reader3D->SetDirectoryName(path1.data());
	Reader3D->SetDataScalarTypeToUnsignedShort();
	Reader3D->Update();
	input = Reader3D->GetOutput();  //将DICOM数据类型转换成vtkImageData数据类型
	Areader = Reader3D;
	// Verify that we actually have a volume
	// 验证输入图像的维度
	int dim[3];
	input->GetDimensions(dim);
	if (dim[0] < 2 ||
		dim[1] < 2 ||
		dim[2] < 2)
	{
		qDebug() << "Error loading data!";
		exit(EXIT_FAILURE);
	}

	vtkPiecewiseFunction *opacityFun = vtkPiecewiseFunction::New();
	opacityFun->SetClamping(0);
	vtkVolumeProperty *property = vtkVolumeProperty::New();

	//先设置一下颜色函数
	vtkColorTransferFunction *colorFun = vtkColorTransferFunction::New();
	colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
	colorFun->AddRGBPoint(-1000, .62, .36, .18, 0.5, 0.0);

	colorFun->AddRGBPoint(-500, .88, .60, .29, 0.33, 0.45);
	colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);
	colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);

	colorFun->AddRGBPoint(-16, 0.73, 0.25, 0.30, 0.49, .61);
	colorFun->AddRGBPoint(641, .90, .82, .56, .5, 0.0);
	colorFun->AddRGBPoint(3071, 1, 1, 1, .5, 0.0);
	colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
	colorFun->AddRGBPoint(-155, .55, .25, .15, 0.5, .92);
	colorFun->AddRGBPoint(217, .88, .60, .29, 0.33, 0.45);
	colorFun->AddRGBPoint(420, 1, .94, .95, 0.5, 0.0);
	colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);
	//试试在之前就设定好各个点的数值
	//opacityFun->AddPoint(0, 0, 0.5, 0.0);
	opacityFun->AddPoint(100, 0.71, 0.5, 0.0);
	opacityFun->AddPoint(999, 0.3, 0.5, 0.0);
	opacityFun->AddPoint(1000, 0.0, 0.5, 0.0);
	opacityFun->SetClamping(0);

	vtkVolume *volume = vtkVolume::New();
	property->SetScalarOpacity(opacityFun);
	property->SetColor(colorFun);
	property->SetInterpolationTypeToLinear();
	//opacityFun->AddPoint(-3024, 0, 0.5, 0.0 );
	//opacityFun->AddPoint(-16, 0, .49, .61 );
	//opacityFun->AddPoint(641, .72, .5, 0.0 );
	//opacityFun->AddPoint(3071, .71, 0.5, 0.0);
	//opacityFun->AddPoint(3071, 1, 0.5, 0.0);
	
	//vtkGPUVolumeRayCastMapper *raymapper = vtkGPUVolumeRayCastMapper::New();
	vtkOpenGLGPUVolumeRayCastMapper *raymapper = vtkOpenGLGPUVolumeRayCastMapper::New();
	//vtkVolumeRayCastCompositeFunction *compositeFunction = vtkVolumeRayCastCompositeFunction::New();
	//vtkVolumeRayCastMapper *raymapper = vtkVolumeRayCastMapper::New();
	//raymapper->SetVolumeRayCastFunction(compositeFunction);
	
	vtkBoxWidget *box = vtkBoxWidget::New();

	raymapper->SetInputConnection(Areader->GetOutputPort());
	//raymapper->SetInputConnection(Reader3D->GetOutputPort());
	volume->SetProperty(property);
	volume->SetMapper(raymapper);

	vtkSmartPointer<vtkVolumeSliderCallbackOpacity2> volumecallbackopacity2 =
		vtkSmartPointer<vtkVolumeSliderCallbackOpacity2>::New();
	volumecallbackopacity2->opaFun = opacityFun;

	vtkSmartPointer<vtkVolumeSliderCallbackOpacity1> volumecallbackopacity1 =
		vtkSmartPointer<vtkVolumeSliderCallbackOpacity1>::New();
	volumecallbackopacity1->opaFun = opacityFun;


	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();

	actor->GetProperty()->SetInterpolationToFlat();


	// A renderer and render window
	

	// An interactor
	//renderWindowInteractor->SetRenderWindow(renderWindow);

	// Add the actors to the scene
	renderer->AddActor(actor);
	//把渲染的物体(DICOM图像)加进去
	renderer->AddVolume(volume);


	// Render an image (lights and cameras are created automatically)
	renderWindow->Render();

	

	//第二个滚动条

	vtkSmartPointer<vtkSliderRepresentation2D> sliderRep2 =
		vtkSmartPointer<vtkSliderRepresentation2D>::New();


	sliderRep2->SetMinimumValue(0.0);
	sliderRep2->SetMaximumValue(1000.0);
	sliderRep2->SetValue(999.0);
	//sliderRep2->SetValue(1.0);
	sliderRep2->SetTitleText("roollbar2");


	// Set color properties:
	// Change the color of the knob that slides
	sliderRep2->GetSliderProperty()->SetColor(1, 0, 0);//red

	// Change the color of the text indicating what the slider controls
	sliderRep2->GetTitleProperty()->SetColor(1, 0, 0);//red

	// Change the color of the text displaying the value
	sliderRep2->GetLabelProperty()->SetColor(1, 0, 0);//red

	// Change the color of the knob when the mouse is held on it
	sliderRep2->GetSelectedProperty()->SetColor(0, 1, 0);//green

	// Change the color of the bar
	sliderRep2->GetTubeProperty()->SetColor(1, 1, 0);//yellow

	// Change the color of the ends of the bar
	sliderRep2->GetCapProperty()->SetColor(1, 1, 0);//yellow

	sliderRep2->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep2->GetPoint1Coordinate()->SetValue(40, 100);
	sliderRep2->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep2->GetPoint2Coordinate()->SetValue(100, 100);

	vtkSmartPointer<vtkSliderWidget> sliderWidget2 =
		vtkSmartPointer<vtkSliderWidget>::New();
	sliderWidget2->SetInteractor(ui.qvtkWidget_x->GetRenderWindow()->GetInteractor());
	sliderWidget2->SetRepresentation(sliderRep2);
	sliderWidget2->SetAnimationModeToAnimate();
	sliderWidget2->EnabledOn();
	sliderWidget2->On();
	sliderWidget2->AddObserver(vtkCommand::InteractionEvent, volumecallbackopacity2);

	//第一个滚动条
	vtkSmartPointer<vtkSliderRepresentation2D> sliderRep1 =
		vtkSmartPointer<vtkSliderRepresentation2D>::New();


	sliderRep1->SetMinimumValue(0.0);
	sliderRep1->SetMaximumValue(1000.0);
	sliderRep1->SetValue(1.0);
	sliderRep1->SetTitleText("rollbar1");



	// Set color properties:
	// Change the color of the knob that slides
	sliderRep1->GetSliderProperty()->SetColor(1, 0, 0);//red

	// Change the color of the text indicating what the slider controls
	sliderRep1->GetTitleProperty()->SetColor(1, 0, 0);//red

	// Change the color of the text displaying the value
	sliderRep1->GetLabelProperty()->SetColor(1, 0, 0);//red

	// Change the color of the knob when the mouse is held on it
	sliderRep1->GetSelectedProperty()->SetColor(0, 1, 0);//green

	// Change the color of the bar
	sliderRep1->GetTubeProperty()->SetColor(1, 1, 0);//yellow

	// Change the color of the ends of the bar
	sliderRep1->GetCapProperty()->SetColor(1, 1, 0);//yellow

	sliderRep1->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep1->GetPoint1Coordinate()->SetValue(40, 40);
	sliderRep1->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep1->GetPoint2Coordinate()->SetValue(100, 40);

	vtkSmartPointer<vtkSliderWidget> sliderWidget1 =
		vtkSmartPointer<vtkSliderWidget>::New();
	sliderWidget1->SetInteractor(ui.qvtkWidget_x->GetRenderWindow()->GetInteractor());
	sliderWidget1->SetRepresentation(sliderRep1);
	sliderWidget1->SetAnimationModeToAnimate();
	sliderWidget1->EnabledOn();
	sliderWidget1->On();
	sliderWidget1->AddObserver(vtkCommand::InteractionEvent, volumecallbackopacity1);

	

	renderWindowInteractor->Initialize();
	renderWindow->Render();

	renderWindowInteractor->Start();

	//释放内存
	opacityFun->Delete();
	colorFun->Delete();
	property->Delete();
	//volume->Delete();
	raymapper->Delete();
	Areader->Delete();
	
	renderWindow->Delete();
	//renderWindowInteractor->Delete();

}