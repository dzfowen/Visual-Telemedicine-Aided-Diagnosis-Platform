
using namespace std;
#include <DataFile.h>
#include <iostream>
#include <stdio.h>
#include <memory.h>
#include <string>
#include "md5.h"
#include <string>
#include <iostream>
#include <string.h>
#include <fstream>
#include <istream>



DataFile::DataFile(string path){
	this->path = path;
	this->md5 = getMD5(path);
	this->fileType = path.substr(path.find_last_of("."));
	this->name = path.substr(path.find_last_of("/") + 1); 
	
	ifstream inFile(path, ios::in);
	istream::pos_type startPos = inFile.tellg();   //�ļ�ͷλ��
	inFile.seekg(0, ios_base::end); // �ƶ����ļ�β
	long size=inFile.tellg(); // ȡ�õ�ǰλ�õ�ָ�볤�� ���ļ�����
	inFile.seekg(startPos); // �ƶ���ԭ����λ��
	this->filebytes=new char[size];
	inFile.read(filebytes, size);

}

DataFile::DataFile()
{

}

char* DataFile::getFilebytes()
{
	return filebytes;
}

string DataFile::getMD5(string pathName)
{
	MD5 md(pathName);
	string result=md.md5();
	return result;
}

string DataFile::getMD5()
{
	return this->md5;
}

std::string DataFile::getType()
{
	return this->fileType;
}

string DataFile::getPath()
{
	return this->path;
}

DataFile::~DataFile()
{

}
