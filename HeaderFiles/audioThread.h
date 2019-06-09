#pragma once
#include "qthread.h"
#include "Service.h"
#include "audioRecordThread.h"
#include <QDebug>
#include <vector>
using namespace std;

class audioThread:public QThread
{
	Q_OBJECT;
public:
	audioThread();
	~audioThread();
	vector<audioConnThread*> allAudioConnThread;
	audioConnThread* connthread;
	audioRecordThread* audioRecordthread;
	bool audioThreadFlag;
	void SetPause();
	void SetRestart();

	void audioMain_ForwardAudioToOthers(char* clientUser, char* Buffer, int BufferSize);
	void audioMain_Disconnect(char* clientUser);


protected:
	void run();
private:
	int socketDescriptor;
	SOCKET serConn;
	sockaddr_in clientsocket;
	int len = sizeof(sockaddr_in);
	SOCKET serSocket;
signals:
	void sendAudioBufferMsg(CHAR * buf);
public slots:
	void sendAudioBufferMsgCopy(CHAR * buf);
	

};
