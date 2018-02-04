#include"Segmentation.h"

void MergeEdge(Mat Src, vector<vector<Point>>& vvptGraphs)
{
	//��ԭͼ��ͬ��Mat,���ڼ�¼ÿ����ļ�������0δ��⣬1�Ѽ��
	Mat mMap(Src.size(), CV_8UC1, Scalar(0));
	Mat mGraph(Src.size(), CV_8UC1, Scalar(0));
	uchar* data = Src.data;
	uchar* dataOfMap = mMap.data;
	uchar* dataOfGraph = mGraph.data;
	int nWidth = Src.cols;
	int nHeight = Src.rows;
	int nArea = nWidth*nHeight;

	//���ڼ���������
	vector<Point> vptNeighbor;
	vptNeighbor.push_back(Point(-1, 0));
	vptNeighbor.push_back(Point(0, -1));
	vptNeighbor.push_back(Point(1, 0));
	vptNeighbor.push_back(Point(0, 1));

	vector<vector<Point>> vvptTempGraph;

	//��ʼ���
	for (int nIndexOfY = 0; nIndexOfY < nHeight; nIndexOfY++)
	{
		for (int nIndexOfX = 0; nIndexOfX < nWidth; nIndexOfX++)
		{
			//��������û�б���⣬��ʼ����������ھ�
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
					//��������
					for (int nIndexOfNeihbor = 0; nIndexOfNeihbor < 4; nIndexOfNeihbor++)
					{
						nCurrX = vptNeighbor.at(nIndexOfNeihbor).x
							+ vptGrowBuffer.at(nIndexOfBuffer).x;
						nCurrY = vptNeighbor.at(nIndexOfNeihbor).y
							+ vptGrowBuffer.at(nIndexOfBuffer).y;

						//��ֹԽ��
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
			}//����ĳһ�����������
		}//for nIndexOfX end
	}//for nIndexOfY end

	//�ٴμ�⣬�ϲ�һЩС����
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
			//��������û�б���⣬��ʼ����������ھ�
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
					//��������
					for (int nIndexOfNeihbor = 0; nIndexOfNeihbor < 4; nIndexOfNeihbor++)
					{
						nCurrX = vptNeighbor.at(nIndexOfNeihbor).x
							+ vptGrowBuffer.at(nIndexOfBuffer).x;
						nCurrY = vptNeighbor.at(nIndexOfNeihbor).y
							+ vptGrowBuffer.at(nIndexOfBuffer).y;

						//��ֹԽ��
						if (nCurrX >= 0 && nCurrX < nWidth&&nCurrY >= 0
							&& nCurrY < nHeight)
						{
							if (dataOfMap[nCurrY*nWidth + nCurrX] == 0)
							{
								double diff = abs(dataOfGraph[nIndexOfY*nWidth + nIndexOfX]
									- dataOfGraph[nCurrY*nWidth + nCurrX]);
								//�ɵ���
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
			}//����ĳһ�����������
		}//for nIndexOfX end
	}//for nIndexOfY end
}//function MergeEdge end