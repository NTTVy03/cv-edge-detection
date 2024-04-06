#include "../Header/Prewitt.h"

const char* ExtractByPrewitt::getName()
{
	return "prewitt";
}

void ExtractByPrewitt::extractEdge(const char* imagePath, Mat& output)
{
	// read image
	Mat image;
	readImage(imagePath, image);

	int numRows = image.rows;
	int numCols = image.cols;

	// create gx, gy, output image with size of rows * columns
	Mat gx, gy;

	// calculate gradient matrix: 
	// gx = I * sobel_x --> show gx
	prewitt_x.calConvolution(image, gx);
	namedWindow("GX", WINDOW_NORMAL);
	imshow("GX", gx);

	// gy = I * sobel_y --> show gy
	prewitt_y.calConvolution(image, gy);
	namedWindow("GY", WINDOW_NORMAL);
	imshow("GY", gy);

	// output = sqrt(gx^2 + gy^2) --> show output
	output = Mat(gx.rows, gx.cols, CV_8U);

	for (int i = 0; i < gx.rows; i++) {
		for (int j = 0; j < gx.cols; j++) {
			int x = gx.at<uchar>(i, j);
			int y = gy.at<uchar>(i, j);

			output.at<uchar>(i, j) = sqrt(x * x + y * y);
		}
	}

	namedWindow("Prewitt", WINDOW_NORMAL);
	imshow("Prewitt", output);
}
