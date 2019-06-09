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
	//设定缓冲区格式
	DWORD bufsize = 1024 ;//每次开辟10k的缓存存储接受到的音频数据
	CHAR *Buffer;//音频的数据缓存
	Buffer = new CHAR[bufsize];
	audioPlay * player = new audioPlay();	//开启播放服务
	while (true){
		//Recieve the audio data
		int recvSize = 0;
		recvSize = recv(SerConn, Buffer, bufsize, 0);
		if (recvSize == 0){
			break;
		}
		//转发audioi
		
		//Play the audioData
		player->audioPlayBuf(Buffer, recvSize);

	}
	closesocket(SerConn);//关闭socket连接
	return;
}

//Send the audio buf
void audioConnThread::sendAudioBuffer(CHAR *buf,int buffersize)
{
	send(SerConn, buf, buffersize, 0);
}

