using namespace std;

#include "server.h"
#include <qfiledialog.h>
#include <qdebug.h>
#include <qpalette.h>
#include <string.h>
#include <DataFile.h>

#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkImageViewer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkCamera.h>
#include <QDebug>
#include <QMutex>
#include <vtkRendererCollection.h>
#include <QPalette>
#include <time.h>
#include <qtimer.h>

#include <windows.h>
#include <WINSOCK2.H>
#include <stdio.h>

#include "createWindowScreenshot.h"

#include <QMessageBox>

#include <QSplitter>
#include <Pluma\Pluma.hpp>

#pragma comment(lib,"ws2_32.lib")

Server *this_server;

int availablechannel = 0;
Service* current_service;

extern Service* service1;
extern Service* service2;
extern Service* service3;
extern Service* service4;

extern string filePath = "";  //保存文件路径的全局变量

float slice_0 = 0;
float slice_x = 0;
float slice_y = 0;
float slice_z = 0;

int recv_mask = 2; //1 represent do not receive label image, 0 represent received label image.


string GetNowOpenFile()
{
	return this_server->mhdFileName;
}
string GetNowLabelFile()
{
	string labelfile = this_server->labelFileName;
	//return labelfile;
	qDebug() << "labelfile" << labelfile.c_str();
	return this_server->labelFileName;
}

std::vector<int> unique_element_in_vector(std::vector<int> v){
	std::vector<int>::iterator vector_iterator;
	sort(v.begin(), v.end());
	vector_iterator = unique(v.begin(), v.end());
	if (vector_iterator != v.end()){
		v.erase(vector_iterator, v.end());
	}
	return v;
}

int find_element_index_in_vector(std::vector<int> v, int element)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (element == v[i])
			return i;
	}
	return -1;
}

void SendNewOpenFileAndDisplay(std::string filename)
{
	this_server->mhdFileName = filename;

	string mhdFileName_raw = this_server->mhdFileName.substr(0, this_server->mhdFileName.find_last_of(".")) + ".raw";
	DataFile* mhdFile = new DataFile(this_server->mhdFileName);
	DataFile* mhdFile_raw = new DataFile(mhdFileName_raw);
	service1->filedir[mhdFile->Name()] = mhdFile;
	service1->filedir[mhdFile_raw->Name()] = mhdFile_raw;
	mhdReader* mhd = new mhdReader();
	this_server->mhdFileName = mhdFile->getPath();
	mhd->Read_Display(mhdFile->getPath(), this_server->GetUI());
}

Ui::ServerClass Server::GetUI()
{
	return this->ui;
}

Server::Server(QWidget *parent)
	: QMainWindow(parent)
{
	this_server = this;

	ui.setupUi(this);// 设置窗口

	//File API
	this->fileAPI = new FileAPI;
	fileAPI->GetNowOpenFile = GetNowOpenFile;
	fileAPI->GetNowLabelFile = GetNowLabelFile;
	fileAPI->SendNewOpenFileAndDisplay = SendNewOpenFileAndDisplay;
	SearchPluginFolder();
	//////YY////
	//edition = new EditMask;
	//////2017.5.28////
	qRegisterMetaType<Data>("Data");
	//设置了每一个service的tcp和http接口
	service1 = new Service(0, this->ui.qvtkWidget_x); 
	service2 = new Service(1, this->ui.qvtkWidget_y);
	service3 = new Service(2, this->ui.qvtkWidget_z);
	service4 = new Service(3, this->ui.qvtkWidget_xyz);
	//初始化tcp和http的连接
	tcpthread_x = new tcpThread_x();
	tcpthread_y = new tcpThread_y();
	tcpthread_z = new tcpThread_z();
	tcpthread_xyz = new tcpThread_xyz();

	httpthread_x = new httpThread_x();
	httpthread_y = new httpThread_y();
	httpthread_z = new httpThread_z();
	httpthread_xyz = new httpThread_xyz();

	//Init the widget Collection
	this->UiWidgetCollection.push_back(ui.qvtkWidget_x);
	this->UiWidgetCollection.push_back(ui.qvtkWidget_y);
	this->UiWidgetCollection.push_back(ui.qvtkWidget_z);
	this->UiWidgetCollection.push_back(ui.qvtkWidget_xyz);

	/*
		Update By Yaotaihang	2015-10-17
		audio service 
	*/
	audiothread = new audioThread();

	this->windowScreenshotCreater = new createWindowScreenshot();//2016-11-6

	//刷新x,y,z的坐标
	connect(tcpthread_x, SIGNAL(refreshGui(Data)), this, SLOT(refresh_x(Data)));
	connect(tcpthread_y, SIGNAL(refreshGui(Data)), this, SLOT(refresh_y(Data)));
	connect(tcpthread_z, SIGNAL(refreshGui(Data)), this, SLOT(refresh_z(Data)));
	connect(tcpthread_xyz, SIGNAL(refreshGui(Data)), this, SLOT(refresh_xyz(Data)));
	//设置当前的Service用户
	connect(ui.toolButton_19, SIGNAL(clicked()), this, SLOT(getControl()));
	//选择显示channel
	connect(ui.toolButton_21, SIGNAL(clicked()), this, SLOT(chooseChannel()));
	//选择x,y,z的显示
	connect(ui.toolButton_22, SIGNAL(clicked()), this, SLOT(hide_1()));
	connect(ui.toolButton_23, SIGNAL(clicked()), this, SLOT(hide_2()));
	connect(ui.toolButton_24, SIGNAL(clicked()), this, SLOT(hide_3()));
	connect(ui.toolButton_25, SIGNAL(clicked()), this, SLOT(hide_4()));
	connect(ui.toolButton_26, SIGNAL(clicked()), this, SLOT(showall()));
	//加载需要操作的数据
	connect(ui.button_LoadData, SIGNAL(clicked()), this, SLOT(on_actionOpen_Scence_triggered()));
	/*
		Update By YaoTaihang	2015-12-12
		Use Screenshot to do video connection
		This part is used to connect ui and define the timer for refreshing screenshot and sending
	*/
	//设定了枚举的四个类型
	this->currentWinForScreenshot = winName_x;
	//创建一个定时器
	this->screenshot_timer = new QTimer(this);


	connect(ui.btn_screenshot, SIGNAL(clicked()), this, SLOT(screenshotFlagChange()));
	connect(screenshot_timer, SIGNAL(timeout()), this, SLOT(screenshotBroadCast()));
	
	/*
		Upadate By YaoTaihang	2015-12-17
		This connect is used to change the flag of audioThread
	*/
	connect(ui.btn_audio, SIGNAL(clicked()), this, SLOT(audioThreadFlagChange()));
	/*
		Update by YaoTaihang	2015-12-01
		Signal and slot for mark line
	*/
	ui.comboBox_brush->insertItem(0, "Obj1");
	ui.comboBox_brush->insertItem(1, "Obj2");
	ui.comboBox_brush->insertItem(2, "Bkg");
	ui.comboBox_brush->insertItem(3, "Mark");

	for (int i = 0; i < 4; i++){
		this->BrushSize[i] = 3;
	}
	connect(ui.horizontalSlider_size, SIGNAL(valueChanged(int)), this, SLOT(refresh_lb_size(int)));
	connect(ui.comboBox_brush, SIGNAL(currentIndexChanged(int)), this, SLOT(refresh_slider_size(int)));
	//初始化窗口
	for (int i = 0; i < UiWidgetCollection.size(); i++){
		this->UiWidgetCollection[i]->GetRenderWindow()->GetInteractor()->Initialize();
	}

	/*
		Upate by YaoTaihang	2015-12-17
		Server screenshot window choose
	*/
	ui.comboBox_screenshotWin->insertItem(0, "Win 1");
	ui.comboBox_screenshotWin->insertItem(1, "Win 2");
	ui.comboBox_screenshotWin->insertItem(2, "Win 3");
	ui.comboBox_screenshotWin->insertItem(3, "Win 4");
	connect(ui.comboBox_screenshotWin, SIGNAL(currentIndexChanged(int)), this, SLOT(serverChangeScreenshotWin(int)));

	/*
		Update by YaoTaihang	2015-11-20
		This part is the definition for mainSocketThread for connections
	*/
	mainSockTread = new mainSocketThread();
	connect(mainSockTread, SIGNAL(main_GetChannelCount(char*)), this, SLOT(server_SendChannelCount(char*)));

	/*
		Update By YaoTaihang	2015-12-14
		This part is used to connect ui and Set the event for screenshot
	*/
	connect(mainSockTread, SIGNAL(main_EventForScreenshot(char*)), this, SLOT(server_screenshotEventSet(char*)));
	this->mainSockTread->EventOrMarkFlag = 0;

	/*
		Update By YaoTaihang	2015-12-17
		Connect change window request
	*/
	connect(mainSockTread, SIGNAL(main_ChangeWinForScreenshot(char*)), this, SLOT(server_ChangeWinForScreenshot(char*)));

	/*
		Update	By YaoTaihang	2016-01-07
		This part is define for scrollbar control
	*/
	//滚动条的改变事件设定
	connect(mainSockTread, SIGNAL(main_ChangeScrollBar(char*)), this, SLOT(server_ChangeScrollBar(char*)));
	connect(ui.horizontalScrollBar_0, SIGNAL(valueChanged(int)), this, SLOT(serverScrollBar0Move(int)));
	connect(ui.horizontalScrollBar_x, SIGNAL(valueChanged(int)), this, SLOT(serverScrollBarXMove(int)));
	connect(ui.horizontalScrollBar_y, SIGNAL(valueChanged(int)), this, SLOT(serverScrollBarYMove(int)));
	connect(ui.horizontalScrollBar_z, SIGNAL(valueChanged(int)), this, SLOT(serverScrollBarZMove(int)));
	
	/*
		Update By YaoTaihang	2016-01-09
		This part is define for init when new user connect
	*/
	//创建新用户连接
	connect(mainSockTread, SIGNAL(main_NewUserConnect(char*)), this, SLOT(server_GetNewUserConnect(char*)));
	
	/*
		Update By YapTaihang	2016-01-12
		This part is define for MarkLine init
	*/
	//初始化所有的markline
	for (int i = 0; i < MarkLineNumServer; i++)
	{
		this->markCallback[i] = vtkSmartPointer<vtkMyMarkCallback>::New();
		this->markCallback[i]->SetAllPolygonalLines(this->allPolygonalLines[i]);
	}
	/*
		Update by YaoTaihang	2016-01-13
		These are signals for mark Line to the UI
	*/
	//对于markline的一些操作
	connect(ui.btn_brush, SIGNAL(clicked()), this, SLOT(btnBrushClicked()));
	connect(ui.btn_clear, SIGNAL(clicked()), this, SLOT(btnClearClicked()));
	connect(ui.btn_save, SIGNAL(clicked()), this, SLOT(SaveLabelFile()));
	connect(ui.comboBox_brush, SIGNAL(currentIndexChanged(int)), this, SLOT(resetColorForMarkLine(int)));
	connect(ui.horizontalSlider_size, SIGNAL(valueChanged(int)), this, SLOT(resetWidthForMarkLine(int)));
	/*
		Update by YaoTaihang	2016-01-14
		This is the connect for audio flag change request
	*/
	connect(mainSockTread, SIGNAL(main_ChangeAudioFlag(char*)), this, SLOT(server_GetRequestForChangeAudioFlag(char*)));
	/*
		Update by YaoTaihang	2016-01-14
		This is the connect for mark flage change request
	*/
	//当点击时，改变flag，并将点击事件传入到方法中。
	connect(mainSockTread, SIGNAL(main_ChangeMarkFlag(char*)), this, SLOT(server_GetRequestForChangeMarkFlag(char*)));
	/*
		Update by YaoTaihang	2016-01-16
		This is the connect for mark event
	*/
	connect(mainSockTread, SIGNAL(main_EventForMarkLine(char*)), this, SLOT(server_MarkLineEventSet(char*)));
	connect(mainSockTread, SIGNAL(main_MarkClear()), this, SLOT(server_GetRequestForMarkClear()));
	
	//use to send plugin list
	connect(mainSockTread, SIGNAL(main_GetPluginList(char*)), this, SLOT(server_GetRequestForGetPluginList(char*)));
	connect(mainSockTread, SIGNAL(main_UsePlugin(char*, char*)), this, SLOT(server_GetRequestForUsePlugin(char*, char*)));
	connect(mainSockTread, SIGNAL(main_OperatePlugin(char*,char*, char*)), this, SLOT(server_GetRequestForOperatePlugin(char*, char*, char*)));

	connect(mainSockTread, SIGNAL(main_SaveLabel(char*)), this, SLOT(server_GetRequestForSaveLabel(char*)));

	connect(mainSockTread, SIGNAL(main_OriginalPoint(char*)), this, SLOT(server_GetRequestForOriginalPoint(char*)));
	connect(mainSockTread, SIGNAL(main_NewPoint(char*)), this, SLOT(server_GetRequestForNewPoint(char*)));
	connect(mainSockTread, SIGNAL(main_EditMask(char*)), this, SLOT(server_GetRequestForEditMask(char*)));
	//connect(mainSockTread, SIGNAL(main_Coordinate(char*)), this, SLOT(server_GetRequestForCoordinate(char*)));
	
	/*
		Update by 占淦	2016-11-14
		This is the connect for 3D show
	*/
	connect(ui.btn_3D, SIGNAL(clicked()), this, SLOT(btn3DClicked()));

	//connect(ui.toolButton_20, SIGNAL(clicked()), this, SLOT());

	/*
		Update by WangYi	2016-11-28
		This is the connect for segmentation
	*/
	//ui.comboBox_segMethods->insertItem(0, "regoin growing");
	//ui.comboBox_segMethods->insertItem(1, "level set");
	//ui.comboBox_segMethods->insertItem(2, "graph cut");
	//ui.comboBox_segMethods->insertItem(3, "random walk");

	//connect(ui.but_seg, SIGNAL(clicked()), this, SLOT(segmentation()));
	//
	//ui.setupUi(this);

	setAcceptDrops(true);//启用textEdit控件的放下操作  

	//connect()
	connect(ui.but_seg, SIGNAL(clicked()), this, SLOT(AddOnePluginClicked()));
	
	mainSockTread->start();

	current_service = new Service();
	current_service = service1;
}


//都是先有了request方法，再有真正的传值方法，最后是操作方法。
void Server::server_GetRequestForMarkClear()
{
	ui.btn_clear->click();
}

void Server::server_MarkLineEventSet(char* EventMessgae)
{
	vtkMyMarkCallback* cur_MarkCallback;

	cur_MarkCallback = this->markCallback[this->currentWinForScreenshot];

	vector<char*> Event = this->mainSockTread->messageSwitcher->StringSplit(EventMessgae, " ");
	//Get Event and Set it
	char * str_PointNumber = (this->mainSockTread->messageSwitcher->StringSplit(Event[1], "="))[1];
	char* str_CommandEvent = (this->mainSockTread->messageSwitcher->StringSplit(Event[Event.size() - 1], "="))[1];
	int PointNumber = atoi(str_PointNumber);
	int CommandEvent = atoi(str_CommandEvent);
	for (int i = 0; i < PointNumber; i++){
		char* str_X = (this->mainSockTread->messageSwitcher->StringSplit(Event[2 + i * 3], "="))[1];
		char* str_Y = (this->mainSockTread->messageSwitcher->StringSplit(Event[3 + i * 3], "="))[1];
		QString qstr_Type = (this->mainSockTread->messageSwitcher->StringSplit(Event[4 + i * 3], "="))[1];
		
		int type = qstr_Type.toInt();
		//qDebug() << "color"<<type;
		int X = atoi(str_X);
		int Y = atoi(str_Y);
		//change this x y to true xy;
		int* win_Size = ui.qvtkWidget_x->GetRenderWindow()->GetSize();
		int win_X = X* win_Size[0] / this->mainSockTread->maxX_ForCtrlClient;
		int win_Y = Y* win_Size[1] / this->mainSockTread->maxY_ForCtrlClient;

		//cur_MarkCallback->ResetMarkLineStyleIndex(type);
		resetColorForMarkLine(type);
		cur_MarkCallback->SetMarkLineUserEventMessage(win_X, win_Y, CommandEvent, type);

		delete[] str_X; str_X = NULL;
		delete[] str_Y; str_Y = NULL;
	}
	delete[] str_PointNumber; str_PointNumber = NULL;
	delete[] str_CommandEvent; str_CommandEvent = NULL;
	Event.clear();
	Event.swap(vector<char*>());
}
//是接受用户操作，并传值给方法。
void Server::server_GetRequestForChangeMarkFlag(char * Flag)
{
	int int_Flag = atoi(Flag);
	if (int_Flag == 1 && !ui.btn_brush->isChecked())
	{
		ui.btn_brush->click();
		this->mainSockTread->EventOrMarkFlag = 1;
	}
	else if (int_Flag == 0 && ui.btn_brush->isChecked())
	{
		ui.btn_brush->click();
		this->mainSockTread->EventOrMarkFlag = 0;
	}
}

void Server::server_GetRequestForChangeAudioFlag(char* Flag)
{
	int int_Flag = atoi(Flag);
	if (int_Flag == 1 && !ui.btn_audio->isChecked())
	{
		ui.btn_audio->click();
	}
	else if (int_Flag == 0 && ui.btn_audio->isChecked())
	{
		ui.btn_audio->click();
	}
}

void Server::serverInitMarkLineCallBack()
{
	/*
		Update by YaoTaihang	2016-01-13
		This Part is the definition for the mark Line
		It contains lines and it's callback function
	*/
	for (int i = 0; i < MarkLineNumServer; i++)
	{
		//If this widget have value for render
		if (this->UiWidgetCollection[i]->GetRenderWindow()->GetRenderers()->GetFirstRenderer() != 0)
		{
			this->markCallback[i]->SetInteractor(this->UiWidgetCollection[i]->GetInteractor());
			this->markCallback[i]->SetCurrentWidget(this->UiWidgetCollection[i]);
			this->markCallback[i]->SetRenderer(this->UiWidgetCollection[i]->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
			this->UiWidgetCollection[i]->GetInteractor()->AddObserver(vtkCommand::LeftButtonPressEvent, this->markCallback[i]);
			this->UiWidgetCollection[i]->GetInteractor()->AddObserver(vtkCommand::MouseMoveEvent, this->markCallback[i]);
		}	
	}
}
//重置对于markline的设定
void Server::btnBrushClicked()
{
	for (int i = 0; i < MarkLineNumServer; i++)
	{
		this->markCallback[i]->ResetFlagForMarkLine();
		this->resetColorForMarkLine(ui.comboBox_brush->currentIndex());
		this->markCallback[i]->ResetMarkLineStyleIndex(0);
	}
}
//清除markline
void Server::btnClearClicked()
{
	for (int i = 0; i < MarkLineNumServer; i++)
	{
		if (this->markCallback[i]->GetAllPolygonalLines().size() != 0)
		{
			this->markCallback[i]->ClearAllLines();
		}
	}
}

void Server::resetColorForMarkLine(int n)
{
	for (int i = 0; i < MarkLineNumServer; i++)
	{
		this->markCallback[i]->ResetMarkLineStyleIndex(n);
		////YY////
		this->markCallback[i]->SetColor(n);
		////2016.12.23////
		switch (n)
		{
		case 0:this->markCallback[i]->ResetLineColor(n, 1, 0, 0); break;
		case 1:this->markCallback[i]->ResetLineColor(n, 0, 1, 0); break;
		case 2:this->markCallback[i]->ResetLineColor(n, 0, 0, 1); break;
		case 3:this->markCallback[i]->ResetLineColor(n, 1, 0, 0); break;
		default:break;
		}
	}
}

void Server::resetWidthForMarkLine(int n)
{
	for (int i = 0; i < MarkLineNumServer; i++)
	{
		this->markCallback[i]->ResetLineWidth(ui.comboBox_brush->currentIndex(), n);
		////YY////
		this->markCallback[i]->SetWidth(n);
		////2016.12.23////
	}
}
//如何初始化的
void Server::server_GetNewUserConnect(char* clientUser){
	//When the new user connect,do init
	if (ui.btn_screenshot->isChecked()){
		vector<char*> params;
		params.push_back(SERVERNAME);
		char* message = this->mainSockTread->messageSwitcher->CreateMessageWithCommand(SEND_SCREENSHOTSTART, params);
		this->mainSockTread->sendMessageToSingleUser(clientUser,message);
	}
	//SetScrollbar
	this->mainSockTread->sendMessageToSingleUser(clientUser,this->serverMakeMaxScrollBarMessage());
	this->mainSockTread->sendMessageToSingleUser(clientUser, this->serverMakeCurScrollBarMessage());
}

//滚动条移动
void Server::serverScrollBar0Move(int curNum)
{
	if (this->currentWinForScreenshot == winName_x)
	{
		this->serverBroadCastCurScrollBar();
	}
}

void Server::serverScrollBarXMove(int curNum)
{
	if (this->currentWinForScreenshot == winName_xyz)
	{
		this->serverBroadCastCurScrollBar();
	}
}

void Server::serverScrollBarYMove(int curNum)
{
	if (this->currentWinForScreenshot == winName_y)
	{
		this->serverBroadCastCurScrollBar();
	}
}

void Server::serverScrollBarZMove(int curNum)
{
	if (this->currentWinForScreenshot == winName_z)
	{ 
		this->serverBroadCastCurScrollBar();
	}
}

//当前的滚动条事件
//获取并且处理当前滚动条的事件
char* Server::serverMakeCurScrollBarMessage()
{
	vector<char*> params;
	params.push_back(SERVERNAME);
	int currentScrollBar;
	//获取当前滚动条数据，并且赋值给currentScrollBar
	switch (this->currentWinForScreenshot){
	case winName_x:currentScrollBar = ui.horizontalScrollBar_0->value(); break;
	case winName_y:currentScrollBar = ui.horizontalScrollBar_y->value(); break;
	case winName_z:currentScrollBar = ui.horizontalScrollBar_z->value(); break;
	case winName_xyz:currentScrollBar = ui.horizontalScrollBar_x->value(); break;
	default:break;
	}
	//？
	std::stringstream ss;
	std::string str_currentScrollBar;
	ss << currentScrollBar;
	ss >> str_currentScrollBar;
	
	char * cur = new char[str_currentScrollBar.length()]; cur[0] = '\0';
	strcat(cur, str_currentScrollBar.c_str());
	params.push_back(cur);
	char* message = this->mainSockTread->messageSwitcher->CreateMessageWithCommand(SEND_SCROLLBARCURSEND, params);
	return message;
}

char* Server::serverMakeMaxScrollBarMessage()
{
	vector<char*> params;
	params.push_back(SERVERNAME);
	int maxScrollBar;
	switch (this->currentWinForScreenshot)
	{
	case winName_x:maxScrollBar = ui.horizontalScrollBar_0->maximum(); break;
	case winName_y:maxScrollBar = ui.horizontalScrollBar_y->maximum(); break;
	case winName_z:maxScrollBar = ui.horizontalScrollBar_z->maximum(); break;
	case winName_xyz:maxScrollBar = ui.horizontalScrollBar_x->maximum(); break;
	default:break;
	}
	std::stringstream ss;
	std::string str_maxScrollBar;
	ss << maxScrollBar;
	ss >> str_maxScrollBar;
	char * max = new char[str_maxScrollBar.length()]; max[0] = '\0';
	strcat(max, str_maxScrollBar.c_str());
	params.push_back(max);

	char* message = this->mainSockTread->messageSwitcher->CreateMessageWithCommand(SEND_SCROLLBARMAXSEND, params);
	return message;
}

//当前背景的滚动条
//将当前滚动条事件和所属的socket传输到mainSocketThread中
void Server::serverBroadCastCurScrollBar()
{
	this->mainSockTread->broadcastMessageToAllClient(this->serverMakeCurScrollBarMessage(),this->mainSockTread->currentCtrlUser);
}

void Server::serverBroadCastMaxScrollBar()
{
	this->mainSockTread->broadcastImageToAllClient(this->serverMakeMaxScrollBarMessage());
}

void Server::server_ChangeScrollBar(char* current){
	//将字符串转化成数字
	int currentScrollBar = atoi(current);
	switch (this->currentWinForScreenshot)
	{
	case winName_x:ui.horizontalScrollBar_0->setValue(currentScrollBar); break;
	case winName_y:ui.horizontalScrollBar_y->setValue(currentScrollBar); break;
	case winName_z:ui.horizontalScrollBar_z->setValue(currentScrollBar); break;
	case winName_xyz:ui.horizontalScrollBar_x->setValue(currentScrollBar); break;
	default:break;
	}
	this->serverBroadCastCurScrollBar();
}
//change screen shot window
void Server::serverChangeScreenshotWin(int winIndex)
{
	this->screenshot_timer->stop();
	this->currentWinForScreenshot = WinName(winIndex);
	this->serverBroadCastMaxScrollBar();
	this->serverBroadCastCurScrollBar();
	this->screenshot_timer->start();
}

/*
	选择3D视图，先选择xyz窗口，然后将体数据渲染到该窗口
	占淦   2016-11-14
*/


/*
	Update By YaoTaihang	2015-12-17
	change window of screenshot
*/
//改变截图窗口
void Server::server_ChangeWinForScreenshot(char* winName)
{
	this->screenshot_timer->stop();
	if (!strcmp(winName, "x"))
	{
		this->currentWinForScreenshot = winName_x;
	}
	else if (!strcmp(winName, "y"))
	{
		this->currentWinForScreenshot = winName_y;
	}
	else if (!strcmp(winName, "z"))
	{
		this->currentWinForScreenshot = winName_z;
	}
	else if (!strcmp(winName, "xyz"))
	{
		this->currentWinForScreenshot = winName_xyz;
	}

	this->serverBroadCastMaxScrollBar();
	this->serverBroadCastCurScrollBar();


	this->screenshot_timer->start();
}

/*
	Update By YaoTaihang	2015-12-17
	Change the flag of audioThread
	控制了音频线程的开启和关闭
*/
void Server::audioThreadFlagChange(){
	if (ui.btn_audio->isChecked()){
		//this part is used to send a message to all client to notivicate the screenshot begin send
		qDebug("-audio Sending begin ");
		vector<char*> params;
		params.push_back(SERVERNAME);
		char* message = this->mainSockTread->messageSwitcher->CreateMessageWithCommand(SEND_AUDIOSTART, params);//mainSocketThread
		this->mainSockTread->broadcastImageToAllClient(message);
		//Start audioService
		this->audiothread->start();
	}
	else
	{
		qDebug("-audio Sending end");
		//this part is used to send a message to all client to notivicate the screenshot end send
		vector<char*> params;
		params.push_back(SERVERNAME);
		char* message = this->mainSockTread->messageSwitcher->CreateMessageWithCommand(SEND_AUDIOSTOP, params);
		this->mainSockTread->broadcastImageToAllClient(message);
		//Stop audioService
		this->audiothread->terminate();
	}
}

void Server::server_screenshotEventSet(char* EventMessgae)
{
	vtkRenderWindowInteractor* cur_Interactor;

	cur_Interactor = this->UiWidgetCollection[this->currentWinForScreenshot]->GetRenderWindow()->GetInteractor();

	vector<char*> Event = this->mainSockTread->messageSwitcher->StringSplit(EventMessgae," ");
	//Get Event and Set it
	char * str_PointNumber = (this->mainSockTread->messageSwitcher->StringSplit(Event[1],"="))[1];
	char* str_CommandEvent = (this->mainSockTread->messageSwitcher->StringSplit(Event[Event.size() - 1], "="))[1];
	int PointNumber = atoi(str_PointNumber);
	int CommandEvent = atoi(str_CommandEvent);
	for (int i = 0; i < PointNumber; i++)
	{
		char* str_X = (this->mainSockTread->messageSwitcher->StringSplit(Event[2 + i * 3], "="))[1];
		char* str_Y = (this->mainSockTread->messageSwitcher->StringSplit(Event[3 + i * 3], "="))[1];
		char* str_Type = (this->mainSockTread->messageSwitcher->StringSplit(Event[4 + i * 3], "="))[1];
		char* str_PointerIndex = (this->mainSockTread->messageSwitcher->StringSplit(Event[5 + i * 3], "="))[1];
		int X = atoi(str_X);
		int Y = atoi(str_Y);
		int PointerIndex = atoi(str_PointerIndex);
		//change this x y to true xy;
		int* win_Size = ui.qvtkWidget_x->GetRenderWindow()->GetSize();
		int win_X = X* win_Size[0] / this->mainSockTread->maxX_ForCtrlClient;
		int win_Y = Y* win_Size[1] / this->mainSockTread->maxY_ForCtrlClient;

		cur_Interactor->SetEventInformation(
			win_X,
			win_Y,
			0,0,0,0,0,
			PointerIndex
		);
		if (!((CommandEvent == vtkCommand::MouseMoveEvent) && (i != PointNumber - 1)))
		{
			cur_Interactor->SetPointerIndex(PointerIndex);
			//Set invoke Event
			cur_Interactor->InvokeEvent(CommandEvent, NULL);
		}
		if (CommandEvent == vtkCommand::LeftButtonReleaseEvent)
		{
			cur_Interactor->ClearContact(PointerIndex);
		}

		delete[] str_X; str_X = NULL;
		delete[] str_Y; str_Y = NULL;
		delete[] str_Type; str_Type = NULL;
		delete[] str_PointerIndex; str_PointerIndex = NULL;
	}
	delete[] str_PointNumber; str_PointNumber = NULL;
	delete[] str_CommandEvent; str_CommandEvent = NULL;
	Event.clear();
	Event.swap(vector<char*>());
};

/*
	Update by YaoTaihang 2015-12-12
	This part is solt definition for vtkwidgt screenshot broad cast
*/
void Server::screenshotBroadCast(){
	//Check the client number ,if not 0, do broad cast
	if (this->mainSockTread->allSocketClients.size() != 0){/*this->mainSockTread->allSocketClients.size() != 0*/
		int length = 0;
		bool isScreenshot = true;
		int widgetIndex = this->currentWinForScreenshot;
		char * msgStream;

		msgStream = this->windowScreenshotCreater->getScreenshotOrDif(this->UiWidgetCollection[widgetIndex]->GetRenderWindow(), length, isScreenshot);
		//qDebug() << "selffuction size:"<<strlen(msgStream);
		

		if (msgStream != NULL)
		{
			char * message = NULL;
			if (isScreenshot)
			{
				
				message = this->mainSockTread->messageSwitcher->CreateMessageWithDynamicCommand(SEND_SCREENSHOTSEND, length, msgStream);
				//qDebug() << "final message0:" << message;
				//qDebug() << "msgStream:" << msgStream;
			}
			else
			{
			
				message = this->mainSockTread->messageSwitcher->CreateMessageWithDynamicCommand(SEND_SCREENSHOTDIFSEND, length, msgStream);
				//qDebug() << "final message1:" << message;
				//qDebug() << "msgStream:" << msgStream;
			}
			
			this->mainSockTread->broadcastImageToAllClient(message, length + NAMELENGTH + BODYLENGTH + ENDBODYLENGTH);

			//qDebug() << "final message:" << message;

			delete[] msgStream; msgStream = NULL;
		}
	}
	else
	{
		//Timer stop
	//	ui.btn_screenshot->setChecked(false);
	//	this->screenshot_timer->stop();
	}//2016-11-6

		/*char * BmpFile;
		//获取当前窗口的值，传入命令中
		BmpFile = createWindowScreenshot::getWindwoPNGFileStream(
			this->UiWidgetCollection[widgetIndex]->GetRenderWindow(), length);
		char * message = this->mainSockTread->messageSwitcher->
			CreateMessageWithDynamicCommand(SEND_SCREENSHOTSEND, length, BmpFile);
		this->mainSockTread->broadcastMessageToAllClient(
			message, length + NAMELENGTH + BODYLENGTH + ENDBODYLENGTH);
		delete[] BmpFile; BmpFile = NULL
	}
	else{
		//Timer stop
		//ui.btn_screenshot->setChecked(false);
		//this->screenshot_timer->stop();
	}*/
};


/*
	Update By YaoTaihang	2015-12-12
	This part is the slot definition for btn_screenshot clicked 
	It will change the timer flag to start or stop
*/
void Server::screenshotFlagChange(){
	if (ui.btn_screenshot->isChecked()){
		//this part is used to send a message to all client to notivicate the screenshot begin send
		qDebug("-Screenshot Sending begin ");
		vector<char*> params;
		//在数组的最后插入一个server
		params.push_back(SERVERNAME);
		//创建sceenShotStart的命令
		char* message = this->mainSockTread->messageSwitcher->CreateMessageWithCommand(SEND_SCREENSHOTSTART, params);
		//广播给所有的用户
		this->mainSockTread->broadcastImageToAllClient(message);
		//SetScrollbar
		this->serverBroadCastMaxScrollBar();
		this->serverBroadCastCurScrollBar();
		//Timer start
		this->screenshot_timer->start(SCREENSHOT_TIME);
	}else{
		qDebug("-Screenshot Sending end");
		//this part is used to send a message to all client to notivicate the screenshot end send
		vector<char*> params;
		params.push_back(SERVERNAME);
		char* message = this->mainSockTread->messageSwitcher->CreateMessageWithCommand(SEND_SCREENSHOTSTOP, params);
		this->mainSockTread->broadcastImageToAllClient(message);
		//Timer stop
		this->screenshot_timer->stop();
	}
}
//刷新滑块的大小
void Server::refresh_slider_size(int n)
{
	ui.horizontalSlider_size->setValue(this->BrushSize[n]);
	char * num = new char[2]; num[2] = '\0';
	itoa(this->BrushSize[n], num, 10);
	ui.label_size->setText(num);
	//delete num;
}
//刷新label的大小
void Server::refresh_lb_size(int n)
{
	this->BrushSize[ui.comboBox_brush->currentIndex()] = n;
	char * num = new char[2]; num[2] = '\0';
	//十进制转化成字符串，(将任意类型的数字转化成字符串)
	itoa(n, num, 10);
	ui.label_size->setText(num);
	delete num;
}
//send channel count
void Server::server_SendChannelCount(char* clientUser)
{
	char channelCount[10]; 
	itoa(availablechannel, channelCount, 10);
	//Create params
	vector<char*> params;
	params.push_back(SERVERNAME);
	params.push_back(channelCount);
	char* message = this->mainSockTread->messageSwitcher->CreateMessageWithCommand(SEND_SENDCHANNELCOUNT,params);
	this->mainSockTread->sendMessageToSingleUser(clientUser,message);
}

Server::~Server()
{
}

//占淦  2016-11-14
void Server::btn3DClicked(){
	DicomReader* dcm = new DicomReader();
	dcm->SetMainSocketThread(this->mainSockTread);
	dcm->DicomRead_3D(filePath,ui);
}


//2016-11-16 流媒体播放音频
void Server::audioplay(){

}

//加载文件选择窗口
void Server::on_actionOpen_Scence_triggered()
{
	
	if (ui.qvtkWidget_x->hasFocus())
	{
		current_service = service1;
		ui.statusBar->showMessage("current_service = service1");
	}
	if (ui.qvtkWidget_y->hasFocus())
	{
		current_service = service2;
		ui.statusBar->showMessage("current_service = service2");
	}
	if (ui.qvtkWidget_z->hasFocus())
	{
		current_service = service3;
		ui.statusBar->showMessage("current_service = service3");
	}
	if (ui.qvtkWidget_xyz->hasFocus())
	{
		current_service = service4;
		ui.statusBar->showMessage("current_service = service4");
	}


	/*
		Update By Yao Taihang	2015-11-27	
		Read a file array To instead read a single file
	*/
	QStringList fileNameList = QFileDialog::getOpenFileNames(
		this, tr("QFileDialog::getOpenFileNames()"),
		"",
		tr("mhd files(*.mhd);;vtk Files(*.vtk);;dcm files(*.dcm)"));

	//QStringList fileNameList;
	//QString filepath = "D:/16data_after_res.mhd";
	//fileNameList.push_back(filepath);

	if (fileNameList.size() == 0)
	{
		return;
	}

	//Get the first file name in the fileNameList to realize the type of the file
	
	QString filename = fileNameList[0]; 
	string filename_string = filename.toStdString(); 
	strcpy_s(path, strlen(filename_string.c_str())+1, filename_string.c_str());
	DataFile* dataFile = new DataFile(filename_string);
	//service1->Currentuser();
	//service2->Currentuser();
	//ui.label_1->setText("Scene Name " + filename);
	time_t t = time(NULL);
	current_service->Lastfile(t);
	current_service->filedir.clear();

	if (dataFile->getType()==".vtk")
	{
		for (int i = 0; i < fileNameList.size(); i++)
		{
			DataFile * thisFile = new DataFile(fileNameList[i].toStdString());
			current_service->filedir[thisFile->Name()] = thisFile;
		}
		VtkReader* vtk = new VtkReader();
		//If the file type is vtk ,give the QStringList to the object
		vtk->Read_Display(fileNameList, ui);

	} 
	else if (dataFile->getType() == ".dcm" || dataFile->getType() == ".DCM")
	{
		/*
		Update by WangYi	2015-12-07
		This part is used to read a dcm file dictionary ,and add into server->file_dir
		*/
		qDebug() << "sa" ;
		string path = dataFile->getPath();
		string dcmpath = path.substr(0, path.find_last_of("/"));
		QString qstring_path = QString::fromStdString(dcmpath);
		QDir dir(qstring_path);
		dir.setFilter(QDir::Files | QDir::NoSymLinks);
		QFileInfoList list = dir.entryInfoList();
		for (int i = 0; i < list.count(); i++)
		{
			QFileInfo file_info = list.at(i);
			QString suffix = file_info.suffix();
			if (QString::compare(suffix, QString("dcm"), Qt::CaseInsensitive) == 0)
			{
				QString absolute_file_path = file_info.absoluteFilePath();
				string thisFileName = absolute_file_path.toStdString();
				DataFile* thisDataFile = new DataFile(thisFileName);
				/*
				Update By YaoTaihang	2015-12-07
				Create FileName
				*/
				int LastIndex = thisFileName.find_last_of("/");
				string dcmFileName = thisFileName.substr(LastIndex + 1, dcmpath.length() - 1 - LastIndex);
				current_service->filedir[dcmFileName] = thisDataFile;
			}
		}

		service1->filedir[dataFile->Name()] = dataFile;
		DicomReader* dcm = new DicomReader();
		dcm->SetMainSocketThread(this->mainSockTread);
		dcm->Read_Display(dataFile->getPath(), ui);

		//将文件路径保存到filePath里面
		//占淦  2016-11-14
		filePath = dataFile->getPath();
	}
	else if (dataFile->getType() == ".mhd")
	{
		string filename1 = filename_string.substr(0, filename_string.find_last_of(".")) + ".raw";
		DataFile* dataFile2 = new DataFile(filename1);
		service1->filedir[dataFile->Name()] = dataFile;
		service1->filedir[dataFile2->Name()] = dataFile2;
		mhdReader *mhd = new mhdReader();
		mhdFileName = dataFile->getPath();
		mhd->Read_Display(dataFile->getPath(), ui);
	}

	/*
		Update by YaoTaihang	2016-01-13
		Init markLineCallback for the widgets which have render
	
	*/
	this->serverInitMarkLineCallBack();
}

/*
	plugin 12.13
*/
int Server::AddOnePluginClicked()
{
	//open ini file and get file
	QString ini_path = QFileDialog::getOpenFileName(this, tr("Select Plugin's ini File"), ".", tr("ini File(*.ini)"));
	//QString ini_path = "C:/workspace/2016-12-13/Server/Server/Plugin/segmentation/FastMarching.ini";
	int return_int = 0;
	return_int = LoadPluginFromIniPath(ini_path);
	return return_int;
}

int Server::OneButtonAddedClicked()
{
	int return_int = 0;
	//Get signal's sender
	PluginButton *plugin_button = dynamic_cast<PluginButton*>(sender());
	//Get function to call
	Button_Function button_function = plugin_button->GetFunction();
	//Call function
	qDebug() << "function is " << button_function;
	qDebug() << "return is " << button_function();
	//return_int = button_function();
	return return_int;
}

void Server::dragEnterEvent(QDragEnterEvent *e)
{
	if (e->mimeData()->hasFormat("text/uri-list")) //now use text to open a plugin
		e->acceptProposedAction(); //allow drag file to the window 
}

void Server::dropEvent(QDropEvent *e) //called when file draged into the window
{
	QList<QUrl> urls = e->mimeData()->urls();
	if (urls.isEmpty()) return;
	QString ini_path = urls.first().toLocalFile();
	if (ini_path.isEmpty())return;
	LoadPluginFromIniPath(ini_path);
}

int Server::LoadPluginFromIniPath(QString ini_path)
{
	int result;

	QFileInfo ini_file(ini_path);

	//get the dir path from ini file opened
	QDir plugin_folder = ini_file.absoluteDir();

	//set plugin layout
	QWidget *plugin_widget = ui.plugin_widget;
	//this->setCentralWidget(plugin_widget);
	QSplitter *button_splitter = new QSplitter;
	QSplitter *combobox_splitter = new QSplitter;
	QSplitter *lineedit_splitter = new QSplitter;
	QVBoxLayout *plugin_layout = new QVBoxLayout;

	//add plugin logo from "logo.jpg" in plugin folder
	QString plugin_logo_path = plugin_folder.absolutePath() + "/logo.jpg";
	QPixmap plugin_logo(plugin_logo_path);
	QLabel *plugin_logo_label = new QLabel();
	plugin_logo_label->setPixmap(plugin_logo);
	plugin_layout->addWidget(plugin_logo_label);

	//add plugin name from ini file name
	QString plugin_name = ini_file.baseName();
	QLabel *plugin_name_label = new QLabel(plugin_name);
	plugin_layout->addWidget(plugin_name_label);

	//add plugin buttons from "main.dll" in plugin folder
	//using pluma to dynamic load dll file
	QString plugin_maindll_path = plugin_folder.absolutePath() + "/" + plugin_name + ".dll";

	pluma.acceptProviderType<PluginInterfaceProvider>();
	pluma.load(plugin_maindll_path.toStdString().c_str());
	pluma.getProviders(providers);

	int index = 0;
	std::vector<PluginInterfaceProvider*>::iterator it;
	for (it = providers.begin(); it != providers.end(); ++it){
		PluginInterface *plugin_interface = (*it)->create();
		Plugin *plugin = new Plugin();
		plugin->_name = plugin_name;
		plugin->_plugin_interface = plugin_interface;
		plugin_interface->SendFileAPI(this->fileAPI);
		int result = 0;

		//About button
		Button *button = new Button();
		result = plugin_interface->GetButtons(button);
		qDebug() << "get button is :" << result;
		if (result == 100)
		{
			result = TransformButtons(plugin, button);
			qDebug() << "transform button is :" << result;
			if (result == -100)
			{
				//result = AddPluginWidgetsToSplitter(_pluginandbuttons.at(index).second, button_splitter);
				qDebug() << "add button is :" << result;
			}
		}
		

		//About combobox
		ComboBox *combobox = new ComboBox();
		result = plugin_interface->GetComboBoxs(combobox);
		qDebug() << "get combobox is :" << result;
		if (result == 100)
		{
			result = TransformComboBoxs(plugin, combobox);
			qDebug() << "transform combobox is :" << result;
			if (result == -100)
			{
				//result = AddPluginWidgetsToSplitter(_pluginandcomboboxs.at(index).second, combobox_splitter);
				qDebug() << "add combobox is :" << result;
			}
		}
		

		//about lineedit
		LineEdit *lineedit = new LineEdit();
		result = plugin_interface->GetLineEdits(lineedit);
		qDebug() << "get lineedit is :" << result;
		if (result == 100)
		{
			result = TransformLineEdits(plugin, lineedit);
			qDebug() << "transform lineedit is :" << result;
			if (result == -100)
			{
				//result = AddPluginWidgetsToSplitter(_pluginandlineedits.at(index).second, lineedit_splitter);
				qDebug() << "add lineedit is :" << result;
			}	
		}

		/*
		_widget_groups = unique_element_in_vector(_widget_groups);
		if (_pluginandbuttons.size() > index)
		{
			result = AddPluginWidgetsToSplitters(_pluginandbuttons.at(index).second);
			qDebug() << result;
		}
		if (_pluginandcomboboxs.size() > index)
		{
			result = AddPluginWidgetsToSplitters(_pluginandcomboboxs.at(index).second);
			qDebug() << result;
		}
		if (_pluginandlineedits.size() > index)
		{
			result = AddPluginWidgetsToSplitters(_pluginandlineedits.at(index).second);
			qDebug() << result;
		}
		*/
		this->_plugins.push_back(plugin);
		this->AddPluginToSplitters(plugin);
		++index;
	}

	//plugin_layout->addWidget(button_splitter);
	//plugin_layout->addWidget(combobox_splitter);
	//plugin_layout->addWidget(lineedit_splitter);
	for (int i = 0; i < _splitters.size(); i++)
	{
		plugin_layout->addWidget(_splitters[i]);
	}
	plugin_widget->setLayout(plugin_layout);

	return 0;
}
/* plugin end */

void Server::on_actionQuit_triggered()
{
	close();
}

//show x,hide y,z,xyz
void Server::hide_1()
{
	this->ui.qvtkWidget_x->show();
	this->ui.qvtkWidget_y->hide();
	this->ui.qvtkWidget_z->hide();
	this->ui.qvtkWidget_xyz->hide();
	this->ui.horizontalScrollBar_0->show();
	this->ui.horizontalScrollBar_x->hide();
	this->ui.horizontalScrollBar_y->hide();
	this->ui.horizontalScrollBar_z->hide();
	this->ui.line_10->hide();
	this->ui.line_11->hide();
}

//show y,hide x,z,xyz
void Server::hide_2()
{
	this->ui.qvtkWidget_x->hide();
	this->ui.qvtkWidget_y->show();
	this->ui.qvtkWidget_z->hide();
	this->ui.qvtkWidget_xyz->hide();
	this->ui.horizontalScrollBar_0->hide();
	this->ui.horizontalScrollBar_x->hide();
	this->ui.horizontalScrollBar_y->show();
	this->ui.horizontalScrollBar_z->hide();
	this->ui.line_10->hide();
	this->ui.line_11->hide();
}

//show z, hide x,y,xyz
void Server::hide_3()
{
	this->ui.qvtkWidget_x->hide();
	this->ui.qvtkWidget_y->hide();
	this->ui.qvtkWidget_z->show();
	this->ui.qvtkWidget_xyz->hide();
	this->ui.horizontalScrollBar_0->hide();
	this->ui.horizontalScrollBar_x->hide();
	this->ui.horizontalScrollBar_y->hide();
	this->ui.horizontalScrollBar_z->show();
	this->ui.line_10->hide();
	this->ui.line_11->hide();
}

//show xyz, hide x,y,z
void Server::hide_4()
{
	this->ui.qvtkWidget_x->hide();
	this->ui.qvtkWidget_y->hide();
	this->ui.qvtkWidget_z->hide();
	this->ui.qvtkWidget_xyz->show();
	this->ui.horizontalScrollBar_0->hide();
	this->ui.horizontalScrollBar_x->show();
	this->ui.horizontalScrollBar_y->hide();
	this->ui.horizontalScrollBar_z->hide();
	this->ui.line_10->hide();
	this->ui.line_11->hide();
}

//show all graph
void Server::showall()
{
	this->ui.qvtkWidget_x->show();
	this->ui.qvtkWidget_y->show();
	this->ui.qvtkWidget_z->show();
	this->ui.qvtkWidget_xyz->show();
	this->ui.horizontalScrollBar_0->show();
	this->ui.horizontalScrollBar_x->show();
	this->ui.horizontalScrollBar_y->show();
	this->ui.horizontalScrollBar_z->show();
	this->ui.line_10->show();
	this->ui.line_11->show();
}

//switch 
//获取channel
void Server::chooseChannel()
{
	bool ok;
	int value = QInputDialog::getInt(this, "get channel count", "input channel number", 1, 1, 4, 1, &ok);
	//QInputDialog::getInt(窗口,标题,输入:,初始值,最小值,最大值,步幅),
	printf("%d",value);
	
	if (ok)
	{	
		MyThread *thread1 = new MyThread();
		thread1->start();


		switch (value)
		{
		case 1:
		{			  
			availablechannel = 1;
			tcpthread_x->start();
			httpthread_x->start();

			break;
		}
		case 2:
		{
			availablechannel = 3;
			tcpthread_x->start();
			tcpthread_y->start();
			httpthread_x->start();
			httpthread_y->start();
			break;
		}
			
		case 3:
		{
			availablechannel = 7;
			tcpthread_x->start();
			tcpthread_y->start();
			tcpthread_z->start();
			httpthread_x->start();
			httpthread_y->start();
			httpthread_z->start();
			break;
		}
		case 4:
		{
			availablechannel = 15;
			tcpthread_x->start();
			tcpthread_y->start();
			tcpthread_z->start();
			tcpthread_xyz->start();
			httpthread_x->start();
			httpthread_y->start();
			httpthread_z->start();
			httpthread_xyz->start();
			break;
		}
		default:
			break;
		}
	}

}
//刷新x,y,z,xyz
void Server::refresh_x(Data data){
	vtkCamera* camera = ui.qvtkWidget_x->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera();
	//初始化camera
	camera->SetPosition(data.position_x, data.position_y, data.position_z);
	camera->SetFocalPoint(data.focalpoint_x, data.focalpoint_y, data.focalpoint_z);
	camera->SetViewUp(data.viewup_x, data.viewup_y, data.viewup_z);
	camera->SetClippingRange(0.1, 10000);

	ui.qvtkWidget_x->GetRenderWindow()->Render();
	if (data.slice_x != 0 && data.slice_y != 0 && data.slice_z != 0)
	{
		ui.horizontalScrollBar_x->setValue(data.slice_z);
		ui.horizontalScrollBar_y->setValue(data.slice_y);
		ui.horizontalScrollBar_z->setValue(data.slice_x);
	}
}

void Server::refresh_y(Data data)
{

	vtkCamera* camera = ui.qvtkWidget_y->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera();
	camera->SetPosition(data.position_x, data.position_y, data.position_z);
	camera->SetFocalPoint(data.focalpoint_x, data.focalpoint_y, data.focalpoint_z);
	camera->SetViewUp(data.viewup_x, data.viewup_y, data.viewup_z);
	camera->SetClippingRange(0.1, 10000);
	ui.qvtkWidget_y->GetRenderWindow()->Render();
	if (data.slice_x != 0 && data.slice_y != 0 && data.slice_z != 0)
	{
		ui.horizontalScrollBar_x->setValue(data.slice_x);
		ui.horizontalScrollBar_y->setValue(data.slice_y);
		ui.horizontalScrollBar_z->setValue(data.slice_z);
	}

}

void Server::refresh_z(Data data)
{
	vtkCamera* camera = ui.qvtkWidget_z->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera();
	camera->SetPosition(data.position_x, data.position_y, data.position_z);
	camera->SetFocalPoint(data.focalpoint_x, data.focalpoint_y, data.focalpoint_z);
	camera->SetViewUp(data.viewup_x, data.viewup_y, data.viewup_z);
	camera->SetClippingRange(0.1, 10000);
	ui.qvtkWidget_z->GetRenderWindow()->Render();
	if (data.slice_x != 0 && data.slice_y != 0 && data.slice_z != 0)
	{
		ui.horizontalScrollBar_x->setValue(data.slice_x);
		ui.horizontalScrollBar_y->setValue(data.slice_y);
		ui.horizontalScrollBar_z->setValue(data.slice_z);
		ui.horizontalScrollBar_x->valueChanged(data.slice_x);
		ui.horizontalScrollBar_y->valueChanged(data.slice_y);
		ui.horizontalScrollBar_z->valueChanged(data.slice_z);
	}

}

void Server::refresh_xyz(Data data)
{

	vtkCamera* camera = ui.qvtkWidget_xyz->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera();
	camera->SetPosition(data.position_x, data.position_y, data.position_z);
	camera->SetFocalPoint(data.focalpoint_x, data.focalpoint_y, data.focalpoint_z);
	camera->SetViewUp(data.viewup_x, data.viewup_y, data.viewup_z);
	camera->SetClippingRange(0.1, 10000);
	ui.qvtkWidget_xyz->GetRenderWindow()->Render();
	if (data.slice_x != 0 && data.slice_y != 0 && data.slice_z != 0)
	{
		ui.horizontalScrollBar_x->setValue(data.slice_x);
		ui.horizontalScrollBar_y->setValue(data.slice_y);
		ui.horizontalScrollBar_z->setValue(data.slice_z);
	}
}
//设置当前使用用户
void Server::getControl()
{
	service1->Currentuser("server");
	service2->Currentuser("server");
	service3->Currentuser("server");
	service4->Currentuser("server");
}

//plugin
int Server::TransformButtons(Plugin *plugin, Button *button)
{
	int return_int = 0;
	if (button == nullptr) return -1;
	if (button->button_name == "defult name") return -1;
	//Deal first button
	PluginButton *plugin_button = new PluginButton();
	plugin_button->SetButton(button);
	plugin->_buttons.push_back(plugin_button);
	_widget_groups.push_back(button->widget_group);
	if (!plugin_button->auto_connect)
		connect(plugin_button, SIGNAL(clicked()), this, SLOT(OneButtonAddedClicked()));

	//Traverse linked list
	Button *button_ptr = button;
	while (button_ptr->next_button != nullptr)
	{
		button_ptr = button_ptr->next_button;
		PluginButton *plugin_button = new PluginButton();
		plugin_button->SetButton(button_ptr);
		plugin->_buttons.push_back(plugin_button);
		_widget_groups.push_back(button_ptr->widget_group);
		if (!plugin_button->auto_connect)
			connect(plugin_button, SIGNAL(clicked()), this, SLOT(OneButtonAddedClicked()));
	}
	return return_int;
}

int Server::TransformComboBoxs(Plugin *plugin, ComboBox *combobox)
{
	int return_int = 0;
	if (combobox == nullptr) return -1;
	if (combobox->combobox_name == "defult name") return -1;
	//Deal first combobox
	PluginComboBox *plugin_combobox = new PluginComboBox();
	plugin_combobox->SetComboBox(combobox);
	plugin->_comboboxs.push_back(plugin_combobox);
	_widget_groups.push_back(combobox->widget_group);
	if (!plugin_combobox->auto_connect)
		connect(plugin_combobox, SIGNAL(clicked()), this, SLOT(OneButtonAddedClicked()));

	//Traverse linked list
	ComboBox *combobox_ptr = combobox;
	while (combobox_ptr->next_combobox != nullptr)
	{
		combobox_ptr = combobox_ptr->next_combobox;
		PluginComboBox *plugin_combobox = new PluginComboBox();
		plugin_combobox->SetComboBox(combobox_ptr);
		plugin->_comboboxs.push_back(plugin_combobox);
		_widget_groups.push_back(combobox_ptr->widget_group);
		if (!plugin_combobox->auto_connect)
			connect(plugin_combobox, SIGNAL(clicked()), this, SLOT(OneButtonAddedClicked()));
	}
	return return_int;
}

int Server::TransformLineEdits(Plugin *plugin, LineEdit *lineedit)
{
	int return_int = 0;
	if (lineedit == nullptr) return -1;
	if (lineedit->lineedit_name == "defult name") return -1;
	//Deal first lineedit
	PluginLineEdit *plugin_lineedit = new PluginLineEdit();
	plugin_lineedit->SetLineEdit(lineedit);
	plugin->_lineedits.push_back(plugin_lineedit);
	_widget_groups.push_back(lineedit->widget_group);
	if (!plugin_lineedit->auto_connect)
		connect(plugin_lineedit, SIGNAL(clicked()), this, SLOT(OneButtonAddedClicked()));

	//Traverse linked list
	LineEdit *lineedit_ptr = lineedit;
	while (lineedit_ptr->next_lineedit != nullptr)
	{
		lineedit_ptr = lineedit_ptr->next_lineedit;
		PluginLineEdit *plugin_lineedit = new PluginLineEdit();
		plugin_lineedit->SetLineEdit(lineedit_ptr);
		plugin->_lineedits.push_back(plugin_lineedit);
		_widget_groups.push_back(lineedit_ptr->widget_group);
		if (!plugin_lineedit->auto_connect)
			connect(plugin_lineedit, SIGNAL(clicked()), this, SLOT(OneButtonAddedClicked()));
	}
	return return_int;
}

template<class PluginWidget>
int Server::AddPluginWidgetsToSplitter(QVector<PluginWidget*> pluginwidgets, QSplitter *splitter)
{
	int return_int = 0;
	if (splitter == nullptr) return_int = -1;
	for each(PluginWidget* plugin_widget in pluginwidgets)
	{
		splitter->addWidget(plugin_widget);
	}
	return return_int;
}

template<class PluginWidget>
int Server::AddPluginWidgetsToSplitters(QVector<PluginWidget*> pluginwidgets)
{
	if (pluginwidgets.size() == 0) return -1;
	int return_int = 0;
	//if (_splitters.size() != 0)
	//{
	//	for each (QSplitter *var in _splitters)
	//	{
	//		delete var;
	//		var = nullptr;
	//	}
	//	_splitters.clear();
	//}
	if (_splitters.size() == 0)
	{
		int group_count = _widget_groups.size();
		for (int i = 0; i < group_count; i++)
		{
			QSplitter *splitter = new QSplitter();
			_splitters.push_back(splitter);
		}
		return_int = 1;
	}
	for each (PluginWidget* plugin_widget in pluginwidgets)
	{
		int index = find_element_index_in_vector(_widget_groups, plugin_widget->_widget_group);
		if (index == -1) continue;
		_splitters[index]->addWidget(plugin_widget);
	}
	return return_int;
}

int	Server::AddPluginToSplitters(Plugin* plugin)
{
	_widget_groups = unique_element_in_vector(_widget_groups);
	int return_int = 0;
	int return_int1 = this->AddPluginWidgetsToSplitters(plugin->_buttons);
	int return_int2 = this->AddPluginWidgetsToSplitters(plugin->_lineedits);
	int return_int3 = this->AddPluginWidgetsToSplitters(plugin->_comboboxs);
	return_int = return_int1 * return_int2 * return_int3;
	return return_int;
}
//plugin for iPad
int Server::SearchPluginFolder()
{
	_plugin_folder = "C:/workspace/server_now/Server/Server/Plugin";
	QDir plugin_folder(_plugin_folder);
	QFileInfoList entrys = plugin_folder.entryInfoList();
	if (entrys.size() == 0) return -1;
	for each (QFileInfo var in entrys)
	{
		if (var.isDir()&&var.baseName()!="")
		{
			qDebug() << var.baseName();
			this->_plugin_names.push_back(var.baseName());
			QString ini_path = var.absoluteFilePath() +"/"+ var.baseName() + ".ini";
			qDebug() << ini_path;
			//this->LoadPluginFromIniPath(ini_path);
		}
	}
	return 0;
}

void Server::server_GetRequestForGetPluginList(char *clientUser)
{
	qDebug() << clientUser << " get plugin list";

	QString message;
	message += "SENDPLUGINLIST";
	while (message.length() < 20)
	{
		message += " ";
	}

	QString body;
	body += "USER=";
	body += clientUser;

	QString pluginlist;
	pluginlist += " PLUGINLIST=";

	if (0 == _plugin_names.size())
	{
		pluginlist += "NULL";
	}
	else
	{
		for (int i = 0; i < _plugin_names.size(); i++)
		{
			if (0 != i) pluginlist += "|";// strcat(pluginList, "|");
			//strcat(pluginList, _plugin_names[i].toStdString().c_str());
			pluginlist += _plugin_names[i];
		}
	}

	body += pluginlist;

	int length = body.length();
	QString lengthStr;
	lengthStr.setNum(length);
	message += lengthStr;
	while (message.length() < 30)
	{
		message += " ";
	}

	message += body;

	message += "ENDBODY";

	qDebug() << message;
	mainSockTread->sendMessageToSingleUser(clientUser, (char*)(message.toStdString().c_str()));
}

void Server::server_GetRequestForUsePlugin(char *clientUser, char *plugin_name)
{
	qDebug() << clientUser << " use " << plugin_name;
	QString plugin_name_str = plugin_name;
	//Test if server has this plugin to use
	bool have_plugin = false;
	for each (QString var in this->_plugin_names)
	{
		if (plugin_name_str == var) have_plugin = true;
	}

	if (have_plugin) // Has this plugin to use
	{
		//Test if server has loaded this plugin
		bool plugin_is_loaded = false;
		if (_plugins.size() > 0)
		{
			for each (Plugin *var in _plugins)
			{
				if (var->_name == plugin_name_str)
				{
					plugin_is_loaded = true;
					_now_plugin = var;
				}
			}
		}
		//If server has this plugin but not loaded it, load it
		if (!plugin_is_loaded)
		{
			QString plugin_ini_path = _plugin_folder + "/" + plugin_name_str + "/" + plugin_name_str + ".ini";
			qDebug() << plugin_ini_path;
			this->LoadPluginFromIniPath(plugin_ini_path);
			server_GetRequestForUsePlugin(clientUser, plugin_name);
			return;
		}
	}

	QString message;
	message += "SENDPLUGININFO";
	while (message.length() < 20)
	{
		message += " ";
	}
	QString body;
	body = body + "USER=" + clientUser;

	if (!have_plugin)
	{
		qDebug() << "no such plugin for using";

		body = body + " NOSUCHPLUGIN";
	}
	else
	{
		body = body + " PLUGINBUTTON=";
		if (_now_plugin->_buttons.size() == 0)
		{
			body = body + "NULL";
		}
		else
		{
			for (int i = 0; i < _now_plugin->_buttons.size(); i++)
			{
				if (0 != i)
				{
					body = body + "|";
				}
				body = body + _now_plugin->_buttons.at(i)->objectName();
			}
		}

		body = body + " PLUGINLINEEDIT=";
		if (_now_plugin->_lineedits.size() == 0)
		{
			body = body + "NULL";
		}
		else
		{
			for (int i = 0; i < _now_plugin->_lineedits.size(); i++)
			{
				if (0 != i)
				{
					body = body + "|";
				}
				body = body + _now_plugin->_lineedits.at(i)->objectName();
			}
		}

		body = body + " PLUGINCOMBOBOX=";
		if (_now_plugin->_comboboxs.size() == 0)
		{
			body = body + "NULL";
		}
		else
		{
			for (int i = 0; i < _now_plugin->_comboboxs.size(); i++)
			{
				if (0 != i)
				{
					body = body + "|";
				}
				body = body + _now_plugin->_comboboxs.at(i)->objectName();
			}
		}
	}
	int length = body.length();
	QString lengthStr;
	lengthStr.setNum(length);
	message += lengthStr;
	while (message.length() < 30)
	{
		message += " ";
	}
	message += body;
	message += "ENDBODY";
	qDebug() << message.toStdString().c_str();
	mainSockTread->sendMessageToSingleUser(clientUser, (char*)(message.toStdString().c_str()));
}

void Server::server_GetRequestForOperatePlugin(char *clientUser, char *pluginWidgetName, char *operate)
{
	qDebug() << clientUser << "do" << operate << "in" << pluginWidgetName;
	QString widget_name = pluginWidgetName;
	QString operate_str = operate;

	QStringList type_and_name = widget_name.split("|");
	if (type_and_name.size() < 2)
	{
		qDebug() << "plugin widget name error";
		return;
	}
	
	QString type = type_and_name[0];

	if ("BUTTON" == type)
	{
		qDebug() << "Button " << type_and_name[1] << " "<<operate;
		if (operate_str != "CLICK") return;
		for each (PluginButton *var in _now_plugin->_buttons)
		{
			if (var->objectName() == type_and_name[1])
			{
				var->GetFunction()();
				return;
			}
		}
	}
	else if ("LINEEDIT" == type)
	{
		qDebug() << "Lineedit " << type_and_name[1] << " " << operate;
		QStringList operate_info = operate_str.split("|");
		if (operate_info.size() < 2) return;
		if (operate_info[0] != "TEXTCHANGE") return;
		for each (PluginLineEdit *var in _now_plugin->_lineedits)
		{
			if (var->objectName() == type_and_name[1])
			{
				int operate_int = operate_info[1].toInt();
				char *operate_char = new char[];
				operate_char[0] = '\0';
				itoa(operate_int, operate_char, 10);
				qDebug()<<"something is changed to "<<(var->GetFunction()(operate_char));
				return;
			}
		}
	}
	else if ("COMBOBOX" == type)
	{
		qDebug() << "combobox " << type_and_name[1] << " " << operate;
	}
	else
	{
		qDebug() << type_and_name[0] << " " << type_and_name[1] << " " << operate;
	}
}

////////////YY///////////////
void Server::getLabelFile()
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

	string Inputfile = this_server->mhdFileName;
	originalReader->SetFileName(Inputfile);
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

	//this->markCallback[0]->GetAllPolygonalLines();


	cv::Mat labelImg(imgSize[1], imgSize[0], CV_8UC3, CV_RGB(0, 0, 0));


	vector<vtkSmartPointer<vtkPolygonalLineData>> allPolygonalLines = this->markCallback[3]->GetAllPolygonalLines();
	vector <int> allPolygonalColor = this->markCallback[3]->GetAllPolygonalColor();
	vector <int> allPolygonalWidth = this->markCallback[3]->GetAllPolygonalWidth();
	int num = allPolygonalColor.size();

	for (int i = 0; i < num; i++)
	{
		vtkSmartPointer<vtkPolygonalLineData> singlePolygonalLine = allPolygonalLines[i];
		//vtkPolygonalLineData singlePolygonalLinetemp = this->singlePolygonalLine;
		vtkPoints *points = singlePolygonalLine->GetPoints();
		int n = points->GetNumberOfPoints();
		double before[3];
		for (int j = 0; j < n; j++)
		{
			double now[3];
			//double* p = points.GetPoint(j);
			points->GetPoint(j, now);
			//int idx = int((now[0] - OriginX) / SpacingX);
			//int idy = int((now[1] - OriginY) / SpacingY);


			int idx = (now[0] - 0.5*ui.qvtkWidget_xyz->width())* imgSize[1] / ui.qvtkWidget_xyz->height() + 0.5*imgSize[0];
			int idy = now[1] * imgSize[1] / ui.qvtkWidget_xyz->height();

			if (j == 0)
			{
				before[0] = idx;
				before[1] = idy;
				before[2] = 0;
				cv::Point center = cv::Point(idx, idy);
				if (allPolygonalColor[i] == 0)
				{
					circle(labelImg, center, allPolygonalWidth[i] * 0.5, CV_RGB(255, 0, 0), -1, 8, 0);
				}
				else if (allPolygonalColor[i] == 1)
				{
					circle(labelImg, center, allPolygonalWidth[i] * 0.5, CV_RGB(0, 255, 0), -1, 8, 0);
				}
				else if (allPolygonalColor[i] == 2)
				{
					circle(labelImg, center, allPolygonalWidth[i] * 0.5, CV_RGB(0, 0, 255), -1, 8, 0);
				}

			}
			else
			{
				cv::Point start = cv::Point(before[0], before[1]);
				cv::Point end = cv::Point(idx, idy);
				if (allPolygonalColor[i] == 0)
				{
					line(labelImg, start, end, CV_RGB(255, 0, 0), allPolygonalWidth[i]);
				}
				else if (allPolygonalColor[i] == 1)
				{
					line(labelImg, start, end, CV_RGB(0, 255, 0), allPolygonalWidth[i]);
				}
				else if (allPolygonalColor[i] == 2)
				{
					line(labelImg, start, end, CV_RGB(0, 0, 255), allPolygonalWidth[i]);
				}
				before[0] = idx;
				before[1] = idy;

			}
		}
	}
	//imshow("label", labelImg);



	for (int z = 0; z < imgSize[2]; z++)
	{

		if (z == ui.horizontalScrollBar_x->value())
		{
			//save to result volume
			for (int y = 0; y < imgSize[1]; y++)
			{
				for (int x = 0; x < imgSize[0]; x++)
				{

					if ((uchar)labelImg.at<Vec3b>(y, x)[0] == 255)
						outImg_mask[z*imgSize[1] * imgSize[0] + y *imgSize[0] + x] = 1;
					else if ((uchar)labelImg.at<Vec3b>(y, x)[1] == 255)
						outImg_mask[z*imgSize[1] * imgSize[0] + y *imgSize[0] + x] = 3;
					else if ((uchar)labelImg.at<Vec3b>(y, x)[2] == 255)
						outImg_mask[z*imgSize[1] * imgSize[0] + y *imgSize[0] + x] = 2;
					else
						outImg_mask[z*imgSize[1] * imgSize[0] + y *imgSize[0] + x] = 0;
				}
			}
		}
		else
		{
			for (int y = 0; y < imgSize[1]; y++)
			{
				for (int x = 0; x < imgSize[0]; x++)
				{
					outImg_mask[z*imgSize[1] * imgSize[0] + y *imgSize[0] + x] = 0;
				}
			}
		}
	}

	writer_mask->SetFileName(labelFileName.c_str());
	//this->labelFileName = "labels.mhd";
	writer_mask->SetInput(outPtr_mask);
	writer_mask->Update();


	//int idx0 = int((x - Origin[0]) / Spacing[0]);
	//int idx1 = int((y - Origin[1]) / Spacing[1]);
	//int idx2 = int((z - Origin[2]) / Spacing[2]);

	allPolygonalLines.swap(vector<vtkSmartPointer<vtkPolygonalLineData>>());
	allPolygonalColor.swap(vector<int>());
	allPolygonalWidth.swap(vector<int>());


}

/////////2016.12.23////////////

void Server::server_GetRequestForSaveLabel(char *clientUser)
{
	string labelfilename = clientUser;
	labelfilename += ".mhd";
	this->labelFileName = labelfilename;
	qDebug() << labelFileName.c_str();
	this->getLabelFile();
}

void Server::SaveLabelFile()
{
	this->labelFileName = "label.mhd";
	this->getLabelFile();
}

void Server::saveOriginalPoint()
{
	vector<vtkSmartPointer<vtkPolygonalLineData>> allPolygonalLines = this->markCallback[3]->GetAllPolygonalLines();
	vector <int> allPolygonalColor = this->markCallback[3]->GetAllPolygonalColor();
	vector <int> allPolygonalWidth = this->markCallback[3]->GetAllPolygonalWidth();
	int num = allPolygonalColor.size();
	for (int i = 0; i < num; i++)
	{
		vtkSmartPointer<vtkPolygonalLineData> singlePolygonalLine = allPolygonalLines[i];
		//vtkPolygonalLineData singlePolygonalLinetemp = this->singlePolygonalLine;
		vtkPoints *points = singlePolygonalLine->GetPoints();
		int n = points->GetNumberOfPoints();
		double before[3];
		for (int j = 0; j < n; j++)
		{
			double now[3];
			//double* p = points.GetPoint(j);
			points->GetPoint(j, now);
			//int idx = int((now[0] - OriginX) / SpacingX);
			//int idy = int((now[1] - OriginY) / SpacingY);


			int idx = (now[0] - 0.5*ui.qvtkWidget_xyz->width())* 512 / ui.qvtkWidget_xyz->height() + 0.5 * 512;
			int idy = now[1] * 512 / ui.qvtkWidget_xyz->height();
			qDebug()<<"originalpoint:" << idx << idy;
		}
	}

}

void Server::server_GetRequestForOriginalPoint(char *message)
{
	//ui.button_OriginalPoints->click();
	this->saveOriginalPoint();
}

void Server::saveNewPoint()
{
	vector<vtkSmartPointer<vtkPolygonalLineData>> allPolygonalLines = this->markCallback[3]->GetAllPolygonalLines();
	vector <int> allPolygonalColor = this->markCallback[3]->GetAllPolygonalColor();
	vector <int> allPolygonalWidth = this->markCallback[3]->GetAllPolygonalWidth();
	int num = allPolygonalColor.size();
	for (int i = 0; i < num; i++)
	{
		vtkSmartPointer<vtkPolygonalLineData> singlePolygonalLine = allPolygonalLines[i];
		//vtkPolygonalLineData singlePolygonalLinetemp = this->singlePolygonalLine;
		vtkPoints *points = singlePolygonalLine->GetPoints();
		int n = points->GetNumberOfPoints();
		double before[3];
		for (int j = 0; j < n; j++)
		{
			double now[3];
			//double* p = points.GetPoint(j);
			points->GetPoint(j, now);
			//int idx = int((now[0] - OriginX) / SpacingX);
			//int idy = int((now[1] - OriginY) / SpacingY);


			int idx = (now[0] - 0.5*ui.qvtkWidget_xyz->width()) * 512 / ui.qvtkWidget_xyz->height() + 0.5 * 512;
			int idy = now[1] * 512 / ui.qvtkWidget_xyz->height();
			qDebug() << "newpoint:" << idx << idy;
		}
	}

}

void Server::server_GetRequestForNewPoint(char *message)
{
	//ui.button_NewPoints->click();
	this->saveNewPoint();
}

void Server::server_GetRequestForEditMask(char* message)
{
	//ui.button_EditMask->click();
	qDebug() << "step3";
}

//void Server::server_GetRequestForCoordinate(char *message)
//{
//	vtkRenderWindowInteractor* cur_Interactor;
//
//	cur_Interactor = this->UiWidgetCollection[this->currentWinForScreenshot]->GetRenderWindow()->GetInteractor();
//
//	vector<char*> Event = this->mainSockTread->messageSwitcher->StringSplit(message, " ");
//	//Get Event and Set it
//	char * str_PointNumber = (this->mainSockTread->messageSwitcher->StringSplit(Event[1], "="))[1];
//	char* str_CommandEvent = (this->mainSockTread->messageSwitcher->StringSplit(Event[Event.size() - 1], "="))[1];
//	int PointNumber = atoi(str_PointNumber);
//	int CommandEvent = atoi(str_CommandEvent);
//	for (int i = 0; i < PointNumber; i++)
//	{
//		char* str_X = (this->mainSockTread->messageSwitcher->StringSplit(Event[2 + i * 3], "="))[1];
//		char* str_Y = (this->mainSockTread->messageSwitcher->StringSplit(Event[3 + i * 3], "="))[1];
//		char* str_Type = (this->mainSockTread->messageSwitcher->StringSplit(Event[4 + i * 3], "="))[1];
//		char* str_PointerIndex = (this->mainSockTread->messageSwitcher->StringSplit(Event[5 + i * 3], "="))[1];
//		int X = atoi(str_X);
//		int Y = atoi(str_Y);
//		int PointerIndex = atoi(str_PointerIndex);
//		//change this x y to true xy;
//		int* win_Size = ui.qvtkWidget_x->GetRenderWindow()->GetSize();
//		int win_X = X* win_Size[0] / this->mainSockTread->maxX_ForCtrlClient;
//		int win_Y = Y* win_Size[1] / this->mainSockTread->maxY_ForCtrlClient;
//
//		cur_Interactor->SetEventInformation(
//			win_X,
//			win_Y,
//			0, 0, 0, 0, 0,
//			PointerIndex
//			);
//	}
//}