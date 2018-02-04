#include"Segmentation.h"
#include"AutoFitGamma.h"
int main()
{
	long lTimeStart = getTickCount();
	Mat mImgInput = imread("Examples//cat.jpg",0);
	
	autoFitGamma(mImgInput);
	GaussianBlur(mImgInput, mImgInput,Size(9, 9), 2, 2);

	vector<vector<Point>> vvptGraphs;
	MergeEdge(mImgInput, vvptGraphs);

	long lTimeEnd = getTickCount();
	cout << "Time Cost:" << 1000.0*(lTimeEnd - lTimeStart) / getTickFrequency()
		<< "ms" << endl;
	cout << "size of vvptGraphs:" << vvptGraphs.size() << endl;

	Mat mMap(mImgInput.size(), CV_8UC3, Scalar(0));
	uchar* dataOfMap = mMap.data;
	int nWidth = mMap.cols;
	int nHeight = mMap.rows;

	//»­Í¼
	RNG rng;
	for (int nIndexOfGraphs = 0; nIndexOfGraphs < vvptGraphs.size(); nIndexOfGraphs++)
	{
		int r = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int b = rng.uniform(0, 255);

		for (int nIndexOfGraph = 0; nIndexOfGraph < vvptGraphs.at(nIndexOfGraphs).size();
			nIndexOfGraph++)
		{
			dataOfMap[vvptGraphs.at(nIndexOfGraphs).at(nIndexOfGraph).y * nWidth * 3
				+ vvptGraphs.at(nIndexOfGraphs).at(nIndexOfGraph).x * 3] = b;
			dataOfMap[vvptGraphs.at(nIndexOfGraphs).at(nIndexOfGraph).y * nWidth * 3
				+ vvptGraphs.at(nIndexOfGraphs).at(nIndexOfGraph).x * 3 + 1] = g;
			dataOfMap[vvptGraphs.at(nIndexOfGraphs).at(nIndexOfGraph).y * nWidth * 3
				+ vvptGraphs.at(nIndexOfGraphs).at(nIndexOfGraph).x * 3 + 2] = r;
		}
	}
	imshow("ori", mImgInput);
	imshow("result", mMap);
	waitKey(0);
	return 0;
}