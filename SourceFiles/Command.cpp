#include "Command.h"
Command::Command(char* name, char* length, vector<char*> params)
{
	this->name = name;
	this->length = length;
	this->params = params;
}