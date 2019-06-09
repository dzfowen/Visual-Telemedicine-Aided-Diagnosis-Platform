#pragma once
#include "qthread.h"
#include "Service.h"
#include <QDebug>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <windows.h>
#include <WINSOCK2.H>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

class tcpConnThread_xyz :
	public QThread
{
	Q_OBJECT
public:
	tcpConnThread_xyz();
	~tcpConnThread_xyz();
	tcpConnThread_xyz(SOCKET);

protected:
	void run();

private:
	SOCKET SerConn;

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

signals:
	void refreshGui(Data);
};

