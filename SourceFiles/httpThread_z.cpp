#include "httpThread_z.h"

extern Service* service3;

void httpThread_z::on_get(lacewing::webserver webserver, lacewing::webserver_request request)
{
	std::string str;
	str = request->GET("Command");
	qDebug() << "http thread_z " << str.c_str() << endl;

	if (strcmp(str.c_str(), "getcurrentuser") == 0)
	{
		request->writef(service3->Currentuser().c_str());
	}
	if (strcmp(str.c_str(), "setcurrentuser") == 0)
	{
		std::string str1 = request->GET("currentuser");
		service3->Currentuser(str1);
	}
	if (strcmp(str.c_str(), "polling") == 0)
	{

	}
	if (strcmp(str.c_str(), "getlastFile") == 0)
	{
		char temp1[100];
		sprintf_s(temp1, "%d", service3->Lastfile());
		request->writef(temp1);
	}
	if (strcmp(str.c_str(), "getFileList") == 0)
	{
		string strTosend;
		map<string, DataFile*>::iterator begin, end;
		end = service3->filedir.end();
		for (begin = service3->filedir.begin(); begin != end; begin++)
		{
			strTosend += (*begin).first + ",";
		}
		if (strTosend.length() != 0)
		{
			strTosend = strTosend.substr(0, strTosend.length() - 1);
		}
		request->writef(strTosend.c_str());
	}
	if (strcmp(str.c_str(), "getFile") == 0)
	{
		string md5 = request->GET("md5");
		map<string, DataFile*>::iterator i;
		i = service3->filedir.find(md5);
		if ((*i).second->getType() == ".vtk")
		{
			//HZIP hz;
			string oripath = (*i).second->getPath();
			//string path = oripath.substr(0, oripath.find_last_of(".")) + ".zip";
			//hz = CreateZip(path.c_str(), 0);
			//ZipAdd(hz, oripath.substr(oripath.find_last_of("/") + 1).c_str(), oripath.c_str());
			//CloseZip(hz);
			//request->write_file(path.c_str());
			request->write_file(oripath.c_str());

		}
		if ((*i).second->getType() == ".mhd")
		{
			request->write_file((*i).second->Path().c_str());

		}
		if ((*i).second->getType() == ".raw")
		{
			request->write_file((*i).second->Path().c_str());

		}
		else if ((*i).second->getType() == ".dcm")
		{
			request->write_file((*i).second->Path().c_str());
			//HZIP hz;
			//string fold = (*i).second->getPath().substr(0, (*i).second->getPath().find_last_of("/"));
			//_finddata_t file;
			//string path2 = fold + ".zip";
			//long longf;
			////TCHAR pathT[50] = { '0' };
			////mbstowcs(pathT, path2.c_str(), path2.size());
			//hz = CreateZip(path2.c_str(), 0);
			//
			//if ((longf = _findfirst((fold + "/*.*").c_str(), &file)) == -1l)
			//{
			//	qDebug() << "cannot find file";
			//}
			//else
			//{
			//	string tempName;
			//	while (_findnext(longf, &file) == 0)
			//	{
			//		tempName = "";
			//		tempName = file.name;
			//		//TCHAR tempNameT[50] = {'0'};
			//		//mbstowcs(tempNameT, tempName.c_str(), tempName.size());
			//		//TCHAR tempNameT2[50] = {'0'};
			//		//mbstowcs(tempNameT2, (fold + "/" + tempName).c_str(), (fold + "/" + tempName).size());
			//		ZipAdd(hz, tempName.c_str(), (fold + "/" + tempName).c_str());
			//		qDebug() << tempName.c_str();
			//	}
			//}
			//_findclose(longf);
			//CloseZip(hz);
			//request->write_file(path2.c_str());
		}
	}
}

httpThread_z::httpThread_z()
{
	eventpump = lacewing::eventpump_new();
	webserver = lacewing::webserver_new(eventpump);
}


httpThread_z::~httpThread_z()
{
}

void httpThread_z::run()
{
	qDebug() << "http thread_z start";	webserver->on_get(on_get);
	webserver->host(20002);
	eventpump->start_eventloop();

	lacewing::webserver_delete(webserver);
	lacewing::pump_delete(eventpump);
}
