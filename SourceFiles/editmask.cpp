#include "editmask.h"




using namespace std;



EditMask::EditMask(QWidget *parent) :
QDialog(parent),
ui(new Ui::Dialog_EditMask)
{
	ui->setupUi(this);
	
	area0 = new EditArea;
	connect(ui->pushButton_cnt1, SIGNAL(clicked()), this, SLOT(pushButton_cnt1_onclick()));
	connect(ui->pushButton_cnt2, SIGNAL(clicked()), this, SLOT(pushButton_cnt2_onclick()));
	//connect(ui->pushButton_cnt3, SIGNAL(clicked()), this, SLOT(pushButton_cnt3_onclick()));
	connect(ui->pushButton_bkg, SIGNAL(clicked()), this, SLOT(pushButton_bkg_onclick()));
	connect(ui->pushButton_obj1, SIGNAL(clicked()), this, SLOT(pushButton_obj1_onclick()));
	connect(ui->pushButton_obj2, SIGNAL(clicked()), this, SLOT(pushButton_obj2_onclick()));
	//connect(ui->pushButton_obj3, SIGNAL(clicked()), this, SLOT(pushButton_obj3_onclick()));
	connect(ui->verticalScrollBar_ScribbleImage, SIGNAL(valueChanged(int)), this, SLOT(changeStartIndex()));

	//connect(ui->pushButton_ContourOverlay_Edit_One, SIGNAL(clicked()), this, SLOT(EditContour_one()));
	connect(ui->pushButton_ContourOverlay_Edit_PointOrigin, SIGNAL(clicked()), this, SLOT(EditContour_PointOrigin()));
	connect(ui->pushButton_ContourOverlay_Edit_PointEnd, SIGNAL(clicked()), this, SLOT(EditContour_PointEnd()));
	connect(ui->pushButton_ContourOverlay_Edit, SIGNAL(clicked()), this, SLOT(EditContour()));
	connect(ui->pushButton_MaskOverlay_Edit, SIGNAL(clicked()), this, SLOT(EditPainting()));

	connect(ui->horizontalSlider_obj1, SIGNAL(valueChanged(int)), this, SLOT(changeSize_obj1()));
	connect(ui->horizontalSlider_obj2, SIGNAL(valueChanged(int)), this, SLOT(changeSize_obj2()));
	//connect(ui->horizontalSlider_obj3, SIGNAL(valueChanged(int)), this, SLOT(changeSize_obj3()));
	connect(ui->horizontalSlider_bkg, SIGNAL(valueChanged(int)), this, SLOT(changeSize_bkg()));

	connect(ui->lineEdit_obj1, SIGNAL(textChanged(QString)), this, SLOT(setSize_obj1()));
	connect(ui->lineEdit_obj2, SIGNAL(textChanged(QString)), this, SLOT(setSize_obj2()));
	//connect(ui->lineEdit_obj3, SIGNAL(textChanged(QString)), this, SLOT(setSize_obj3()));
	connect(ui->lineEdit_bkg, SIGNAL(textChanged(QString)), this, SLOT(setSize_bkg()));

	connect(ui->pushButton_ContourOverlay_Edit_Clear, SIGNAL(clicked()), this, SLOT(ClearContourPoints()));
	connect(ui->pushButton_MaskOverlay_Edit_Clear, SIGNAL(clicked()), this, SLOT(ClearPainting()));

	connect(ui->pushButton_SaveChanges, SIGNAL(clicked()), this, SLOT(SaveChanges()));
	connect(ui->pushButton_Reset, SIGNAL(clicked()), this, SLOT(ResetMask()));
	connect(ui->pushButton_ReloadMask, SIGNAL(clicked()), this, SLOT(ReloadMask()));
	connect(ui->pushButton_SaveMaskAs, SIGNAL(clicked()), this, SLOT(SaveResult()));

	connect(ui->pushButton_FitTheScreen, SIGNAL(clicked()), this, SLOT(fit_Image()));
	connect(ui->pushButton_OriginalSize, SIGNAL(clicked()), this, SLOT(originalSize()));
	connect(ui->horizontalSlider_zoom, SIGNAL(valueChanged(int)), this, SLOT(zoom()));

}

EditMask::~EditMask()
{
	delete ui;
}

void EditMask::setTitle(QString Title)
{
	setWindowTitle(Title);
}

void EditMask::show(QColor obj1, QColor obj2, QColor obj3, QColor bkg, QColor cnt1, QColor cnt2, QColor cnt3, int obj1o, int obj2o, int obj3o, int bkgo, int cnt1o, int cnt2o, int cnt3o, char* oriFile, char* maskFile, int index)
{

	oriMhd=oriFile;
	maskMhd=maskFile;
	copyMhdFile(maskMhd, maskOri);
	copyMhdFile(maskMhd, maskNew);

	fgOverlayColor = obj1;
	fgOverlayColor1 = obj2;
	fgOverlayColor2 = obj3;
	bgOverlayColor = bkg;
	contourOverlayColor = cnt1;
	contourOverlayColor1 = cnt2;
	contourOverlayColor2 = cnt3;

	fgOverlayOpacity = obj1o;
	fgOverlayOpacity1 = obj2o;
	fgOverlayOpacity2 = obj3o;
	bgOverlayOpacity = bkgo;
	contourOverlayOpacity = cnt1o;
	contourOverlayOpacity1 = cnt2o;
	contourOverlayOpacity2 = cnt3o;

	str_index = index;

	

	ui->pushButton_cnt1->setStyleSheet(QString("QPushButton\n"
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
		"    border:2px solid rgb( %1, %2, %3);\n"
		"}\n"
		"").arg(QString::number(contourOverlayColor.red()), QString::number(contourOverlayColor.green()), QString::number(contourOverlayColor.blue())));

	ui->pushButton_cnt2->setStyleSheet(QString("QPushButton\n"
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
		"    border:2px solid rgb( %1, %2, %3);\n"
		"}\n"
		"").arg(QString::number(contourOverlayColor1.red()), QString::number(contourOverlayColor1.green()), QString::number(contourOverlayColor1.blue())));
	/*ui->pushButton_cnt3->setStyleSheet(QString("QPushButton\n"
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
		"    border:2px solid rgb( %1, %2, %3);\n"
		"}\n"
		"").arg(QString::number(contourOverlayColor2.red()), QString::number(contourOverlayColor2.green()), QString::number(contourOverlayColor2.blue())));*/
	ui->pushButton_obj1->setStyleSheet(QString("QPushButton\n"
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
		"    border:1px solid rgb( %1, %2, %3);\n"
		"}\n"
		"").arg(QString::number(fgOverlayColor.red()), QString::number(fgOverlayColor.green()), QString::number(fgOverlayColor.blue())));
	ui->pushButton_obj2->setStyleSheet(QString("QPushButton\n"
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
		"    border:1px solid rgb( %1, %2, %3);\n"
		"}\n"
		"").arg(QString::number(fgOverlayColor1.red()), QString::number(fgOverlayColor1.green()), QString::number(fgOverlayColor1.blue())));
	/*ui->pushButton_obj3->setStyleSheet(QString("QPushButton\n"
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
		"    border:1px solid rgb( %1, %2, %3);\n"
		"}\n"
		"").arg(QString::number(fgOverlayColor2.red()), QString::number(fgOverlayColor2.green()), QString::number(fgOverlayColor2.blue())));*/
	ui->pushButton_bkg->setStyleSheet(QString("QPushButton\n"
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
		"    border:1px solid rgb( %1, %2, %3);\n"
		"}\n"
		"").arg(QString::number(bgOverlayColor.red()), QString::number(bgOverlayColor.green()), QString::number(bgOverlayColor.blue())));


	   

	copyMhdFile(maskMhd, maskNew);
	copyMhdFile(maskMhd, maskEdit);
	cout << "-------------" << maskEdit << endl;
	loadData();
	area0->objBrushColor = obj1;
	area0->obj1BrushColor = obj2;
	area0->obj2BrushColor = obj3;
	area0->bkgBrushColor = bkg;
	area0->objBrushOpacity = obj1o;
	area0->obj1BrushOpacity = obj2o;
	area0->obj2BrushOpacity = obj3o;
	area0->bkgBrushOpacity = bkgo;
	ui->lineEdit_obj1->setText(QString::number(area0->objBrushRadius));
	ui->lineEdit_obj2->setText(QString::number(area0->obj1BrushRadius));
	//ui->lineEdit_obj3->setText(QString::number(area0->obj2BrushRadius));
	ui->lineEdit_bkg->setText(QString::number(area0->bkgBrushRadius));

	ui->horizontalSlider_obj1->setValue(area0->objBrushRadius);
	ui->horizontalSlider_obj2->setValue(area0->obj1BrushRadius);
	//ui->horizontalSlider_obj3->setValue(area0->obj2BrushRadius);
	ui->horizontalSlider_bkg->setValue(area0->bkgBrushRadius);
	int value;
	value = index + 1;
	ui->verticalScrollBar_ScribbleImage->setValue(value);
	


}

void EditMask::loadData()
{


	vStrImg.swap(vector<short>());
	string SoriginImgFile;
	SoriginImgFile = oriMhd;

	//graphicsView_ScribbleImage


	//originImgFile = SoriginImgFile.c_str();
	DataFile* dataFile = new DataFile(SoriginImgFile);
	//service1->filedir[dataFile->getMD5() + dataFile->FileType()] = dataFile;

	if (dataFile->getType() == ".mhd")
	{
		imageType = 1;
		strcpy_s(oriMhd, strlen(SoriginImgFile.c_str()) + 1, SoriginImgFile.c_str());
		loadOriginal3DImage(oriMhd, str_index);//get vStrImg
	}
	else if (dataFile->getType() == ".dcm")
	{
		imageType = 2;
		string directory = SoriginImgFile.substr(0, SoriginImgFile.find_last_of("/"));
		strcpy_s(oriMhd, strlen(directory.c_str()) + 1, directory.c_str());
		loadOriginal3DImage(DICOMtoMHD, str_index);
	}


	img3D_2D(vStrImg, str_index, imgFileName);

	if (init(imgFileName) == -1)
	{
		cout << "Could not initialize" << endl;
		//return -1;
	}
	


	InputDisplay();
	oSize = QScribbleImg.size();

	QString slices = QString::number(depth);
	ui->label_ScibbleImage_ValueOfSliceNumber->setText(slices);
	//ui.label_Mask_ValueOfSliceNumber->setText(slices);
	//ui.label_MaskOverlay_ValueOfSliceNumber->setText(slices);
	//ui.label_ContourOverlay_ValueOfSliceNumber->setText(slices);

	ui->verticalScrollBar_ScribbleImage->setMaximum(depth);
	//ui.verticalScrollBar_Mask->setMaximum(depth);
	//ui.verticalScrollBar_MaskOverlay->setMaximum(depth);
	//ui.verticalScrollBar_ContourOverlay->setMaximum(depth);

	QString index = QString::number(str_index);
	ui->label_ScribbleImage_ValueOfSliceNumber_Value->setText(index);
	//ui.label_Mask_ValueOfSliceNumber_Value->setText(index);
	//ui.label_MaskOverlay_ValueOfSliceNumber_Value->setText(index);
	//ui.label_ContourOverlay_ValueOfSliceNumber_Value->setText(index);

	
	area0->setImageSize(width, height);
	area0->init(width, height);
	ui->scrollArea_ScribbleArea->setWidget(area0);
	int x = QScribbleImgScaled.width();
	int y = QScribbleImgScaled.height();
	ui->scrollArea_ScribbleArea->setGeometry(0.5*(ui->scrollArea_ContourOverlay->width() - x), 0.5*(ui->scrollArea_ContourOverlay->height() - y), x, y);

	area0->cSize.width = ui->horizontalSlider_zoom->value()*0.01*area0->oSize.width;
	area0->cSize.height = ui->horizontalSlider_zoom->value()*0.01*area0->oSize.height;

	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_obj_isOn = false;
	area0->pushButton_bkg_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;


	contourArea0 = new EditContourArea;
	contourArea0->setImageSize(width, height);
	contourArea0->init(width, height);
	ui->scrollArea_EditContourArea->setWidget(contourArea0);
	ui->scrollArea_EditContourArea->setGeometry(0.5*(ui->scrollArea_ContourOverlay->width() - x), 0.5*(ui->scrollArea_ContourOverlay->height() - y), x, y);
	contourArea0->EditContourOne_isOn = false;
	contourArea0->EditContourPointOrigin_isOn = false;
	contourArea0->EditContourPointEnd_isOn = false;


	area0->select = Rect(0, 0, width, height);


	zoomInfactor = ui->horizontalSlider_zoom->value()*0.01;
	area0->zoomInfactor = zoomInfactor;
	contourArea0->zoomInfactor = zoomInfactor;

	area0->qSize = qSize;
	area0->scaleImage();

	contourArea0->qSize = qSize;
	contourArea0->scaleImage();




	OverlayDisplay();
}


void EditMask::InputDisplay()
{
	QScribbleImg = QImage(imgFileName);

	qSize = ui->horizontalSlider_zoom->value()*0.01*QScribbleImg.size();
	QScribbleImgScaled = QScribbleImg.scaled(qSize, Qt::KeepAspectRatio);

	P_inputImage = P_inputImage.fromImage(QScribbleImgScaled);


	ui->label_OriginalDisplay->setPixmap(P_inputImage);
	ui->label_OriginalDisplay->show();
}



int EditMask::loadOriginal3DImage(char * imgName, int str_index)
{
	typedef short							PixelType;
	typedef itk::Image<PixelType, 3>		ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;

	ReaderType::Pointer originalReader = ReaderType::New();
	typedef std::list<itk::LightObject::Pointer > RegisteredObjectsContainerType;

	RegisteredObjectsContainerType registeredIOs =
		itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
	qDebug() << registeredIOs.size();
	itk::MetaImageIOFactory::RegisterOneFactory();

	originalReader->SetFileName(imgName);
	originalReader->Update();

	ImageType::Pointer		originalPointer = originalReader->GetOutput();
	ImageType::SizeType		imgSize = originalPointer->GetLargestPossibleRegion().GetSize();
	ImageType::SpacingType	imgSpacing = originalPointer->GetSpacing();
	ImageType::IndexType    imgIndex = originalPointer->GetLargestPossibleRegion().GetIndex();
	ImageType::PointType    imgOrigin = originalPointer->GetOrigin();

	ImageType::PixelType	*originalImg = originalReader->GetOutput()->GetBufferPointer();

	width = imgSize[0];
	height = imgSize[1];
	depth = imgSize[2];

	spacing_x = imgSpacing[0];
	spacing_y = imgSpacing[1];
	spacing_z = imgSpacing[2];

	index_x = imgIndex[0];
	index_y = imgIndex[1];
	index_z = imgIndex[2];

	origin_x = imgOrigin[0];
	origin_y = imgOrigin[1];
	origin_z = imgOrigin[2];

	vImage.swap(vector<short>());
	vImage.reserve(width*height+10);
	for (int k = 0; k < depth; k++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i< width; i++)
			{
				short pixel;
				pixel = originalImg[k*height*width + j * width + i];
				vImage.push_back(pixel);
				if (pixel>pixel_max)
					pixel_max = pixel;
				else if (pixel < pixel_min)
					pixel_min = pixel;
			}
		}
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			short pixel;
			pixel = originalImg[str_index * height * width + y * width + x];
			vStrImg.push_back(pixel);
		}
	}
	//cout << "pixelmax is" <<pixelmax<<"pixelmin is"<<pixelmin<< endl;
	cout << "Information has received." << endl;
	cout << "The width, height, depth of the 3D image is " << width << "*" << height << "*" << depth << "." << endl;
	return 0;
}

int EditMask::img3D_2D(vector<short> img3D, int str_index, char*img2D)
{

	//3D->2D
	typedef itk::Image< unsigned char, 2 > ImageType2;
	ImageType2::Pointer outputimage = ImageType2::New();

	ImageType2::IndexType start;
	start[0] = index_x;  // first index on X  
	start[1] = index_y;  // first index on Y  

	ImageType2::SizeType  size;
	size[0] = width;  // size along X  
	size[1] = height;  // size along Y  

	ImageType2::SpacingType	outimgSpacing;
	outimgSpacing[0] = spacing_x;
	outimgSpacing[1] = spacing_y;

	ImageType2::RegionType region;
	region.SetSize(size);
	region.SetIndex(start);
	outputimage->SetRegions(region);
	outputimage->SetSpacing(outimgSpacing);
	outputimage->Allocate();

	ImageType2::PixelType  initialValue = 0;
	outputimage->FillBuffer(initialValue);
	//img3D = vStrImg;


	for (int j = 0; j < size[1]; j++)
	{
		for (int i = 0; i< size[0]; i++)
		{
			ImageType2::IndexType pixelIndex;
			pixelIndex[0] = i;
			pixelIndex[1] = j;

			ImageType2::PixelType   pixelValue = outputimage->GetPixel(pixelIndex);
			short pixelv;
			pixelv = img3D[j * size[0] + i];
			short pixel;
			pixel = (pixelv - pixel_min) * 255 / (pixel_max - pixel_min);
			outputimage->SetPixel(pixelIndex, pixel);
		}
	}

	typedef itk::ImageFileWriter< ImageType2 > WriterType2;
	WriterType2::Pointer writer = WriterType2::New();

	// Or other file format, such as mhd/mha, png, jpg etc.  
	itk::JPEGImageIOFactory::RegisterOneFactory();
	writer->SetFileName(img2D);
	writer->SetInput(outputimage);
	writer->Update();

	cout << "2D image has displayed." << endl;
	cout << "The width, height of the 2D image is " << size[0] << "*" << size[1] << "." << endl;

	return 0;

}

int EditMask::init(char * imgFileName)
{
	// Read the file
	inputImg = imread(imgFileName, CV_LOAD_IMAGE_COLOR);
	//showImg = inputImg.clone();
	//segShowImg = inputImg.clone();

	//contourImg = inputImg.clone();

	// Check for invalid input
	if (!inputImg.data)
	{
		cout << "Could not open or find the image: " << imgFileName << std::endl;
		return -1;
	}

	// this is the mask to keep the user scribbles
	fgMask.create(2, inputImg.size, CV_8UC4);
	fgMask = (0, 0, 0, 0);
	fgMask1.create(2, inputImg.size, CV_8UC4);
	fgMask1 = (0, 0, 0, 0);
	fgMask2.create(2, inputImg.size, CV_8UC4);
	fgMask2 = (0, 0, 0, 0);
	bgMask.create(2, inputImg.size, CV_8UC4);
	bgMask = (0, 0, 0, 0);
	segMask.create(2, inputImg.size, CV_8UC1);
	segMask = 0;
	segMaskfg.create(2, inputImg.size, CV_8UC1);
	segMaskfg = 0;
	segMaskfg1.create(2, inputImg.size, CV_8UC1);
	segMaskfg1 = 0;
	segMaskfg2.create(2, inputImg.size, CV_8UC1);
	segMaskfg2 = 0;

	fgMaskScaled.create(2, inputImg.size, CV_8UC4);
	fgMaskScaled = (0, 0, 0, 0);
	fgMask1Scaled.create(2, inputImg.size, CV_8UC4);
	fgMask1Scaled = (0, 0, 0, 0);
	fgMask2Scaled.create(2, inputImg.size, CV_8UC4);
	fgMask2Scaled = (0, 0, 0, 0);
	bgMaskScaled.create(2, inputImg.size, CV_8UC4);
	bgMaskScaled = (0, 0, 0, 0);
	segMaskScaled.create(2, inputImg.size, CV_8UC1);
	segMaskScaled = 0;
	segMaskfgScaled.create(2, inputImg.size, CV_8UC1);
	segMaskfgScaled = 0;
	segMaskfg1Scaled.create(2, inputImg.size, CV_8UC1);
	segMaskfg1Scaled = 0;
	segMaskfg2Scaled.create(2, inputImg.size, CV_8UC1);
	segMaskfg2Scaled = 0;

	contourSeg0.create(2, inputImg.size, CV_8UC1);
	contourSeg0 = 0;
	contourSeg1.create(2, inputImg.size, CV_8UC1);
	contourSeg1 = 0;
	contourSeg2.create(2, inputImg.size, CV_8UC1);
	contourSeg2 = 0;

	contourSeg0Scaled.create(2, inputImg.size, CV_8UC1);
	contourSeg0 = 0;
	contourSeg1Scaled.create(2, inputImg.size, CV_8UC1);
	contourSeg1 = 0;
	contourSeg2Scaled.create(2, inputImg.size, CV_8UC1);
	contourSeg2 = 0;

	return 0;
}

void EditMask::copyMhdFile(char* file1, char* file2)
{
	/*string SFile1(file1);
	string SFile2(file2);*/
	int num = MultiByteToWideChar(0, 0, file1, -1, NULL, 0);
	wchar_t *copy = new wchar_t[num];
	MultiByteToWideChar(0, 0, file1, -1, copy, num);
	num = MultiByteToWideChar(0, 0, file2, -1, NULL, 0);
	wchar_t *save = new wchar_t[num];
	MultiByteToWideChar(0, 0, file2, -1, save, num);
	//CopyFile(_T(copy), _T(save), FALSE);
	//CopyFile(copy, save, FALSE);
	CopyFile(file1, file2, FALSE);

	string SFile1Raw(file1);
	string SFile2Raw(file2);

	int index = SFile1Raw.size() - 1;
	int indexNew = index - 3;
	while (index > indexNew)
	{

		SFile1Raw.erase(index, 1);
		index--;

	}


	index = SFile2Raw.size() - 1;
	indexNew = index - 3;
	while (index > indexNew)
	{

		SFile2Raw.erase(index, 1);
		index--;

	}

	SFile1Raw = SFile1Raw + "raw";
	SFile2Raw = SFile2Raw + "raw";


	char*saveFileRaw = (char*)SFile2Raw.data();
	char*copyFileRaw = (char*)SFile1Raw.data();
	num = MultiByteToWideChar(0, 0, copyFileRaw, -1, NULL, 0);
	wchar_t *copyRaw = new wchar_t[num];
	MultiByteToWideChar(0, 0, copyFileRaw, -1, copyRaw, num);
	num = MultiByteToWideChar(0, 0, saveFileRaw, -1, NULL, 0);
	wchar_t *saveRaw = new wchar_t[num];
	MultiByteToWideChar(0, 0, saveFileRaw, -1, saveRaw, num);
	CopyFile(copyFileRaw, saveFileRaw, FALSE);

}

void EditMask::OverlayDisplay()
{
	readMask(maskEdit);
	//readOverlays();
	displayOverlays();
}

void EditMask::readMask(char* file)
{
	typedef short							PixelType;
	typedef itk::Image<PixelType, 3>		ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;

	ReaderType::Pointer originalReader = ReaderType::New();
	typedef std::list<itk::LightObject::Pointer > RegisteredObjectsContainerType;

	RegisteredObjectsContainerType registeredIOs =
		itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
	qDebug() << registeredIOs.size();
	itk::MetaImageIOFactory::RegisterOneFactory();

	originalReader->SetFileName(file);
	originalReader->Update();

	ImageType::Pointer		originalPointer = originalReader->GetOutput();
	ImageType::PixelType	*originalImg = originalReader->GetOutput()->GetBufferPointer();


	fgMask = (0, 0, 0, 0);
	fgMask1 = (0, 0, 0, 0);
	fgMask2 = (0, 0, 0, 0);
	bgMask = (0, 0, 0, 0);
	segMask = 0;
	segMaskfg = 0;
	segMaskfg1 = 0;
	segMaskfg2 = 0;
	contourSeg0 = 0;
	contourSeg1 = 0;
	contourSeg2 = 0;


	//contourArea->contourMask = 0;
	//contourArea->maskTemp = 0;
	//contourArea->contourImg = 0;

	//update();

	/*fgOverlayOpacity;
	bgOverlayOpacity;
	fgOverlayOpacity1;
	fgOverlayOpacity2;*/

	int a = 255;
	a = a*fgOverlayOpacity*0.01;
	int b = 255;
	b = b*bgOverlayOpacity*0.01;
	int c = 255;
	c = c*fgOverlayOpacity1*0.01;
	int d = 255;
	d = d*fgOverlayOpacity2*0.01;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x< width; x++)
		{
			if (originalImg[str_index*height*width + y * width + x] == 0)
			{
				(uchar)bgMask.at<Vec4b>(y, x)[0] = bgOverlayColor.blue();
				(uchar)bgMask.at<Vec4b>(y, x)[1] = bgOverlayColor.green();
				(uchar)bgMask.at<Vec4b>(y, x)[2] = bgOverlayColor.red();
				(uchar)bgMask.at<Vec4b>(y, x)[3] = b;

				segMask.at<uchar>(y, x) = 0;
				segMaskfg.at<uchar>(y, x) = 0;
				segMaskfg1.at<uchar>(y, x) = 0;
				segMaskfg2.at<uchar>(y, x) = 0;
				/*(uchar)segMask.at<Vec4b>(y, x)[0] = 0;
				(uchar)segMask.at<Vec4b>(y, x)[1] = 0;
				(uchar)segMask.at<Vec4b>(y, x)[2] = 0;
				(uchar)segMask.at<Vec4b>(y, x)[3] = 255;*/

			}
			//2017/06/08 wy
			else if (originalImg[str_index*height*width + y * width + x] == 2)
			{
				(uchar)fgMask.at<Vec4b>(y, x)[0] = fgOverlayColor.blue();
				(uchar)fgMask.at<Vec4b>(y, x)[1] = fgOverlayColor.green();
				(uchar)fgMask.at<Vec4b>(y, x)[2] = fgOverlayColor.red();
				(uchar)fgMask.at<Vec4b>(y, x)[3] = a;

				segMask.at<uchar>(y, x) = 255;
				contourSeg0.at<uchar>(y, x) = 255;
				segMaskfg.at<uchar>(y, x) = 255;
				segMaskfg1.at<uchar>(y, x) = 0;
				segMaskfg2.at<uchar>(y, x) = 0;

				/*(uchar)segMask.at<Vec4b>(y, x)[0] = 255;
				(uchar)segMask.at<Vec4b>(y, x)[1] = 255;
				(uchar)segMask.at<Vec4b>(y, x)[2] = 255;
				(uchar)segMask.at<Vec4b>(y, x)[3] = 255;*/
			}
			else if (originalImg[str_index*height*width + y * width + x] == 3)
			{
				(uchar)fgMask1.at<Vec4b>(y, x)[0] = fgOverlayColor1.blue();
				(uchar)fgMask1.at<Vec4b>(y, x)[1] = fgOverlayColor1.green();
				(uchar)fgMask1.at<Vec4b>(y, x)[2] = fgOverlayColor1.red();
				(uchar)fgMask1.at<Vec4b>(y, x)[3] = c;

				segMask.at<uchar>(y, x) = 160;
				contourSeg1.at<uchar>(y, x) = 255;
				segMaskfg.at<uchar>(y, x) = 0;
				segMaskfg1.at<uchar>(y, x) = 255;
				segMaskfg2.at<uchar>(y, x) = 0;

				/*(uchar)segMask.at<Vec4b>(y, x)[0] = 160;
				(uchar)segMask.at<Vec4b>(y, x)[1] = 160;
				(uchar)segMask.at<Vec4b>(y, x)[2] = 160;
				(uchar)segMask.at<Vec4b>(y, x)[3] = 255;*/
			}
			else if (originalImg[str_index*height*width + y * width + x] == 4)
			{
				(uchar)fgMask2.at<Vec4b>(y, x)[0] = fgOverlayColor2.blue();
				(uchar)fgMask2.at<Vec4b>(y, x)[1] = fgOverlayColor2.green();
				(uchar)fgMask2.at<Vec4b>(y, x)[2] = fgOverlayColor2.red();
				(uchar)fgMask2.at<Vec4b>(y, x)[3] = d;

				segMask.at<uchar>(y, x) = 80;
				contourSeg2.at<uchar>(y, x) = 255;
				segMaskfg.at<uchar>(y, x) = 0;
				segMaskfg1.at<uchar>(y, x) = 0;
				segMaskfg2.at<uchar>(y, x) = 255;

				/*(uchar)segMask.at<Vec4b>(y, x)[0] = 80;
				(uchar)segMask.at<Vec4b>(y, x)[1] = 80;
				(uchar)segMask.at<Vec4b>(y, x)[2] = 80;
				(uchar)segMask.at<Vec4b>(y, x)[3] = 80;*/
			}
		}
	}
	
	cv::resize(bgMask, bgMaskScaled, area0->cSize);
	cv::resize(fgMask, fgMaskScaled, area0->cSize);
	cv::resize(fgMask1, fgMask1Scaled, area0->cSize);
	cv::resize(fgMask2, fgMask2Scaled, area0->cSize);
	cv::resize(contourSeg0, contourSeg0Scaled, area0->cSize);
	cv::resize(contourSeg1, contourSeg1Scaled, area0->cSize);
	cv::resize(contourSeg2, contourSeg2Scaled, area0->cSize);



	contourArea0->contourMask = contourSeg0.clone();
	contourArea0->contourImg = (0, 0, 0, 0);
	contourArea0->contourImg0 = (0, 0, 0, 0);
	contourArea0->contourImg1 = (0, 0, 0, 0);
	contourArea0->contourImg2 = (0, 0, 0, 0);
	//contourImg = inputImg.clone();
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//cv::threshold(contourArea->contourMask, contourArea->contourMask, 120, 255, CV_THRESH_BINARY);
	findContours(contourArea0->contourMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	Scalar color;
	color[0] = contourOverlayColor.blue();
	color[1] = contourOverlayColor.green();
	color[2] = contourOverlayColor.red();
	color[3] = 255 * contourOverlayOpacity*0.01;
	for (int i = 0; i< contours.size(); i++)
	{
		drawContours(contourArea0->contourImg, contours, i, color, 1, 8, hierarchy, 0, Point());
		drawContours(contourArea0->contourImg0, contours, i, color, 1, 8, hierarchy, 0, Point());
	}

	contourArea0->contourMask = contourSeg1.clone();
	//contourImg = inputImg.clone();
	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	//cv::threshold(contourArea->contourMask, contourArea->contourMask, 120, 255, CV_THRESH_BINARY);
	findContours(contourArea0->contourMask, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	color[0] = contourOverlayColor1.blue();
	color[1] = contourOverlayColor1.green();
	color[2] = contourOverlayColor1.red();
	color[3] = 255 * contourOverlayOpacity1*0.01;
	for (int i = 0; i< contours1.size(); i++)
	{
		drawContours(contourArea0->contourImg, contours1, i, color, 1, 8, hierarchy1, 0, Point());
		drawContours(contourArea0->contourImg1, contours1, i, color, 1, 8, hierarchy1, 0, Point());
	}

	contourArea0->contourMask = contourSeg2.clone();
	//contourImg = inputImg.clone();
	vector<vector<Point> > contours2;
	vector<Vec4i> hierarchy2;
	//cv::threshold(contourArea->contourMask, contourArea->contourMask, 120, 255, CV_THRESH_BINARY);
	findContours(contourArea0->contourMask, contours2, hierarchy2, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	color[0] = contourOverlayColor2.blue();
	color[1] = contourOverlayColor2.green();
	color[2] = contourOverlayColor2.red();
	color[3] = 255 * contourOverlayOpacity2*0.01;
	for (int i = 0; i< contours2.size(); i++)
	{
		drawContours(contourArea0->contourImg, contours2, i, color, 1, 8, hierarchy2, 0, Point());
		drawContours(contourArea0->contourImg2, contours2, i, color, 1, 8, hierarchy2, 0, Point());
	}




	//imwrite(maskImg, segMask);
	//imwrite(fgMaskOverlay, fgMask);
	//imwrite(fgMaskOverlay1, fgMask1);
	//imwrite(fgMaskOverlay2, fgMask2);
	//imwrite(bgMaskOverlay, bgMask);
	//imwrite(contourOverlay, contourArea0->contourImg);


	//imwrite(maskImg, segMask);
	//imwrite(fgMaskOverlay, fgMask);
	//imwrite(fgMaskOverlay1, fgMask1);
	//imwrite(fgMaskOverlay2, fgMask2);
	//imwrite(bgMaskOverlay, bgMask);

	//if (ui->pushButton_cnt1->isChecked() == true)
	//{
	//	imwrite(contourOverlay, contourArea0->contourImg0);
	//}
	//else if (ui->pushButton_cnt2->isChecked() == true)
	//{
	//	imwrite(contourOverlay, contourArea0->contourImg1);
	//}
	//else if (ui->pushButton_cnt3->isChecked() == true)
	//{
	//	imwrite(contourOverlay, contourArea0->contourImg2);
	//}
	//else if (ui->pushButton_obj1->isChecked() == true)
	//{
	//	imwrite(contourOverlay, contourArea0->contourImg0);
	//}
	//else if (ui->pushButton_obj2->isChecked() == true)
	//{
	//	imwrite(contourOverlay, contourArea0->contourImg1);
	//}
	//else if (ui->pushButton_obj3->isChecked() == true)
	//{
	//	imwrite(contourOverlay, contourArea0->contourImg2);
	//}
	//else if (ui->pushButton_bkg->isChecked() == true)
	//{
	//	imwrite(contourOverlay, contourArea0->contourImg);
	//}
	//else
	//{
	//	imwrite(contourOverlay, contourArea0->contourImg);
	//}


	contours.~vector();
	hierarchy.~vector();
	contours1.~vector();
	hierarchy1.~vector();
	contours2.~vector();
	hierarchy2.~vector();


}
 
void EditMask::writeMask(char* file)
{
	typedef short							PixelType;
	typedef itk::Image<PixelType, 3>		ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;

	ReaderType::Pointer originalReader = ReaderType::New();
	typedef std::list<itk::LightObject::Pointer > RegisteredObjectsContainerType;

	RegisteredObjectsContainerType registeredIOs =
		itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
	qDebug() << registeredIOs.size();
	itk::MetaImageIOFactory::RegisterOneFactory();

	

	originalReader->SetFileName(file);
	originalReader->Update();


	ImageType::Pointer		originalPointer = originalReader->GetOutput();
	ImageType::SizeType		imgSize = originalPointer->GetLargestPossibleRegion().GetSize();
	ImageType::SpacingType	imgSpacing = originalPointer->GetSpacing();
	ImageType::IndexType    imgIndex = originalPointer->GetLargestPossibleRegion().GetIndex();
	ImageType::PointType    imgOrigin = originalPointer->GetOrigin();


	ImageType::PixelType	*originalImg = originalReader->GetOutput()->GetBufferPointer();



	typedef itk::ImageFileWriter< ImageType >  WriterType;

	WriterType::Pointer writer_mask = WriterType::New();

	ImageType::Pointer outPtr_mask = ImageType::New();
	//ImageType::SizeType outSize;
	//ImageType::SpacingType	imgSpacing;
	//ImageType::PointType    imgOrigin;
	//outSize[0] = width;
	//outSize[1] = height;
	//outSize[2] = depth;

	//imgSpacing[0] = spacing_x;
	//imgSpacing[1] = spacing_y;
	//imgSpacing[2] = spacing_z;

	//imgOrigin[0] = origin_x;
	//imgOrigin[1] = origin_y;
	//imgOrigin[2] = origin_z;

	outPtr_mask->SetRegions(imgSize);
	outPtr_mask->SetSpacing(imgSpacing);
	outPtr_mask->SetOrigin(imgOrigin);
	outPtr_mask->Allocate(true);

	ImageType::PixelType *outImg_mask = outPtr_mask->GetBufferPointer();

	//cv::resize(area->fgScribbleMask, area->objLabel, area->oSize);
	//cv::resize(area->bgScribbleMask, area->bkgLabel, area->oSize);
	//cv::resize(area->fgScribbleMask1, area->objLabel1, area->oSize);
	//cv::resize(area->fgScribbleMask2, area->objLabel2, area->oSize);

	for (int z = 0; z < depth; z++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
					outImg_mask[z*width*height + y*width + x] = originalImg[z*width*height + y*width + x];
			}
		}
	}




	writer_mask->SetFileName(maskMhd);
	writer_mask->SetInput(outPtr_mask);
	writer_mask->Update();


}

void EditMask::saveMask(char* file)
{

	

		typedef short							PixelType;
		typedef itk::Image<PixelType, 3>		ImageType;
		typedef itk::ImageFileReader<ImageType> ReaderType;

		ReaderType::Pointer originalReader = ReaderType::New();
		typedef std::list<itk::LightObject::Pointer > RegisteredObjectsContainerType;

		RegisteredObjectsContainerType registeredIOs =
			itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
		qDebug() << registeredIOs.size();
		itk::MetaImageIOFactory::RegisterOneFactory();



		originalReader->SetFileName(file);
		originalReader->Update();


		ImageType::Pointer		originalPointer = originalReader->GetOutput();
		ImageType::SizeType		imgSize = originalPointer->GetLargestPossibleRegion().GetSize();
		ImageType::SpacingType	imgSpacing = originalPointer->GetSpacing();
		ImageType::IndexType    imgIndex = originalPointer->GetLargestPossibleRegion().GetIndex();
		ImageType::PointType    imgOrigin = originalPointer->GetOrigin();



		ImageType::PixelType	*originalImg = originalReader->GetOutput()->GetBufferPointer();




		typedef itk::ImageFileWriter< ImageType >  WriterType;

		WriterType::Pointer writer_mask = WriterType::New();

		ImageType::Pointer outPtr_mask = ImageType::New();
		//ImageType::SizeType outSize;
		//ImageType::SpacingType	imgSpacing;
		//ImageType::PointType    imgOrigin;
		//outSize[0] = width;
		//outSize[1] = height;
		//outSize[2] = depth;

		//imgSpacing[0] = spacing_x;
		//imgSpacing[1] = spacing_y;
		//imgSpacing[2] = spacing_z;

		//imgOrigin[0] = origin_x;
		//imgOrigin[1] = origin_y;
		//imgOrigin[2] = origin_z;

		outPtr_mask->SetRegions(imgSize);
		outPtr_mask->SetSpacing(imgSpacing);
		outPtr_mask->SetOrigin(imgOrigin);
		outPtr_mask->Allocate(true);

		ImageType::PixelType *outImg_mask = outPtr_mask->GetBufferPointer();

		//cv::resize(area->fgScribbleMask, area->objLabel, area->oSize);
		//cv::resize(area->bgScribbleMask, area->bkgLabel, area->oSize);
		//cv::resize(area->fgScribbleMask1, area->objLabel1, area->oSize);
		//cv::resize(area->fgScribbleMask2, area->objLabel2, area->oSize);

		for (int z = 0; z < depth; z++)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
						outImg_mask[z*width*height + y*width + x] = originalImg[z*width*height + y*width + x];

				}
			}
		}



		/*for (int y = 0; y<height; y++)
		{
		for (int x = 0; x<width; x++)
		{
		if (area->objLabel.at<uchar>(y, x) == 255)
		{
		outImg_mask[str_index*height*width + y*width + x] = 2;
		}
		else if (area->bkgLabel.at<uchar>(y, x) == 255)
		{
		outImg_mask[str_index*height*width + y*width + x] = 1;
		}
		else if (area->objLabel1.at<uchar>(y, x) == 255)
		{
		outImg_mask[str_index*height*width + y*width + x] = 3;
		}
		else if (area->objLabel2.at<uchar>(y, x) == 255)
		{
		outImg_mask[str_index*height*width + y*width + x] = 4;
		}
		else
		{
		outImg_mask[str_index*height*width + y*width + x] = 0;
		}
		}
		}*/


		//for (int cur_index = (str_index - 1); cur_index >= 0;)
		//{
		//	//save to result volume
		//	for (int y = 0; y <height; y++)
		//	{
		//		for (int x = 0; x < width; x++)
		//		{
		//			outImg_mask[cur_index*height*width + y *width + x] = originalImg[cur_index*height*width + y *width + x];
		//		}
		//	}
		//	cur_index--;
		//}
		//for (int cur_index = (str_index + 1); cur_index < depth;)
		//{
		//	//save to result volume
		//	for (int y = 0; y < height; y++)
		//	{
		//		for (int x = 0; x < width; x++)
		//		{
		//			outImg_mask[cur_index*height*width + y *width + x] = originalImg[cur_index*height*width + y *width + x];
		//		}
		//	}
		//	cur_index++;
		//}


		writer_mask->SetFileName(maskMhd);
		writer_mask->SetInput(outPtr_mask);
		writer_mask->Update();


		//copyMhdFile(file, maskSaveFile);

}

void EditMask::ReloadMask()
{
	QMessageBox box;
	box.setWindowTitle(tr("Reload Mask"));
	box.setIcon(QMessageBox::Warning);
	box.setText(tr("Are you sure to discard all the changes?"));
	box.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel);
	if (box.exec() == QMessageBox::Discard)
	{
		copyMhdFile(maskOri, maskMhd);
		copyMhdFile(maskOri, maskEdit);
		ClearContourPoints();
		OverlayDisplay();
	}
}

void EditMask::ResetMask()
{
	copyMhdFile(maskNew, maskEdit);
	ClearContourPoints();
	OverlayDisplay();
}

void EditMask::ClearContourPoints()
{
	ui->pushButton_ContourOverlay_Edit_PointOrigin->setChecked(false);
	ui->pushButton_ContourOverlay_Edit_PointEnd->setChecked(false);

	contourArea0->EditContourOne_isOn = false;
	contourArea0->EditContourPointOrigin_isOn = false;
	contourArea0->EditContourPointEnd_isOn = false;

	contourArea0->contourLoop = 0;
	contourArea0->contourOriginPoint_x.swap(vector<short>());
	contourArea0->contourOriginPoint_y.swap(vector<short>());
	contourArea0->contourEndPoint_x.swap(vector<short>());
	contourArea0->contourEndPoint_y.swap(vector<short>());

	contourArea0->numPointOrigin = 0;
	contourArea0->numPointEnd = 0;

	contourArea0->image.fill(0);

	update();
}

void EditMask::ClearPainting()
{
	area0->imageObj.fill(0);
	area0->imageObj1.fill(0);
	area0->imageObj2.fill(0);
	area0->imageBkg.fill(0);
	area0->fgScribbleMask = 0;
	area0->fgScribbleMask1 = 0;
	area0->fgScribbleMask2 = 0;
	area0->bgScribbleMask = 0;
	update();
}

void EditMask::SaveResult()
{
	QString QSaveMaskFile = QFileDialog::getSaveFileName(this, "file dialog", "f:");
	qDebug() << QSaveMaskFile;
	string SSaveMaskFile = QSaveMaskFile.toStdString();
	//string SMaskFile(maskFile);
	char*saveFile = (char*)SSaveMaskFile.data();
	copyMhdFile(maskEdit, saveFile);

	QMessageBox message(QMessageBox::NoIcon, "Message", "The mask file has been saved.");
	//message.setAttribute(Qt::WA_DeleteOnClose);
	message.setIconPixmap(QPixmap("icon.png"));
	message.exec();
}

void EditMask::displayOverlays()
{
	imwrite(maskImg, segMask);
	imwrite(maskImgfg, segMaskfg);
	imwrite(maskImgfg1, segMaskfg1);
	imwrite(maskImgfg2, segMaskfg2);
	imwrite(fgMaskOverlay, fgMask);
	imwrite(fgMaskOverlay1, fgMask1);
	imwrite(fgMaskOverlay2, fgMask2);
	imwrite(bgMaskOverlay, bgMask);

	if (ui->pushButton_cnt1->isChecked() == true)
	{
		imwrite(contourOverlay, contourArea0->contourImg0);
	}
	else if (ui->pushButton_cnt2->isChecked() == true)
	{
		imwrite(contourOverlay, contourArea0->contourImg1);
	}
	/*else if (ui->pushButton_cnt3->isChecked() == true)
	{
		imwrite(contourOverlay, contourArea0->contourImg2);
	}*/
	else if (ui->pushButton_obj1->isChecked() == true)
	{
		imwrite(contourOverlay, contourArea0->contourImg0);
	}
	else if (ui->pushButton_obj2->isChecked() == true)
	{
		imwrite(contourOverlay, contourArea0->contourImg1);
	}
	/*else if (ui->pushButton_obj3->isChecked() == true)
	{
		imwrite(contourOverlay, contourArea0->contourImg2);
	}*/
	else if (ui->pushButton_bkg->isChecked() == true)
	{
		imwrite(contourOverlay, contourArea0->contourImg);
	}
	else
	{
		imwrite(contourOverlay, contourArea0->contourImg);
	}

	//imwrite(contourOverlay, contourArea0->contourImg);

	QfgMaskOverlay = QImage(fgMaskOverlay);
	QbgMaskOverlay = QImage(bgMaskOverlay);
	QfgMaskOverlay1 = QImage(fgMaskOverlay1);
	QfgMaskOverlay2 = QImage(fgMaskOverlay2);
	QcontourOverlay = QImage(contourOverlay);
	QsegMaskImg = QImage(maskImg);
	QsegMaskImgfg = QImage(maskImgfg);
	QsegMaskImgfg1 = QImage(maskImgfg1);
	QsegMaskImgfg2 = QImage(maskImgfg2);

	QfgMaskOverlayScaled = QfgMaskOverlay.scaled(qSize, Qt::KeepAspectRatio);
	QbgMaskOverlayScaled = QbgMaskOverlay.scaled(qSize, Qt::KeepAspectRatio);
	QfgMaskOverlay1Scaled = QfgMaskOverlay1.scaled(qSize, Qt::KeepAspectRatio);
	QfgMaskOverlay2Scaled = QfgMaskOverlay2.scaled(qSize, Qt::KeepAspectRatio);
	QcontourOverlayScaled = QcontourOverlay.scaled(qSize, Qt::KeepAspectRatio);
	QsegMaskImgScaled = QsegMaskImg.scaled(qSize, Qt::KeepAspectRatio);
	QsegMaskImgfgScaled = QsegMaskImgfg.scaled(qSize, Qt::KeepAspectRatio);
	QsegMaskImgfg1Scaled = QsegMaskImgfg1.scaled(qSize, Qt::KeepAspectRatio);
	QsegMaskImgfg2Scaled = QsegMaskImgfg2.scaled(qSize, Qt::KeepAspectRatio);
	/*ui.label_fgMaskOverlay->setPixmap(QPixmap::fromImage(QfgMaskOverlayScaled));
	ui.label_fgMaskOverlay->show();
	ui.label_bgMaskOverlay->setPixmap(QPixmap::fromImage(QbgMaskOverlayScaled));
	ui.label_bgMaskOverlay->show();
	ui.label_ContourOverlay->setPixmap(QPixmap::fromImage(QcontourOverlayScaled));
	ui.label_ContourOverlay->show();
	ui.label_Mask_Display->setPixmap(QPixmap::fromImage(QsegMaskImgScaled));
	ui.label_Mask_Display->show();*/

	PM_fgMaskOverlay = PM_fgMaskOverlay.fromImage(QfgMaskOverlayScaled);
	PM_bgMaskOverlay = PM_bgMaskOverlay.fromImage(QbgMaskOverlayScaled);
	PM_fgMaskOverlay1 = PM_fgMaskOverlay1.fromImage(QfgMaskOverlay1Scaled);
	PM_fgMaskOverlay2 = PM_fgMaskOverlay2.fromImage(QfgMaskOverlay2Scaled);
	PM_contourOverlay = PM_contourOverlay.fromImage(QcontourOverlayScaled);
	PM_segMaskImg = PM_segMaskImg.fromImage(QsegMaskImgScaled);
	PM_segMaskImgfg = PM_segMaskImgfg.fromImage(QsegMaskImgfgScaled);
	PM_segMaskImgfg1 = PM_segMaskImgfg1.fromImage(QsegMaskImgfg1Scaled);
	PM_segMaskImgfg2 = PM_segMaskImgfg2.fromImage(QsegMaskImgfg2Scaled);
	
	if (ui->pushButton_cnt1->isChecked() == true)
	{
		ui->label_MaskOverlay_fg->setPixmap(PM_fgMaskOverlay);
		ui->label_MaskOverlay_fg->show();
		ui->label_MaskOverlay_fg1->setPixmap(PM_fgMaskOverlay1);
		ui->label_MaskOverlay_fg1->hide();
		ui->label_MaskOverlay_fg2->setPixmap(PM_fgMaskOverlay2);
		ui->label_MaskOverlay_fg2->hide();
		ui->label_MaskOverlay_bg->setPixmap(PM_bgMaskOverlay);
		ui->label_MaskOverlay_bg->hide();
		ui->label_OriginalDisplay->setPixmap(P_inputImage);
		ui->label_OriginalDisplay->show();
		ui->label_ContourOverlay->setPixmap(PM_contourOverlay);
		ui->label_ContourOverlay->show();
		ui->label_MaskDisplay->hide();
	}
	else if (ui->pushButton_cnt2->isChecked() == true)
	{
		ui->label_MaskOverlay_fg->setPixmap(PM_fgMaskOverlay);
		ui->label_MaskOverlay_fg->hide();
		ui->label_MaskOverlay_fg1->setPixmap(PM_fgMaskOverlay1);
		ui->label_MaskOverlay_fg1->show();
		ui->label_MaskOverlay_fg2->setPixmap(PM_fgMaskOverlay2);
		ui->label_MaskOverlay_fg2->hide();
		ui->label_MaskOverlay_bg->setPixmap(PM_bgMaskOverlay);
		ui->label_MaskOverlay_bg->hide();
		ui->label_OriginalDisplay->setPixmap(P_inputImage);
		ui->label_OriginalDisplay->show();
		ui->label_ContourOverlay->setPixmap(PM_contourOverlay);
		ui->label_ContourOverlay->show();
		ui->label_MaskDisplay->hide();
	}
	/*else if (ui->pushButton_cnt3->isChecked() == true)
	{
		ui->label_MaskOverlay_fg->setPixmap(PM_fgMaskOverlay);
		ui->label_MaskOverlay_fg->hide();
		ui->label_MaskOverlay_fg1->setPixmap(PM_fgMaskOverlay1);
		ui->label_MaskOverlay_fg1->hide();
		ui->label_MaskOverlay_fg2->setPixmap(PM_fgMaskOverlay2);
		ui->label_MaskOverlay_fg2->show();
		ui->label_MaskOverlay_bg->setPixmap(PM_bgMaskOverlay);
		ui->label_MaskOverlay_bg->hide();
		ui->label_OriginalDisplay->setPixmap(P_inputImage);
		ui->label_OriginalDisplay->show();
		ui->label_ContourOverlay->setPixmap(PM_contourOverlay);
		ui->label_ContourOverlay->show();
		ui->label_MaskDisplay->hide();
	}*/
	else if (ui->pushButton_bkg->isChecked() == true)
	{
		ui->label_MaskOverlay_fg->setPixmap(PM_fgMaskOverlay);
		ui->label_MaskOverlay_fg->hide();
		ui->label_MaskOverlay_fg1->setPixmap(PM_fgMaskOverlay1);
		ui->label_MaskOverlay_fg1->hide();
		ui->label_MaskOverlay_fg2->setPixmap(PM_fgMaskOverlay2);
		ui->label_MaskOverlay_fg2->hide();
		ui->label_MaskOverlay_bg->setPixmap(PM_bgMaskOverlay);
		ui->label_MaskOverlay_bg->show();
		ui->label_OriginalDisplay->setPixmap(P_inputImage);
		ui->label_OriginalDisplay->show();
		ui->label_ContourOverlay->setPixmap(PM_contourOverlay);
		ui->label_ContourOverlay->hide();
		ui->label_MaskDisplay->hide();
	}
	else if (ui->pushButton_obj1->isChecked() == true)
	{
		ui->label_MaskOverlay_fg->setPixmap(PM_fgMaskOverlay);
		ui->label_MaskOverlay_fg->show();
		ui->label_MaskOverlay_fg1->setPixmap(PM_fgMaskOverlay1);
		ui->label_MaskOverlay_fg1->hide();
		ui->label_MaskOverlay_fg2->setPixmap(PM_fgMaskOverlay2);
		ui->label_MaskOverlay_fg2->hide();
		ui->label_MaskOverlay_bg->setPixmap(PM_bgMaskOverlay);
		ui->label_MaskOverlay_bg->hide();
		ui->label_OriginalDisplay->setPixmap(P_inputImage);
		ui->label_OriginalDisplay->show();
		ui->label_ContourOverlay->setPixmap(PM_contourOverlay);
		ui->label_ContourOverlay->hide();
		ui->label_MaskDisplay->hide();
	}
	else if (ui->pushButton_obj2->isChecked() == true)
	{
		ui->label_MaskOverlay_fg->setPixmap(PM_fgMaskOverlay);
		ui->label_MaskOverlay_fg->hide();
		ui->label_MaskOverlay_fg1->setPixmap(PM_fgMaskOverlay1);
		ui->label_MaskOverlay_fg1->show();
		ui->label_MaskOverlay_fg2->setPixmap(PM_fgMaskOverlay2);
		ui->label_MaskOverlay_fg2->hide();
		ui->label_MaskOverlay_bg->setPixmap(PM_bgMaskOverlay);
		ui->label_MaskOverlay_bg->hide();
		ui->label_OriginalDisplay->setPixmap(P_inputImage);
		ui->label_OriginalDisplay->show();
		ui->label_ContourOverlay->setPixmap(PM_contourOverlay);
		ui->label_ContourOverlay->hide();
		ui->label_MaskDisplay->hide();
	}
	/*else if (ui->pushButton_obj3->isChecked() == true)
	{
		ui->label_MaskOverlay_fg->setPixmap(PM_fgMaskOverlay);
		ui->label_MaskOverlay_fg->hide();
		ui->label_MaskOverlay_fg1->setPixmap(PM_fgMaskOverlay1);
		ui->label_MaskOverlay_fg1->hide();
		ui->label_MaskOverlay_fg2->setPixmap(PM_fgMaskOverlay2);
		ui->label_MaskOverlay_fg2->show();
		ui->label_MaskOverlay_bg->setPixmap(PM_bgMaskOverlay);
		ui->label_MaskOverlay_bg->hide();
		ui->label_OriginalDisplay->setPixmap(P_inputImage);
		ui->label_OriginalDisplay->show();
		ui->label_ContourOverlay->setPixmap(PM_contourOverlay);
		ui->label_ContourOverlay->hide();
		ui->label_MaskDisplay->hide();
	}*/
	else
	{
		ui->label_MaskOverlay_fg->setPixmap(PM_fgMaskOverlay);
		ui->label_MaskOverlay_fg->show();
		ui->label_MaskOverlay_fg1->setPixmap(PM_fgMaskOverlay1);
		ui->label_MaskOverlay_fg1->show();
		ui->label_MaskOverlay_fg2->setPixmap(PM_fgMaskOverlay2);
		ui->label_MaskOverlay_fg2->show();
		ui->label_MaskOverlay_bg->setPixmap(PM_bgMaskOverlay);
		ui->label_MaskOverlay_bg->show();
		ui->label_OriginalDisplay->setPixmap(P_inputImage);
		ui->label_OriginalDisplay->show();
		ui->label_ContourOverlay->setPixmap(PM_contourOverlay);
		ui->label_ContourOverlay->show();
		ui->label_MaskDisplay->hide();
	}

	
}

void EditMask::changeStartIndex()
{
	//if (area0->setLabels == 1)
	//{
	//	if (ui.checkBox_LoadLabels->isChecked() == false)
	//	{
	//		writeLabels(maskFile);
	//	}
	//	else
	//	{
	//		writeLabels(labelCopyFile);
	//	}
	//}
	/*area->setLabels = 0;*/

	str_index = ui->verticalScrollBar_ScribbleImage->value() - 1;
	QString index = QString::number(str_index + 1);
	ui->label_ScribbleImage_ValueOfSliceNumber_Value->setText(index);
	//ui.label_Mask_ValueOfSliceNumber_Value->setText(index);
	//ui.label_MaskOverlay_ValueOfSliceNumber_Value->setText(index);
	//ui.label_ContourOverlay_ValueOfSliceNumber_Value->setText(index);

	ui->label_ScribbleImage_ValueOfSliceNumber_Value->setText(index);

	vStrImg.swap(vector<short>());


	//for (int y = 0; y < height; y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{
	//		//vROI.push_back(1);
	//		vStrSeg.push_back(1);
	//	}
	//}
	readImage();

	InputDisplay();



	//area->select = Rect(0, 0, width, height);
	//clearAll();
	//area->imageROI.fill(0);
	OverlayDisplay();
	//ui.verticalScrollBar_Mask->setValue(str_index+1);
	//ui.verticalScrollBar_MaskOverlay->setValue(str_index+1);
	//ui.verticalScrollBar_ContourOverlay->setValue(str_index+1);
	update();
}


void EditMask::originalSize()
{

	ui->label_ZoomValue->setText(QString(" %1 %").arg(QString::number(100)));
	ui->horizontalSlider_zoom->setValue(100);
	QScribbleImg = QImage(imgFileName);

	qSize = oSize;
	QScribbleImgScaled = QScribbleImg;

	P_inputImage = P_inputImage.fromImage(QScribbleImgScaled);

	ui->label_OriginalDisplay->setPixmap(P_inputImage);
	ui->label_OriginalDisplay->show();
	displayOverlays();
	int x = QScribbleImgScaled.width();
	int y = QScribbleImgScaled.height();
	ui->scrollArea_ScribbleArea->setGeometry(0.5*(ui->scrollArea_ContourOverlay->width() - x), 0.5*(ui->scrollArea_ContourOverlay->height() - y), x, y);
	ui->scrollArea_EditContourArea->setGeometry(0.5*(ui->scrollArea_ContourOverlay->width() - x), 0.5*(ui->scrollArea_ContourOverlay->height() - y), x, y);

	zoomInfactor = 1;
	area0->zoomInfactor = zoomInfactor;
	contourArea0->zoomInfactor = zoomInfactor;

	area0->qSize = qSize;
	area0->cSize.width = ui->horizontalSlider_zoom->value()*0.01*area0->oSize.width;
	area0->cSize.height = ui->horizontalSlider_zoom->value()*0.01*area0->oSize.height;
	area0->scaleImage();

	contourArea0->qSize = qSize;
	contourArea0->scaleImage();
}

void EditMask::fit_Image()
{

	//QScribbleImgScaled = QScribbleImg.scaled(ui.label_ScribbleImage_Display->size(), Qt::KeepAspectRatio);
	////  imgScaled = img.QImage::scaled(ui->imagelabel->width(),ui->imagelabel->height(),Qt::KeepAspectRatio);
	//ui.label_ScribbleImage_Display->setPixmap(QPixmap::fromImage(QScribbleImgScaled));
	//ui.label_OriginalDisplay->setPixmap(QPixmap::fromImage(QScribbleImgScaled));

	//QfgMaskOverlayScaled = QfgMaskOverlay.scaled(ui.label_MaskOverlay_fg->size(), Qt::KeepAspectRatio);
	//QfgMaskOverlay1Scaled = QfgMaskOverlay.scaled(ui.label_MaskOverlay_fg1->size(), Qt::KeepAspectRatio);
	//QfgMaskOverlay2Scaled = QfgMaskOverlay.scaled(ui.label_MaskOverlay_fg2->size(), Qt::KeepAspectRatio);
	//QbgMaskOverlayScaled = QbgMaskOverlay.scaled(ui.label_MaskOverlay_bg->size(), Qt::KeepAspectRatio);
	//QcontourOverlayScaled = QcontourOverlay.scaled(ui.label_ContourOverlay->size(), Qt::KeepAspectRatio);
	//QsegMaskImgScaled = QsegMaskImg.scaled(ui.label_MaskDisplay->size(), Qt::KeepAspectRatio);

	//qSize.width = ui.label_ScribbleImage_Display->size().width;


	//ui.label_MaskOverlay_fg->setPixmap(QPixmap::fromImage(QfgMaskOverlayScaled));
	//ui.label_MaskOverlay_bg->setPixmap(QPixmap::fromImage(QbgMaskOverlayScaled));
	//ui.label_ContourOverlay->setPixmap(QPixmap::fromImage(QcontourOverlayScaled));
	//ui.label_MaskDisplay->setPixmap(QPixmap::fromImage(QsegMaskImgScaled));

	//area->imageROI = area->imageROI.scaled(ui.label_ScribbleImage_Display->size(), Qt::KeepAspectRatio);
	//area->imageObj = area->imageObj.scaled(ui.label_ScribbleImage_Display->size(), Qt::KeepAspectRatio);
	//area->imageBkg = area->imageBkg.scaled(ui.label_ScribbleImage_Display->size(), Qt::KeepAspectRatio);
	//area->imageNotes= area->imageNotes.scaled(ui.label_ScribbleImage_Display->size(), Qt::KeepAspectRatio);


	int a = ui->label_OriginalDisplay->width();
	int b = oSize.width();
	int value = (100 * a) / b;
	a = ui->label_OriginalDisplay->height();
	b = oSize.height();
	int value0 = (100 * a) / b;
	if (value > value0)
	{
		value = value0;
	}
	ui->label_ZoomValue->setText(QString(" %1 %").arg(QString::number(value)));
	ui->horizontalSlider_zoom->setValue(value);
	InputDisplay();
	displayOverlays();
	int x = QScribbleImgScaled.width();
	int y = QScribbleImgScaled.height();
	ui->scrollArea_ScribbleArea->setGeometry(0.5*(ui->scrollArea_ContourOverlay->width() - x), 0.5*(ui->scrollArea_ContourOverlay->height() - y), x, y);
	ui->scrollArea_EditContourArea->setGeometry(0.5*(ui->scrollArea_ContourOverlay->width() - x), 0.5*(ui->scrollArea_ContourOverlay->height() - y), x, y);

	zoomInfactor = ui->horizontalSlider_zoom->value()*0.01;
	area0->zoomInfactor = zoomInfactor;
	contourArea0->zoomInfactor = zoomInfactor;

	area0->qSize = qSize;
	area0->cSize.width = ui->horizontalSlider_zoom->value()*0.01*area0->oSize.width;
	area0->cSize.height = ui->horizontalSlider_zoom->value()*0.01*area0->oSize.height;
	area0->scaleImage();

	contourArea0->qSize = qSize;
	contourArea0->scaleImage();

}

void EditMask::zoom()
{
	int value = ui->horizontalSlider_zoom->value();
	ui->label_ZoomValue->setText(QString(" %1 %").arg(QString::number(value)));
	InputDisplay();
	displayOverlays();
	int x = QScribbleImgScaled.width();
	int y = QScribbleImgScaled.height();
	ui->scrollArea_ScribbleArea->setGeometry(0.5*(ui->scrollArea_ContourOverlay->width() - x), 0.5*(ui->scrollArea_ContourOverlay->height() - y), x, y);
	ui->scrollArea_EditContourArea->setGeometry(0.5*(ui->scrollArea_ContourOverlay->width() - x), 0.5*(ui->scrollArea_ContourOverlay->height() - y), x, y);

	zoomInfactor = ui->horizontalSlider_zoom->value()*0.01;
	area0->zoomInfactor = zoomInfactor;
	contourArea0->zoomInfactor = zoomInfactor;

	area0->qSize = qSize;
	area0->cSize.width = ui->horizontalSlider_zoom->value()*0.01*area0->oSize.width;
	area0->cSize.height = ui->horizontalSlider_zoom->value()*0.01*area0->oSize.height;
	area0->scaleImage();

	contourArea0->qSize = qSize;
	contourArea0->scaleImage();
}



void EditMask::readImage()
{
	vStrImg.swap(vector<short>());
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			short pixel;
			pixel = vImage[str_index * height * width + y * width + x];
			vStrImg.push_back(pixel);
		}
	}

	img3D_2D(vStrImg, str_index, imgFileName);

	if (init(imgFileName) == -1)
	{
		cout << "Could not initialize" << endl;
		//return -1;
	}



}



void EditMask::EditContour_one()
{

	contourArea0->EditContourOne_isOn = true;
	contourArea0->contourLoop = 0;
	contourArea0->One_isDone = 0;
	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_obj_isOn = false;
	area0->pushButton_bkg_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;
	//ui.pushButton_Select->setChecked(false);
	//ui.pushButton_ROI->setChecked(false);
	//ui.pushButton_obj->setChecked(false);
	//ui.pushButton_bkg->setChecked(false);
	//ui.pushButton_Notes->setChecked(false);
	//ui.pushButton_Eraser->setChecked(false);
	contourArea0->contourOriginPoint_x.swap(vector<short>());
	contourArea0->contourOriginPoint_y.swap(vector<short>());
	contourArea0->contourEndPoint_x.swap(vector<short>());
	contourArea0->contourEndPoint_y.swap(vector<short>());

	//for (int i = 1; i > 0;)
	//{
	//	int key = 0;
	//	switch (contourArea->One_isDone)
	//	{
	//	case '1':
	//	{
	//				contourArea->image.fill(0);
	//				morphing(contourArea->contourLoop, 10, 10);
	//				OverlayDisplay();
	//				contourArea->One_isDone = false;
	//				break;
	//	}
	//	
	//	}
	//}



}

void EditMask::EditContour_PointOrigin()
{
	ui->pushButton_ContourOverlay_Edit_PointEnd->setChecked(false);
	contourArea0->EditContourOne_isOn = false;

	contourArea0->EditContourPointEnd_isOn = false;
	contourArea0->contourLoop = 0;
	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_obj_isOn = false;
	area0->pushButton_obj1_isOn = false;
	area0->pushButton_obj2_isOn = false;
	area0->pushButton_bkg_isOn = false;
	area0->pushButton_Notes_isOn = false; 
	area0->pushButton_Eraser_isOn = false;
	//ui.pushButton_Select->setChecked(false);
	//ui.pushButton_ROI->setChecked(false);
	//ui.pushButton_obj->setChecked(false);
	//ui.pushButton_bkg->setChecked(false);
	//ui.pushButton_Notes->setChecked(false);
	//ui.pushButton_Eraser->setChecked(false);

	if (ui->pushButton_cnt1->isChecked() == false && ui->pushButton_cnt2->isChecked() == false)
	{
		ui->pushButton_cnt1->setChecked(true);
		pushButton_cnt1_onclick();
		ui->pushButton_ContourOverlay_Edit_PointOrigin->setChecked(true);
		contourArea0->EditContourPointOrigin_isOn = true;

	}
	if (ui->pushButton_ContourOverlay_Edit_PointOrigin->isChecked()==true)
	{
		contourArea0->EditContourPointOrigin_isOn = true;
	}
	else
	{
		contourArea0->EditContourPointOrigin_isOn = false;
	}
}

void EditMask::EditContour_PointEnd()
{
	ui->pushButton_ContourOverlay_Edit_PointOrigin->setChecked(false);
	contourArea0->EditContourOne_isOn = false;
	contourArea0->EditContourPointOrigin_isOn = false;

	contourArea0->contourLoop = 0;
	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_obj_isOn = false;
	area0->pushButton_obj1_isOn = false;
	area0->pushButton_obj2_isOn = false;
	area0->pushButton_bkg_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;
	//ui.pushButton_Select->setChecked(false);
	//ui.pushButton_ROI->setChecked(false);
	//ui.pushButton_obj->setChecked(false);
	//ui.pushButton_bkg->setChecked(false);
	//ui.pushButton_Notes->setChecked(false);
	//ui.pushButton_Eraser->setChecked(false);

	if (ui->pushButton_cnt1->isChecked() == false && ui->pushButton_cnt2->isChecked() == false)
	{
		ui->pushButton_cnt1->setChecked(true);
		pushButton_cnt1_onclick();
		ui->pushButton_ContourOverlay_Edit_PointEnd->setChecked(true);
		contourArea0->EditContourPointEnd_isOn = true;
	}
	if (ui->pushButton_ContourOverlay_Edit_PointEnd->isChecked() == true)
	{
		contourArea0->EditContourPointEnd_isOn = true;
	}
	else
	{
		contourArea0->EditContourPointEnd_isOn = false;
	}
}

void EditMask::EditContour()
{
	copyMhdFile(maskEdit, maskNew);
	typedef short							PixelType;
	typedef itk::Image<PixelType, 3>		ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;

	ReaderType::Pointer originalReader = ReaderType::New();
	typedef std::list<itk::LightObject::Pointer > RegisteredObjectsContainerType;

	RegisteredObjectsContainerType registeredIOs =
		itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
	qDebug() << registeredIOs.size();
	itk::MetaImageIOFactory::RegisterOneFactory();



	originalReader->SetFileName(maskEdit);
	originalReader->Update();


	ImageType::Pointer		originalPointer = originalReader->GetOutput();
	ImageType::SizeType		imgSize = originalPointer->GetLargestPossibleRegion().GetSize();
	ImageType::SpacingType	imgSpacing = originalPointer->GetSpacing();
	ImageType::IndexType    imgIndex = originalPointer->GetLargestPossibleRegion().GetIndex();
	ImageType::PointType    imgOrigin = originalPointer->GetOrigin();



	ImageType::PixelType	*originalImg = originalReader->GetOutput()->GetBufferPointer();




	typedef itk::ImageFileWriter< ImageType >  WriterType;

	WriterType::Pointer writer_mask = WriterType::New();

	ImageType::Pointer outPtr_mask = ImageType::New();
	//ImageType::SizeType outSize;
	//ImageType::SpacingType	imgSpacing;
	//ImageType::PointType    imgOrigin;
	//outSize[0] = width;
	//outSize[1] = height;
	//outSize[2] = depth;

	//imgSpacing[0] = spacing_x;
	//imgSpacing[1] = spacing_y;
	//imgSpacing[2] = spacing_z;

	//imgOrigin[0] = origin_x;
	//imgOrigin[1] = origin_y;
	//imgOrigin[2] = origin_z;

	outPtr_mask->SetRegions(imgSize);
	outPtr_mask->SetSpacing(imgSpacing);
	outPtr_mask->SetOrigin(imgOrigin);
	outPtr_mask->Allocate(true);

	ImageType::PixelType *outImg_mask = outPtr_mask->GetBufferPointer();

	//cv::resize(area->fgScribbleMask, area->objLabel, area->oSize);
	//cv::resize(area->bgScribbleMask, area->bkgLabel, area->oSize);
	//cv::resize(area->fgScribbleMask1, area->objLabel1, area->oSize);
	//cv::resize(area->fgScribbleMask2, area->objLabel2, area->oSize);

	//for (int z = 0; z < depth; z++)
	//{
	//	for (int y = 0; y < height; y++)
	//	{
	//		for (int x = 0; x < width; x++)
	//		{
	//			outImg_mask[z*width*height + y*width + x] = originalImg[z*width*height + y*width + x];

	//		}
	//	}
	//}





	
	contourArea0->EditContourOne_isOn = false;
	contourArea0->EditContourPointOrigin_isOn = false;
	contourArea0->EditContourPointEnd_isOn = false;
	
	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_obj_isOn = false;
	area0->pushButton_obj1_isOn = false;
	area0->pushButton_obj2_isOn = false;
	area0->pushButton_bkg_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;
	//ui.pushButton_Select->setChecked(false);
	//ui.pushButton_ROI->setChecked(false);
	//ui.pushButton_obj->setChecked(false);
	//ui.pushButton_bkg->setChecked(false);
	//ui.pushButton_Notes->setChecked(false);
	//ui.pushButton_Eraser->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_One->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_PointOrigin->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_PointEnd->setChecked(false);

	contourArea0->image.fill(0);
	if (contourArea0->contourLoop==0)
	{
		if (contourArea0->numPointOrigin <= contourArea0->numPointEnd)
			contourArea0->contourLoop = contourArea0->numPointOrigin;
		if (contourArea0->numPointOrigin > contourArea0->numPointEnd)
			contourArea0->contourLoop = contourArea0->numPointEnd;
	}
	morphing(contourArea0->contourLoop, 20, 20);
    contourArea0->contourLoop = 0;
	contourArea0->numPointOrigin = 0;
	contourArea0->numPointEnd = 0;


	cv::resize(bgMask, bgMaskScaled, area0->cSize);
	cv::resize(fgMask, fgMaskScaled, area0->cSize);
	cv::resize(fgMask1, fgMask1Scaled, area0->cSize);
	cv::resize(fgMask2, fgMask2Scaled, area0->cSize);

	contourSeg0 = 0;
	contourSeg1 = 0;
	contourSeg2 = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x< width; x++)
		{
			if ((uchar)bgMask.at<Vec4b>(y, x)[3] == 0)
			{
				contourSeg0.at<uchar>(y, x) = 0;
				contourSeg1.at<uchar>(y, x) = 0;
				contourSeg2.at<uchar>(y, x) = 0;
				outImg_mask[str_index*width*height + y*width + x] = 0;

			}
			 if ((uchar)fgMask.at<Vec4b>(y, x)[3] != 0)
			{

				contourSeg0.at<uchar>(y, x) = 255;
				outImg_mask[str_index*width*height + y*width + x] = 2;
			}
			else if ((uchar)fgMask1.at<Vec4b>(y, x)[3] != 0)
			{
				contourSeg1.at<uchar>(y, x) = 255;
				outImg_mask[str_index*width*height + y*width + x] = 3;
			}
			else if ((uchar)fgMask2.at<Vec4b>(y, x)[3] != 0)
			{
				contourSeg2.at<uchar>(y, x) = 255;
				outImg_mask[str_index*width*height + y*width + x] = 4;
			}
		}
	}
	for (int cur_index = (str_index - 1); cur_index >= 0;)
	{
		//save to result volume
		for (int y = 0; y <height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				outImg_mask[cur_index*height*width + y *width + x] = originalImg[cur_index*height*width + y *width + x];
			}
		}
		cur_index--;
	}
	for (int cur_index = (str_index + 1); cur_index < depth;)
	{
		//save to result volume
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				outImg_mask[cur_index*height*width + y *width + x] = originalImg[cur_index*height*width + y *width + x];
			}
		}
		cur_index++;
	}

	writer_mask->SetFileName(maskEdit);
	writer_mask->SetInput(outPtr_mask);
	writer_mask->Update();

	cv::resize(contourSeg0, contourSeg0Scaled, area0->cSize);
	cv::resize(contourSeg1, contourSeg1Scaled, area0->cSize);
	cv::resize(contourSeg2, contourSeg2Scaled, area0->cSize);



	contourArea0->contourMask = contourSeg0.clone();
	contourArea0->contourImg = (0, 0, 0, 0);
	contourArea0->contourImg0 = (0, 0, 0, 0);
	contourArea0->contourImg1 = (0, 0, 0, 0);
	contourArea0->contourImg2 = (0, 0, 0, 0);
	//contourImg = inputImg.clone();
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//cv::threshold(contourArea->contourMask, contourArea->contourMask, 120, 255, CV_THRESH_BINARY);
	findContours(contourArea0->contourMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	Scalar color;
	color[0] = contourOverlayColor.blue();
	color[1] = contourOverlayColor.green();
	color[2] = contourOverlayColor.red();
	color[3] = 255 * contourOverlayOpacity*0.01;
	for (int i = 0; i< contours.size(); i++)
	{
		drawContours(contourArea0->contourImg, contours, i, color, 1, 8, hierarchy, 0, Point());
		drawContours(contourArea0->contourImg0, contours, i, color, 1, 8, hierarchy, 0, Point());
	}

	contourArea0->contourMask = contourSeg1.clone();
	//contourImg = inputImg.clone();
	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	//cv::threshold(contourArea->contourMask, contourArea->contourMask, 120, 255, CV_THRESH_BINARY);
	findContours(contourArea0->contourMask, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	color[0] = contourOverlayColor1.blue();
	color[1] = contourOverlayColor1.green();
	color[2] = contourOverlayColor1.red();
	color[3] = 255 * contourOverlayOpacity1*0.01;
	for (int i = 0; i< contours1.size(); i++)
	{
		drawContours(contourArea0->contourImg, contours1, i, color, 1, 8, hierarchy1, 0, Point());
		drawContours(contourArea0->contourImg1, contours1, i, color, 1, 8, hierarchy1, 0, Point());
	}

	contourArea0->contourMask = contourSeg2.clone();
	//contourImg = inputImg.clone();
	vector<vector<Point> > contours2;
	vector<Vec4i> hierarchy2;
	//cv::threshold(contourArea->contourMask, contourArea->contourMask, 120, 255, CV_THRESH_BINARY);
	findContours(contourArea0->contourMask, contours2, hierarchy2, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	color[0] = contourOverlayColor2.blue();
	color[1] = contourOverlayColor2.green();
	color[2] = contourOverlayColor2.red();
	color[3] = 255 * contourOverlayOpacity2*0.01;
	for (int i = 0; i< contours2.size(); i++)
	{
		drawContours(contourArea0->contourImg, contours2, i, color, 1, 8, hierarchy2, 0, Point());
		drawContours(contourArea0->contourImg2, contours2, i, color, 1, 8, hierarchy2, 0, Point());
	}




	contours.~vector();
	hierarchy.~vector();
	contours1.~vector();
	hierarchy1.~vector();
	contours2.~vector();
	hierarchy2.~vector();

	/*for (int y = 0; y<height; y++)
	{
	for (int x = 0; x<width; x++)
	{
	if (area->objLabel.at<uchar>(y, x) == 255)
	{
	outImg_mask[str_index*height*width + y*width + x] = 2;
	}
	else if (area->bkgLabel.at<uchar>(y, x) == 255)
	{
	outImg_mask[str_index*height*width + y*width + x] = 1;
	}
	else if (area->objLabel1.at<uchar>(y, x) == 255)
	{
	outImg_mask[str_index*height*width + y*width + x] = 3;
	}
	else if (area->objLabel2.at<uchar>(y, x) == 255)
	{
	outImg_mask[str_index*height*width + y*width + x] = 4;
	}
	else
	{
	outImg_mask[str_index*height*width + y*width + x] = 0;
	}
	}
	}*/



	ui->pushButton_ContourOverlay_Edit_PointEnd->setChecked(false);
	ui->pushButton_ContourOverlay_Edit_PointOrigin->setChecked(false);
	displayOverlays();
}

void EditMask::EditPainting()
{
	typedef short							PixelType;
	typedef itk::Image<PixelType, 3>		ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;

	ReaderType::Pointer originalReader = ReaderType::New();
	typedef std::list<itk::LightObject::Pointer > RegisteredObjectsContainerType;

	RegisteredObjectsContainerType registeredIOs =
		itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
	qDebug() << registeredIOs.size();
	itk::MetaImageIOFactory::RegisterOneFactory();

	originalReader->SetFileName(maskEdit);
	originalReader->Update();

	ImageType::Pointer		originalPointer = originalReader->GetOutput();
	ImageType::SizeType		imgSize = originalPointer->GetLargestPossibleRegion().GetSize();
	ImageType::SpacingType	imgSpacing = originalPointer->GetSpacing();
	ImageType::IndexType    imgIndex = originalPointer->GetLargestPossibleRegion().GetIndex();
	ImageType::PointType    imgOrigin = originalPointer->GetOrigin();

	ImageType::PixelType	*originalImg = originalReader->GetOutput()->GetBufferPointer();



	typedef itk::ImageFileWriter< ImageType >  WriterType;

	WriterType::Pointer writer_mask = WriterType::New();

	ImageType::Pointer outPtr_mask = ImageType::New();
	//ImageType::SizeType outSize;
	//ImageType::SpacingType	imgSpacing;
	//ImageType::PointType    imgOrigin;
	//outSize[0] = width;
	//outSize[1] = height;
	//outSize[2] = depth;

	//imgSpacing[0] = spacing_x;
	//imgSpacing[1] = spacing_y;
	//imgSpacing[2] = spacing_z;

	//imgOrigin[0] = origin_x;
	//imgOrigin[1] = origin_y;
	//imgOrigin[2] = origin_z;

	outPtr_mask->SetRegions(imgSize);
	outPtr_mask->SetSpacing(imgSpacing);
	outPtr_mask->SetOrigin(imgOrigin);
	outPtr_mask->Allocate(true);

	ImageType::PixelType *outImg_mask = outPtr_mask->GetBufferPointer();

	cv::resize(area0->fgScribbleMask, area0->objLabel, area0->oSize);
	cv::resize(area0->bgScribbleMask, area0->bkgLabel, area0->oSize);
	cv::resize(area0->fgScribbleMask1, area0->objLabel1, area0->oSize);
	cv::resize(area0->fgScribbleMask2, area0->objLabel2, area0->oSize);


	if (ui->pushButton_obj1->isChecked() == true)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (area0->objLabel.at<uchar>(y, x) == 255)
				{
					outImg_mask[str_index*height*width + y*width + x] = 2;
				}
				else
				{
					outImg_mask[str_index*height*width + y*width + x] = originalImg[str_index*height*width + y*width + x];
				}
			}
		}
	}
	else if (ui->pushButton_obj2->isChecked() == true)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (area0->objLabel1.at<uchar>(y, x) == 255)
				{
					outImg_mask[str_index*height*width + y*width + x] = 3;
				}
				else
				{
					outImg_mask[str_index*height*width + y*width + x] = originalImg[str_index*height*width + y*width + x];
				}
			}
		}
	}
	/*else if (ui->pushButton_obj3->isChecked() == true)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (area0->objLabel2.at<uchar>(y, x) == 255)
				{
					outImg_mask[str_index*height*width + y*width + x] = 4;
				}
				else
				{
					outImg_mask[str_index*height*width + y*width + x] = originalImg[str_index*height*width + y*width + x];
				}
			}
		}
	}*/
	else if (ui->pushButton_bkg->isChecked() == true)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (area0->bkgLabel.at<uchar>(y, x) == 255)
				{
					outImg_mask[str_index*height*width + y*width + x] = 0;
				}
				else
				{
					outImg_mask[str_index*height*width + y*width + x] = originalImg[str_index*height*width + y*width + x];
				}
			}
		}
	}


	for (int cur_index = (str_index - 1); cur_index >= 0;)
	{
		//save to result volume
		for (int y = 0; y <height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				outImg_mask[cur_index*height*width + y *width + x] = originalImg[cur_index*height*width + y *width + x];
			}
		}
		cur_index--;
	}
	for (int cur_index = (str_index + 1); cur_index < depth;)
	{
		//save to result volume
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				outImg_mask[cur_index*height*width + y *width + x] = originalImg[cur_index*height*width + y *width + x];
			}
		}
		cur_index++;
	}


	writer_mask->SetFileName(maskEdit);
	writer_mask->SetInput(outPtr_mask);
	writer_mask->Update();

	ClearPainting();
	OverlayDisplay();
}


void EditMask::SaveChanges()
{
	copyMhdFile(maskEdit, maskMhd);
	
	QMessageBox message(QMessageBox::NoIcon, "Message", "The changes had been saved.");
	//message.setAttribute(Qt::WA_DeleteOnClose);
	message.setIconPixmap(QPixmap("icon.png"));
	message.exec();
}

//void EditMask::SaveObjectsChanges()
//{
//	typedef short							PixelType;
//	typedef itk::Image<PixelType, 3>		ImageType;
//	typedef itk::ImageFileReader<ImageType> ReaderType;
//
//	ReaderType::Pointer originalReader = ReaderType::New();
//	typedef std::list<itk::LightObject::Pointer > RegisteredObjectsContainerType;
//
//	RegisteredObjectsContainerType registeredIOs =
//		itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
//	qDebug() << registeredIOs.size();
//	itk::MetaImageIOFactory::RegisterOneFactory();
//
//
//
//	originalReader->SetFileName(maskEdit);
//	originalReader->Update();
//
//
//	ImageType::Pointer		originalPointer = originalReader->GetOutput();
//	ImageType::SizeType		imgSize = originalPointer->GetLargestPossibleRegion().GetSize();
//	ImageType::SpacingType	imgSpacing = originalPointer->GetSpacing();
//	ImageType::IndexType    imgIndex = originalPointer->GetLargestPossibleRegion().GetIndex();
//	ImageType::PointType    imgOrigin = originalPointer->GetOrigin();
//
//
//
//	ImageType::PixelType	*originalImg = originalReader->GetOutput()->GetBufferPointer();
//
//
//
//
//	typedef itk::ImageFileWriter< ImageType >  WriterType;
//
//	WriterType::Pointer writer_mask = WriterType::New();
//
//	ImageType::Pointer outPtr_mask = ImageType::New();
//	//ImageType::SizeType outSize;
//	//ImageType::SpacingType	imgSpacing;
//	//ImageType::PointType    imgOrigin;
//	//outSize[0] = width;
//	//outSize[1] = height;
//	//outSize[2] = depth;
//
//	//imgSpacing[0] = spacing_x;
//	//imgSpacing[1] = spacing_y;
//	//imgSpacing[2] = spacing_z;
//
//	//imgOrigin[0] = origin_x;
//	//imgOrigin[1] = origin_y;
//	//imgOrigin[2] = origin_z;
//
//	outPtr_mask->SetRegions(imgSize);
//	outPtr_mask->SetSpacing(imgSpacing);
//	outPtr_mask->SetOrigin(imgOrigin);
//	outPtr_mask->Allocate(true);
//
//	ImageType::PixelType *outImg_mask = outPtr_mask->GetBufferPointer();
//
//	//cv::resize(area->fgScribbleMask, area->objLabel, area->oSize);
//	//cv::resize(area->bgScribbleMask, area->bkgLabel, area->oSize);
//	//cv::resize(area->fgScribbleMask1, area->objLabel1, area->oSize);
//	//cv::resize(area->fgScribbleMask2, area->objLabel2, area->oSize);
//
//	//for (int z = 0; z < depth; z++)
//	//{
//	//	for (int y = 0; y < height; y++)
//	//	{
//	//		for (int x = 0; x < width; x++)
//	//		{
//	//			outImg_mask[z*width*height + y*width + x] = originalImg[z*width*height + y*width + x];
//
//	//		}
//	//	}
//	//}
//
//
//
//	for (int y = 0; y<height; y++)
//	{
//	for (int x = 0; x<width; x++)
//	{
//		if ((uchar)bgMask.at<Vec4b>(y, x)[3] ==0)
//	{
//	   outImg_mask[str_index*height*width + y*width + x] = 0;
//	}
//		else if ((uchar)fgMask.at<Vec4b>(y, x)[3] > 0)
//	{
//	outImg_mask[str_index*height*width + y*width + x] = 2;
//	}
//		else if ((uchar)fgMask1.at<Vec4b>(y, x)[3] > 0)
//	{
//	outImg_mask[str_index*height*width + y*width + x] = 3;
//	}
//		else if ((uchar)fgMask2.at<Vec4b>(y, x)[3] > 0)
//	{
//	outImg_mask[str_index*height*width + y*width + x] = 4;
//	}
//	/*else
//	{
//	outImg_mask[str_index*height*width + y*width + x] = 0;
//	}*/
//	}
//	}
//
//
//	for (int cur_index = (str_index - 1); cur_index >= 0;)
//	{
//		//save to result volume
//		for (int y = 0; y <height; y++)
//		{
//			for (int x = 0; x < width; x++)
//			{
//				outImg_mask[cur_index*height*width + y *width + x] = originalImg[cur_index*height*width + y *width + x];
//			}
//		}
//		cur_index--;
//	}
//	for (int cur_index = (str_index + 1); cur_index < depth;)
//	{
//		//save to result volume
//		for (int y = 0; y < height; y++)
//		{
//			for (int x = 0; x < width; x++)
//			{
//				outImg_mask[cur_index*height*width + y *width + x] = originalImg[cur_index*height*width + y *width + x];
//			}
//		}
//		cur_index++;
//	}
//
//
//	writer_mask->SetFileName(maskNew);
//	writer_mask->SetInput(outPtr_mask);
//	writer_mask->Update();
//
//	QMessageBox message(QMessageBox::NoIcon, "Message", "The changes has been saved.");
//	//message.setAttribute(Qt::WA_DeleteOnClose);
//	message.setIconPixmap(QPixmap("icon.png"));
//	message.exec();
//	//copyMhdFile(file, maskSaveFile);
//}

void EditMask::morphing(int Feat_num, double Div_x, double Div_y) {
	float px1[100], py1[100];
	float px2[100], py2[100];
	float distance_x[100];
	float distance_y[100];

	int wi = (int)Div_x, hi = (int)Div_y;
	float size_w = (float)(width / Div_x), size_h = (float)(height / Div_y);
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

	//Bitmap ^ bm = (Bitmap ^)(pictureBox4->Image);
	//Bitmap ^ bm2 = (Bitmap ^)(pictureBox3->Image);


	for (int Loop1 = 1; Loop1 <= Feat_num; Loop1++){
		/* px1[Loop1 - 1] = (float)Xi[Loop1] / (width / (float)Div_x);
		py1[Loop1 - 1] = (float)Yi[Loop1] / (height / (float)Div_y);
		px2[Loop1 - 1] = (float)Xi[Loop1 + (int)Feat_num] / (width / (float)Div_x);
		py2[Loop1 - 1] = (float)Yi[Loop1 + (int)Feat_num] / (height / (float)Div_y);*/

		px1[Loop1 - 1] = (float)contourArea0->contourOriginPoint_x[Loop1 - 1] / (width / (float)Div_x);
		py1[Loop1 - 1] = (float)contourArea0->contourOriginPoint_y[Loop1 - 1] / (height / (float)Div_y);
		px2[Loop1 - 1] = (float)contourArea0->contourEndPoint_x[Loop1 - 1] / (width / (float)Div_x);
		py2[Loop1 - 1] = (float)contourArea0->contourEndPoint_y[Loop1 - 1] / (height / (float)Div_y);


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
					if (ui->pushButton_cnt1->isChecked() == true)
					{
						pixel = segMaskfg.at<uchar>(left, top);
					}
					else if (ui->pushButton_cnt2->isChecked() == true)
					{
						pixel = segMaskfg1.at<uchar>(left, top);
					}
					/*else if (ui->pushButton_cnt3->isChecked() == true)
					{
						pixel = segMaskfg2.at<uchar>(left, top);
					}*/
					
					/*if (left == original_y&&top == original_x){  }
					else
					{
					cout << left <<"&"<<top<< endl;
					cout << original_y << "&" << original_x << endl;
					}*/

					//cout << pixel << endl;
					
						contourArea0->maskTemp.at<uchar>(original_y, original_x) = pixel;
		

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
	contourArea0->contourLoop = 0;
	contourArea0->contourOriginPoint_x.swap(vector<short>());
	contourArea0->contourOriginPoint_y.swap(vector<short>());
	contourArea0->contourEndPoint_x.swap(vector<short>());
	contourArea0->contourEndPoint_y.swap(vector<short>());
	if (ui->pushButton_cnt1->isChecked() == true)
	{
		segMaskfg = contourArea0->maskTemp.clone();
		contourArea0->contourMask = segMaskfg.clone();
		contourArea0->contourImg0 = (0, 0, 0, 0);
	}
	else if (ui->pushButton_cnt2->isChecked() == true)
	{
		segMaskfg1 = contourArea0->maskTemp.clone();
		contourArea0->contourMask = segMaskfg1.clone();
		contourArea0->contourImg1 = (0, 0, 0, 0);
	}
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
	segShowImg = inputImg.clone();
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(contourArea0->contourMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(0, 255, 0, 255);
		if (ui->pushButton_cnt1->isChecked() == true)
		{
			drawContours(contourArea0->contourImg0, contours, i, color, 1, 8, hierarchy, 0, Point());
		}
		else if (ui->pushButton_cnt2->isChecked() == true)
		{
			drawContours(contourArea0->contourImg1, contours, i, color, 1, 8, hierarchy, 0, Point());
		}
		/*else if (ui->pushButton_cnt3->isChecked() == true)
		{
			drawContours(contourArea0->contourImg2, contours, i, color, 1, 8, hierarchy, 0, Point());
		}*/
	}
	//vStrSeg.swap(vector<short>());

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (ui->pushButton_cnt1->isChecked() == true)
			{
				if (segMaskfg.at<uchar>(y, x) == 255)
				{
					segMaskfg1.at<uchar>(y, x) = 0;
					segMaskfg2.at<uchar>(y, x) = 0;
					(uchar)fgMask.at<Vec4b>(y, x)[3] = fgOverlayOpacity*0.01*255;
					(uchar)fgMask.at<Vec4b>(y, x)[0] = fgOverlayColor.blue();
					(uchar)fgMask.at<Vec4b>(y, x)[1] = fgOverlayColor.green();
					(uchar)fgMask.at<Vec4b>(y, x)[2] = fgOverlayColor.red();
					(uchar)fgMask1.at<Vec4b>(y, x)[3] = 0;
					(uchar)fgMask2.at<Vec4b>(y, x)[3] = 0;
					(uchar)bgMask.at<Vec4b>(y, x)[3] = 0;

					////(uchar)segShowImg.at<Vec3b>(y, x)[2] = 200;
					//(uchar)fgMask.at<Vec4b>(y, x)[3] = 255;
					//(uchar)fgMask.at<Vec4b>(y, x)[2] = 255;
				}
				else
				{
					(uchar)fgMask.at<Vec4b>(y, x)[3] = 0;
					(uchar)bgMask.at<Vec4b>(y, x)[3] = bgOverlayOpacity*0.01 * 255;


				}
			}
			else if (ui->pushButton_cnt2->isChecked() == true)
			{
				if (segMaskfg1.at<uchar>(y, x) == 255)
				{
					segMaskfg.at<uchar>(y, x) = 0;
					segMaskfg2.at<uchar>(y, x) = 0;
					(uchar)fgMask1.at<Vec4b>(y, x)[3] = fgOverlayOpacity1*0.01 * 255;
					(uchar)fgMask1.at<Vec4b>(y, x)[0] = fgOverlayColor1.blue();
					(uchar)fgMask1.at<Vec4b>(y, x)[1] = fgOverlayColor1.green();
					(uchar)fgMask.at<Vec4b>(y, x)[2] = fgOverlayColor.red();
					(uchar)fgMask.at<Vec4b>(y, x)[3] = 0;
					(uchar)fgMask2.at<Vec4b>(y, x)[3] = 0;
					(uchar)bgMask.at<Vec4b>(y, x)[3] = 0;

					////(uchar)segShowImg.at<Vec3b>(y, x)[2] = 200;
					//(uchar)fgMask.at<Vec4b>(y, x)[3] = 255;
					//(uchar)fgMask.at<Vec4b>(y, x)[2] = 255;
				}
				else
				{
					(uchar)fgMask1.at<Vec4b>(y, x)[3] = 0;
					(uchar)bgMask.at<Vec4b>(y, x)[3] = bgOverlayOpacity*0.01 * 255;
				}
			}
			//else if (ui->pushButton_cnt3->isChecked() == true)
			//{
			//	if (segMaskfg2.at<uchar>(y, x) == 255)
			//	{
			//		segMaskfg1.at<uchar>(y, x) = 0;
			//		segMaskfg.at<uchar>(y, x) = 0;
			//		(uchar)fgMask2.at<Vec4b>(y, x)[3] = fgOverlayOpacity*0.01 * 255;
			//		(uchar)fgMask2.at<Vec4b>(y, x)[0] = fgOverlayColor2.blue();
			//		(uchar)fgMask2.at<Vec4b>(y, x)[1] = fgOverlayColor2.green();
			//		(uchar)fgMask2.at<Vec4b>(y, x)[2] = fgOverlayColor2.red();
			//		(uchar)fgMask1.at<Vec4b>(y, x)[3] = 0;
			//		(uchar)fgMask.at<Vec4b>(y, x)[3] = 0;
			//		(uchar)bgMask.at<Vec4b>(y, x)[3] = 0;

			//		////(uchar)segShowImg.at<Vec3b>(y, x)[2] = 200;
			//		//(uchar)fgMask.at<Vec4b>(y, x)[3] = 255;
			//		//(uchar)fgMask.at<Vec4b>(y, x)[2] = 255;
			//	}
			//	else
			//	{
			//		(uchar)fgMask2.at<Vec4b>(y, x)[3] = 0;
			//		(uchar)bgMask.at<Vec4b>(y, x)[3] = bgOverlayOpacity*0.01 * 255;
			//	}
			//}
			
		}
	}


	//imshow("Contour Mask", contourMask);
	/*imshow("Contour Image", contourArea->contourImg);
	imshow("Segmentation Mask", segMask);
	imshow("Segmentation Image", segShowImg);*/
	//imshow("Mask Temp", maskTemp);
	//imshow("Segmentation Mask", segMask);
}

void EditMask::closeEvent(QCloseEvent *event)
{
	QMessageBox box;
		box.setWindowTitle(tr("Use new mask"));
		box.setIcon(QMessageBox::Question);
		box.setText(tr("Do you want to use the new mask which you have edited?"));
		box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		if (box.exec() == QMessageBox::No)
		{
			copyMhdFile(maskOri, maskMhd);
		}
}


void EditMask::pushButton_cnt1_onclick()
{
	ui->scrollArea_ScribbleArea->hide();
	ui->scrollArea_EditContourArea->show();
	//ui->pushButton_cnt1->setChecked(false);
	ui->pushButton_cnt2->setChecked(false);
	//ui->pushButton_cnt3->setChecked(false);
	ui->pushButton_bkg->setChecked(false);
	ui->pushButton_obj1->setChecked(false);
	ui->pushButton_obj2->setChecked(false);
	//ui->pushButton_obj3->setChecked(false);
	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_bkg_isOn = false;
	area0->pushButton_obj_isOn = false;
	area0->pushButton_obj1_isOn = false;
	area0->pushButton_obj2_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;
	ClearContourPoints();
	ClearPainting();
	displayOverlays();
}

void EditMask::pushButton_cnt2_onclick()
{
	ui->scrollArea_ScribbleArea->hide();
	ui->scrollArea_EditContourArea->show();
	ui->pushButton_cnt1->setChecked(false);
	//ui->pushButton_cnt2->setChecked(false);
	//ui->pushButton_cnt3->setChecked(false);
	ui->pushButton_bkg->setChecked(false);
	ui->pushButton_obj1->setChecked(false);
	ui->pushButton_obj2->setChecked(false);
	//ui->pushButton_obj3->setChecked(false);
	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_bkg_isOn = false;
	area0->pushButton_obj_isOn = false;
	area0->pushButton_obj1_isOn = false;
	area0->pushButton_obj2_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;
	ClearContourPoints();
	ClearPainting();
	displayOverlays();
}

//void EditMask::pushButton_cnt3_onclick()
//{
//	ui->scrollArea_ScribbleArea->hide();
//	ui->scrollArea_EditContourArea->show();
//	ui->pushButton_cnt1->setChecked(false);
//	ui->pushButton_cnt2->setChecked(false);
//	//ui->pushButton_cnt3->setChecked(false);
//	ui->pushButton_bkg->setChecked(false);
//	ui->pushButton_obj1->setChecked(false);
//	ui->pushButton_obj2->setChecked(false);
//	//ui->pushButton_obj3->setChecked(false);
//	area0->pushButton_Select_isOn = false;
//	area0->pushButton_ROI_isOn = false;
//	area0->pushButton_bkg_isOn = false;
//	area0->pushButton_obj_isOn = false;
//	area0->pushButton_obj1_isOn = false;
//	area0->pushButton_obj2_isOn = false;
//	area0->pushButton_Notes_isOn = false;
//	area0->pushButton_Eraser_isOn = false;
//	ClearContourPoints();
//	ClearPainting();
//	displayOverlays();
//}

void EditMask::pushButton_bkg_onclick()
{
	ui->scrollArea_ScribbleArea->show();
	ui->scrollArea_EditContourArea->hide();
	ui->pushButton_cnt1->setChecked(false);
	ui->pushButton_cnt2->setChecked(false);
	//ui->pushButton_cnt3->setChecked(false);
	//ui->pushButton_bkg->setChecked(false);
	ui->pushButton_obj1->setChecked(false);
	ui->pushButton_obj2->setChecked(false);
	//ui->pushButton_obj3->setChecked(false);

	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_obj_isOn = false;
	if (ui->pushButton_bkg->isChecked() == true)
	{
		area0->pushButton_bkg_isOn = true;
	}
	else
	{
		area0->pushButton_bkg_isOn = false;
	}
	area0->pushButton_obj1_isOn = false;
	area0->pushButton_obj2_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;

	contourArea0->EditContourOne_isOn = false;
	contourArea0->EditContourPointOrigin_isOn = false;
	contourArea0->EditContourPointEnd_isOn = false;
	//ui.pushButton_ContourOverlay_Edit_One->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_PointOrigin->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_PointEnd->setChecked(false);

	/*QPalette palette = ui.textBrowser->palette();
	palette.setColor(QPalette::Base, area->objBrushColor);
	ui.textBrowser->setPalette(palette);

	QString size = QString::number(area->objBrushRadius);
	ui.lineEdit_BrushSize->setText(size);

	ui.horizontalSlider_Brush_BrushSize->setValue(area->objBrushRadius);

	QString opacity = QString::number(area->objBrushOpacity);
	ui.lineEdit_Brush_Opacity->setText(opacity);

	ui.horizontalSlider_Brush_Opacity->setValue(area->objBrushOpacity);*/


	ClearContourPoints();
	ClearPainting();
	update();

	displayOverlays();
}

void EditMask::pushButton_obj1_onclick()
{
	if (ui->pushButton_obj1->isChecked() == true)
	{
		ui->scrollArea_ScribbleArea->show();	
		ui->scrollArea_EditContourArea->hide();
	}
	
	ui->pushButton_cnt1->setChecked(false);
	ui->pushButton_cnt2->setChecked(false);
	//ui->pushButton_cnt3->setChecked(false);
	ui->pushButton_bkg->setChecked(false);
	
	//ui->pushButton_obj1->setChecked(false);
	ui->pushButton_obj2->setChecked(false);
	//ui->pushButton_obj3->setChecked(false);

	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	if (ui->pushButton_obj1->isChecked() == true)
	{
		area0->pushButton_obj_isOn = true;
	}
	else
	{
		area0->pushButton_obj_isOn = false;
	}

	area0->pushButton_bkg_isOn = false;
	area0->pushButton_obj1_isOn = false;
	area0->pushButton_obj2_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;

	contourArea0->EditContourOne_isOn = false;
	contourArea0->EditContourPointOrigin_isOn = false;
	contourArea0->EditContourPointEnd_isOn = false;
	//ui.pushButton_ContourOverlay_Edit_One->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_PointOrigin->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_PointEnd->setChecked(false);

	/*QPalette palette = ui.textBrowser->palette();
	palette.setColor(QPalette::Base, area->objBrushColor);
	ui.textBrowser->setPalette(palette);

	QString size = QString::number(area->objBrushRadius);
	ui.lineEdit_BrushSize->setText(size);

	ui.horizontalSlider_Brush_BrushSize->setValue(area->objBrushRadius);

	QString opacity = QString::number(area->objBrushOpacity);
	ui.lineEdit_Brush_Opacity->setText(opacity);

	ui.horizontalSlider_Brush_Opacity->setValue(area->objBrushOpacity);*/

	/*cv::resize(area0->fgScribbleMask, area0->objLabel, area0->oSize);
	cv::resize(area0->bgScribbleMask, area0->bkgLabel, area0->oSize);
	cv::resize(area0->fgScribbleMask1, area0->objLabel1, area0->oSize);
	cv::resize(area0->fgScribbleMask2, area0->objLabel2, area0->oSize);
	for (int y = 0; y<height; y++)
	{
		for (int x = 0; x<width; x++)
		{
			if (area0->objLabel.at<uchar>(y, x) == 255)
			{
				fgMask.at<uchar>(y, x) = 255;
			}
			else if (area0->bkgLabel.at<uchar>(y, x) == 255)
			{
				bgMask.at<uchar>(y, x) = 255;
			}
			else if (area0->objLabel1.at<uchar>(y, x) == 255)
			{
				fgMask1.at<uchar>(y, x) = 255;
			}
			else if (area0->objLabel2.at<uchar>(y, x) == 255)
			{
				fgMask2.at<uchar>(y, x) = 255;
			}
		
		}
	}*/

	ClearContourPoints();
	ClearPainting();
	update();
	displayOverlays();
}

void EditMask::pushButton_obj2_onclick()
{
	ui->scrollArea_ScribbleArea->show();
	ui->scrollArea_EditContourArea->hide();
	ui->pushButton_cnt1->setChecked(false);
	ui->pushButton_cnt2->setChecked(false);
	//ui->pushButton_cnt3->setChecked(false);
	ui->pushButton_bkg->setChecked(false);
	ui->pushButton_obj1->setChecked(false);
	//ui->pushButton_obj2->setChecked(false);
	//ui->pushButton_obj3->setChecked(false);

	area0->pushButton_Select_isOn = false;
	area0->pushButton_ROI_isOn = false;
	area0->pushButton_obj_isOn = false;
	area0->pushButton_bkg_isOn = false;
	if (ui->pushButton_obj2->isChecked() == true)
	{
		area0->pushButton_obj1_isOn = true;
	}
	else
	{
		area0->pushButton_obj1_isOn = false;
	}
	area0->pushButton_obj2_isOn = false;
	area0->pushButton_Notes_isOn = false;
	area0->pushButton_Eraser_isOn = false;

	contourArea0->EditContourOne_isOn = false;
	contourArea0->EditContourPointOrigin_isOn = false;
	contourArea0->EditContourPointEnd_isOn = false;
	//ui.pushButton_ContourOverlay_Edit_One->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_PointOrigin->setChecked(false);
	//ui.pushButton_ContourOverlay_Edit_PointEnd->setChecked(false);

	/*QPalette palette = ui.textBrowser->palette();
	palette.setColor(QPalette::Base, area->objBrushColor);
	ui.textBrowser->setPalette(palette);

	QString size = QString::number(area->objBrushRadius);
	ui.lineEdit_BrushSize->setText(size);

	ui.horizontalSlider_Brush_BrushSize->setValue(area->objBrushRadius);

	QString opacity = QString::number(area->objBrushOpacity);
	ui.lineEdit_Brush_Opacity->setText(opacity);

	ui.horizontalSlider_Brush_Opacity->setValue(area->objBrushOpacity);*/
	/*cv::resize(area0->fgScribbleMask, area0->objLabel, area0->oSize);
	cv::resize(area0->bgScribbleMask, area0->bkgLabel, area0->oSize);
	cv::resize(area0->fgScribbleMask1, area0->objLabel1, area0->oSize);
	cv::resize(area0->fgScribbleMask2, area0->objLabel2, area0->oSize);
	for (int y = 0; y<height; y++)
	{
		for (int x = 0; x<width; x++)
		{
			if (area0->objLabel.at<uchar>(y, x) == 255)
			{
				fgMask.at<uchar>(y, x) = 255;
			}
			else if (area0->bkgLabel.at<uchar>(y, x) == 255)
			{
				bgMask.at<uchar>(y, x) = 255;
			}
			else if (area0->objLabel1.at<uchar>(y, x) == 255)
			{
				fgMask1.at<uchar>(y, x) = 255;
			}
			else if (area0->objLabel2.at<uchar>(y, x) == 255)
			{
				fgMask2.at<uchar>(y, x) = 255;
			}

		}
	}*/

	ClearContourPoints();
	ClearPainting();
	update();
	displayOverlays();
}

//void EditMask::pushButton_obj3_onclick()
//{
//	ui->scrollArea_ScribbleArea->show();
//	ui->scrollArea_EditContourArea->hide();
//	ui->pushButton_cnt1->setChecked(false);
//	ui->pushButton_cnt2->setChecked(false);
//	//ui->pushButton_cnt3->setChecked(false);
//	ui->pushButton_bkg->setChecked(false);
//	ui->pushButton_obj1->setChecked(false);
//	ui->pushButton_obj2->setChecked(false);
//	//ui->pushButton_obj3->setChecked(false);
//
//	area0->pushButton_Select_isOn = false;
//	area0->pushButton_ROI_isOn = false;
//	area0->pushButton_obj_isOn = false;
//	area0->pushButton_bkg_isOn = false;
//	area0->pushButton_obj1_isOn = false;
//	/*if (ui->pushButton_obj3->isChecked() == true)
//	{
//		area0->pushButton_obj2_isOn = true;
//	}
//	else
//	{
//		area0->pushButton_obj2_isOn = false;
//	}*/
//	area0->pushButton_obj2_isOn = false;
//	area0->pushButton_Notes_isOn = false;
//	area0->pushButton_Eraser_isOn = false;
//
//	contourArea0->EditContourOne_isOn = false;
//	contourArea0->EditContourPointOrigin_isOn = false;
//	contourArea0->EditContourPointEnd_isOn = false;
//	//ui.pushButton_ContourOverlay_Edit_One->setChecked(false);
//	//ui.pushButton_ContourOverlay_Edit_PointOrigin->setChecked(false);
//	//ui.pushButton_ContourOverlay_Edit_PointEnd->setChecked(false);
//
//	/*QPalette palette = ui.textBrowser->palette();
//	palette.setColor(QPalette::Base, area->objBrushColor);
//	ui.textBrowser->setPalette(palette);
//
//	QString size = QString::number(area->objBrushRadius);
//	ui.lineEdit_BrushSize->setText(size);
//
//	ui.horizontalSlider_Brush_BrushSize->setValue(area->objBrushRadius);
//
//	QString opacity = QString::number(area->objBrushOpacity);
//	ui.lineEdit_Brush_Opacity->setText(opacity);
//
//	ui.horizontalSlider_Brush_Opacity->setValue(area->objBrushOpacity);*/
//	/*cv::resize(area0->fgScribbleMask, area0->objLabel, area0->oSize);
//	cv::resize(area0->bgScribbleMask, area0->bkgLabel, area0->oSize);
//	cv::resize(area0->fgScribbleMask1, area0->objLabel1, area0->oSize);
//	cv::resize(area0->fgScribbleMask2, area0->objLabel2, area0->oSize);
//	for (int y = 0; y<height; y++)
//	{
//		for (int x = 0; x<width; x++)
//		{
//			if (area0->objLabel.at<uchar>(y, x) == 255)
//			{
//				fgMask.at<uchar>(y, x) = 255;
//			}
//			else if (area0->bkgLabel.at<uchar>(y, x) == 255)
//			{
//				bgMask.at<uchar>(y, x) = 255;
//			}
//			else if (area0->objLabel1.at<uchar>(y, x) == 255)
//			{
//				fgMask1.at<uchar>(y, x) = 255;
//			}
//			else if (area0->objLabel2.at<uchar>(y, x) == 255)
//			{
//				fgMask2.at<uchar>(y, x) = 255;
//			}
//
//		}
//	}*/
//
//	ClearContourPoints();
//	ClearPainting();
//	update();
//	displayOverlays();
//}



void EditMask::changeSize_obj1()
{
	QString size = QString::number(ui->horizontalSlider_obj1->value());
	ui->lineEdit_obj1->setText(size);
	area0->objBrushRadius = ui->horizontalSlider_obj1->value();
	update();
}

void EditMask::changeSize_obj2()
{
	QString size = QString::number(ui->horizontalSlider_obj2->value());
	ui->lineEdit_obj2->setText(size);
	area0->obj1BrushRadius = ui->horizontalSlider_obj2->value();
	update();
}

//void EditMask::changeSize_obj3()
//{
//	QString size = QString::number(ui->horizontalSlider_obj3->value());
//	ui->lineEdit_obj3->setText(size);
//	area0->obj2BrushRadius = ui->horizontalSlider_obj3->value();
//	update();
//}

void EditMask::changeSize_bkg()
{
	QString size = QString::number(ui->horizontalSlider_bkg->value());
	ui->lineEdit_bkg->setText(size);
	area0->bkgBrushRadius = ui->horizontalSlider_bkg->value();
	update();
}

void EditMask::setSize_obj1()
{
	QString value = ui->lineEdit_obj1->text();
	int size = value.toInt();
	ui->horizontalSlider_obj1->setValue(size);
	area0->objBrushRadius = size;
}

void EditMask::setSize_obj2()
{
	QString value = ui->lineEdit_obj2->text();
	int size = value.toInt();
	ui->horizontalSlider_obj2->setValue(size);
	area0->obj1BrushRadius = size;
}

//void EditMask::setSize_obj3()
//{
//	QString value = ui->lineEdit_obj3->text();
//	int size = value.toInt();
//	ui->horizontalSlider_obj3->setValue(size);
//	area0->obj2BrushRadius = size;
//}

void EditMask::setSize_bkg()
{
	QString value = ui->lineEdit_bkg->text();
	int size = value.toInt();
	ui->horizontalSlider_bkg->setValue(size);
	area0->bkgBrushRadius = size;
}