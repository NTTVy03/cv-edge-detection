#include "../Header/OpenCV.h"

const char* ExtractByOpenCV::getName()
{
	return "opencv";
}

void ExtractByOpenCV::extractEdge(const char* imagePath, Mat& output)
{
	Mat image;
	readImage(imagePath, image);

	Canny(image, output, 100, 200);
	namedWindow("Canny - OpenCV", WINDOW_KEEPRATIO);
	imshow("Canny - OpenCV", output);
}
