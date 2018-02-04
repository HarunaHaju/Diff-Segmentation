#include"Segmentation.h"

void MergeEdge(Mat Src, vector<vector<Point>>& vvptGraphs)
{
	//与原图相同的Mat,用于记录每个点的监测情况，0未检测，1已检测
	Mat mMap(Src.size(), CV_8UC1, Scalar(0));
	Mat mGraph(Src.size(), CV_8UC1, Scalar(0));
	uchar* data = Src.data;
	uchar* dataOfMap = mMap.data;
	uchar* dataOfGraph = mGraph.data;
	int nWidth = Src.cols;
	int nHeight = Src.rows;
	int nArea = nWidth*nHeight;

	//用于检测的四领域
	vector<Point> vptNeighbor;
	vptNeighbor.push_back(Point(-1, 0));
	vptNeighbor.push_back(Point(0, -1));
	vptNeighbor.push_back(Point(1, 0));
	vptNeighbor.push_back(Point(0, 1));

	vector<vector<Point>> vvptTempGraph;

	//开始检测
	for (int nIndexOfY = 0; nIndexOfY < nHeight; nIndexOfY++)
	{
		for (int nIndexOfX = 0; nIndexOfX < nWidth; nIndexOfX++)
		{
			//如果这个点没有被检测，则开始检测这个点的邻居
			if (dataOfMap[nIndexOfY*nWidth + nIndexOfX] == 0)
			{
				vector<Point> vptGraph;
				vector<Point> vptGrowBuffer;
				vptGraph.push_back(Point(nIndexOfX, nIndexOfY));
				vptGrowBuffer.push_back(Point(nIndexOfX, nIndexOfY));
				int nCurrX = 0;
				int nCurrY = 0;

				for (int nIndexOfBuffer = 0; nIndexOfBuffer < vptGrowBuffer.size();
					nIndexOfBuffer++)
				{
					//检查邻域点
					for (int nIndexOfNeihbor = 0; nIndexOfNeihbor < 4; nIndexOfNeihbor++)
					{
						nCurrX = vptNeighbor.at(nIndexOfNeihbor).x
							+ vptGrowBuffer.at(nIndexOfBuffer).x;
						nCurrY = vptNeighbor.at(nIndexOfNeihbor).y
							+ vptGrowBuffer.at(nIndexOfBuffer).y;

						//防止越界
						if (nCurrX >= 0 && nCurrX < nWidth&&nCurrY >= 0
							&& nCurrY < nHeight)
						{
							if (dataOfMap[nCurrY*nWidth + nCurrX] == 0)
							{
								double diff =abs(data[nIndexOfY*nWidth+ nIndexOfX]
									- data[nCurrY*nWidth + nCurrX]);
								if (diff <= 10)
								{
									vptGraph.push_back(Point(nCurrX, nCurrY));
									vptGrowBuffer.push_back(Point(nCurrX, nCurrY));
									dataOfMap[nCurrY*nWidth + nCurrX] = 1;
								}
							}
						}
					}//for nIndexOfBuffer end
				}//for nIndexOfNeihbor end
				vvptTempGraph.push_back(vptGraph);
			}//对于某一个区域检测结束
		}//for nIndexOfX end
	}//for nIndexOfY end

	//再次检测，合并一些小区域
	for (int nIndexOfvvpt = 0; nIndexOfvvpt < vvptTempGraph.size(); nIndexOfvvpt++)
	{
		double sum = 0;
		int mean = 0;
		for (int nIndexOfvpt = 0; 
			nIndexOfvpt < vvptTempGraph.at(nIndexOfvvpt).size(); nIndexOfvpt++)
		{
			sum += data[vvptTempGraph.at(nIndexOfvvpt).at(nIndexOfvpt).y*nWidth 
				+ vvptTempGraph.at(nIndexOfvvpt).at(nIndexOfvpt).x];
		}
		mean = sum / vvptTempGraph.at(nIndexOfvvpt).size();
		for (int nIndexOfvpt = 0;
			nIndexOfvpt < vvptTempGraph.at(nIndexOfvvpt).size(); nIndexOfvpt++)
		{
			dataOfGraph[vvptTempGraph.at(nIndexOfvvpt).at(nIndexOfvpt).y*nWidth
				+ vvptTempGraph.at(nIndexOfvvpt).at(nIndexOfvpt).x] = mean;
			dataOfMap[vvptTempGraph.at(nIndexOfvvpt).at(nIndexOfvpt).y*nWidth
				+ vvptTempGraph.at(nIndexOfvvpt).at(nIndexOfvpt).x] = 0;
		}
	}
	for (int nIndexOfY = 0; nIndexOfY < nHeight; nIndexOfY++)
	{
		for (int nIndexOfX = 0; nIndexOfX < nWidth; nIndexOfX++)
		{
			//如果这个点没有被检测，则开始检测这个点的邻居
			if (dataOfMap[nIndexOfY*nWidth + nIndexOfX] == 0)
			{
				vector<Point> vptGraph;
				vector<Point> vptGrowBuffer;
				vptGraph.push_back(Point(nIndexOfX, nIndexOfY));
				vptGrowBuffer.push_back(Point(nIndexOfX, nIndexOfY));
				int nCurrX = 0;
				int nCurrY = 0;

				for (int nIndexOfBuffer = 0; nIndexOfBuffer < vptGrowBuffer.size();
					nIndexOfBuffer++)
				{
					//检查邻域点
					for (int nIndexOfNeihbor = 0; nIndexOfNeihbor < 4; nIndexOfNeihbor++)
					{
						nCurrX = vptNeighbor.at(nIndexOfNeihbor).x
							+ vptGrowBuffer.at(nIndexOfBuffer).x;
						nCurrY = vptNeighbor.at(nIndexOfNeihbor).y
							+ vptGrowBuffer.at(nIndexOfBuffer).y;

						//防止越界
						if (nCurrX >= 0 && nCurrX < nWidth&&nCurrY >= 0
							&& nCurrY < nHeight)
						{
							if (dataOfMap[nCurrY*nWidth + nCurrX] == 0)
							{
								double diff = abs(dataOfGraph[nIndexOfY*nWidth + nIndexOfX]
									- dataOfGraph[nCurrY*nWidth + nCurrX]);
								//可调参
								if (diff <= 20)
								{
									vptGraph.push_back(Point(nCurrX, nCurrY));
									vptGrowBuffer.push_back(Point(nCurrX, nCurrY));
									dataOfMap[nCurrY*nWidth + nCurrX] = 1;
								}
							}
						}
					}//for nIndexOfBuffer end
				}//for nIndexOfNeihbor end
				vvptGraphs.push_back(vptGraph);
			}//对于某一个区域检测结束
		}//for nIndexOfX end
	}//for nIndexOfY end
}//function MergeEdge end