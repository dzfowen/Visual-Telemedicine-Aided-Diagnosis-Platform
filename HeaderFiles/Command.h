/*
	By YaoTaihang	2015-11-03
	This Obejct is used to storage single command which is getted by CommandCollection from file.
*/
#include <stdio.h>
#include <vector>
#include <string>
using std::vector;
using std::string;


class Command
{
public:
	char* name;
	char* length;
	vector<char*> params;
	Command();
	Command(char* name, char* length,vector<char*> params);
	~Command();
private:

};