#include "MyThread.h"
#include <QDebug>

MyThread::MyThread()
{
	eventpump = lacewing::eventpump_new();
	webserver = lacewing::webserver_new(eventpump);
}


MyThread::~MyThread()
{
}




void MyThread::run(){
	eventpump = lacewing::eventpump_new();
	webserver = lacewing::webserver_new(eventpump);
	webserver->on_get(on_get);
	webserver->host(8888);
	eventpump->start_eventloop();

	lacewing::webserver_delete(webserver);
	lacewing::pump_delete(eventpump);
}

void MyThread::on_get(lacewing::webserver webserver, lacewing::webserver_request request)
{

	std::string str;
	str = request->GET("Command");
	//获取请求命令
	qDebug() << "my thread get:" << str.c_str();
	//string:c_str返回字符串首地址
	if (strcmp(str.c_str(), "getChannelCount") == 0)
	{
		char temp[5];

		sprintf_s(temp, "%d", availablechannel);
		//将availablechannel写入temp，并防止了溢出。
		request->writef(temp);

		qDebug() << "my thread send:" << temp;
	}
}

