#pragma once

#define WHITE 255
#define GRAY 200
#define BLACK 0
#define PI 3.14
#include "EdgeExtractor.h"
#include "Mask.h"
#include <cmath>

class ExtractByCanny :
    public EdgeExtractor
{
private:
    Mask filter = Mask({ {2,4,5,4,2}, {4,9,12,9,4}, {5,12,15,12,5}, { 4,9,12,9,4 }, { 2,4,5,4,2 } });
    double alpha = 159;

    Mask sobel_x = Mask({ {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} });
    Mask sobel_y = Mask({ {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} });

    vector<int> angles = {0, 45, 90, 135};

    float threadhold_high = 200;
    float threadhold_low = 100;

private:
    void smoothing(const Mat& image, Mat& smoothImage);
    void calculateGradient(const Mat& image, Mat& gx, Mat& gy, Mat&g);
    void calculateAngles(const Mat& gx, const Mat& gy, Mat& angles);
    int approximateAngle(float angle);
    void NMS(Mat& image, const Mat&g, const Mat& angles);
    bool isLocalMaxima(int i, int j, const Mat& g, int angles);
    bool isInBound(int i, int j, int rows, int cols);
    void threshold(Mat& image);
    void hysteresis(Mat& image);
    bool isNeighborOfStrong(int i, int j, const Mat& image);
    void updateNeighbors(int row, int col, Mat& image);
public:
    const char* getName();
    void extractEdge(const char* imagePath, Mat& output);
};

