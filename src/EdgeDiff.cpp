#include"EdgeDiff.h"

EdgeDiff::EdgeDiff()
{
	ptStartPos_ = Point(-1, -1);
	ptEndPos_ = Point(-1, -1);
	nDiff_ = -1;
}

EdgeDiff::EdgeDiff(Point ptStartPos, Point ptEndPos, int nDiff)
{
	ptStartPos_ = ptStartPos;
	ptEndPos_ = ptEndPos;
	nDiff_ = nDiff_;
}

EdgeDiff::~EdgeDiff()
{
}

//getter
int EdgeDiff::getDiff()
{
	return nDiff_;
}

Point EdgeDiff::getStartPos()
{
	return ptStartPos_;
}

Point EdgeDiff::getEndPos()
{
	return ptEndPos_;
}

//setter
void EdgeDiff::setDiff(int nDiff)
{
	nDiff_ = nDiff;
}

void EdgeDiff::setStartPos(Point ptStartPos)
{
	ptStartPos_ = ptStartPos;
}

void EdgeDiff::setEndPos(Point ptEndPos)
{
	ptEndPos_ = ptEndPos;
}