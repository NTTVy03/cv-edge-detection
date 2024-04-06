#pragma once
#include "EdgeExtractor.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ExtractByOpenCV: public EdgeExtractor
{
public:
	const char* getName();
	void extractEdge(const char* imagePath, Mat& output);
};

