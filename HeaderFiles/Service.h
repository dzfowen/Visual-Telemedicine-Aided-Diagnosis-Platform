#pragma once
#include <string>
#include <time.h>
#include <map>
#include "DataFile.h"
#include "httpThread_x.h"
#include "QVTKWidget.h"

class Service
{
public:
	Service();
	Service(int count,QVTKWidget* widget);//将VTKWindow展示在QWindow上
	~Service();
	std::string Currentuser() const { return currentuser; }
	void Currentuser(std::string val) { currentuser = val; }

	int Httpport() const { return httpport; }
	void Httpport(int val) { httpport = val; }

	long Lastfile() const { return lastfile; }
	void Lastfile(long val) { lastfile = val; }

	int Tcpport() const { return tcpport; }
	void Tcpport(int val) { tcpport = val; }

	QVTKWidget* Widget() const { return widget; }
	void Widget(QVTKWidget* val) { widget = val; }

	std::map<std::string, DataFile*> filedir;

	double getCurrentpositionX();
	void SetCurrentpositionX(double);

	double getCurrentpositionY();
	void SetCurrentpositionY(double);

	double getCurrentpositionZ();
	void SetCurrentpositionZ(double);

	double getCurrentfocalpointX();
	void setCurrentfocalpointX(double);

	double getCurrentfocalpointY();
	void setCurrentfocalpointY(double);

	double getCurrentfocalpointZ();
	void setCurrentfocalpointZ(double);

	double getCurrentviewupX();
	void setCurrentviewupX(double);

	double getCurrentviewupY();
	void setCurrentviewupY(double);

	double getCurrentviewupZ();
	void setCurrentviewupZ(double);


private:

	int httpport;

	int tcpport;

	long lastfile;

	std::string currentuser;

	QVTKWidget* widget;


	double CurrentpositionX;
	double CurrentpositionY;
	double CurrentpositionZ;
	//焦点x,y,z的当前值
	double CurrentfocalpointX;
	double CurrentfocalpointY;
	double CurrentfocalpointZ;

	double CurrentviewupX;
	double CurrentviewupY;
	double CurrentviewupZ;
	//获取时间标识
	long getTimeStamp();

	void FileUpdate();
};

