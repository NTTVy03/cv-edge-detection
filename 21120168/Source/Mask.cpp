#include "../Header/Mask.h"

Mask::Mask(vector<vector<int>> m)
{
	rows = m.size();
	cols = m[0].size();

	matrix.resize(rows);
	for (int i = 0; i < rows; i++) {
		if (m[i].size() != cols) {
			rows = 0;
			cols = 0;
			exit(-1);
		}
		matrix[i].resize(cols);
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = m[i][j];
		}
	}
}

int Mask::getRows()
{
	return rows;
}

int Mask::getCols()
{
	return cols;
}

void Mask::calConvolution(const Mat& img, Mat& output, int alpha)
{
	// ADD PADDING TO THE img 
	Mat paddingImg = addPadding(img, rows / 2, cols / 2);

	int img_rows = paddingImg.rows;
	int img_cols = paddingImg.cols;

	output.create(img_rows - rows + 1, img_cols - cols + 1, CV_8U);

	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			// (i,j) is top-left cell of sub-matrix in the image
			int sum = 0;

			for (int x = 0; x < rows; x++) {
				for (int y = 0; y < cols; y++) {
					sum += (matrix[x][y] * paddingImg.at<uchar>(i + x, j + y));
				}
			}

			if (alpha != 0)
				sum = sum / alpha;

			if (sum > 255) sum = 255;
			if (sum < 0) sum = 0;

			output.at<uchar>(i, j) = sum;

		}
	}
}

Mat Mask::addPadding(const Mat& img, int pad_row, int pad_col)
{
	// add padding to the img
	// add pad_row to the top and the bottom 
	// add pad_col to the left and right

	int top = pad_row;
	int bottom = pad_row;
	int left = pad_col;
	int right = pad_col;

	cv::Mat paddedImg;
	cv::copyMakeBorder(img, paddedImg, top, bottom, left, right, cv::BORDER_CONSTANT, 0);

	return paddedImg;
}
