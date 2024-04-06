#include "../Header/EdgeExtractor.h"

bool EdgeExtractor::readImage(const char* imagePath, Mat& image)
{
    image = imread(imagePath, IMREAD_GRAYSCALE);

    if (image.empty()) return false;

    return true;
}
