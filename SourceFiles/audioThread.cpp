/*
	audioThread 
	creat by Yaotaihang
	2015-10-15
*/
#include "audioThread.h"

audioThread::audioThread()
{
	audioThreadFlag = false;

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
	serSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(40000);
	bind(serSocket, (sockaddr*)&addr, sizeof(sockaddr));
	listen(serSocket, 100);

	//Define record audio service
	audioRecordthread = new audioRecordThread();
	//connect(audioRecordthread, SIGNAL(sendAudioBufferMsg(CHAR*)), this, SLOT(sendAudioBufferMsgCopy(CHAR*)));
};
audioThread::~audioThread()
{

};

void audioThread::run()
{
	this->audioThreadFlag = true;
	//Begin record audio service
	bool audioRecordStartFlag = false;
	int clientnum = 0;
	
	while (this->audioThreadFlag)
	{
		qDebug() << "audioThread waiting accept";
		SOCKET serConn = accept(serSocket, (struct sockaddr*)&clientsocket, &len);
		connthread = new audioConnThread(serConn);

		//Add this connection into audioRecord thread
		allAudioConnThread.push_back(connthread);

		//Connect frome the single audio to main audio

		audioRecordthread->copyAllAudioConnThread(allAudioConnThread);
		clientnum++;
		qDebug("There are totally %d clients", clientnum);
		//This conn start
		connthread->start();
		//If audio record do not start , start it
		if (audioRecordStartFlag == false)
		{
			audioRecordthread->start();
			audioRecordStartFlag = true;
		}
	}
	closesocket(serSocket);
	WSACleanup();
};

void audioThread::sendAudioBufferMsgCopy(CHAR* buf)
{
	emit sendAudioBufferMsg(buf);
};

void audioThread::SetPause()
{
	this->audioThreadFlag = false;
	this->audioRecordthread->audioRecordThreadFlag = false;
}

void audioThread::SetRestart()
{
	this->audioThreadFlag = true;
	this->audioRecordthread->audioRecordThreadFlag = true;
}

void audioThread::audioMain_ForwardAudioToOthers(char* clientUser, char* Buffer, int BufferSize)
{
	for (int i = 0; i < this->allAudioConnThread.size(); i++)
	{
		if (strcmp(this->allAudioConnThread[i]->ClientUser, clientUser))
		{
			this->allAudioConnThread[i]->sendAudioBuffer(Buffer, BufferSize);
		}
	}
}

void audioThread::audioMain_Disconnect(char* clientUser)
{
	for (int i = 0; i < this->allAudioConnThread.size(); i++)
	{
		if (!strcmp(this->allAudioConnThread[i]->ClientUser, clientUser))
		{
			std::vector<audioConnThread*>::iterator it = this->allAudioConnThread.begin() + i;
			this->allAudioConnThread.erase(it);
			break;
		}
	}
}