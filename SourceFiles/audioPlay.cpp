
#include "audioPlay.h"

audioPlay::audioPlay()
{
	wfx.wFormatTag = WAVE_FORMAT_PCM;//���ò��������ĸ�ʽ  
	wfx.nChannels = 1;//������Ƶ�ļ���ͨ������  
	wfx.nSamplesPerSec = 8000;//����ÿ���������źͼ�¼ʱ������Ƶ��  
	wfx.nAvgBytesPerSec = 16000;//���������ƽ�����ݴ�����,��λbyte/s�����ֵ���ڴ��������С�Ǻ����õ�  
	wfx.nBlockAlign = 2;//���ֽ�Ϊ��λ���ÿ����  
	wfx.wBitsPerSample = 16;
	wfx.cbSize = 0;//������Ϣ�Ĵ�С  
	wait = CreateEvent(NULL, 0, 0, NULL);
	//�򿪲����豸
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
	waveOutPrepareHeader(hwo, &wh, sizeof(WAVEHDR));//׼��һ���������ݿ����ڲ���  
	waveOutWrite(hwo, &wh, sizeof(WAVEHDR));//����Ƶý���в��ŵڶ�������whָ��������  
	WaitForSingleObject(wait, INFINITE);//�������hHandle�¼����ź�״̬����ĳһ�߳��е��øú���ʱ���߳���ʱ��������ڹ����INFINITE�����ڣ��߳����ȴ��Ķ����Ϊ���ź�״̬����ú�����������  
	waveOutUnprepareHeader(hwo, &wh, sizeof(WAVEHDR));//��������  
}