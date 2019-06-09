#include "Service.h"



Service::Service()
{
}

Service::Service(int count,QVTKWidget* widget)
{
	this->widget = widget;
	tcpport = 10000 + count;
	httpport = 20000 + count;
	lastfile = 0;
	currentuser = "server";
}


Service::~Service()
{
}

//double Service::getCurrentpositionX()
//{
//	return this->CurrentfocalpointX;
//}
//
//void Service::SetCurrentpositionX(double CurrentpositionX)
//{
//	this->CurrentfocalpointX = CurrentpositionX;
//}
//
//double Service::getCurrentpositionY()
//{
//	return this->CurrentfocalpointY;
//}
//
//void Service::SetCurrentpositionY(double CurrentpositionY)
//{
//	this->CurrentfocalpointY = CurrentpositionY;
//}
//
//double Service::getCurrentpositionZ()
//{
//	return this->CurrentpositionZ;
//}
//
//void Service::SetCurrentpositionZ(double CurrentpositionZ)
//{
//	this->CurrentfocalpointZ = CurrentpositionZ;
//}
//
//double Service::getCurrentfocalpointX()
//{
//	return this->getCurrentfocalpointX;
//}
//
//void Service::setCurrentfocalpointX(double CurrentfocalpointX)
//{
//	this->CurrentfocalpointX = CurrentfocalpointX;
//}
//
//double Service::getCurrentfocalpointY()
//{
//	return this->getCurrentfocalpointY;
//}
//
//void Service::setCurrentfocalpointY(double CurrentfocalpointY)
//{
//	this->CurrentfocalpointY = CurrentfocalpointY;
//}
//
//double Service::getCurrentfocalpointZ()
//{
//	return this->getCurrentfocalpointZ;
//}
//
//void Service::setCurrentfocalpointZ(double CurrentfocalpointZ)
//{
//	this->CurrentfocalpointZ = CurrentfocalpointZ;
//}
//
//double Service::getCurrentviewupX()
//{
//	return this->CurrentviewupX;
//}
//
//void Service::setCurrentviewupX(double CurrentviewupX)
//{
//	this->CurrentviewupX = CurrentviewupX;
//}
//
//double Service::getCurrentviewupY()
//{
//	return this->CurrentviewupY;
//}
//
//void Service::setCurrentviewupY(double CurrentviewupY)
//{
//	this->CurrentviewupY = CurrentviewupY;
//}
//
//double Service::getCurrentviewupZ()
//{
//	return this->CurrentviewupZ;
//}
//
//void Service::setCurrentviewupZ(double CurrentviewupZ)
//{
//	this->CurrentviewupZ = CurrentviewupZ;
//}
