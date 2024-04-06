#include "../Header/Laplace.h"

const char* ExtractByLaplace::getName()
{
	return "laplace";
}

void ExtractByLaplace::extractEdge(const char* imagePath, Mat& output)
{
	Mask laplace = laplace_55;

	// read image
	Mat image;
	readImage(imagePath, image);

	int numRows = image.rows;
	int numCols = image.cols;

	laplace.calConvolution(image, output);

	namedWindow("Laplace", WINDOW_NORMAL);
	imshow("Laplace", output);
}
