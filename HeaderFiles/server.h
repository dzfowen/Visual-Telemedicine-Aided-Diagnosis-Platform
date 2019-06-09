#ifndef SERVER_H
#define SERVER_H

#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL)

#include <QtWidgets/QMainWindow>
#include "ui_server.h"
#include "vtkDistanceWidget.h"
#include "vtkResliceImageViewerMeasurements.h"
#include "vtkSmartPointer.h"
#include "vtkImagePlaneWidget.h"
#include "QtWidgets/QInputDialog"
#include <map>
#include "lacewing.h"
#include "MyThread.h"
#include "httpThread_x.h"
#include "httpThread_y.h"
#include "httpThread_z.h"
#include "httpThread_xyz.h"
#include "tcpThread_x.h"
#include "tcpThread_y.h"
#include "tcpThread_z.h"
#include "tcpThread_xyz.h"

#include "audioThread.h"
//////YY////
//#include "editmask.h"
//////2017.5.28////
#include "tcpConnThread_x.h"
#include "Segmentation.h"
#include "VtkReader.h"
#include "mhdReader.h"
#include "Segmentation.h"
#include "DicomReader.h"

#include "mainSocketThread.h"
#include "vtkMyMarkCallback.h"
#include "createWindowScreenshot.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QSplitter>
#include "pluginbutton.h"
#include "plugincombobox.h"
#include "pluginlineedit.h"
#include "Plugin.h"

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

////YY////
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp> 

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
// Software Guide : BeginCodeSnippet
#include "itkCannySegmentationLevelSetImageFilter.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
// Software Guide : EndCodeSnippet

#include "itkFastMarchingImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkZeroCrossingImageFilter.h"


using namespace std;
using namespace cv;

////2016.12.23////

#define SERVERNAME "server"
#define SCREENSHOT_TIME 10		//the ms of screenshot send time

#define MarkLineNumServer 4

class Server : public QMainWindow
{
	Q_OBJECT

public:
	Server(QWidget *parent = 0); //QWideget is the base of all ui classes
	~Server();

	void MhdToJpg();
	mainSocketThread * mainSockTread;
	enum WinName{ winName_x, winName_y, winName_z, winName_xyz };

	/*
		Update by YaoTaihang	2016-01-13
		This part is the statement for the mark Line
		It contains callback function and line Polydata
	*/
	vtkSmartPointer< vtkMyMarkCallback > markCallback[MarkLineNumServer];  //two classes of vtk
	vector<vtkSmartPointer<vtkPolygonalLineData>> allPolygonalLines[MarkLineNumServer];	

	//////////YY//////////

	vector <int> allPolygonalColor[MarkLineNumServer];
	vector <int> allPolygonalWidth[MarkLineNumServer];

	/////2016.12.23/////

	//This is the Collection for 4 widget
	vector<QVTKWidget*> UiWidgetCollection;

	FileAPI *fileAPI;
	string mhdFileName;
	string labelFileName;
	Ui::ServerClass GetUI();

	std::vector<int> _widget_groups; //to place widget_group ints;
	QVector<QSplitter*> _splitters; //splitters for group layouts;

	//About Plugin Widghts
	int TransformButtons(Plugin* plugin, Button *button); //Transform button_struct to qt's pushbutton for one plugin
	int TransformComboBoxs(Plugin* plugin, ComboBox *combobox);
	int TransformLineEdits(Plugin* plugin, LineEdit *lineedit);

	int AddPluginToSplitters(Plugin* plugin);

	//Add PluginWidget
	template<class PluginWidget>
	int AddPluginWidgetsToSplitter(QVector<PluginWidget*>widgets, QSplitter *splitter);
	
	template<class PluginWidget>
	int AddPluginWidgetsToSplitters(QVector<PluginWidget*>widgets);
	///YY///
	void Edit();
	///2017.5.28///
private:
	Ui::ServerClass ui;

	struct Data
	{
		float position_x;
		float position_y;
		float position_z;
		float focalpoint_x;
		float focalpoint_y;
		float focalpoint_z;
		float viewup_x;
		float viewup_y;
		float viewup_z;
		float slice_x;
		float slice_y;
		float slice_z;
	};

	tcpThread_x* tcpthread_x;
	tcpThread_y* tcpthread_y;
	tcpThread_z* tcpthread_z;
	tcpThread_xyz* tcpthread_xyz;

	httpThread_x* httpthread_x;
	httpThread_y* httpthread_y;
	httpThread_z* httpthread_z;
	httpThread_xyz* httpthread_xyz;
	///////YY/////
	//EditMask *edition;
	//QColor fgOverlayColor = Qt::red;
	//QColor bgOverlayColor = Qt::blue;
	//QColor fgOverlayColor1 = QColor(0, 255, 255, 255);
	//QColor fgOverlayColor2 = QColor(255, 0, 255, 255);
	//QColor contourOverlayColor = Qt::green;
	//QColor contourOverlayColor1 = QColor(0, 255, 255, 255);
	//QColor contourOverlayColor2 = QColor(255, 0, 255, 255);

	//int fgOverlayOpacity = 20;
	//int bgOverlayOpacity = 20;
	//int fgOverlayOpacity1 = 20;
	//int fgOverlayOpacity2 = 20;
	//int contourOverlayOpacity = 80;
	//int contourOverlayOpacity1 = 80;
	//int contourOverlayOpacity2 = 80;
	///////2017.5.28////
	
	
	audioThread* audiothread;

	createWindowScreenshot * windowScreenshotCreater;//2016-11-6

	QTimer *screenshot_timer;	//timeor for screenshot 

	char path[100];		//opened file path
	int BrushSize[4];	//Define brush size for 4 kinds of brush

	int currentWinForScreenshot;

	//two scrill control pointers
	char* serverMakeCurScrollBarMessage();
	char* serverMakeMaxScrollBarMessage();
	void serverBroadCastCurScrollBar();
	void serverBroadCastMaxScrollBar();
	void serverInitMarkLineCallBack();

	//plugin 12.13
	QString _plugin_folder;
	//QStringList _plugin_names_loaded;
	QStringList _plugin_names;
	std::vector<PluginInterfaceProvider*> providers;
	QVector<Plugin*> _plugins; //Plugins Vector
	//PluginInterface *_plugin;
	pluma::Pluma pluma;
	int LoadPluginFromIniPath(QString ini_path);
	Plugin *_now_plugin;

	int SearchPluginFolder();

protected:
	void dragEnterEvent(QDragEnterEvent *e);
	void dropEvent(QDropEvent *e);

	vtkSmartPointer< vtkResliceImageViewer > riw[3];

private slots:
	void on_actionOpen_Scence_triggered();
	void on_actionQuit_triggered();
	void chooseChannel();
	void hide_1();
	void hide_2();
	void hide_3();
	void hide_4();
	void showall();
	 
	void refresh_x(Data);
	void refresh_y(Data);
	void refresh_z(Data);
	void refresh_xyz(Data);

	void refresh_lb_size(int);
	void refresh_slider_size(int);

	void getControl();
	void server_SendChannelCount(char*);

	void screenshotFlagChange();
	void screenshotBroadCast();
	void server_screenshotEventSet(char*);
	void server_MarkLineEventSet(char*);

	void audioThreadFlagChange();
	//void audioStart();
	void server_ChangeWinForScreenshot(char*);
	void serverChangeScreenshotWin(int);
	
	//void serverChangeScreenshotWin3D(int); //’º‰∆ 2016-11-14

	void server_ChangeScrollBar(char*);
	void serverScrollBar0Move(int);
	void serverScrollBarXMove(int);
	void serverScrollBarYMove(int);
	void serverScrollBarZMove(int);

	void server_GetNewUserConnect(char*);

	void btnBrushClicked();
	void resetColorForMarkLine(int);
	void resetWidthForMarkLine(int);
	void btnClearClicked();

	void server_GetRequestForChangeAudioFlag(char*);
	void server_GetRequestForChangeMarkFlag(char*);

	void server_GetRequestForMarkClear();

	void server_GetRequestForGetPluginList(char*);
	void server_GetRequestForUsePlugin(char*, char*);
	void server_GetRequestForOperatePlugin(char*, char*, char*);

	void server_GetRequestForSaveLabel(char*);

	void server_GetRequestForOriginalPoint(char*);
	void server_GetRequestForNewPoint(char*);
	void server_GetRequestForEditMask(char*);
	//void server_GetRequestForCoordinate(char*);
	/*
	Update by ’º‰∆	2016-11-14
	This is the connect for 3D show
	*/
	void btn3DClicked();

	//2016-11-16
	void audioplay();

	//use to add one plugin from a plugin folder with a ini file
	int AddOnePluginClicked();

	//use to call function when one button from plugin is clicked
	//NOTICE now only support void prarmeter and int return value
	//for more kinds of use, contact us to add new function
	int OneButtonAddedClicked();

	void SaveLabelFile();

	////YY////
	void getLabelFile();
	////2016.12.23////
	void saveOriginalPoint();
	void saveNewPoint();
};

#endif // SERVER_H
