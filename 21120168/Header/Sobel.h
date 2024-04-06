#pragma once
#include "EdgeExtractor.h"
#include "Mask.h"

class ExtractBySobel :
    public EdgeExtractor
{
private:
    Mask sobel_x = Mask( { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} });
    Mask sobel_y = Mask( { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} });
public:
    const char* getName();
    void extractEdge(const char* imagePath, Mat& output);
};

