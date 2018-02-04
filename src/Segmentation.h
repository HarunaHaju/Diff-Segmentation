/*
*Copyright:lwx
*Author:lwx
*Date:2017-08-01
*/
#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include<opencv.hpp>
#include"EdgeDiff.h"
#include<vector>
#include<numeric>
using namespace std;
using namespace cv;

void MergeEdge(Mat Src,vector<vector<Point>>& vvptGraphs);

#endif