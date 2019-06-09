#ifndef CREATEWINDOWSCREENSHOT_H
/*
#ifndef CREATEWINDOWSCREENSHOT_H
#define CREATEWINDOWSCREENSHOT_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>  
#include <streambuf>
#include <vtkWindowToImageFilter.h>
#include <vtkBMPWriter.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <qdebug.h>
#include <vtkZLibDataCompressor.h>


using namespace std;

#define TEMPFILENAMEPATH "PngTempFile.png"

class createWindowScreenshot
{
public:
	createWindowScreenshot();
	~createWindowScreenshot();
	static char * getWindwoPNGFileStream(vtkSmartPointer<vtkRenderWindow> renWin, int &fileLength)
	{
		vtkSmartPointer<vtkWindowToImageFilter> filter = vtkSmartPointer<vtkWindowToImageFilter>::New();

		filter->SetInput(renWin);

		//vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
		vtkSmartPointer<vtkBMPWriter> writer = vtkSmartPointer<vtkBMPWriter>::New();
		
		writer->SetFileName(TEMPFILENAMEPATH);
		writer->SetInputConnection(filter->GetOutputPort());
		writer->Write();
	
		

		//Read file
		FILE *src_fp;
		if ((src_fp = fopen(TEMPFILENAMEPATH, "rb")) == NULL)
		{
			printf("fopen %s failed./n", TEMPFILENAMEPATH);
		}
		fseek(src_fp, 0L, SEEK_END);
		int src_len = ftell(src_fp);

		char* result = new char[src_len];

		fseek(src_fp, 0L, SEEK_SET);
		fread(result, src_len, 1, src_fp);
		fclose(src_fp);


		//Compress data
		vtkSmartPointer<vtkZLibDataCompressor> dataCompressor = vtkSmartPointer<vtkZLibDataCompressor>::New();
		int new_len = dataCompressor->GetMaximumCompressionSpace(src_len);
		char* new_result = new char[new_len];
		size_t compress_len = dataCompressor->Compress((unsigned char*)result, src_len, (unsigned char*)new_result, new_len);
		

		/*
			Update by YaoTaihang	2015-12-21
			Add message length into this file message
		*/
/*
		std::stringstream ss;
		std::string str_UncompressLen;
		ss << src_len;
		ss >> str_UncompressLen;

		char * final_result = new char[str_UncompressLen.length() + 1 + compress_len]; final_result[0] = '\0';
		strcat(final_result, str_UncompressLen.c_str());
		strcat(final_result, " ");
		for (int i = 0; i < compress_len; i++)
		{
			final_result[i + str_UncompressLen.length() + 1] = new_result[i];
		}

		fileLength = str_UncompressLen.length() + 1 + compress_len;
		
		delete[] result; result = NULL;
		delete[] new_result; new_result = NULL;

		return final_result;
	}
private:

};

createWindowScreenshot::createWindowScreenshot()
{

}

createWindowScreenshot::~createWindowScreenshot()
{
}
#endif
*/

#define CREATEWINDOWSCREENSHOT_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>  
#include <streambuf>
#include <vtkWindowToImageFilter.h>
#include <vtkBMPWriter.h>
#include <vtkPNGWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <qdebug.h>
#include <vtkZLibDataCompressor.h>
#include <windows.h>

using namespace std;

#define TEMPFILENAMEPATH "TempFile"
#define IFRAMETHRESHHOLD 4
#define PFRAMETHRESHHOLD 50

struct PixelDif
{
	unsigned char Dif_Channel1;
	unsigned char Dif_Channel2;
	unsigned char Dif_Channel3;
};

struct PixelDif_Compress
{
	PixelDif pixDif;
	int num;
};

class createWindowScreenshot
{
public:
	int PFramenNum;
	int PointNum;

	vtkSmartPointer<vtkImageData> I_ImageDate;

	createWindowScreenshot();
	~createWindowScreenshot();
	// Get screenshot(I_Frame) of Dif(P_Frame) as stream
	char * getScreenshotOrDif(vtkSmartPointer<vtkRenderWindow> renWin, int &msgLength, bool &isScreenshot);

private:
	/*
	Update by Yaotaihang	2016-09-22
	Change screenshot cast to img difference case, this part is defined to find difference between two screenshot, and store it.
	*/
	// check need Cast New I Frame to all users, if need return P_Frame, gibe pixDifs back
	bool checkNeedCastNewIFrame(vtkSmartPointer<vtkImageData> P_ImageDate, vector<PixelDif> &pixDifs, int &DifPointsNum);
	// Get screenshot(I_Frame) as stream
	char * getWindwoPNGFileStream(vtkSmartPointer<vtkWindowToImageFilter> filter, int &fileLength);
	// Refresh I_Frame
	void recreateIFrameScreenshot(vtkSmartPointer<vtkImageData> P_ImageDate);
	// Zlib Compress
	static char* getZlibCompressMsg(char* unCompressMsg, int unCompressMsg_len, int &finalLength);
	// Run algorithm
	static void getRunPixedlDifCompress(vector<PixelDif> &pixDifs, vector<PixelDif_Compress> &pixelDif_Compress);
}; 
#endif