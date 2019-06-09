#include "singleSocketThread.h"
#include <qdebug.h>

singleSocketThread::singleSocketThread()
{

}

singleSocketThread::singleSocketThread(SOCKET socket, MessageSwitcher * messageSwitcher)
{
	this->currentSocket = socket;
	this->messageSwitcher = messageSwitcher;
	this->ClientUser[0] = '\0';
}

singleSocketThread::~singleSocketThread()
{
	closesocket(this->currentSocket);
}
//处理网络命令请求的
void singleSocketThread::run()
{
	//Keep reading message
	while (true)
	{
		//Get the msg command
		char * messageHead = new char[NAMELENGTH + BODYLENGTH+1]; messageHead[NAMELENGTH + BODYLENGTH] = '\0';
		char * commandName = new char[NAMELENGTH+1]; commandName[NAMELENGTH] = '\0';
		char * length = new char[BODYLENGTH+1]; length[BODYLENGTH] = '\0';
		//将网络中接收的数据传到messageHead中。
		int errorFlag = recv(this->currentSocket, messageHead, NAMELENGTH + BODYLENGTH, 0);
		//Check the client connect when it is domn,releas it
		if (errorFlag == 0 ){
			emit socket_ClientDisconnect(this->ClientUser);
			break;
		}
		this->messageSwitcher->ReadMessageHeadForGetNameAndLength(messageHead, commandName, length);
		
		//qDebug() << messageHead;
		//qDebug() << commandName;
		
		//Get message body and check it
		int Length = atoi(length);
		char * messageBody = new char[Length+1]; messageBody[Length] = '\0';
		char * messageTail = new char[ENDBODYLENGTH+1]; messageTail[ENDBODYLENGTH] = '\0';
		recv(this->currentSocket, messageBody, Length, 0); 
		recv(this->currentSocket, messageTail, ENDBODYLENGTH, 0);

		qDebug() << messageHead<<" "<<messageBody;

		//Check the message whether is complete
		if (!strcmp(messageTail, ENDBODY))
		{
			//All Commands are here
			if (!strcmp(commandName, RECV_CLIENTCONNECT))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				strcpy(this->ClientUser,params[0]);
				this->SendImage = true;
				emit sochet_NewUserConnect(params[0]);
				qDebug("-Client User:%s		is connected.", this->ClientUser);
			}
			else if (!strcmp(commandName, RECV_CLIENTDISCONNECT))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				qDebug("-Client User:%s		is disconnect.", params[0]);
				//Send client disconnet to main socket thread
				emit socket_ClientDisconnect(this->ClientUser);
				break;
			}
			else if (!strcmp(commandName, RECV_LIVEBREATHE))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				//You can do anything when the socket is alive
			}
			else if (!strcmp(commandName, RECV_GETCHANNELCOUNT))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				//Client wants to know the count of channel
				qDebug("-Client User:%s		requests chanel count.",params[0]);
				emit socket_GetChannelCount(this->ClientUser);
			}
			else if (!strcmp(commandName, SEND_SCREENSHOTSEND))
			{
				//Got A BMP FILE
				//转发
				emit socket_ForwardToOtherClient(this->ClientUser, messageBody);
			}
			else if (!strcmp(commandName, RECV_SCREENSHOTGETCTRL))
			{
				//When Some one will get screenshot control
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				qDebug("-Client User:%s		requests get screenshot control.",params[0]);
				emit socket_ClientGetScreenshotCtrl(this->ClientUser, params[1], params[2]);
			}
			else if (!strcmp(commandName, RECV_SCREENSHOTEVENT))
			{
				//When get some event for screenshot ,send signal to server
				emit socket_EventForScreenshot(messageBody);
			}
			else if (!strcmp(commandName, RECV_SCREENSHOTCHANGEWIN))
			{
				//When get change window request
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				qDebug("-Client User:%s		send screenshot change windows requset,change it into %s.", params[0],params[1]);
				emit socket_ChangeWinForScreenshot(params[1]);
			}
			else if (!strcmp(commandName, RECV_SCROLLBARCURSEND))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				emit socket_ChangeScrollBar(params[0],params[1]);
			}
			else if (!strcmp(commandName, RECV_AUDIOREQFLAGCHANGE))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				emit socket_ChangeAudioFlag(params[0], params[1]);
			}
			else if (!strcmp(commandName, RECV_MARKREQFLAGCHANEG))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				emit socket_ChangeMarkFlag(params[0], params[1]);
			}
			else if (!strcmp(commandName, RECV_MARKREQCLEAR))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				emit socket_MarkClear(params[0]);
			}
			else if (!strcmp(commandName, RECV_GETPLUGINLIST))
			{ 
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				if (params.size() < 1) continue;
				strcpy(this->ClientUser, params[0]);
				emit socket_GetPluginList(params[0]);
			}
			else if (!strcmp(commandName, RECV_USEPLUGIN))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				if (params.size() < 2) continue;
				emit socket_UsePlugin(params[0], params[1]);
			}
			else if (!strcmp(commandName, RECV_OPERATEPLUGIN))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				if (params.size() < 3) continue;
				emit socket_OperatePlugin(params[0], params[1], params[2]);
			}
			else if (!strcmp(commandName, RECV_SAVELABEL))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				if (params.size() < 1) continue;
				emit socket_SaveLabel(params[0]);
			}
			else if (!strcmp(commandName, RECV_ORIGINALPOINT))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				if (params.size() < 1) continue;
				emit socket_OriginalPoint(messageBody);
				qDebug() << messageBody;
			}
			else if (!strcmp(commandName, RECV_NEWPOINT))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				if (params.size() < 1) continue;
				emit socket_NewPoint(params[0]);
			}
			else if (!strcmp(commandName, RECV_EDITMASK))
			{
				vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
				if (params.size() < 1) continue;
				emit socket_EditMask(params[0]);
				qDebug() << "step1";
			}
			//else if (!strcmp(commandName, RECV_COORDINATE))
			//{
			//	vector<char*> params = this->messageSwitcher->ReadMessageWithCommand(commandName, messageBody);
			//	//if (params.size() < 1) continue;
			//	emit socket_Coordinate(messageBody);
			//	//qDebug() << messageBody;
			//}
		}
	}
}
//send message to current socket client
void singleSocketThread::sendMessageToCurrentSocketClient(char* message, int MessageLastUseFlag)
{   
	qDebug() << strlen(message);

	send(this->currentSocket, message, strlen(message), 0);
	//if (MessageLastUseFlag){
	//	delete[] message; message = NULL;
	//}
} 

void singleSocketThread::sendMessageToCurrentSocketClient(char* message, int messageLength, int MessageLastUseFlag)
{
	qDebug() << strlen(message);

	//qDebug() <<"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" <<messageLength;
	send(this->currentSocket, message, messageLength , 0);
	if (MessageLastUseFlag){
		//qDebug() << "get a last message?";
		//delete[] message; message = NULL;
	}
}
