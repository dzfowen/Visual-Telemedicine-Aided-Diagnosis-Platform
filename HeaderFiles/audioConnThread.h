#ifndef AUDIOCONNTHREAD_H
#define AUDIOCONNTHREAD_H
#pragma once
#include "qthread.h"
#include "Service.h"
#include "audioPlay.h"
#include <QDebug>
#include <windows.h>
#include <WINSOCK2.H>
#include <stdio.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")


class audioConnThread : public QThread{
	Q_OBJECT
public:
	audioConnThread();
	~audioConnThread();
	audioConnThread(SOCKET);

	char ClientUser[20];
	SOCKET SerConn;

	void sendAudioBuffer(CHAR * buf, int buffersize);
protected:
	void run();
private:

signals ://可以看做是私有的
	void audioSingle_ForwardAudioToOthers(char* clientUser, char* Buffer, int BufferSize);
		 void audioSingle_Disconnect(char* clientUser);
};
#endif
