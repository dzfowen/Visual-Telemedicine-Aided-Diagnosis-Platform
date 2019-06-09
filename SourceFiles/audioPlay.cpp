
#include "audioPlay.h"

audioPlay::audioPlay()
{
	wfx.wFormatTag = WAVE_FORMAT_PCM;//设置波形声音的格式  
	wfx.nChannels = 1;//设置音频文件的通道数量  
	wfx.nSamplesPerSec = 8000;//设置每个声道播放和记录时的样本频率  
	wfx.nAvgBytesPerSec = 16000;//设置请求的平均数据传输率,单位byte/s。这个值对于创建缓冲大小是很有用的  
	wfx.nBlockAlign = 2;//以字节为单位设置块对齐  
	wfx.wBitsPerSample = 16;
	wfx.cbSize = 0;//额外信息的大小  
	wait = CreateEvent(NULL, 0, 0, NULL);
	//打开播放设备
	if (waveOutOpen(&hwo, WAVE_MAPPER, &wfx, (DWORD_PTR)wait, 0L, CALLBACK_EVENT))
	{
		qDebug("Open audio play faild!");
	}
}

audioPlay::~audioPlay()
{
	waveOutClose(hwo);
}

void audioPlay::audioPlayBuf(char* buf,int bufsize)
{
	int dolenght = 0;
	int playsize = bufsize;
	wh.lpData = buf + dolenght;
	wh.dwBufferLength = playsize;
	wh.dwFlags = 0L;
	wh.dwLoops = 1L;
	waveOutPrepareHeader(hwo, &wh, sizeof(WAVEHDR));//准备一个波形数据块用于播放  
	waveOutWrite(hwo, &wh, sizeof(WAVEHDR));//在音频媒体中播放第二个函数wh指定的数据  
	WaitForSingleObject(wait, INFINITE);//用来检测hHandle事件的信号状态，在某一线程中调用该函数时，线程暂时挂起，如果在挂起的INFINITE毫秒内，线程所等待的对象变为有信号状态，则该函数立即返回  
	waveOutUnprepareHeader(hwo, &wh, sizeof(WAVEHDR));//清理数据  
}