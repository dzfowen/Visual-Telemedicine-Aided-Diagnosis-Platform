#ifndef AUDIOPLAY_H
#define AUDIOPLAY_H
#include <stdio.h>  
#include <Windows.h>  
#include <QDebug>
#pragma comment(lib, "winmm.lib")  

class audioPlay
{
public:
	audioPlay();
	~audioPlay();
	void audioPlayBuf(char* buf,int bufsize);
private:
	HWAVEOUT        hwo;
	WAVEHDR         wh;
	WAVEFORMATEX    wfx;
	HANDLE          wait;
};
#endif