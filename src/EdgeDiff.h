/*
*Copyright:lwx
*Author:lwx
*Date:2017-08-01
*/
#ifndef EDGEDIFF_H
#define EDGEDIFF_H

#include<opencv.hpp>
using namespace cv;
using namespace std;

class EdgeDiff
{
public:
	EdgeDiff();
	EdgeDiff(Point ptStartPos, Point ptEndPos, int nDiff);
	~EdgeDiff();

	//getter
	int getDiff();
	Point getStartPos();
	Point getEndPos();

	//setter
	void setDiff(int nDiff);
	void setStartPos(Point ptStartPos);
	void setEndPos(Point ptEndPos);

private:
	Point ptStartPos_;
	Point ptEndPos_;
	int nDiff_;
};

#endif