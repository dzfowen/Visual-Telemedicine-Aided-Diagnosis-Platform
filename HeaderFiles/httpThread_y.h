#pragma once
#include "qthread.h"
#include "lacewing.h"
#include "DataFile.h"
#include "Service.h"
class httpThread_y :
	public QThread
{
public:
	httpThread_y();
	~httpThread_y();
	static void on_get(lacewing::webserver webserver, lacewing::webserver_request request);


protected:
	void run();

private:
	lacewing::eventpump eventpump;
	lacewing::webserver webserver;

};


