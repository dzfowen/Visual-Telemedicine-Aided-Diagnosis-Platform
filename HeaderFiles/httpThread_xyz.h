#pragma once
#include "qthread.h"
#include "lacewing.h"
#include "DataFile.h"
#include "Service.h"
#include <QDebug>
#include <QReadWriteLock>
class httpThread_xyz :
	public QThread
{
public:
	httpThread_xyz();
	~httpThread_xyz();
	static void on_get(lacewing::webserver webserver, lacewing::webserver_request request);



protected:
	void run();

private:
	lacewing::eventpump eventpump;
	lacewing::webserver webserver;

};

