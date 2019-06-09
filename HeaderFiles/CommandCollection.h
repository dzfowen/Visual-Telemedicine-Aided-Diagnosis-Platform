/*
	By YaoTaihang	2015-11-03
	This Object is used to creat commandCollection by command.xml file at loacl project.
	CommandCollection is used to write commands by messages or translate messages into command.
	CommandCollection is storaged by command obeject;

*/

#include <stdio.h>
#include "tinyxml.h"
#include "Command.h"
class CommandCollection
{
public:
	vector<Command*> AllCommands;
	CommandCollection(char* filePath);
	~CommandCollection();
private:
};