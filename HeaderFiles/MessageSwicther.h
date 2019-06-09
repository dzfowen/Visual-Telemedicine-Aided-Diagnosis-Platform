/*
	By YaoTaihang	2015-11-3
	This object is used to get message and translate it into function, it can also make a message
	by command and send it to connecter;
*/
#include "CommandCollection.h"
#define NAMELENGTH 20
#define BODYLENGTH 10
#define ENDBODYLENGTH 7
#define ENDBODY "ENDBODY"
#define DYNAMICLENGTH "0"

#define RECV_CLIENTCONNECT "CLIENTCONNECT"
#define RECV_CLIENTDISCONNECT "CLIENTDISCONNECT"
#define RECV_LIVEBREATHE "LIVEBREATHE"
#define RECV_GETCHANNELCOUNT "GETCHANNELCOUNT"
#define RECV_SCREENSHOTGETCTRL "SCREENSHOTGETCTRL"
#define RECV_SCREENSHOTEVENT "SCREENSHOTEVENT"
#define RECV_SCREENSHOTCHANGEWIN "SCREENSHOTCHANGEWIN"
#define RECV_SCROLLBARCURSEND "SCROLLBARCURSEND"
#define RECV_AUDIOREQFLAGCHANGE "AUDIOREQFLAGCHANGE"
#define RECV_MARKREQFLAGCHANEG "MARKREQFLAGCHANEG"
#define RECV_MARKREQCLEAR "MARKREQCLEAR"
#define RECV_GETPLUGINLIST "GETPLUGINLIST"
#define RECV_USEPLUGIN "USEPLUGIN"
#define RECV_OPERATEPLUGIN "OPERATEPLUGIN"
#define RECV_SAVELABEL "SAVELABEL"
#define RECV_ORIGINALPOINT "ORIGINALPOINT"
#define RECV_NEWPOINT "NEWPOINT"
#define RECV_EDITMASK "EDITMASK"
#define RECV_COORDINATE "COORDINATE"

#define SEND_SENDCHANNELCOUNT "SENDCHANNELCOUNT"
#define SEND_LIVEBREATHE "LIVEBREATHE"
#define SEND_SCREENSHOTSEND "SCREENSHOTSEND"
#define SEND_SCREENSHOTDIFSEND "SCREENSHOTDIFSEND"
#define SEND_SCREENSHOTSTART "SCREENSHOTSTART"
#define SEND_SCREENSHOTSTOP "SCREENSHOTSTOP"
#define SEND_AUDIOSTART "AUDIOSTART"
#define SEND_AUDIOSTOP "AUDIOSTOP"
#define SEND_SCROLLBARMAXSEND "SCROLLBARMAXSEND"
#define SEND_SCROLLBARCURSEND "SCROLLBARCURSEND"
#define SEND_SENDPLUGININFO "SENDPLUGININFO"

class MessageSwitcher
{
public:
	char * CommandXMLFilePath;
	CommandCollection * myCommandCollection;
	MessageSwitcher(char * MessageSwitcher);
	~MessageSwitcher();

	//Message with Params with confirm length
	char* CreateMessageWithCommand(char* CommandName, vector<char*> params);
	//Message with Single Parm with dynamic length
	char* CreateMessageWithDynamicCommand(char* CommandName, long int exLength, char * param);
	//Read Message by Command
	vector<char*> ReadMessageWithCommand(char* CommandName, char* CommandMessageBody);
	/*
		Read Message Head , Getting the length and CommandName
		char * CommandName is the var for saving the CommandName
		int & Length is the var for saving the Length about the messagebody
	*/
	void ReadMessageHeadForGetNameAndLength (char* MessageHead, char * CommandName, char * Length);

	//Push Space to some blank without char
	static void PushSpaceToString(char * str, int size);
	//Split the string src by string separator
	static vector<char*> StringSplit(char* src, char *separator);
private:

};


