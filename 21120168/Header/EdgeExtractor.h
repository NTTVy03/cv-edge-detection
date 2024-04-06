#pragma once
#include "opencv2\core.hpp"
#include "opencv2\opencv.hpp"
using namespace cv;

class EdgeExtractor
{
protected:
	bool readImage(const char* imagePath, Mat& image);
public:
	virtual const char* getName() = 0;
	virtual void extractEdge(const char* imagePath, Mat& output) = 0;
};

