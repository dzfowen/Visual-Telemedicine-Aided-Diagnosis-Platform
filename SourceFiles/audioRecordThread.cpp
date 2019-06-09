#include "audioRecordThread.h"
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	qDebug("callback success");
	//qDebug("%c",dwInstance);
}

audioRecordThread::audioRecordThread()
{
	this->audioRecordThreadFlag = false;
}
audioRecordThread::~audioRecordThread()
{

}
void audioRecordThread::run()
{
	this->audioRecordThreadFlag = true;

	HWAVEIN hWaveIn;  //输入设备
	WAVEFORMATEX waveform; //采集音频的格式，结构体
	BYTE *Buffer;//采集音频时的数据缓存
	WAVEHDR wHdr; //采集音频时包含数据缓存的结构体
	HANDLE          wait;
	waveform.wFormatTag = WAVE_FORMAT_PCM;//声音格式为PCM
	waveform.nSamplesPerSec = 8000;//采样率，16000次/秒
	waveform.wBitsPerSample = 16;//采样比特，16bits/次
	waveform.nChannels = 1;//采样声道数，2声道
	waveform.nAvgBytesPerSec = 16000;//每秒的数据率，就是每秒能采集多少字节的数据
	waveform.nBlockAlign = 2;//一个块的大小，采样bit的字节数乘以声道数
	waveform.cbSize = 0;//一般为0

	//设定缓冲区格式
	DWORD bufsize = 1024*320;//每次开辟10k的缓存存储录音数据
	int time = 3000;//时间间隔

	wHdr.dwBufferLength = bufsize;
	wHdr.dwBytesRecorded = 0;
	wHdr.dwUser = 0;
	wHdr.dwFlags = 0;
	wHdr.dwLoops = 1;

	wait = CreateEvent(NULL, 0, 0, NULL);
	//使用waveInOpen函数开启音频采集
	//打开录音设备函数
	if (!waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform,(DWORD_PTR)wait, 0L, CALLBACK_EVENT))
	{
		//用于缓存声音 将pcm转成wav的文件
		//audioPlay* a = new audioPlay();
		//FILE *temppf;
		while (this->audioRecordThreadFlag)
		{
			Buffer = new BYTE[bufsize];
			wHdr.lpData = (LPSTR)Buffer;
			waveInPrepareHeader(hWaveIn, &wHdr, sizeof(WAVEHDR));//准备一个波形数据块头用于录音
			waveInAddBuffer(hWaveIn, &wHdr, sizeof (WAVEHDR));//指定波形数据块为录音输入缓存
			waveInStart(hWaveIn);//开始录音
			Sleep(time);//等待声音录制1s
			waveInReset(hWaveIn);//停止录音
			CopyMemory(Buffer, wHdr.lpData, wHdr.dwBytesRecorded);
			//拷贝录音数据
			

			//调用函数发送数据
			
			for each (audioConnThread* var_conn in allAudioConnThread)
			{
				var_conn->sendAudioBuffer((char*)Buffer, wHdr.dwBytesRecorded);
			}
			delete Buffer;
		}	
	}

	else
	{
		qDebug("Audio can not be open!");
	}
	waveInClose(hWaveIn);
	return;
}
void audioRecordThread::copyAllAudioConnThread(vector<audioConnThread*> allconn)
{
	allAudioConnThread = allconn;
}

