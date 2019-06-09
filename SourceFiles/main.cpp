#include "server.h"
#include <QtWidgets/QApplication>
#include "Service.h"


Service* service1;
Service* service2;
Service* service3;
Service* service4;




int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	Server w;
	w.show();//显示窗体
	return a.exec();
}
