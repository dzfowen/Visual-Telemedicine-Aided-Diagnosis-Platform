#include "qthread.h"
#include <WINSOCK2.H>
#include <string>

#include "MessageSwicther.h"

class singleSocketThread :public QThread
{
	Q_OBJECT;
public:
	MessageSwitcher * messageSwitcher;

	SOCKET currentSocket;
	char ClientUser[NAMELENGTH];
	bool SendImage = false;

	singleSocketThread();
	singleSocketThread(SOCKET socket, MessageSwitcher * messageSwitcher);
	~singleSocketThread();
	//Send message to current socket client
	void sendMessageToCurrentSocketClient(char* message, int MessageLastUseFlag);
	void sendMessageToCurrentSocketClient(char* message, int messaheLength, int MessageLastUseFlag);
	
protected:
	void run();
signals:
	void socket_ClientDisconnect(char*);
	void socket_GetChannelCount(char*);
	void socket_ForwardToOtherClient(char*, char*);
	void socket_ClientGetScreenshotCtrl(char*, char*, char*);
	void socket_EventForScreenshot(char*);
	void socket_ChangeWinForScreenshot(char*);
	void socket_ChangeScrollBar(char*, char*);
	void sochet_NewUserConnect(char*);
	void socket_ChangeAudioFlag(char*, char*);
	void socket_ChangeMarkFlag(char*, char*);
	void socket_MarkClear(char*);
	void socket_GetPluginList(char*);
	void socket_UsePlugin(char*, char*);
	void socket_OperatePlugin(char*, char*, char*);
	void socket_SaveLabel(char*);
	void socket_OriginalPoint(char*);
	void socket_NewPoint(char*);
	void socket_EditMask(char*);
	//void socket_Coordinate(char*);
};

