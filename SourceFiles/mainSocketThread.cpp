#include "mainSocketThread.h"

mainSocketThread::mainSocketThread()
{
	this->messageSwitcher = new MessageSwitcher("Command.xml");
	//Set currentCtrlUser to server
	this->currentCtrlUser = "server";

	HANDLE hThread;
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(2, 2);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	if (err)
	{
		qDebug() << "fail to open socket";
	}
	mainSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(60001);
	bind(mainSocket, (sockaddr*)&addr, sizeof(sockaddr));
	listen(mainSocket, 100);
}

mainSocketThread::~mainSocketThread()
{
	closesocket(mainSocket);
	WSACleanup();
}
//传入socket和singleSocket初始化
void mainSocketThread::run()
{
	while (true)
	{
		qDebug() << "MainSocketThread waiting accept";
		SOCKET serConn = accept(mainSocket, (struct sockaddr*)&clientsocket, &len);

		singleSocketThread* singleSock = new singleSocketThread(serConn, this->messageSwitcher);

		//There can be the place for bindng some slot and signal funtions
		this->bindSingleSignalsAndMainSlots(singleSock, this);
		//Add this client into the vector
		this->allSocketClients.push_back(singleSock);

		qDebug("-This client SOCKET:%d		Total client conut:%d---", serConn, this->allSocketClients.size());
		singleSock->start();
	}
	closesocket(mainSocket);
	WSACleanup();
}

void mainSocketThread::broadcastImageToAllClient(char * message)
{
	for (int i = 0; i < this->allSocketClients.size(); i++)
	{
		if (allSocketClients[i]->ClientUser[0] != '\0')
		{
			if (allSocketClients[i]->SendImage == false)
			{
				continue;
			}
			qDebug() << allSocketClients[i]->ClientUser;
			if (i != this->allSocketClients.size() - 1)
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, NOLASTMESSAGEUSE);
			}
			else
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, ISLASTMESSAGEUSE);
			}
		}
	}
}

void mainSocketThread::broadcastMessageToAllClient(char * message)
{
	for (int i = 0; i < this->allSocketClients.size(); i++)
	{
		if (allSocketClients[i]->ClientUser[0] != '\0')
		{
			if (i != this->allSocketClients.size() - 1)
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, NOLASTMESSAGEUSE);
			}
			else
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, ISLASTMESSAGEUSE);
			}
		}
	}
}

void mainSocketThread::broadcastMessageToAllClient(char * message, char* ExceptClientName)
{
	bool cmpFlag = false;
	if (this->allSocketClients.size() != 0)
	{
		cmpFlag = !strcmp(this->allSocketClients[this->allSocketClients.size() - 1]->ClientUser, ExceptClientName);
	}
	for (int i = 0; i < this->allSocketClients.size(); i++)
	{
		if (allSocketClients[i]->ClientUser[0] != '\0')
		{
			if ((cmpFlag && i == this->allSocketClients.size() - 2) || (!cmpFlag && i == this->allSocketClients.size() - 1))
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, ISLASTMESSAGEUSE);
				break;
			}
			else if (!strcmp(this->allSocketClients[i]->ClientUser, ExceptClientName))
			{
				continue;
			}
			else
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, NOLASTMESSAGEUSE);
			}
		}
	}
}

void mainSocketThread::broadcastImageToAllClient(char * message, int messageLength)
{
	for (int i = 0; i < this->allSocketClients.size(); i++)
	{
		if (allSocketClients[i]->ClientUser[0] != '\0')
		{
			if (allSocketClients[i]->SendImage == false)
			{
				continue;
			}
			qDebug() << allSocketClients[i]->ClientUser;
			if (i != this->allSocketClients.size() - 1)
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, messageLength, NOLASTMESSAGEUSE);
			}
			else
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, messageLength, ISLASTMESSAGEUSE);
			}
		}
	}
}

void mainSocketThread::broadcastMessageToAllClient(char * message, int messageLength)
{
	for (int i = 0; i < this->allSocketClients.size(); i++)
	{
		if (allSocketClients[i]->ClientUser[0] != '\0')
		{
			if (i != this->allSocketClients.size() - 1)
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, messageLength, NOLASTMESSAGEUSE);
			}
			else
			{
				allSocketClients[i]->sendMessageToCurrentSocketClient(message, messageLength, ISLASTMESSAGEUSE);
			}
		}
	}
}

void mainSocketThread::bindSingleSignalsAndMainSlots(singleSocketThread* singleClient, mainSocketThread* current)
{
	connect(singleClient, SIGNAL(socket_ClientDisconnect(char*)), current, SLOT(main_DeletSocketWhenClientDisconnet(char*)));
	connect(singleClient, SIGNAL(socket_GetChannelCount(char*)), current, SLOT(main_GetChannlCountWhenClienRequset(char*)));
	connect(singleClient, SIGNAL(socket_ClientGetScreenshotCtrl(char*,char*,char*)), current, SLOT(main_SetScreenshotCtrlWhenClientRequset(char*,char*,char*)));
	connect(singleClient, SIGNAL(socket_EventForScreenshot(char*)), current, SLOT(main_GetEventForScreenshotWhenGet(char*)));
	connect(singleClient, SIGNAL(socket_ChangeWinForScreenshot(char*)), current, SLOT(main_GetReqForChangeWinScreenshot(char*)));
	connect(singleClient, SIGNAL(socket_ChangeScrollBar(char*, char*)), current, SLOT(main_GetScrollBarCurrent(char*, char*)));
	connect(singleClient, SIGNAL(sochet_NewUserConnect(char*)), current, SLOT(main_GetNewUserConnect(char*)));
	connect(singleClient, SIGNAL(socket_ChangeAudioFlag(char*, char*)), current, SLOT(main_GetRequestForChangeAudioFlag(char*, char*)));
	connect(singleClient, SIGNAL(socket_ChangeMarkFlag(char*, char*)), current, SLOT(main_GetRequestForChangeMarkFlag(char*, char*)));
	connect(singleClient, SIGNAL(socket_MarkClear(char*)), current, SLOT(main_GetRequestForClearMark(char*)));
	connect(singleClient, SIGNAL(socket_GetPluginList(char*)), current, SLOT(main_GetRequestForGetPluginList(char*)));
	connect(singleClient, SIGNAL(socket_UsePlugin(char*, char*)), current, SLOT(main_GetRequestForUsePlugin(char*, char*)));
	connect(singleClient, SIGNAL(socket_OperatePlugin(char*, char*, char*)), current, SLOT(main_GetRequestForOperatePlugin(char*, char*, char*)));
	connect(singleClient, SIGNAL(socket_SaveLabel(char*)), current, SLOT(main_GetRequestForSaveLabel(char*)));
	connect(singleClient, SIGNAL(socket_OriginalPoint(char*)), current, SLOT(main_GetRequestForOriginalPoint(char*)));
	connect(singleClient, SIGNAL(socket_NewPoint(char*)), current, SLOT(main_GetRequestForNewPoint(char*)));
	connect(singleClient, SIGNAL(socket_EditMask(char*)), current, SLOT(main_GetRequestForEditMask(char*)));
	//connect(singleClient, SIGNAL(socket_Coordinate(char*)), current, SLOT(main_GetRequestForCoordinate(char*)));
}

void mainSocketThread::sendMessageToSingleUser(char* clientUser, char* message)
{
	for (int i = 0; i < this->allSocketClients.size(); i++)
	{
		//qDebug() << this->allSocketClients[i]->ClientUser;
		if (!strcmp(this->allSocketClients[i]->ClientUser, clientUser))
		{
			this->allSocketClients[i]->sendMessageToCurrentSocketClient(message,1);
			break;
		}
	}
}

void mainSocketThread::main_DeletSocketWhenClientDisconnet(char * currentUser)
{
	for (int i = 0; i < this->allSocketClients.size(); i++)
	{
		if (!strcmp(this->allSocketClients[i]->ClientUser, currentUser))
		{
			std::vector<singleSocketThread*>::iterator it = this->allSocketClients.begin() + i;
			this->allSocketClients.erase(it);
			break;
		}
	}
}

void mainSocketThread::main_GetChannlCountWhenClienRequset(char* clientUser)
{
	emit main_GetChannelCount(clientUser);
}

void mainSocketThread::main_SetScreenshotCtrlWhenClientRequset(char* clientUser,char* maxX,char*maxY)
{
	//bind username and ctrl for current ctrl user
	this->currentCtrlUser = clientUser;
	this->maxX_ForCtrlClient = atoi(maxX);
	this->maxY_ForCtrlClient = atoi(maxY);
	for (int i = 0; i < this->allSocketClients.size(); i++)
	{
		if (!strcmp(this->allSocketClients[i]->ClientUser, this->currentCtrlUser))
		{
			this->currentCtrlClient = this->allSocketClients[i];
			break;
		}
	}
}

void mainSocketThread::main_GetEventForScreenshotWhenGet(char *EventMessage)
{
	vector<char*> params = this->messageSwitcher->StringSplit(EventMessage, " ");
	char * Username = (this->messageSwitcher->StringSplit(params[0], "="))[1];
	//Get the event username, check it equals to currentCtrlUser
	if (!strcmp(this->currentCtrlUser, Username))
	{
		/*
			Check the value if EventOrMarkFlag = 0 ,send it to set event
			If it is 1, set it use to mark line
		*/
		if (this->EventOrMarkFlag == 0)
		{
			emit main_EventForScreenshot(EventMessage);
		}
		else
		{
			emit main_EventForMarkLine(EventMessage);
		}

	}	
}
void mainSocketThread::main_GetReqForChangeWinScreenshot(char* winName)
{
	emit main_ChangeWinForScreenshot(winName);
}
void mainSocketThread::main_GetScrollBarCurrent(char* clientUser, char* current)
{
	if (!strcmp(this->currentCtrlUser, clientUser))
	{
		emit main_ChangeScrollBar(current);
	}
}
void mainSocketThread::main_GetNewUserConnect(char* clientUser)
{
	emit main_NewUserConnect(clientUser);
}
void mainSocketThread::main_GetRequestForChangeAudioFlag(char* clientUser, char* Flag)
{
	if (!strcmp(this->currentCtrlUser, clientUser))
	{
		emit main_ChangeAudioFlag(Flag);
	}
}
void mainSocketThread::main_GetRequestForChangeMarkFlag(char* clientUser, char* Flag)
{
	if (!strcmp(this->currentCtrlUser, clientUser))
	{
		emit main_ChangeMarkFlag(Flag);
	}
}
void mainSocketThread::main_GetRequestForClearMark(char* clientUser)
{
	if (!strcmp(this->currentCtrlUser, clientUser))
	{
		emit main_MarkClear();
	}
}

void mainSocketThread::main_GetRequestForUsePlugin(char *clientUser, char *plugin_name)
{
	emit main_UsePlugin(clientUser, plugin_name);
}

void mainSocketThread::main_GetRequestForOperatePlugin(char *clientUser, char *pluginWidgetName, char *operate)
{
	emit main_OperatePlugin(clientUser, pluginWidgetName, operate);
}

void mainSocketThread::main_GetRequestForGetPluginList(char *clientUser)
{
	emit main_GetPluginList(clientUser);
}

void mainSocketThread::main_GetRequestForSaveLabel(char *clientUser)
{
	emit main_SaveLabel(clientUser);
}

void mainSocketThread::main_GetRequestForOriginalPoint(char *clientUser)
{
	emit main_OriginalPoint(clientUser);
}

void mainSocketThread::main_GetRequestForNewPoint(char *clientUser)
{
	emit main_NewPoint(clientUser);
}

void mainSocketThread::main_GetRequestForEditMask(char *clientUser)
{
	qDebug() << "step2";
	emit main_EditMask(clientUser);
	
}

//void mainSocketThread::main_GetRequestForCoordinate(char *message)
//{
//	emit main_Coordinate(message);
//}