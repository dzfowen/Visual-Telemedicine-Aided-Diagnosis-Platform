#ifndef AUDIORECORDTHREAD_H
#define AUDIORECORDTHREAD_H

#include "qthread.h"
#include "Service.h"
#include "audioConnThread.h"
#include <QDebug>
#include <windows.h>
#include <WINSOCK2.H>
#include <stdio.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "winmm.lib")  

class audioRecordThread :public QThread{
	Q_OBJECT
public:
	audioRecordThread();
	~audioRecordThread();
	vector<audioConnThread*> allAudioConnThread;
	void copyAllAudioConnThread(vector<audioConnThread*> allconn);
	void audioCallback();
	bool audioRecordThreadFlag;
protected:
	void run();
signals:
	void sendAudioBufferMsg(CHAR * buf);
};

#endif
