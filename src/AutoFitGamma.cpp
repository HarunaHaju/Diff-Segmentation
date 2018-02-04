#include"AutoFitGamma.h"

void autoFitGamma(cv::Mat& src, int nAdjustMethod)
{
	double dMeanGrey = countMeanGrey(src);
	double dB = countLowestGreyRate(src,55);
	double dA = 1 - dB;
	double dC = dA + 0.05;
	double dGamma = 0;
	double f1 = 0;
	double f2 = 0;
	double f3 = 0;
	double dPI = 3.14159;
	double dAlpha = atan(-dB / dMeanGrey);
	double dCosAlpha = cos(dAlpha);
	double dSinAlpha = sin(dAlpha);

	//创建映射表，并根据选择的调整方法，来进行计算
	unsigned char szLookUpTable[256];
	switch (nAdjustMethod)
	{
		//每个灰度级单独取gamma值
	case 0:
	{
			  for (int i = 0; i < 256; i++)
			  {
				  f1 = dA*cos(dPI*i / 2 / dMeanGrey);
				  f2 = (0.002*sin(4 * dPI * i / 255) + dB)*dCosAlpha + i*dSinAlpha;
				  f3 = dC * abs(i / dMeanGrey - 1)*cos(3 * dPI*i / 255);
				  dGamma = pow(abs(f1 + f2 + f3 + 1), -1);
				  if (dGamma <= 0)
				  {
					  szLookUpTable[i] = pow(dPI, abs(dGamma));
					  continue;
				  }
				  szLookUpTable[i] = pow((float)(i / 255.0), dGamma) * 255.0;
			  }
			  break;
	}
		//取最多的那个灰度级的gamma值
	case 1:
	{
			  int nMostGreyLevel = countMostGreyLevel(src);
			  f1 = dA*cos(dPI*nMostGreyLevel / 2 / dMeanGrey);
			  f2 = (0.002*sin(4 * dPI * nMostGreyLevel / 255) + dB)*dCosAlpha
				  + nMostGreyLevel*dSinAlpha;
			  f3 = dC * abs(nMostGreyLevel / dMeanGrey - 1)*cos(3 * dPI*nMostGreyLevel / 255);
			  dGamma = pow(abs(f1 + f2 + f3 + 1), -1);
			  if (dGamma <= 0)
			  {
				  dGamma = pow(50, abs(dGamma));
			  }
			  for (int i = 0; i < 256; i++)
			  {
				  szLookUpTable[i] = pow((float)(i / 255.0), dGamma) * 255.0;
			  }
			  break;
	}
		//分为5块，每块取最多的那个灰度级的gamma值
	case 2:
	{
			  for (int i = 0; i < 5; i++)
			  {
				  int nMostGreyLevel = countMostGreyLevel(src, i * 51, (i + 1) * 51 + 1);
				  f1 = dA*cos(dPI*nMostGreyLevel / 2 / dMeanGrey);
				  f2 = (0.002*sin(4 * dPI * nMostGreyLevel / 255) + dB)*dCosAlpha
					  + nMostGreyLevel*dSinAlpha;
				  f3 = dC * abs(nMostGreyLevel / dMeanGrey - 1)*cos(3 * dPI*nMostGreyLevel / 255);
				  dGamma = pow(abs(f1 + f2 + f3 + 1), -1);
				  if (dGamma <= 0) dGamma = pow(10, abs(dGamma));
				  for (int j = i * 51; j < (i + 1) * 51 + 1; j++)
				  {
					  szLookUpTable[j] = pow((float)(j / 255.0), dGamma) * 255.0;
				  }
			  }
			  break;
	}
	default:
		break;
	}

	uchar* pucDataOfSrc = src.data;
	int nHeight = src.rows;
	int nWidth = src.cols;
	for (int nIndexOfY = 0; nIndexOfY < nHeight; nIndexOfY++)
	{
		for (int nIndexOfX = 0; nIndexOfX < nWidth; nIndexOfX++)
		{
			pucDataOfSrc[nIndexOfY*nWidth + nIndexOfX] =
				szLookUpTable[pucDataOfSrc[nIndexOfY*nWidth + nIndexOfX]];
		}
	}
}

double countMeanGrey(cv::Mat src)
{
	double dMeanGrey = 0;
	uchar* pucDataOfSrc = src.data;
	int nHeight = src.rows;
	int nWidth = src.cols;
	int nCountOfPix = nHeight*nWidth;
	for (int nIndexOfY = 0; nIndexOfY < nHeight; nIndexOfY++)
	{
		for (int nIndexOfX = 0; nIndexOfX < nWidth; nIndexOfX++)
		{
			dMeanGrey += pucDataOfSrc[nIndexOfY*nWidth + nIndexOfX] / (double)nCountOfPix;
		}
	}
	return dMeanGrey;
}

double countLowestGreyRate(cv::Mat src, int nLowGreyValue)
{
	double dRate = 0;
	uchar* pucDataOfSrc = src.data;
	int nHeight = src.rows;
	int nWidth = src.cols;
	int nCountOfPix = nHeight*nWidth;
	for (int nIndexOfY = 0; nIndexOfY < nHeight; nIndexOfY++)
	{
		for (int nIndexOfX = 0; nIndexOfX < nWidth; nIndexOfX++)
		{
			if (pucDataOfSrc[nIndexOfY*nWidth + nIndexOfX] <= nLowGreyValue)
			{
				dRate++;
			}
		}
	}
	return dRate / nCountOfPix;
}

int countMostGreyLevel(cv::Mat src)
{
	double dRate = 0;
	int szGreyCount[256] = { 0 };
	uchar* pucDataOfSrc = src.data;
	int nHeight = src.rows;
	int nWidth = src.cols;
	int nCountOfPix = nHeight*nWidth;
	for (int nIndexOfY = 0; nIndexOfY < nHeight; nIndexOfY++)
	{
		for (int nIndexOfX = 0; nIndexOfX < nWidth; nIndexOfX++)
		{
			szGreyCount[pucDataOfSrc[nIndexOfY*nWidth + nIndexOfX]]++;
		}
	}
	int nMostGreyLevel = 0;
	for (int i = 0; i < 256; i++)
	{
		if (szGreyCount[i] > szGreyCount[nMostGreyLevel])
		{
			nMostGreyLevel = i;
		}
	}
	return nMostGreyLevel;
}

int countMostGreyLevel(cv::Mat src, int nMinGrey, int nMaxGrey)
{
	double dRate = 0;
	int szGreyCount[256] = { 0 };
	uchar* pucDataOfSrc = src.data;
	int nHeight = src.rows;
	int nWidth = src.cols;
	int nCountOfPix = nHeight*nWidth;
	for (int nIndexOfY = 0; nIndexOfY < nHeight; nIndexOfY++)
	{
		for (int nIndexOfX = 0; nIndexOfX < nWidth; nIndexOfX++)
		{
			if (pucDataOfSrc[nIndexOfY*nWidth + nIndexOfX] >= nMinGrey &&
				pucDataOfSrc[nIndexOfY*nWidth + nIndexOfX] < nMaxGrey)
			{
				szGreyCount[pucDataOfSrc[nIndexOfY*nWidth + nIndexOfX]]++;
			}
		}
	}
	int nMostGreyLevel = 0;
	for (int i = 0; i < 256; i++)
	{
		if (szGreyCount[i] > szGreyCount[nMostGreyLevel])
		{
			nMostGreyLevel = i;
		}
	}
	return nMostGreyLevel;
}