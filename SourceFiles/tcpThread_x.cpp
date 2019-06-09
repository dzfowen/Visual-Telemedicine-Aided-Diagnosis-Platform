#include "tcpThread_x.h"

tcpThread_x::tcpThread_x()
{
	
	HANDLE hThread;  //���
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
	addr.sin_family = AF_INET;//��ַ���壬����������TCP/IPЭ��
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(30000);
	bind(serSocket, (sockaddr*)&addr, sizeof(sockaddr));//ָ����ַ��Ϣ
	listen(serSocket, 100);
}


tcpThread_x::~tcpThread_x()
{
}

void tcpThread_x::run()
{
	//ʼ�ռ�����socket������
	while (1)
	{
		qDebug() << "tcpThread_x waiting accept";
		SOCKET serConn = accept(serSocket, (struct sockaddr*)&clientsocket, &len);
		connthread = new tcpConnThread_x(serConn);
		connect(connthread, SIGNAL(refreshGui(Data)), this, SLOT(refresh(Data)));
		connthread->start();
	}
	closesocket(serSocket);
	WSACleanup();

}

void tcpThread_x::refresh(Data data)
{
	emit refreshGui(data);
}


