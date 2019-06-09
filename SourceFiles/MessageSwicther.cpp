#include "MessageSwicther.h"
#include "qdebug.h"
//将src中的separator全部找出存到vector中并返回。
vector<char*> MessageSwitcher::StringSplit(char* src, char *separator){
	string str(src);
	//string sep(separator);
	vector<char*> result;
	string substring;
	string::size_type start = 0, index;
	do
	{
		//返回的是位置索引，由srart位置起查找第一个出现的separator
		index = str.find_first_of(separator, start);
		//这里的npos是当查找没有找到时的返回值
		if (index != string::npos)
		{
			//将查找到的字符串赋值给substring
			substring = str.substr(start, index - start);
			char* sub = new char[substring.length()+1];
			//string.c_str()将字符串转换成char型指针，指向第一个
			strcpy(sub, substring.c_str());
			sub[substring.length()] = '\0';
			//将sub存储到result 中
			result.push_back(sub);
			//从index开始搜索不匹配separator的字符，即开始下一次搜寻
			start = str.find_first_not_of(separator, index);
			//全部都匹配了，则搜寻结束，返回result
			if (start == string::npos) 
				return result;
		}
	} while (index != string::npos);

	//the last token
	//未指定长度的情况下，将start延续到结尾。
	substring = str.substr(start);
	char* sub = new char[substring.length() + 1];
	strcpy(sub, substring.c_str());
	sub[substring.length()] = '\0';
	result.push_back(sub);
	return result;
}
//在str后面加上size个空格
void MessageSwitcher::PushSpaceToString(char * str, int size){
	for (int i = strlen(str); i < size; i++)
	{
		str[i] = ' ';
	}
	str[size] = '\0';
}

MessageSwitcher::MessageSwitcher(char * CommandXMLFilePath)
{
	//Load Command File
	this->CommandXMLFilePath = CommandXMLFilePath;
	this->myCommandCollection = new CommandCollection(this->CommandXMLFilePath);
}
// creat message with command
char* MessageSwitcher::CreateMessageWithCommand(char * CommandName, vector<char*> params){
	//Traverse CommandCollection
	for (int i = 0; i < this->myCommandCollection->AllCommands.size(); i++)
	{
		//Search right Command
		if (!strcmp(this->myCommandCollection->AllCommands[i]->name, CommandName))
		{
			//Create Message
			char* name = new char[NAMELENGTH]; name[0] = '\0';
			char* length = new char[BODYLENGTH]; length[0] = '\0';
			strcpy(name, this->myCommandCollection->AllCommands[i]->name);
			PushSpaceToString(name, NAMELENGTH);
			strcpy(length, this->myCommandCollection->AllCommands[i]->length);
			PushSpaceToString(length, BODYLENGTH);
			int Length = atoi(length);
			char* CommandMessageBody = new char[Length]; CommandMessageBody[0] = '\0';
			if (params.size() == this->myCommandCollection->AllCommands[i]->params.size())
			{
				for (int j = 0; j < params.size(); j++)
				{
					if (j != 0){
						strcat(CommandMessageBody, " ");
					}
					//连接两个字符串
					strcat(CommandMessageBody, myCommandCollection->AllCommands[i]->params[j]);
					strcat(CommandMessageBody, "=");
					strcat(CommandMessageBody, params[j]);

				}
			}
			PushSpaceToString(CommandMessageBody,Length);
			/*
				Because of the problem like:
				"CRT detected that the application wrote to memory after end of heap buffer"
				This char* size must new a size with length + 1
			*/
			char * CommandMessage = new char[NAMELENGTH + BODYLENGTH + Length + ENDBODYLENGTH + 1];
			CommandMessage[0] = '\0';
			CommandMessage[NAMELENGTH + BODYLENGTH + Length + ENDBODYLENGTH] = '\0';
			strcat(CommandMessage, name);
			strcat(CommandMessage, length);
			strcat(CommandMessage, CommandMessageBody);
			strcat(CommandMessage, ENDBODY);

			params.clear();
			params.swap(vector<char*>());

			return CommandMessage;
		}
	}
	return NULL;
}
// creat message with dynamic command
char* MessageSwitcher::CreateMessageWithDynamicCommand(char * CommandName, long int exLength, char * param){
	//Traverse CommandCollection
	for (int i = 0; i < this->myCommandCollection->AllCommands.size(); i++)
	{
		
		//Search right Command
		if (!strcmp(this->myCommandCollection->AllCommands[i]->name, CommandName))
		{
			
			if (!strcmp(this->myCommandCollection->AllCommands[i]->length, DYNAMICLENGTH))
			{
				
				//Create Message
				char* name = new char[NAMELENGTH]; name[0] = '\0';
				char* length = new char[BODYLENGTH]; length[0] = '\0';
				strcpy(name, this->myCommandCollection->AllCommands[i]->name);
				PushSpaceToString(name, NAMELENGTH);
				itoa(exLength, length, 10);
				PushSpaceToString(length, BODYLENGTH);
				
				
				char * CommandMessage = new char[NAMELENGTH + BODYLENGTH + exLength + ENDBODYLENGTH + 1];
				memset(CommandMessage, 0, NAMELENGTH + BODYLENGTH + exLength + ENDBODYLENGTH + 1);
				strcat(CommandMessage,name);
				strcat(CommandMessage, length);
				for (int j = 0; j < exLength; j++)
				{
					CommandMessage[NAMELENGTH + BODYLENGTH + j] = param[j];
				}

				for (int j = 0; j < ENDBODYLENGTH; j++)
				{
					CommandMessage[NAMELENGTH + BODYLENGTH + exLength + j] = ENDBODY[j];
				}

				CommandMessage[NAMELENGTH + BODYLENGTH + exLength + ENDBODYLENGTH + 1] = '\0';

				return CommandMessage;
			}
		}
	}
	return NULL;
}
// read message with command
vector<char*> MessageSwitcher::ReadMessageWithCommand(char* CommandName, char* CommandMessageBody)
{
	vector <char*> params;
	//Traverse C
	for (int i = 0; i < this->myCommandCollection->AllCommands.size(); i++)
	{
		//Search right Command
		if (!strcmp(this->myCommandCollection->AllCommands[i]->name, CommandName))
		{
			vector<char*> allParams;
			allParams = this->StringSplit(CommandMessageBody, " ");
			for (int j = 0; j < allParams.size(); j++)
			{
				params.push_back(this->StringSplit(allParams[j],"=")[1]);
			}
			return params;
		}
	}
	return params;
}
// 
void MessageSwitcher::ReadMessageHeadForGetNameAndLength(char* MessageHead, char * CommandName, char * Length){
	vector<char* > head = this->StringSplit(MessageHead, " ");
	strcpy(CommandName, head[0]);
	CommandName[strlen(head[0])] =  '\0';
	strcpy(Length, head[1]);
	Length[strlen(head[1])] = '\0';
}