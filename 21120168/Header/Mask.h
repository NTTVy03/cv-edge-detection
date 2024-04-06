#pragma once
#include <vector>
#include "opencv2\core.hpp"

using namespace cv;
using namespace std;

class Mask
{
private:
	vector<vector<int>> matrix;
	int cols, rows;
public:
	Mask(vector<vector<int>> m);

	int getRows();
	int getCols();

	void calConvolution(const Mat& img, Mat& output, int alpha = 0);
	Mat addPadding(const Mat& img, int pad_row, int pad_col);
};

