#pragma once
#include "qthread.h"
#include "lacewing.h"
#include "DataFile.h"
#include "Service.h"
#include <QDebug>
#include <QReadWriteLock>
class httpThread_x :
	public QThread
{
public:
	httpThread_x();
	~httpThread_x();
	static void on_get(lacewing::webserver webserver, lacewing::webserver_request request);



protected:
	void run();

private:
	lacewing::eventpump eventpump;
	lacewing::webserver webserver;	
};

