#include <audioConnThread.h>

audioConnThread::audioConnThread(){}
audioConnThread::audioConnThread(SOCKET serconn){
	this->SerConn = serconn;
}
audioConnThread::~audioConnThread(){}
void audioConnThread::run(){
	//Get this client user
	char recvClientuser[20];
	recv(SerConn, this->ClientUser, 20, 0);
	qDebug("%s------User is connecting to get Audio Service", this->ClientUser);
	//Play the audio what recieved
	//�趨��������ʽ
	DWORD bufsize = 1024 ;//ÿ�ο���10k�Ļ���洢���ܵ�����Ƶ����
	CHAR *Buffer;//��Ƶ�����ݻ���
	Buffer = new CHAR[bufsize];
	audioPlay * player = new audioPlay();	//�������ŷ���
	while (true){
		//Recieve the audio data
		int recvSize = 0;
		recvSize = recv(SerConn, Buffer, bufsize, 0);
		if (recvSize == 0){
			break;
		}
		//ת��audioi
		
		//Play the audioData
		player->audioPlayBuf(Buffer, recvSize);

	}
	closesocket(SerConn);//�ر�socket����
	return;
}

//Send the audio buf
void audioConnThread::sendAudioBuffer(CHAR *buf,int buffersize)
{
	send(SerConn, buf, buffersize, 0);
}

