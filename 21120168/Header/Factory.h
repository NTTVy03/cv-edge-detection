#pragma once
#include "EdgeExtractor.h"
#include "Canny.h"
#include "Laplace.h"
#include "OpenCV.h"
#include "Prewitt.h"
#include "Sobel.h"

class Factory
{
public:
	static EdgeExtractor* getDetector(char* algorithm);
	static vector<EdgeExtractor*> getAllDetectors();
};

