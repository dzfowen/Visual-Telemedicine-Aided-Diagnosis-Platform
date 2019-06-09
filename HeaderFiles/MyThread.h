#pragma once
#include <QThread>
#include "lacewing.h"
#include <string>

extern int availablechannel;

class MyThread :
	public QThread
{
public:
	MyThread();
	~MyThread();
	static void on_get(lacewing::webserver webserver, lacewing::webserver_request request);
	
protected:
	void run();
private:

	lacewing::eventpump eventpump;
	lacewing::webserver webserver;

};

