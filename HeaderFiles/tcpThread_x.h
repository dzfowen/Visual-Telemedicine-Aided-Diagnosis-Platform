#pragma once
#include "qthread.h"
#include "Service.h"
#include "tcpConnThread_x.h"
#include <QDebug>

class tcpThread_x :
	public QThread
{
	Q_OBJECT
public:
	tcpThread_x();
	~tcpThread_x();

protected:
	void run();

private:
	int socketDescriptor;
	SOCKET serConn;
	sockaddr_in clientsocket;
	int len = sizeof(sockaddr_in);

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

	SOCKET serSocket;
	tcpConnThread_x* connthread;

signals:
	void refreshGui(Data);

private slots:
	void refresh(Data);
};

