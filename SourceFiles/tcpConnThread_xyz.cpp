#include "tcpConnThread_xyz.h"

extern Service* service4;
extern float slice_x;
extern float slice_y;
extern float slice_z;


tcpConnThread_xyz::tcpConnThread_xyz()
{
}

tcpConnThread_xyz::tcpConnThread_xyz(SOCKET serconn)
{
	this->SerConn = serconn;
}


tcpConnThread_xyz::~tcpConnThread_xyz()
{
}

void tcpConnThread_xyz::run()
{
	while (true)
	{

		//qDebug() << "tcpConnThread run";
		char recvflag;
		Data data;
		recv(SerConn, &recvflag, 1, 0);
		QVTKWidget* widget = service4->Widget();
		vtkSmartPointer<vtkRenderWindow> renwin = widget->GetRenderWindow();
		vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
		if ('1' == recvflag)
		{
			//qDebug() << "tcp send buf";
			char sendBuf[48];
			camera = renwin->GetRenderers()->GetFirstRenderer()->GetActiveCamera();

			memset(sendBuf, 0, sizeof(sendBuf));
			memset(&data, 0, sizeof(data));
			data.position_x = camera->GetPosition()[0];
			data.position_y = camera->GetPosition()[1];
			data.position_z = camera->GetPosition()[2];
			data.focalpoint_x = camera->GetFocalPoint()[0];
			data.focalpoint_y = camera->GetFocalPoint()[1];
			data.focalpoint_z = camera->GetFocalPoint()[2];
			data.viewup_x = camera->GetViewUp()[0];
			data.viewup_y = camera->GetViewUp()[1];
			data.viewup_z = camera->GetViewUp()[2];
			data.slice_x = slice_x;
			data.slice_y = slice_y;
			data.slice_z = slice_z;

			memcpy(sendBuf, &data, sizeof(data));
			send(SerConn, sendBuf, sizeof(sendBuf), 0);


		}
		else if ('2' == recvflag)
		{
			camera = renwin->GetRenderers()->GetFirstRenderer()->GetActiveCamera();
			char recvbuf[48];
			recv(SerConn, recvbuf, sizeof(recvbuf), 0);
			memset(&data, 0, sizeof(data));
			memcpy(&data, recvbuf, sizeof(recvbuf));

			emit refreshGui(data);
		}
	}
	closesocket(SerConn);
	return;
}
