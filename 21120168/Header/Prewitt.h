#pragma once
#include "EdgeExtractor.h"
#include "Mask.h"

class ExtractByPrewitt :
    public EdgeExtractor
{
private:
    Mask prewitt_x = Mask({ {-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1} });
    Mask prewitt_y = Mask({ {-1, -1, -1}, {0, 0, 0}, {1, 1, 1} });

public:
    const char* getName();
    void extractEdge(const char* imagePath, Mat& output);
};


