#ifndef MAINSOCJERTTHREAD_H
#define MAINSOCJERTTHREAD_H
#include "qthread.h"
#include "singleSocketThread.h"
#include "vector"
#include <QDebug>
using namespace std;

#define ISLASTMESSAGEUSE 1
#define NOLASTMESSAGEUSE 0



class mainSocketThread :public QThread
{
	Q_OBJECT;
public:
	MessageSwitcher * messageSwitcher;
	vector<singleSocketThread*> allSocketClients;

	SOCKET mainSocket;
	sockaddr_in clientsocket;
	int len = sizeof(sockaddr_in);

	char * currentCtrlUser;
	singleSocketThread* currentCtrlClient;

	int maxX_ForCtrlClient = 0;
	int maxY_ForCtrlClient = 0;

	//This is markLine and Event flag, when markline flag = 1 ,another is 0
	int EventOrMarkFlag = 0;

	mainSocketThread();
	~mainSocketThread();

	//Broadcast message to all client
	void broadcastImageToAllClient(char * message);
	void broadcastMessageToAllClient(char * message);
	void broadcastMessageToAllClient(char * message, char* ExceptClientName);
	void broadcastImageToAllClient(char * message, int messageLength);
	void broadcastMessageToAllClient(char * message,int messageLength);
	//Bind singleSocketThreads' signals and mainSocketThread's slots functions
	void bindSingleSignalsAndMainSlots(singleSocketThread* singleClient,mainSocketThread* current);
	//Send message to the single user
	void sendMessageToSingleUser(char* clientUser, char* Message);
protected:
	void run();

signals:
	//Some signals which need be sended to Server Thread
	void main_GetChannelCount(char*);
	void main_EventForScreenshot(char*);
	void main_EventForMarkLine(char*);
	void main_ChangeWinForScreenshot(char*);
	void main_ChangeScrollBar(char*);
	void main_NewUserConnect(char*);
	void main_ChangeAudioFlag(char*);
	void main_ChangeMarkFlag(char*);
	void main_MarkClear();
	void main_GetPluginList(char*);
	void main_UsePlugin(char*, char*);
	void main_OperatePlugin(char*, char*, char*);
	void main_SaveLabel(char*);
	void main_OriginalPoint(char*);
	void main_NewPoint(char*);
	void main_EditMask(char*);
	//void main_Coordinate(char*);

private slots:
	//When the client send disconnet message ,delete this socket
	void main_DeletSocketWhenClientDisconnet(char* clientUser);
	//When the cilent send a message to get channel count ,send it
	void main_GetChannlCountWhenClienRequset(char* clientUser);
	//When the client get the message ,forwadr it 
	//When the client requests get the screenshot control 
	void main_SetScreenshotCtrlWhenClientRequset(char* clientUser,char* maxX,char* maxY);
	//When the client get event from the controller
	void main_GetEventForScreenshotWhenGet(char* EventMessage);
	//When the client get change window request
	void main_GetReqForChangeWinScreenshot(char* winName);
	//When the control client sent current scrollbar ,change it
	void main_GetScrollBarCurrent(char* clientUser, char* current);
	//When new user connect ,do init
	void main_GetNewUserConnect(char*);
	//When the controller send request to change the flag of audio
	void main_GetRequestForChangeAudioFlag(char* clientUser, char* Flag); 
	//When the controller send request to change the flag of mark
	void main_GetRequestForChangeMarkFlag(char* clientUser, char* Flag);
	//When the controller send request to clear all mark
	void main_GetRequestForClearMark(char* clientUser);
	//When client send request to get plugin list
	void main_GetRequestForGetPluginList(char *clientUser);
	//When client send request to use plugin
	void main_GetRequestForUsePlugin(char *clientUser, char *pluginName);
	//When client send request to operate a plugin widget
	void main_GetRequestForOperatePlugin(char *clientUser, char *pluginWidgetName, char *operate);

	void main_GetRequestForSaveLabel(char *clientUser);

	void main_GetRequestForOriginalPoint(char *clientUser);
	void main_GetRequestForNewPoint(char *clientUser);
	void main_GetRequestForEditMask(char *clientUser);
	//void main_GetRequestForCoordinate(char *message);
};

#endif
