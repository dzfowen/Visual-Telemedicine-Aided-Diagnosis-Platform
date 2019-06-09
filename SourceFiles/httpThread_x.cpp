#include "httpThread_x.h"
#include <iostream>
#include <string>
#include <io.h>
#include "zip.h"
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <fstream>

extern Service* service1;
extern int recv_mask;
extern QStringList fileNameList;

void httpThread_x::on_get(lacewing::webserver webserver, lacewing::webserver_request request)
{
	std::string str;
	str = request->GET("Command");

	if (strcmp(str.c_str(), "getcurrentuser") == 0)

	{
		request->writef(service1->Currentuser().c_str());
	}
	if (strcmp(str.c_str(), "setcurrentuser") == 0)
	{
		std::string str1 = request->GET("currentuser");
		service1->Currentuser(str1);
	}
	if (strcmp(str.c_str(), "polling") == 0)
	{

	}
	if (strcmp(str.c_str(), "getlastFile") == 0)
	{
		char temp1[100];
		sprintf_s(temp1, "%d", service1->Lastfile());
		request->writef(temp1);
	}
	if (strcmp(str.c_str(), "segmentation") == 0)
	{
		request->write_file("output.jpg");
	}
	if (strcmp(str.c_str(), "finish") == 0)
	{
		char temp1[5];
		sprintf_s(temp1, "%d", recv_mask);
		request->writef(temp1);
	}
	if (strcmp(str.c_str(), "vtkFile") == 0)
	{
		request->write_file("a.vtk");
		qDebug() << "get vtk file" << endl;
	}

	if (strcmp(str.c_str(), "getFileList") == 0)
	{
		string strTosend;
		map<string, DataFile*>::iterator begin, end;
		end = service1->filedir.end();
		for (begin = service1->filedir.begin(); begin != end; begin++)
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
		i = service1->filedir.find(md5);
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
			qDebug("-----------dcm------");
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

void on_upload_start(lacewing::webserver,
	lacewing::webserver_request request,
	lacewing::webserver_upload upload)
{
	upload->set_autosave();
}

void on_upload_post(lacewing::webserver,
	lacewing::webserver_request request,
	lacewing::webserver_upload uploads[],
	size_t num_uploads)
{
	//qDebug() << "begin receive label image" << endl;
	for (size_t i = 0; i < num_uploads; ++i)

	{
		cout << uploads[i]->filename() << endl;
		cout << uploads[i]->autosave_filename() << endl;
		FILE *in_file, *out_file;
		char data[128];
		size_t bytes_in, bytes_out;
		long len = 0;

		fopen_s(&in_file, uploads[i]->autosave_filename(), "rb");
		fopen_s(&out_file, uploads[i]->filename(), "wb");

		while ((bytes_in = fread(data, 1, 128, in_file)) > 0)
		{
			bytes_out = fwrite(data, 1, bytes_in, out_file);
			if (bytes_in != bytes_out)
			{
				return;
			}
			len += bytes_out;
		}
		fclose(in_file);
		fclose(out_file);
		recv_mask = 0;
		qDebug() << "receive " << uploads[i]->filename() << endl;
	}
}


httpThread_x::httpThread_x()
{
	eventpump = lacewing::eventpump_new();
	webserver = lacewing::webserver_new(eventpump);
}


httpThread_x::~httpThread_x()
{

}

void httpThread_x::run()
{

	qDebug() << "http thread_x start";
	webserver->on_get(on_get);
	webserver->on_upload_start(on_upload_start);
	webserver->on_upload_post(on_upload_post);
	webserver->host(20000);
	eventpump->start_eventloop();

	lacewing::webserver_delete(webserver);
	lacewing::pump_delete(eventpump);
}
