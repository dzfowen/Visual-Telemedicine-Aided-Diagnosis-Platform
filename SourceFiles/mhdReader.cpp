#include "server.h"
#include "mhdReader.h"
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

#include <vtkImageCast.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeRayCastIsosurfaceFunction.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolume.h>

#include <MyVolumeRendering.h>
#include "MouseInteractorStylePP.h"
#include "MouseInteractorStylePP2.h"



extern float slice_x;
extern float slice_y;
extern float slice_z;
extern int recv_mask;


mhdReader::mhdReader()
{
}


mhdReader::~mhdReader()
{
}

void mhdReader::Read_Display(string path, Ui::ServerClass ui)
{
	currentui = ui;
	strcpy_s(filepath, strlen(path.c_str()) + 1, path.c_str());
	reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName(path.c_str());
	reader->Update();

	filpYFilter = vtkSmartPointer<vtkImageFlip>::New();
	filpYFilter->SetFilteredAxis(1);
	filpYFilter->SetInputConnection(reader->GetOutputPort());
	filpYFilter->Update();

	int imageDims[3];
	reader->GetOutput()->GetDimensions(imageDims);
	////YY////
	double* origin = reader->GetOutput()->GetOrigin();
	double* spacing = reader->GetOutput()->GetSpacing();
	int* extent = reader->GetOutput()->GetExtent();
	////2016.12.23////
	////YY////
	edition = new EditMask;
	////2017.5.28////

	ui.horizontalScrollBar_x->setMinimum(1);
	ui.horizontalScrollBar_y->setMinimum(1);
	ui.horizontalScrollBar_z->setMinimum(1);
	ui.horizontalScrollBar_x->setMaximum(imageDims[2]);
	ui.horizontalScrollBar_y->setMaximum(imageDims[1]);
	ui.horizontalScrollBar_z->setMaximum(imageDims[0]);

	for (int i = 0; i < 3; i++)
	{
		riw[i] = vtkSmartPointer< vtkResliceImageViewer >::New();
	}
	ui.qvtkWidget_z->SetRenderWindow(riw[0]->GetRenderWindow());
	riw[0]->SetupInteractor(
		ui.qvtkWidget_z->GetRenderWindow()->GetInteractor());

	ui.qvtkWidget_y->SetRenderWindow(riw[1]->GetRenderWindow());
	riw[1]->SetupInteractor(
		ui.qvtkWidget_y->GetRenderWindow()->GetInteractor());

	ui.qvtkWidget_xyz->SetRenderWindow(riw[2]->GetRenderWindow());
	riw[2]->SetupInteractor(
		ui.qvtkWidget_xyz->GetRenderWindow()->GetInteractor());
	////YY////
	vtkSmartPointer< vtkInteractorStyle > interactorStyle = vtkSmartPointer< vtkInteractorStyle >::New();
	interactorStyle->AutoAdjustCameraClippingRangeOn();
	ui.qvtkWidget_xyz->GetInteractor()->SetInteractorStyle(interactorStyle);
	int *size = ui.qvtkWidget_xyz->GetRenderWindow()->GetSize();
	int *intersize = ui.qvtkWidget_xyz->GetRenderWindow()->GetInteractor()->GetSize();
	int x = size[0];
	int y = size[1];
	int x1 = intersize[0];
	int y1 = intersize[1];

	//change brightness and contrast
	shiftScaleFilter = vtkSmartPointer<vtkImageShiftScale>::New();
	shiftScaleFilter->SetOutputScalarTypeToShort();
	shiftScaleFilter->SetInputData(filpYFilter->GetOutput());
	shiftScaleFilter->Update();
	////2016.12.23////

	for (int i = 0; i < 3; i++)
	{
		// make them all share the same re slice cursor object.
		vtkResliceCursorLineRepresentation *rep =
			vtkResliceCursorLineRepresentation::SafeDownCast(
			riw[i]->GetResliceCursorWidget()->GetRepresentation());
		riw[i]->SetResliceCursor(riw[0]->GetResliceCursor());

		rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(i);

		//change brightness and contrast
		//riw[i]->SetInputData(reader->GetOutput());
		riw[i]->SetInputData(shiftScaleFilter->GetOutput());
		////YY////
		riw[i]->SetSize(ui.qvtkWidget_xyz->geometry().width(), ui.qvtkWidget_x->geometry().height());
		////2016.12.23////
		riw[i]->SetSliceOrientation(i);
		riw[i]->SetResliceModeToAxisAligned();
		////YY////
		riw[i]->Render();
		////2016.12.23////
	}

	vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkProperty> ipwProp = vtkSmartPointer<vtkProperty>::New();

	vtkSmartPointer< vtkRenderer > ren = vtkSmartPointer< vtkRenderer >::New();

	renderForWidgetX = vtkSmartPointer< vtkRenderer >::New();

	ui.qvtkWidget_x->GetRenderWindow()->AddRenderer(renderForWidgetX);
	vtkRenderWindowInteractor *iren = ui.qvtkWidget_x->GetInteractor();









	for (int i = 0; i < 3; i++)
	{
		planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
		planeWidget[i]->SetInteractor(iren);
		planeWidget[i]->SetPicker(picker);
		planeWidget[i]->RestrictPlaneToVolumeOn();
		planeWidget[i]->SetTexturePlaneProperty(ipwProp);
		planeWidget[i]->TextureInterpolateOff();
		planeWidget[i]->SetResliceInterpolateToLinear();
		planeWidget[i]->SetInputConnection(filpYFilter->GetOutputPort());
		planeWidget[i]->SetPlaneOrientation(i);
		planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
		planeWidget[i]->DisplayTextOn();
		planeWidget[i]->SetDefaultRenderer(renderForWidgetX);
		planeWidget[i]->SetWindowLevel(1358, -27);
		planeWidget[i]->On();
		planeWidget[i]->InteractionOn();
	}

	vtkSmartPointer<vtkResliceCursorCallback> cbk =
		vtkSmartPointer<vtkResliceCursorCallback>::New();

	for (int i = 0; i < 3; i++)
	{
		cbk->IPW[i] = planeWidget[i];
		cbk->RCW[i] = riw[i]->GetResliceCursorWidget();
		riw[i]->GetResliceCursorWidget()->AddObserver(
			vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk);
		riw[i]->GetResliceCursorWidget()->AddObserver(
			vtkResliceCursorWidget::WindowLevelEvent, cbk);
		riw[i]->GetResliceCursorWidget()->AddObserver(
			vtkResliceCursorWidget::ResliceThicknessChangedEvent, cbk);
		riw[i]->GetResliceCursorWidget()->AddObserver(
			vtkResliceCursorWidget::ResetCursorEvent, cbk);
		riw[i]->GetInteractorStyle()->AddObserver(
			vtkCommand::WindowLevelEvent, cbk);
		////YY////
		riw[i]->GetRenderer()->GetActiveCamera()->SetDistance(1000);
		////2016.12.23////

		// Make them all share the same color map.
		riw[i]->SetLookupTable(riw[0]->GetLookupTable());
		planeWidget[i]->GetColorMap()->SetLookupTable(riw[0]->GetLookupTable());
		//planeWidget[i]->GetColorMap()->SetInputConnection(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap()->GetInput());
		planeWidget[i]->SetColorMap(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap());
	}

	////YY////
	riw[2]->GetRenderer()->ResetCamera();
	vtkCamera* camera = riw[2]->GetRenderer()->GetActiveCamera();
	camera->ParallelProjectionOn();
	//
	//vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
	//riw[2]->GetRenderer()->SetActiveCamera(camera);

	double xc = origin[0] + 0.5*(extent[0] + extent[1])*spacing[0];
	double yc = origin[1] + 0.5*(extent[2] + extent[3])*spacing[1];
	double xd = (extent[1] - extent[0] + 1)*spacing[0];
	double yd = (extent[3] - extent[2] + 1)*spacing[1];

	double d = camera->GetDistance();
	camera->SetParallelScale(0.5f*static_cast<float>(yd));
	camera->SetFocalPoint(xc, yc, 0.0);
	camera->SetPosition(xc, yc, +d);

	////2016.12.23////


	ui.qvtkWidget_x->show();
	ui.qvtkWidget_y->show();
	ui.qvtkWidget_z->show();
	ui.horizontalScrollBar_x->setValue(riw[2]->GetSlice());
	ui.horizontalScrollBar_y->setValue(riw[1]->GetSlice());
	ui.horizontalScrollBar_z->setValue(riw[0]->GetSlice());
	slice_z = ui.horizontalScrollBar_x->value();
	slice_y = ui.horizontalScrollBar_y->value();
	slice_x = ui.horizontalScrollBar_z->value();


	connect(ui.horizontalScrollBar_x, SIGNAL(valueChanged(int)), this, SLOT(slider_x_moved(int)));
	connect(ui.horizontalScrollBar_y, SIGNAL(valueChanged(int)), this, SLOT(slider_y_moved(int)));
	connect(ui.horizontalScrollBar_z, SIGNAL(valueChanged(int)), this, SLOT(slider_z_moved(int)));

	/*
	Update by YaoTaihang	2015-12-10
	Connect volume rendering button and function
	*/
	connect(ui.btn_volume, SIGNAL(clicked()), this, SLOT(openVolumeRendering()));

	////////////////YY 2017.5.28/////////////////
	//connect(ui.menuEdit_mask->menuAction(), SIGNAL(triggered()), this, SLOT(test()));
	//connect(ui.button_EditMask, SIGNAL(clicked()), this, SLOT(Edit()));
	////////////////YY End/////////////////

	//change brightness and contrast
	connect(ui.horizontalSlider_brightness,SIGNAL(valueChanged(int)),this,SLOT(changeBrighteness(int)));
	connect(ui.horizontalSlider_contrast, SIGNAL(valueChanged(int)), this, SLOT(changeContrast(int)));
	
	//overlap
	connect(ui.overlap_button, SIGNAL(clicked()),this,SLOT(overlap()));

	//modify
	connect(ui.button_OriginalPoints, SIGNAL(clicked()), this, SLOT(origianlPoint()));
	connect(ui.button_NewPoints, SIGNAL(clicked()), this, SLOT(newPoint()));
	connect(ui.button_EditMask, SIGNAL(clicked()), this, SLOT(editMask()));

	/*connect(mainSockTread, SIGNAL(main_OriginalPoint(char*)), this, SLOT(server_GetRequestForOriginalPoint()));
	connect(mainSockTread, SIGNAL(main_NewPoint(char*)), this, SLOT(server_GetRequestForNewPoint()));
	connect(mainSockTread, SIGNAL(main_EditMask(char*)), this, SLOT(server_GetRequestForEditMask()));*/
}

/*
Update by YaoTaihng 2015-12-10
volumeRendering function
*/
void mhdReader::openVolumeRendering()
{
	if (currentui.btn_volume->isChecked())
	{
		if (this->renderForVolume == NULL)
		{
			MyVolumeRendering * myVolumeRendering = new MyVolumeRendering();
			myVolumeRendering->SetVtkMetaImageReader(this->reader);
			this->renderForVolume = myVolumeRendering->StartVolumRenderingAndReturnRenderer();
		}
		currentui.qvtkWidget_x->GetRenderWindow()->RemoveRenderer(this->renderForWidgetX);
		currentui.qvtkWidget_x->GetRenderWindow()->AddRenderer(this->renderForVolume);
	}
	else
	{
		currentui.qvtkWidget_x->GetRenderWindow()->RemoveRenderer(this->renderForVolume);
		currentui.qvtkWidget_x->GetRenderWindow()->AddRenderer(this->renderForWidgetX);
	}
	currentui.qvtkWidget_x->update();
}

//change brightness and contrast
void mhdReader::changeBrighteness(int Brightness)
{
	int brightness = Brightness;
	qDebug() << brightness;
	shiftScaleFilter->SetShift((brightness - 50) * 60);
	shiftScaleFilter->Modified();
	shiftScaleFilter->Update();
	for (int i = 0; i < 3; i++)
	{
		riw[i]->Render();
	}
}

void mhdReader::changeContrast(int Contrast)
{
	int contrast = Contrast;
	shiftScaleFilter->SetScale(contrast * 0.1 + 1);
	shiftScaleFilter->Modified();
	shiftScaleFilter->Update();
	for (int i = 0; i < 3; i++)
	{
		riw[i]->Render();
	}
}

void mhdReader::slider_x_moved(int n)
{
	riw[2]->SetSlice(n);
	planeWidget[2]->SetSliceIndex(n);
	//currentui.qvtkWidget_x->setFocus();
	slice_z = n;
}

void mhdReader::slider_y_moved(int n)
{
	riw[1]->SetSlice(n);
	planeWidget[1]->SetSliceIndex(n);
	slice_y = n;
}

void mhdReader::slider_z_moved(int n)
{
	riw[0]->SetSlice(n);
	planeWidget[0]->SetSliceIndex(n);
	slice_x = n;
}

void mhdReader::Saveimg()
{
	vStrImg.swap(vector<short>());
}

////YY////
void mhdReader::test()
{
	cout << "11" << endl;
}
void mhdReader::Edit()
{
	//edition->setTitle(QString("Edit Mask"));
	//
	//
	///*QString originImgFile1 = QFileDialog::getOpenFileName(NULL, "Image", "c:", "Image Files(*.mhd)");
	//string originImgFile2 = originImgFile1.toStdString();
	//char* originImgFile = (char*)originImgFile2.data();*/
	//char* originImgFile = this->filepath;
	////char* originImgFile = "C:\\workspace\\server_now\\Server\\Server\\RegistrationData\\CD22\\PV\\PreOperation\\CT_Image_Rez\\CD22_PV_01_Rez.mhd";
	////char* originImgFile = originImgFile1;
	//qDebug() << "originImgFile is" <<originImgFile;
	//string path = originImgFile;
	//string maskSaveFilepath = path.substr(0, path.find_last_of("/")) + "/output.mhd";


	////string maskSaveFilepath = "C:\\workspace\\server_now\\Server\\Server\\RegistrationData\\CD22\\PV\\PreOperation\\Liver\\CD22_PV_01_Rez_Liver.mhd";
	////qDebug() << maskSaveFilepath.c_str();
	///*QString maskSaveFilepath1 = QFileDialog::getOpenFileName(NULL, "Image", "c:", "Image Files(*.mhd)");
	//string maskSaveFilepath2 = maskSaveFilepath1.toStdString();*/


	//char* maskSaveFile = (char*)maskSaveFilepath.data();
	//qDebug() <<"mask is"<< maskSaveFile;
	//int str_index = currentui.horizontalScrollBar_x->value();
	//qDebug() << str_index;
	//////originImgFile是当前显示的医疗图片地址名字, maskSaveFile是需要修改的mask的地址名字, str_index是当前的切片序号类型是int，把这三个替换成你当前程序里的名字或数值即可
	//edition->show(fgOverlayColor, fgOverlayColor1, fgOverlayColor2, bgOverlayColor, contourOverlayColor, contourOverlayColor1, contourOverlayColor2, fgOverlayOpacity, fgOverlayOpacity1, fgOverlayOpacity2, bgOverlayOpacity, contourOverlayOpacity, contourOverlayOpacity1, contourOverlayOpacity2, originImgFile, maskSaveFile, str_index);
	//edition->exec();
	//////edition->maskMhd这个是修改后的mask，地址就是maskSaveFile，可以用代码读取，后续在你们server主页面怎么显示我就不清楚了
	edition->setTitle(QString("Edit Mask"));
	char* originImgFile = this->filepath;
	qDebug() << originImgFile;
	string path = originImgFile;
	string maskSaveFilepath = path.substr(0, path.find_last_of("/")) + "/output.mhd";
	//qDebug() << maskSaveFilepath.c_str();
	char* maskSaveFile = (char*)maskSaveFilepath.data();
	qDebug() << maskSaveFile;
	int str_index = currentui.horizontalScrollBar_x->value();
	qDebug() << str_index;
	////originImgFile是当前显示的医疗图片地址名字, maskSaveFile是需要修改的mask的地址名字, str_index是当前的切片序号类型是int，把这三个替换成你当前程序里的名字或数值即可
	edition->show(fgOverlayColor, fgOverlayColor1, fgOverlayColor2, bgOverlayColor, contourOverlayColor, contourOverlayColor1, contourOverlayColor2, fgOverlayOpacity, fgOverlayOpacity1, fgOverlayOpacity2, bgOverlayOpacity, contourOverlayOpacity, contourOverlayOpacity1, contourOverlayOpacity2, originImgFile, maskSaveFile, str_index);
	edition->exec();
	////edition->maskMhd这个是修改后的mask，地址就是maskSaveFile，可以用代码读取，后续在你们server主页面怎么显示我就不清楚了

}
////2017.5.28////

void mhdReader::overlap()
{
	QString Image = QFileDialog::getOpenFileName(NULL, "Image", "c:", "Image Files(*.mhd)");
	qDebug() << Image;
	vtkMetaImageReader* overlapReader = vtkMetaImageReader::New();
	string filename = Image.toStdString();
	overlapReader->SetFileName(filename.c_str());
	vtkSmartPointer<vtkImageBlend> imageBlend = vtkSmartPointer<vtkImageBlend>::New();
	imageBlend->AddInputConnection(overlapReader->GetOutputPort());
	imageBlend->AddInputConnection(this->reader->GetOutputPort());
	imageBlend->SetOpacity(0, 0.9);
	imageBlend->SetOpacity(1, 0.5);
	imageBlend->Update();
	/*shiftScaleFilter->SetShift(100);
	shiftScaleFilter->SetScale(1.1);
	shiftScaleFilter->Modified();*/
	

	this->filpYFilter->SetFilteredAxis(1);
	this->filpYFilter->SetInputData(imageBlend->GetOutput());
	this->filpYFilter->Update();
	shiftScaleFilter->SetInputData(this->filpYFilter->GetOutput());
	shiftScaleFilter->Update();
	

	riw[2]->SetInputData(shiftScaleFilter->GetOutput());
	riw[1]->SetInputData(shiftScaleFilter->GetOutput());
	riw[0]->SetInputData(shiftScaleFilter->GetOutput());
}

void mhdReader::origianlPoint()
{
	vtkSmartPointer<vtkPointPicker> pointPicker = vtkSmartPointer<vtkPointPicker>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = riw[2]->GetInteractor();
	renderWindowInteractor->SetPicker(pointPicker);
	renderWindowInteractor->SetRenderWindow(riw[2]->GetRenderWindow());

	vtkSmartPointer< MouseInteractorStylePP > style = vtkSmartPointer<MouseInteractorStylePP>::New();
	renderWindowInteractor->SetInteractorStyle(style);
}

void mhdReader::newPoint()
{
	vtkSmartPointer<vtkPointPicker> pointPicker = vtkSmartPointer<vtkPointPicker>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = riw[2]->GetInteractor();
	renderWindowInteractor->SetPicker(pointPicker);
	renderWindowInteractor->SetRenderWindow(riw[2]->GetRenderWindow());

	vtkSmartPointer< MouseInteractorStylePP2 > style2 = vtkSmartPointer<MouseInteractorStylePP2>::New();
	renderWindowInteractor->SetInteractorStyle(style2);
}

void mhdReader::editMask()
{
	char* originImgFile = this->filepath;
	
	qDebug() << originImgFile;

	char s1[500];
	sprintf_s(s1, "%s %s %s %s %s", "C:\\workspace\\server_now\\Server\\Server\\modifyData\\EXE\\ImageReadCastWrite.exe",
		originImgFile, "C:\\workspace\\server_now\\Server\\Server\\modifyData\\newMask.mhd",
		"C:\\workspace\\server_now\\Server\\Server\\modifyData\\png\\mask", "png");
	qDebug("%s", s1);
	//iPad
	/*sprintf_s(s1, "%s %s %s %s %s", "C:\\workspace\\server_now\\Server\\Server\\modifyData\\EXE\\ImageReadCastWrite.exe",
		"C:\\workspace\\server_now\\Server\\Server\\CD22_PV_01_Rez_Liver.mhd", "C:\\workspace\\server_now\\Server\\Server\\modifyData\\newMask.mhd",
		"C:\\workspace\\server_now\\Server\\Server\\modifyData\\png\\mask", "png");
	qDebug("%s", s1);*/
	system(s1);
	
	//get two poins
	double x1, y1, z1;
	ifstream infile;
	infile.open("C:\\workspace\\server_now\\Server\\Server\\modifyData\\originalPoints.txt");
	infile >> x1 >> y1 >> z1;
	infile.close();
	qDebug("-----%f-----%f-----%f", x1, y1, z1);

	double x2, y2, z2;
	infile.open("C:\\workspace\\server_now\\Server\\Server\\modifyData\\newPoints.txt");
	infile >> x2 >> y2 >> z2;
	infile.close();
	qDebug("-----%f-----%f-----%f", x2, y2, z2);

	vtkImageData* inputImage = riw[2]->GetInput();
	double* origin = inputImage->GetOrigin();
	double* spacing = inputImage->GetSpacing();
	qDebug("-----%f-----%f-----%f", origin[0], origin[1], origin[2]);
	qDebug("-----%f-----%f-----%f", spacing[0], spacing[1], spacing[2]);
	
	int oriPointx = int((x1 - origin[0]) / spacing[0]);
	int oriPointy = 512 - int((y1 - origin[1]) / spacing[1]);
	int oriPointz = int((z1 - origin[2]) / spacing[2]);
	qDebug("-----%d-----%d-----%d", oriPointx, oriPointy, oriPointz);

	int newPointx = int((x2 - origin[0]) / spacing[0]);
	int newPointy = 512 - int((y2 - origin[1]) / spacing[1]);
	int newPointz = int((z2 - origin[2]) / spacing[2]);
	qDebug("-----%d-----%d-----%d", newPointx, newPointy, newPointz);

	//get mask png
	int z = riw[2]->GetSlice();
	string zstr;
	qDebug() << z;
	if (z < 100)
	{
		zstr = to_string(z);
		zstr = "0" + zstr;
	}
	else
	{
		zstr = to_string(z);
	}
	qDebug() << zstr.c_str();
	string changeMaskPng = "C:\\workspace\\server_now\\Server\\Server\\modifyData\\png\\mask" + zstr + ".png";

	cv::Mat image = cv::imread(changeMaskPng, 0);
	//std::vector<std::vector<cv::Point>> contours;
	////获取轮廓不包括轮廓内的轮廓  
	//cv::findContours(image, contours,
	//	CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//cv::Mat pngContour(image.size(), CV_8U, cv::Scalar(255));
	//cv::drawContours(pngContour, contours,
	//	-1, cv::Scalar(0), 2);
	/*cv::imshow("originalImage", image);
	cv::imshow("originalContour", pngContour);*/

	////获取所有轮廓包括轮廓内的轮廓  
	//std::vector<std::vector<cv::Point>> allContours;
	//cv::Mat allContoursResult(image.size(), CV_8U, cv::Scalar(255));
	//cv::findContours(image, allContours,
	//	CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	//cv::drawContours(allContoursResult, allContours, -1,
	//	cv::Scalar(0), 2);
	//cv::imshow("allContours", allContoursResult);

	////获取轮廓的等级  
	//std::vector<cv::Vec4i> hierarchy;
	//cv::findContours(image, contours, hierarchy, CV_RETR_TREE,
	//	CV_CHAIN_APPROX_NONE);

	float px1[100], py1[100];
	float px2[100], py2[100];
	float distance_x[100];
	float distance_y[100];

	cv::Mat segMaskfg = cv::imread(changeMaskPng, 0);
	cv::Mat maskTemp, changedMask;

	maskTemp.create(cvSize(512, 512), CV_8UC1);
	maskTemp = 0;

	int width = 512;
	int height = 512;
	int Div_x = 20;
	int	Div_y = 20;
	int wi = (int)Div_x, hi = (int)Div_y;
	float size_w = (float)(width / Div_x), size_h = (float)(height / Div_y);// width,height是读入图像的长宽
	int pi;
	int ba_i, ba_j;
	float ba_s, ba_t;
	float B_s[4], B_t[4];
	float w_all;
	float value_x[122][122] = { 0 }, value_y[122][122] = { 0 };
	float weigh[122][122] = { 0 };
	float transfer_x[122][122] = { 0 }, transfer_y[122][122] = { 0 };
	float master_x[122][122] = { 0 }, master_y[122][122] = { 0 };
	int time;
	int original_x, original_y;
	float morph_x, morph_y;
	float f_x, f_y;
	float temporary_x, temporary_y;
	int t_x, t_y;
	int top, under, left, right;
	float r, g, b;

	int Feat_num = 1;
	float contourOriginPoint_x[] = { oriPointx };
	float contourOriginPoint_y[] = { oriPointy };
	float contourEndPoint_x[] = { newPointx };
	float contourEndPoint_y[] = { newPointy };
	//Bitmap ^ bm = (Bitmap ^)(pictureBox4->Image);
	//Bitmap ^ bm2 = (Bitmap ^)(pictureBox3->Image);


	for (int Loop1 = 1; Loop1 <= Feat_num; Loop1++){
		/* px1[Loop1 - 1] = (float)Xi[Loop1] / (width / (float)Div_x);
		py1[Loop1 - 1] = (float)Yi[Loop1] / (height / (float)Div_y);
		px2[Loop1 - 1] = (float)Xi[Loop1 + (int)Feat_num] / (width / (float)Div_x);
		py2[Loop1 - 1] = (float)Yi[Loop1 + (int)Feat_num] / (height / (float)Div_y);*/

		px1[Loop1 - 1] = contourOriginPoint_x[Loop1 - 1] / (width / (float)Div_x);// 两组坐标
		py1[Loop1 - 1] = contourOriginPoint_y[Loop1 - 1] / (height / (float)Div_y);
		px2[Loop1 - 1] = contourEndPoint_x[Loop1 - 1] / (width / (float)Div_x);
		py2[Loop1 - 1] = contourEndPoint_y[Loop1 - 1] / (height / (float)Div_y);


		distance_x[Loop1 - 1] = px1[Loop1 - 1] - px2[Loop1 - 1];
		distance_y[Loop1 - 1] = py1[Loop1 - 1] - py2[Loop1 - 1];
	}

	for (time = 1; time <= 3; time++){

		for (pi = 0; pi<Feat_num; pi++){
			ba_i = (int)px2[pi] - 1;
			ba_j = (int)py2[pi] - 1;
			ba_s = px2[pi] - (int)px2[pi];
			ba_t = py2[pi] - (int)py2[pi];

			B_s[0] = ((1 - ba_s)*(1 - ba_s)*(1 - ba_s) / 6);
			B_s[1] = ((3 * ba_s*ba_s*ba_s - 6 * ba_s*ba_s + 4) / 6);
			B_s[2] = ((-3 * ba_s*ba_s*ba_s + 3 * ba_s*ba_s + 3 * ba_s + 1) / 6);
			B_s[3] = (ba_s*ba_s*ba_s / 6);
			B_t[0] = ((1 - ba_t)*(1 - ba_t)*(1 - ba_t) / 6);
			B_t[1] = ((3 * ba_t*ba_t*ba_t - 6 * ba_t*ba_t + 4) / 6);
			B_t[2] = ((-3 * ba_t*ba_t*ba_t + 3 * ba_t*ba_t + 3 * ba_t + 1) / 6);
			B_t[3] = (ba_t*ba_t*ba_t / 6);

			w_all = B_s[0] * B_t[0] * B_s[0] * B_t[0] + B_s[0] * B_t[1] * B_s[0] * B_t[1] +
				B_s[0] * B_t[2] * B_s[0] * B_t[2] + B_s[0] * B_t[3] * B_s[0] * B_t[3] +
				B_s[1] * B_t[0] * B_s[1] * B_t[0] + B_s[1] * B_t[1] * B_s[1] * B_t[1] +
				B_s[1] * B_t[2] * B_s[1] * B_t[2] + B_s[1] * B_t[3] * B_s[1] * B_t[3] +
				B_s[2] * B_t[0] * B_s[2] * B_t[0] + B_s[2] * B_t[1] * B_s[2] * B_t[1] +
				B_s[2] * B_t[2] * B_s[2] * B_t[2] + B_s[2] * B_t[3] * B_s[2] * B_t[3] +
				B_s[3] * B_t[0] * B_s[3] * B_t[0] + B_s[3] * B_t[1] * B_s[3] * B_t[1] +
				B_s[3] * B_t[2] * B_s[3] * B_t[2] + B_s[3] * B_t[3] * B_s[3] * B_t[3];


			for (int Loop1 = 0; Loop1 <= 3; Loop1++){
				for (int Loop2 = 0; Loop2 <= 3; Loop2++){
					if (ba_i == -1 && Loop1 == 0){
					}
					else if (ba_i == Div_x && Loop1 == 3){
					}
					else if (ba_j == -1 && Loop2 == 0){
					}
					else if (ba_j == Div_y && Loop2 == 3){
					}
					else{
						value_x[ba_i + Loop1][ba_j + Loop2] += distance_x[pi] * B_s[Loop1] * B_t[Loop2] / w_all *
							B_s[Loop1] * B_t[Loop2] * B_s[Loop1] * B_t[Loop2];
						value_y[ba_i + Loop1][ba_j + Loop2] += distance_y[pi] * B_s[Loop1] * B_t[Loop2] / w_all *
							B_s[Loop1] * B_t[Loop2] * B_s[Loop1] * B_t[Loop2];
						weigh[ba_i + Loop1][ba_j + Loop2] += B_s[Loop1] * B_t[Loop2] * B_s[Loop1] * B_t[Loop2];
					}
				}
			}
		}


		for (int Loop1 = 0; Loop1 <= wi; Loop1++){
			for (int Loop2 = 0; Loop2 <= hi; Loop2++){
				if (weigh[Loop1][Loop2] == 0){
					transfer_x[Loop1][Loop2] = master_x[Loop1][Loop2];
					transfer_y[Loop1][Loop2] = master_y[Loop1][Loop2];
				}
				else{
					transfer_x[Loop1][Loop2] = master_x[Loop1][Loop2] + value_x[Loop1][Loop2] / weigh[Loop1][Loop2];
					transfer_y[Loop1][Loop2] = master_y[Loop1][Loop2] + value_y[Loop1][Loop2] / weigh[Loop1][Loop2];
				}
			}
		}


		for (int Loop1 = 0; Loop1<Feat_num; Loop1++){
			ba_i = (int)px2[Loop1] - 1;
			ba_j = (int)py2[Loop1] - 1;
			ba_s = px2[Loop1] - (int)px2[Loop1];
			ba_t = py2[Loop1] - (int)py2[Loop1];

			B_s[0] = ((1 - ba_s)*(1 - ba_s)*(1 - ba_s) / 6);
			B_s[1] = ((3 * ba_s*ba_s*ba_s - 6 * ba_s*ba_s + 4) / 6);
			B_s[2] = ((-3 * ba_s*ba_s*ba_s + 3 * ba_s*ba_s + 3 * ba_s + 1) / 6);
			B_s[3] = (ba_s*ba_s*ba_s / 6);
			B_t[0] = ((1 - ba_t)*(1 - ba_t)*(1 - ba_t) / 6);
			B_t[1] = ((3 * ba_t*ba_t*ba_t - 6 * ba_t*ba_t + 4) / 6);
			B_t[2] = ((-3 * ba_t*ba_t*ba_t + 3 * ba_t*ba_t + 3 * ba_t + 1) / 6);
			B_t[3] = (ba_t*ba_t*ba_t / 6);

			f_x = 0;
			f_y = 0;
			for (int Loop2 = 0; Loop2 <= 3; Loop2++){
				for (int Loop3 = 0; Loop3 <= 3; Loop3++){
					if (ba_i == -1 && Loop2 == 0){
					}
					else if (ba_i == Div_x && Loop2 == 3){
					}
					else if (ba_j == -1 && Loop3 == 0){
					}
					else if (ba_j == Div_y && Loop3 == 3){
					}
					else{
						f_x += (transfer_x[ba_i + Loop2][ba_j + Loop3] - master_x[ba_i + Loop2][ba_j + Loop3]) * B_s[Loop2] * B_t[Loop3];
						f_y += (transfer_y[ba_i + Loop2][ba_j + Loop3] - master_y[ba_i + Loop2][ba_j + Loop3]) * B_s[Loop2] * B_t[Loop3];
					}
				}
			}
			distance_x[Loop1] = (distance_x[Loop1] - f_x) * 2;
			distance_y[Loop1] = (distance_y[Loop1] - f_y) * 2;
		}


		if (time <= 2){
			for (int Loop1 = 0; Loop1<Feat_num; Loop1++){
				px2[Loop1] = px2[Loop1] * 2;
				py2[Loop1] = py2[Loop1] * 2;
			}
			for (int Loop1 = 0; Loop1 <= wi; Loop1++){
				for (int Loop2 = 0; Loop2 <= hi; Loop2++){
					value_x[Loop1][Loop2] = 0;
					value_y[Loop1][Loop2] = 0;
					weigh[Loop1][Loop2] = 0;


					master_x[Loop1 * 2][Loop2 * 2] = (transfer_x[Loop1 - 1][Loop2 - 1] + transfer_x[Loop1 - 1][Loop2 + 1] +
						transfer_x[Loop1 + 1][Loop2 - 1] + transfer_x[Loop1 + 1][Loop2 + 1] +
						transfer_x[Loop1 - 1][Loop2] * 6 + transfer_x[Loop1][Loop2 - 1] * 6 +
						transfer_x[Loop1][Loop2 + 1] * 6 + transfer_x[Loop1 + 1][Loop2] * 6 +
						transfer_x[Loop1][Loop2] * 36) / 32;
					master_y[Loop1 * 2][Loop2 * 2] = (transfer_y[Loop1 - 1][Loop2 - 1] + transfer_y[Loop1 - 1][Loop2 + 1] +
						transfer_y[Loop1 + 1][Loop2 - 1] + transfer_y[Loop1 + 1][Loop2 + 1] +
						transfer_y[Loop1 - 1][Loop2] * 6 + transfer_y[Loop1][Loop2 - 1] * 6 +
						transfer_y[Loop1][Loop2 + 1] * 6 + transfer_y[Loop1 + 1][Loop2] * 6 +
						transfer_y[Loop1][Loop2] * 36) / 32;
					master_x[Loop1 * 2][Loop2 * 2 + 1] = (transfer_x[Loop1 - 1][Loop2] + transfer_x[Loop1 - 1][Loop2 + 1] +
						transfer_x[Loop1 + 1][Loop2] + transfer_x[Loop1 + 1][Loop2 + 1] +
						transfer_x[Loop1][Loop2] * 6 + transfer_x[Loop1][Loop2 + 1] * 6) / 8;
					master_y[Loop1 * 2][Loop2 * 2 + 1] = (transfer_y[Loop1 - 1][Loop2] + transfer_y[Loop1 - 1][Loop2 + 1] +
						transfer_y[Loop1 + 1][Loop2] + transfer_y[Loop1 + 1][Loop2 + 1] +
						transfer_y[Loop1][Loop2] * 6 + transfer_y[Loop1][Loop2 + 1] * 6) / 8;
					master_x[Loop1 * 2 + 1][Loop2 * 2] = (transfer_x[Loop1][Loop2 - 1] + transfer_x[Loop1][Loop2 + 1] +
						transfer_x[Loop1 + 1][Loop2 - 1] + transfer_x[Loop1 + 1][Loop2 + 1] +
						transfer_x[Loop1][Loop2] * 6 + transfer_x[Loop1 + 1][Loop2] * 6) / 8;
					master_y[Loop1 * 2 + 1][Loop2 * 2] = (transfer_y[Loop1][Loop2 - 1] + transfer_y[Loop1][Loop2 + 1] +
						transfer_y[Loop1 + 1][Loop2 - 1] + transfer_y[Loop1 + 1][Loop2 + 1] +
						transfer_y[Loop1][Loop2] * 6 + transfer_y[Loop1 + 1][Loop2] * 6) / 8;
					master_x[Loop1 * 2 + 1][Loop2 * 2 + 1] = (transfer_x[Loop1][Loop2] + transfer_x[Loop1][Loop2 + 1] +
						transfer_x[Loop1 + 1][Loop2] + transfer_x[Loop1 + 1][Loop2 + 1]) / 2;
					master_y[Loop1 * 2 + 1][Loop2 * 2 + 1] = (transfer_y[Loop1][Loop2] + transfer_y[Loop1][Loop2 + 1] +
						transfer_y[Loop1 + 1][Loop2] + transfer_y[Loop1 + 1][Loop2 + 1]) / 2;
				}
			}
			wi = wi * 2;
			hi = hi * 2;
			size_w = size_w / 2;
			size_h = size_h / 2;
		}

		else if (time == 3){

			for (original_x = 0; original_x <= width - 1; original_x++){
				for (original_y = 0; original_y <= height - 1; original_y++){
					morph_x = (float)original_x / size_w;
					morph_y = (float)original_y / size_h;
					ba_i = (int)morph_x - 1;
					ba_j = (int)morph_y - 1;
					ba_s = morph_x - (int)morph_x;
					ba_t = morph_y - (int)morph_y;

					B_s[0] = ((1 - ba_s)*(1 - ba_s)*(1 - ba_s) / 6);
					B_s[1] = ((3 * ba_s*ba_s*ba_s - 6 * ba_s*ba_s + 4) / 6);
					B_s[2] = ((-3 * ba_s*ba_s*ba_s + 3 * ba_s*ba_s + 3 * ba_s + 1) / 6);
					B_s[3] = (ba_s*ba_s*ba_s / 6);
					B_t[0] = ((1 - ba_t)*(1 - ba_t)*(1 - ba_t) / 6);
					B_t[1] = ((3 * ba_t*ba_t*ba_t - 6 * ba_t*ba_t + 4) / 6);
					B_t[2] = ((-3 * ba_t*ba_t*ba_t + 3 * ba_t*ba_t + 3 * ba_t + 1) / 6);
					B_t[3] = (ba_t*ba_t*ba_t / 6);

					f_x = 0;
					f_y = 0;
					for (int Loop1 = 0; Loop1 <= 3; Loop1++){
						for (int Loop2 = 0; Loop2 <= 3; Loop2++){
							if (ba_i == -1 && Loop1 == 0){
							}
							else if (ba_i == Div_x && Loop1 == 3){
							}
							else if (ba_j == -1 && Loop2 == 0){
							}
							else if (ba_j == Div_y && Loop2 == 3){
							}
							else{
								f_x += transfer_x[ba_i + Loop1][ba_j + Loop2] * B_s[Loop1] * B_t[Loop2];
								f_y += transfer_y[ba_i + Loop1][ba_j + Loop2] * B_s[Loop1] * B_t[Loop2];
							}
						}
					}
					temporary_x = original_x + f_x*size_w;
					temporary_y = original_y + f_y*size_h;
					if (temporary_x < 0)	temporary_x = 0;		else if (temporary_x > width - 1)	temporary_x = width - 1;
					if (temporary_y < 0)	temporary_y = 0;		else if (temporary_y > height - 1)	temporary_y = height - 1;


					t_x = (int)temporary_x;		t_y = (int)temporary_y;
					top = (int)temporary_x;		under = (int)temporary_x + 1;
					left = (int)temporary_y;	right = (int)temporary_y + 1;
					if (top < 0)	top = 0;			else if (top > width - 1)	top = width - 1;
					if (under < 0)	under = 0;	else if (under > width - 1)	under = width - 1;
					if (left < 0)	left = 0;		else if (left > height - 1)	left = height - 1;
					if (right < 0)	right = 0;	else if (right > height - 1)	right = height - 1;

					//float pixel_1,pixel_2,pixel_3,pixel_4,pixel;
					//pixel = segMask.at<uchar>(original_y, original_x);
					//pixel_1 = segMask.at<uchar>(left,top);
					//pixel_2 = segMask.at<uchar>(right, top);
					//pixel_3 = segMask.at<uchar>(left, under);
					//pixel_4 = segMask.at<uchar>(right, under);
					////cout << pixel << pixel_1 << pixel_2 << pixel_3 << pixel_4 << endl;
					//pixel = pixel_1*((float)t_x + 1 - temporary_x)*((float)t_y + 1 - temporary_y) +
					// pixel_2*((float)t_x + 1 - temporary_x)*(temporary_y - (float)t_y) +
					// pixel_3*(temporary_x - (float)t_x)*((float)t_y + 1 - temporary_y) +
					// pixel_4*(temporary_x - (float)t_x)*(temporary_y - (float)t_y);

					int pixel;
					pixel = segMaskfg.at<uchar>(left, top);

					maskTemp.at<uchar>(original_y, original_x) = pixel;


					//cout << pixel<<endl;
					/*Color c1 = bm->GetPixel(top, left);		Color c2 = bm->GetPixel(top, right);
					Color c3 = bm->GetPixel(under, left);	Color c4 = bm->GetPixel(under, right);
					r = c1.R*((float)t_x + 1 - temporary_x)*((float)t_y + 1 - temporary_y) +
					c2.R*((float)t_x + 1 - temporary_x)*(temporary_y - (float)t_y) +
					c3.R*(temporary_x - (float)t_x)*((float)t_y + 1 - temporary_y) +
					c4.R*(temporary_x - (float)t_x)*(temporary_y - (float)t_y);
					g = c1.G*((float)t_x + 1 - temporary_x)*((float)t_y + 1 - temporary_y) +
					c2.G*((float)t_x + 1 - temporary_x)*(temporary_y - (float)t_y) +
					c3.G*(temporary_x - (float)t_x)*((float)t_y + 1 - temporary_y) +
					c4.G*(temporary_x - (float)t_x)*(temporary_y - (float)t_y);
					b = c1.B*((float)t_x + 1 - temporary_x)*((float)t_y + 1 - temporary_y) +
					c2.B*((float)t_x + 1 - temporary_x)*(temporary_y - (float)t_y) +
					c3.B*(temporary_x - (float)t_x)*((float)t_y + 1 - temporary_y) +
					c4.B*(temporary_x - (float)t_x)*(temporary_y - (float)t_y);
					Color c = Color::FromArgb((int)(r + 0.5), (int)(g + 0.5), (int)(b + 0.5));
					bm2->SetPixel(original_x, original_y, c);*/
				}
			}
		}
	}
	/*contourArea0->contourLoop = 0;
	contourArea0->contourOriginPoint_x.swap(vector<short>());
	contourArea0->contourOriginPoint_y.swap(vector<short>());
	contourArea0->contourEndPoint_x.swap(vector<short>());
	contourArea0->contourEndPoint_y.swap(vector<short>());*/

	changedMask = maskTemp.clone();

	/*else if (ui->pushButton_cnt3->isChecked() == true)
	{
	segMaskfg2 = contourArea0->maskTemp.clone();
	contourArea0->contourMask = segMaskfg2.clone();
	contourArea0->contourImg2 = (0, 0, 0, 0);
	}*/
	//segMask = contourArea0->maskTemp.clone();
	/*contourArea0->contourMask = segMask.clone();
	contourArea0->contourImg = (0, 0, 0, 0);*/
	//fgMask = (0, 0, 0, 0);
	//fgMask1 = (0, 0, 0, 0);
	//fgMask2 = (0, 0, 0, 0);
	//bgMask = (0, 0, 0, 0);
	//segShowImg = inputImg.clone();
	//vector<vector<Point> > contours;
	//vector<Vec4i> hierarchy;
	//findContours(contourArea0->contourMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	//for (int i = 0; i< contours.size(); i++)
	//{
	//	Scalar color = Scalar(0, 255, 0, 255);
	//	if (ui->pushButton_cnt1->isChecked() == true)
	//	{
	//		drawContours(contourArea0->contourImg0, contours, i, color, 1, 8, hierarchy, 0, Point());
	//	}
	//	else if (ui->pushButton_cnt2->isChecked() == true)
	//	{
	//		drawContours(contourArea0->contourImg1, contours, i, color, 1, 8, hierarchy, 0, Point());
	//	}
	//	/*else if (ui->pushButton_cnt3->isChecked() == true)
	//	{
	//	drawContours(contourArea0->contourImg2, contours, i, color, 1, 8, hierarchy, 0, Point());
	//	}*/
	//}
	////vStrSeg.swap(vector<short>());

	//for (int y = 0; y < height; y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{
	//		if (ui->pushButton_cnt1->isChecked() == true)
	//		{
	//			if (segMaskfg.at<uchar>(y, x) == 255)
	//			{
	//				segMaskfg1.at<uchar>(y, x) = 0;
	//				segMaskfg2.at<uchar>(y, x) = 0;
	//				(uchar)fgMask.at<Vec4b>(y, x)[3] = fgOverlayOpacity*0.01 * 255;
	//				(uchar)fgMask.at<Vec4b>(y, x)[0] = fgOverlayColor.blue();
	//				(uchar)fgMask.at<Vec4b>(y, x)[1] = fgOverlayColor.green();
	//				(uchar)fgMask.at<Vec4b>(y, x)[2] = fgOverlayColor.red();
	//				(uchar)fgMask1.at<Vec4b>(y, x)[3] = 0;
	//				(uchar)fgMask2.at<Vec4b>(y, x)[3] = 0;
	//				(uchar)bgMask.at<Vec4b>(y, x)[3] = 0;

	//				////(uchar)segShowImg.at<Vec3b>(y, x)[2] = 200;
	//				//(uchar)fgMask.at<Vec4b>(y, x)[3] = 255;
	//				//(uchar)fgMask.at<Vec4b>(y, x)[2] = 255;
	//			}
	//			else
	//			{
	//				(uchar)fgMask.at<Vec4b>(y, x)[3] = 0;
	//				(uchar)bgMask.at<Vec4b>(y, x)[3] = bgOverlayOpacity*0.01 * 255;


	//			}
	//		}
	//		else if (ui->pushButton_cnt2->isChecked() == true)
	//		{
	//			if (segMaskfg1.at<uchar>(y, x) == 255)
	//			{
	//				segMaskfg.at<uchar>(y, x) = 0;
	//				segMaskfg2.at<uchar>(y, x) = 0;
	//				(uchar)fgMask1.at<Vec4b>(y, x)[3] = fgOverlayOpacity1*0.01 * 255;
	//				(uchar)fgMask1.at<Vec4b>(y, x)[0] = fgOverlayColor1.blue();
	//				(uchar)fgMask1.at<Vec4b>(y, x)[1] = fgOverlayColor1.green();
	//				(uchar)fgMask.at<Vec4b>(y, x)[2] = fgOverlayColor.red();
	//				(uchar)fgMask.at<Vec4b>(y, x)[3] = 0;
	//				(uchar)fgMask2.at<Vec4b>(y, x)[3] = 0;
	//				(uchar)bgMask.at<Vec4b>(y, x)[3] = 0;

	//				////(uchar)segShowImg.at<Vec3b>(y, x)[2] = 200;
	//				//(uchar)fgMask.at<Vec4b>(y, x)[3] = 255;
	//				//(uchar)fgMask.at<Vec4b>(y, x)[2] = 255;
	//			}
	//			else
	//			{
	//				(uchar)fgMask1.at<Vec4b>(y, x)[3] = 0;
	//				(uchar)bgMask.at<Vec4b>(y, x)[3] = bgOverlayOpacity*0.01 * 255;
	//			}
	//		}
	//		//else if (ui->pushButton_cnt3->isChecked() == true)
	//		//{
	//		//	if (segMaskfg2.at<uchar>(y, x) == 255)
	//		//	{
	//		//		segMaskfg1.at<uchar>(y, x) = 0;
	//		//		segMaskfg.at<uchar>(y, x) = 0;
	//		//		(uchar)fgMask2.at<Vec4b>(y, x)[3] = fgOverlayOpacity*0.01 * 255;
	//		//		(uchar)fgMask2.at<Vec4b>(y, x)[0] = fgOverlayColor2.blue();
	//		//		(uchar)fgMask2.at<Vec4b>(y, x)[1] = fgOverlayColor2.green();
	//		//		(uchar)fgMask2.at<Vec4b>(y, x)[2] = fgOverlayColor2.red();
	//		//		(uchar)fgMask1.at<Vec4b>(y, x)[3] = 0;
	//		//		(uchar)fgMask.at<Vec4b>(y, x)[3] = 0;
	//		//		(uchar)bgMask.at<Vec4b>(y, x)[3] = 0;

	//		//		////(uchar)segShowImg.at<Vec3b>(y, x)[2] = 200;
	//		//		//(uchar)fgMask.at<Vec4b>(y, x)[3] = 255;
	//		//		//(uchar)fgMask.at<Vec4b>(y, x)[2] = 255;
	//		//	}
	//		//	else
	//		//	{
	//		//		(uchar)fgMask2.at<Vec4b>(y, x)[3] = 0;
	//		//		(uchar)bgMask.at<Vec4b>(y, x)[3] = bgOverlayOpacity*0.01 * 255;
	//		//	}
	//		//}

	//	}
	//}


	//imshow("Contour Mask", contourMask);
	/*imshow("Contour Image", contourArea->contourImg);
	imshow("Segmentation Mask", segMask);
	imshow("Segmentation Image", segShowImg);*/
	//imshow("Mask Temp", maskTemp);
	//imshow("Segmentation Mask", segMask);
	//cv::imshow("changeMask", changedMask);
	cv::imwrite(changeMaskPng, changedMask);
	/*std::vector<std::vector<cv::Point>> changedContour;
	cv::findContours(changedMask, changedContour,
		CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cv::Mat Contour(changedMask.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(Contour, changedContour,
		-1, cv::Scalar(0), 2);
	cv::imshow("changeContour", Contour);

	cv::imwrite("C:\\Users\\WangYi\\Downloads\\CD22\\CD22\\PV\\PreOperation\\Liver\\png\\changeContour.png", Contour);*/

	//morphing(1,20,20);
	//cv::waitKey(0);

	char s[500];
	sprintf_s(s, "%s %s %s %s %s %s %s", "C:\\workspace\\server_now\\Server\\Server\\modifyData\\EXE\\VolumeFromSlices.exe",
		"C:\\workspace\\server_now\\Server\\Server\\modifyData\\png", "mask", ".png", "0", "235", 
		"C:\\workspace\\server_now\\Server\\Server\\modifyData\\png\\changedMask.mhd");
	qDebug("%s", s);
	system(s);
	string modifyImage = "C:\\workspace\\server_now\\Server\\Server\\modifyData\\png\\changedMask.mhd";
	Read_Display(modifyImage,this->currentui);
}

//void mhdReader::server_GetRequestForOriginalPoint()
//{
//	currentui.button_OriginalPoints->click();
//}
//
//void mhdReader::server_GetRequestForNewPoint()
//{
//	currentui.button_NewPoints->click();
//}
//
//void mhdReader::server_GetRequestForEditMask()
//{
//	currentui.button_EditMask->click();
//}