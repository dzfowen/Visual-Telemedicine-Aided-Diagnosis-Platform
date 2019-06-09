#include "MessageSwicther.h"
#include "qdebug.h"
//��src�е�separatorȫ���ҳ��浽vector�в����ء�
vector<char*> MessageSwitcher::StringSplit(char* src, char *separator){
	string str(src);
	//string sep(separator);
	vector<char*> result;
	string substring;
	string::size_type start = 0, index;
	do
	{
		//���ص���λ����������srartλ������ҵ�һ�����ֵ�separator
		index = str.find_first_of(separator, start);
		//�����npos�ǵ�����û���ҵ�ʱ�ķ���ֵ
		if (index != string::npos)
		{
			//�����ҵ����ַ�����ֵ��substring
			substring = str.substr(start, index - start);
			char* sub = new char[substring.length()+1];
			//string.c_str()���ַ���ת����char��ָ�룬ָ���һ��
			strcpy(sub, substring.c_str());
			sub[substring.length()] = '\0';
			//��sub�洢��result ��
			result.push_back(sub);
			//��index��ʼ������ƥ��separator���ַ�������ʼ��һ����Ѱ
			start = str.find_first_not_of(separator, index);
			//ȫ����ƥ���ˣ�����Ѱ����������result
			if (start == string::npos) 
				return result;
		}
	} while (index != string::npos);

	//the last token
	//δָ�����ȵ�����£���start��������β��
	substring = str.substr(start);
	char* sub = new char[substring.length() + 1];
	strcpy(sub, substring.c_str());
	sub[substring.length()] = '\0';
	result.push_back(sub);
	return result;
}
//��str�������size���ո�
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
					//���������ַ���
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