#ifndef AUTOFITGAMMA_H
#define AUTOFITGAMMA_H

#include<opencv.hpp>
using namespace cv;
using namespace std;

void autoFitGamma(cv::Mat& src, int nAdjustMethod = 1);
int countMostGreyLevel(cv::Mat src, int nMinGrey, int nMaxGrey);
int countMostGreyLevel(cv::Mat src);
double countMeanGrey(cv::Mat src);
double countLowestGreyRate(cv::Mat src, int nLowGreyValue = 51);
#endif