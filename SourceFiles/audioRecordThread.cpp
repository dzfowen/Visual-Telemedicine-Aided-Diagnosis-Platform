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

	HWAVEIN hWaveIn;  //�����豸
	WAVEFORMATEX waveform; //�ɼ���Ƶ�ĸ�ʽ���ṹ��
	BYTE *Buffer;//�ɼ���Ƶʱ�����ݻ���
	WAVEHDR wHdr; //�ɼ���Ƶʱ�������ݻ���Ľṹ��
	HANDLE          wait;
	waveform.wFormatTag = WAVE_FORMAT_PCM;//������ʽΪPCM
	waveform.nSamplesPerSec = 8000;//�����ʣ�16000��/��
	waveform.wBitsPerSample = 16;//�������أ�16bits/��
	waveform.nChannels = 1;//������������2����
	waveform.nAvgBytesPerSec = 16000;//ÿ��������ʣ�����ÿ���ܲɼ������ֽڵ�����
	waveform.nBlockAlign = 2;//һ����Ĵ�С������bit���ֽ�������������
	waveform.cbSize = 0;//һ��Ϊ0

	//�趨��������ʽ
	DWORD bufsize = 1024*320;//ÿ�ο���10k�Ļ���洢¼������
	int time = 3000;//ʱ����

	wHdr.dwBufferLength = bufsize;
	wHdr.dwBytesRecorded = 0;
	wHdr.dwUser = 0;
	wHdr.dwFlags = 0;
	wHdr.dwLoops = 1;

	wait = CreateEvent(NULL, 0, 0, NULL);
	//ʹ��waveInOpen����������Ƶ�ɼ�
	//��¼���豸����
	if (!waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform,(DWORD_PTR)wait, 0L, CALLBACK_EVENT))
	{
		//���ڻ������� ��pcmת��wav���ļ�
		//audioPlay* a = new audioPlay();
		//FILE *temppf;
		while (this->audioRecordThreadFlag)
		{
			Buffer = new BYTE[bufsize];
			wHdr.lpData = (LPSTR)Buffer;
			waveInPrepareHeader(hWaveIn, &wHdr, sizeof(WAVEHDR));//׼��һ���������ݿ�ͷ����¼��
			waveInAddBuffer(hWaveIn, &wHdr, sizeof (WAVEHDR));//ָ���������ݿ�Ϊ¼�����뻺��
			waveInStart(hWaveIn);//��ʼ¼��
			Sleep(time);//�ȴ�����¼��1s
			waveInReset(hWaveIn);//ֹͣ¼��
			CopyMemory(Buffer, wHdr.lpData, wHdr.dwBytesRecorded);
			//����¼������
			

			//���ú�����������
			
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

