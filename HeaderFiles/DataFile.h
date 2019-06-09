#pragma once

using namespace std;
#include <string.h>
#include <string>



class DataFile
{
private:
	string path;
	
	//	vtkActor* actor;
	string md5;
	string name;

	string fileType;

	char* filebytes;
public:
	DataFile();
	~DataFile();
	DataFile(string path);
	char* getFilebytes();
	string getMD5(string pathNama);
	string getMD5();
	string getType();
	string getPath();

	std::string FileType() const { return fileType; }
	void FileType(std::string val) { fileType = val; }
	std::string Path() const { return path; }
	void Path(std::string val) { path = val; }
	std::string Name() const { return name; }
	void Name(std::string val) { name = val; }
};

