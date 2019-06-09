#include "tcpThread_z.h"

tcpThread_z::tcpThread_z()
{

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
	addr.sin_port = htons(30002);
	bind(serSocket, (sockaddr*)&addr, sizeof(sockaddr));
	listen(serSocket, 100);
}


tcpThread_z::~tcpThread_z()
{
}

void tcpThread_z::run()
{
	while (1)
	{
		qDebug() << "tcpThread_z waiting accept";
		SOCKET serConn = accept(serSocket, (struct sockaddr*)&clientsocket, &len);
		connthread = new tcpConnThread_z(serConn);
		connect(connthread, SIGNAL(refreshGui(Data)), this, SLOT(refresh(Data)));

		connthread->start();
	}
	closesocket(serSocket);
	WSACleanup();

}

void tcpThread_z::refresh(Data data)
{
	emit refreshGui(data);
}


