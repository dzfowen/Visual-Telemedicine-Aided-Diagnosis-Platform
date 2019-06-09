#pragma once
#include "qthread.h"
#include "Service.h"
#include "tcpConnThread_z.h"
#include <QDebug>

class tcpThread_z :
	public QThread
{
	Q_OBJECT
public:
	tcpThread_z();
	~tcpThread_z();

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
	};

	SOCKET serSocket;
	tcpConnThread_z* connthread;

signals:
	void refreshGui(Data);

	private slots:
	void refresh(Data);
};

