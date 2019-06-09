#include "createWindowScreenshot.h"
createWindowScreenshot::createWindowScreenshot()
{
	this->PFramenNum = 0;
	this->PointNum = 0;
	this->I_ImageDate = NULL;
}

createWindowScreenshot::~createWindowScreenshot()
{
}

char * createWindowScreenshot::getScreenshotOrDif(vtkSmartPointer<vtkRenderWindow> renWin, int &msgLength, bool &isScreenshot)
{
	vtkSmartPointer<vtkWindowToImageFilter> filter = vtkSmartPointer<vtkWindowToImageFilter>::New();
	filter->SetInput(renWin);

	vtkSmartPointer<vtkImageData> P_ImageDate = filter->GetOutput();
	filter->Update();
	int difPointsNum = 0;
	vector<PixelDif> pixDifs;

	//判断是否传新的一张完整图
	if (checkNeedCastNewIFrame(P_ImageDate, pixDifs, difPointsNum))
	{
		// Return I_Frame 
		isScreenshot = true;
		//传新图，直接截取当前图片压缩发送
		return this->getWindwoPNGFileStream(filter, msgLength);
	}
	else
	{
		// Return P_Frame 
		isScreenshot = false;
		if (difPointsNum != 0)
		{
			// i - i-1 way to compress
			int *imageInfo = I_ImageDate->GetDimensions();
			int width = *imageInfo;
			int height = *(imageInfo + 1);

			vector<PixelDif> newDifs;

			for (int i = 0; i < width; i++)
			{
				newDifs.push_back(pixDifs[i]);
			}

			for (int point_index = width; point_index < pixDifs.size(); point_index++)
			{
				PixelDif pd;
				pd.Dif_Channel1 = pixDifs[point_index].Dif_Channel1 - pixDifs[point_index - width].Dif_Channel1;
				pd.Dif_Channel2 = pixDifs[point_index].Dif_Channel2 - pixDifs[point_index - width].Dif_Channel2;
				pd.Dif_Channel3 = pixDifs[point_index].Dif_Channel3 - pixDifs[point_index - width].Dif_Channel3;
				newDifs.push_back(pd);
			}

			vector<PixelDif_Compress> pixelDifs_Compress;
			createWindowScreenshot::getRunPixedlDifCompress(newDifs, pixelDifs_Compress);

			// Trans pixDifs to pixelDifs_Compress*
			int length = sizeof(PixelDif_Compress)*pixelDifs_Compress.size();

			char* msg = new char[length]; msg[0] = '\0';//'\0'
			memcpy(msg, &pixelDifs_Compress[0], length);

			//for (int i = 0; i < length; i++){
			//	qDebug()<< msg[i];
			//}



			/*
			Another way to xxx
			*/
			//char* msg = "";
			//for (int i = 0; i < pixelDifs_Compress.size(); i++)
			//{
			//msg += 'x';
			//msg += pixelDifs_Compress.at(i).pixDif.Dif_Channel1;
			//}
			this->getWindwoPNGFileStream(filter, msgLength);

			qDebug() << "uncompress length is " << length;
			return  createWindowScreenshot::getZlibCompressMsg(msg, length, msgLength);
		}
		return NULL;

	}
}

char * createWindowScreenshot::getWindwoPNGFileStream(vtkSmartPointer<vtkWindowToImageFilter> filter, int &finalLength)
{
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

	return createWindowScreenshot::getZlibCompressMsg(result, src_len, finalLength);
}

bool createWindowScreenshot::checkNeedCastNewIFrame(vtkSmartPointer<vtkImageData> P_ImageDate, vector<PixelDif> &pixDifs, int &DifPointsNum)
{
	int *P_dims = P_ImageDate->GetDimensions();//获取P图片的维度
	// If I frame is not exist, create it by this P frame
	//如果新图不存在，传原图（前一张）
	if (this->PointNum == 0 || this->I_ImageDate == NULL)
	{

		this->recreateIFrameScreenshot(P_ImageDate);
		return true;
	}

	// If I-P frames have different dims,recreat I Frame

	int *I_dims = this->I_ImageDate->GetDimensions();//获取I图片的维度
	//如果I-P图的维度不同，即图片长宽值不同，传新图
	if (I_dims == NULL || P_dims == NULL || I_dims[0] != P_dims[0] || I_dims[1] != P_dims[1])
	{
		this->recreateIFrameScreenshot(P_ImageDate);
		return true;
	}

	// If P_Frame is use too many times, need cast a new I_Frame to all users
	//如果原图使用超过20次，传新图
	if (this->PFramenNum >= PFRAMETHRESHHOLD){
		this->recreateIFrameScreenshot(P_ImageDate);
		return true;
	}

	// Calculate every point
	//计算每个像素的像素值差异
	DifPointsNum = 0;
	for (int j = 0; j < I_dims[1]; j++)
	{
		for (int i = 0; i < I_dims[0]; i++)
		{
			unsigned char* I_Pixel = (unsigned char*)I_ImageDate->GetScalarPointer(i, j, 0);
			unsigned char* P_Pixel = (unsigned char*)P_ImageDate->GetScalarPointer(i, j, 0);
			unsigned char difs[3];

			difs[0] = *P_Pixel - *I_Pixel;
			difs[1] = *(P_Pixel + 1) - *(I_Pixel + 1);
			difs[2] = *(P_Pixel + 2) - *(I_Pixel + 2);

			int intdif[3];


			if (difs[0] != 0 || difs[1] != 0 || difs[2] != 0)
			{
				DifPointsNum++;
				if (DifPointsNum >= this->PointNum / IFRAMETHRESHHOLD)
				{
					// If more than a half of the points have changed, recreate I frame
					this->recreateIFrameScreenshot(P_ImageDate);
					return true;
				}
			}

			PixelDif dif = { difs[0], difs[1], difs[2] };
			pixDifs.push_back(dif);
		}
	}
	//	qDebug() << this->PointNum / IFRAMETHRESHHOLD;
	//	qDebug() << DifPointsNum;
	//	qDebug() << IFRAMETHRESHHOLD;
	// Update this P as next I, but not cast it as I,only cast difs
	this->I_ImageDate = P_ImageDate;
	this->PFramenNum++;
	//qDebug() << PFramenNum;
	return false;

}

void createWindowScreenshot::recreateIFrameScreenshot(vtkSmartPointer<vtkImageData> P_ImageDate)
{
	int *P_dims = P_ImageDate->GetDimensions();
	this->I_ImageDate = P_ImageDate;
	this->PFramenNum = 0;
	this->PointNum = P_dims[0] * P_dims[1] * P_dims[2];
}

char* createWindowScreenshot::getZlibCompressMsg(char* unCompressMsg, int unCompressMsg_len, int &finalLength)
{
	//Compress data
	vtkSmartPointer<vtkZLibDataCompressor> dataCompressor = vtkSmartPointer<vtkZLibDataCompressor>::New();
	int new_len = dataCompressor->GetMaximumCompressionSpace(unCompressMsg_len);
	char* new_result = new char[new_len];
	size_t compress_len = dataCompressor->Compress((unsigned char*)unCompressMsg, unCompressMsg_len, (unsigned char*)new_result, new_len);
	qDebug() << "compress length is " << (int)compress_len;

	/*
	Update by YaoTaihang	2015-12-21
	Add message length into this file message
	*/
	std::stringstream ss;
	std::string str_UncompressLen;
	ss << unCompressMsg_len;
	ss >> str_UncompressLen;

	char * final_result = new char[str_UncompressLen.length() + 1 + compress_len]; final_result[0] = '\0';
	strcat(final_result, str_UncompressLen.c_str());
	strcat(final_result, " ");
	for (int i = 0; i < compress_len; i++)
	{
		final_result[i + str_UncompressLen.length() + 1] = new_result[i];
	}

	finalLength = str_UncompressLen.length() + 1 + compress_len + 1;

	delete[] unCompressMsg; unCompressMsg = NULL;
	delete[] new_result; new_result = NULL;
	qDebug() << "self final size:" << finalLength;
	return final_result;
}

void createWindowScreenshot::getRunPixedlDifCompress(vector<PixelDif> &pixDifs, vector<PixelDif_Compress> &pixelDifs_Compress)
{
	int length = pixDifs.size();

	int i = 0;
	PixelDif LastPixelDif = pixDifs[0];
	int SamePixelNum = 0;
	while (i < length)
	{
		if (pixDifs[i].Dif_Channel1 == LastPixelDif.Dif_Channel1 && pixDifs[i].Dif_Channel2 == LastPixelDif.Dif_Channel2 &&pixDifs[i].Dif_Channel3 == LastPixelDif.Dif_Channel3)
		{
			// If Same , SamePixelNum++
			SamePixelNum++;
		}
		else
		{
			// If not , update LastPixelDif and SamePixelNum
			PixelDif_Compress pixelDif_Compress = { LastPixelDif, SamePixelNum };
			pixelDifs_Compress.push_back(pixelDif_Compress);

			LastPixelDif = pixDifs[i];
			SamePixelNum = 1;
		}
		i++;
	}

	PixelDif_Compress pixelDif_Compress = { LastPixelDif, SamePixelNum };
	pixelDifs_Compress.push_back(pixelDif_Compress);
	//qDebug() << "size:"<<pixelDifs_Compress.size();


}