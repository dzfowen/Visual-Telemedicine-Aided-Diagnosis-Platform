/*
	By YaoTaihang	2015-11-03
	This Object is used to creat commandCollection by command.xml file at loacl project.
	CommandCollection is used to write commands by messages or translate messages into command.
	CommandCollection is storaged by command obeject;
*/
#include "CommandCollection.h"
#include <qdebug.h>
CommandCollection::CommandCollection(char * filePath)
{
	qDebug("enter command");
	//Load CommandFile
	TiXmlDocument doc(filePath);
	doc.LoadFile();
	
	//Analysis this CommandFile
	TiXmlElement * rootElement = doc.RootElement();
	for (TiXmlElement * CommandElement = rootElement->FirstChildElement("Command");
		CommandElement != NULL;
		CommandElement = CommandElement->NextSiblingElement())
	{
		//Change const char* into char * 
		char * name = new char[strlen(CommandElement->Attribute("name"))];
		strcpy(name, CommandElement->Attribute("name"));
		char * length = new char[strlen(CommandElement->Attribute("length"))];
		strcpy(length, CommandElement->Attribute("length"));

		vector<char*> params;
		for (TiXmlElement * commandParamElement = CommandElement->FirstChildElement("param");
			commandParamElement != NULL;
			commandParamElement = commandParamElement->NextSiblingElement())
		{
			//Change const char* into char * 
			char * param = new char[strlen(commandParamElement->FirstChild()->Value())];
			strcpy(param, commandParamElement->FirstChild()->Value());
			params.push_back(param);
		}
		
		//Create new Command
		Command * command = new Command(name, length, params);
		//Add this Command into CommandCollection
		this->AllCommands.push_back(command);
	}
}