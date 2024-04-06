#include "../Header/Canny.h"

void ExtractByCanny::smoothing(const Mat& image, Mat& smoothImage)
{
	filter.calConvolution(image, smoothImage, alpha);
}

void ExtractByCanny::calculateGradient(const Mat& image, Mat& gx, Mat& gy, Mat& g)
{
	// gx = I * sobel_x --> show gx
	sobel_x.calConvolution(image, gx);

	// gy = I * sobel_y --> show gy
	sobel_y.calConvolution(image, gy);

	// output = sqrt(gx^2 + gy^2) --> show output
	g = Mat(gx.rows, gx.cols, CV_8U);

	for (int i = 0; i < gx.rows; i++) {
		for (int j = 0; j < gx.cols; j++) {
			int x = gx.at<uchar>(i, j);
			int y = gy.at<uchar>(i, j);

			g.at<uchar>(i, j) = sqrt(x * x + y * y);
		}
	}
}

void ExtractByCanny::calculateAngles(const Mat& gx, const Mat& gy, Mat& angles)
{
	int rows = gx.rows;
	int cols = gy.cols;

	angles = Mat(rows, cols, CV_8U); // 0, 45, 90, 135

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int x = gx.at<uchar>(i, j);
			int y = gy.at<uchar>(i, j);
			float angle = (x != 0 ? atan(1.0 * y / x) * 180 / PI : 0);

			angles.at<uchar>(i, j) = approximateAngle(angle);
		}
	}
}

int ExtractByCanny::approximateAngle(float angle)
{
	int n = angles.size();
	int id = -1;
	float delta = 360;

	for (int i = 0; i < n; i++) {
		if (angles[i] < 0) angles[i] += 180;
		if (abs(angle - angles[i]) < delta) {
			delta = abs(angle - angles[i]);
			id = i;
		}
	}

	return angles[id];
}

void ExtractByCanny::NMS(Mat& image, const Mat& g, const Mat& angles)
{
	int rows = g.rows;
	int cols = g.cols;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (isLocalMaxima(i, j, g, angles.at<uchar>(i,j))) {
				image.at<uchar>(i, j) = g.at<uchar>(i, j);
			}
			else {
				image.at<uchar>(i, j) = BLACK;
			}
		}
	}

}

bool ExtractByCanny::isLocalMaxima(int i, int j, const Mat& g, int angles)
{
	if (g.at<uchar>(i, j) == 0) return false;

	vector<int> dx, dy;

	if (angles == 90) { // left - right
		dx = {-1,1};
		dy = {0,0};
	} else if (angles == 135) { // top left - bottom right
		dx = { -1,1 };
		dy = { -1,1 };
	} else if (angles == 0) { // top - bottom
		dx = { 0,0 };
		dy = { -1,1 };
	} else if (angles == 45) { // top right - bottom left
		dx = { 1,-1 };
		dy = { -1,1 };
	}

	for (int t = 0; t < dx.size(); t++) {
		int ii = i + dx[t];
		int jj = j + dy[t];

		if (isInBound(ii, jj, g.rows, g.cols)) {
			int current = g.at<uchar>(i, j);
			int neighbour = g.at<uchar>(ii, jj);

			if (current <= neighbour)
				return false;
		}
	}

	return true;
}

bool ExtractByCanny::isInBound(int i, int j, int rows, int cols)
{
	if (i < 0) return false;
	if (j < 0) return false;
	if (i >= rows) return false;
	if (j >= cols) return false;

	return true;
}

void ExtractByCanny::threshold(Mat& image)
{
	int rows = image.rows;
	int cols = image.cols;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int value = image.at<uchar>(i, j);
			int newValue = BLACK;

			if (value >= threadhold_high) newValue = WHITE;
			else if (value >= threadhold_low) newValue = GRAY;

			image.at<uchar>(i, j) = newValue;
		}
	}
}

void ExtractByCanny::hysteresis(Mat& image)
{
	int rows = image.rows;
	int cols = image.cols;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// Recursively update the neighboring pixels
			updateNeighbors(i, j, image);
		}
	}
}

void ExtractByCanny::updateNeighbors(int row, int col, Mat& image)
{
	int rows = image.rows;
	int cols = image.cols;

	if (isInBound(row, col, rows, cols)) {
		int current = image.at<uchar>(row, col);
		if (current == GRAY && isNeighborOfStrong(row, col, image)) {
			image.at<uchar>(row, col) = WHITE;

			// Define the neighborhood offsets (8-connectivity)
			int offsets[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

			for (int k = 0; k < 8; k++) {
				int newRow = row + offsets[k][0];
				int newCol = col + offsets[k][1];

				updateNeighbors(newRow, newCol, image);
			}
		}
	}	
}

bool ExtractByCanny::isNeighborOfStrong(int i, int j, const Mat& image)
{
	int rows = image.rows;
	int cols = image.cols;

	vector<int> dx = { 1, 1, 1, 0, 0, -1, -1, -1 };
	vector<int> dy = { 0, 1, -1, 1, -1, 0, 1, -1 };
	int numNeighbors = dx.size();

	for (int t = 0; t < numNeighbors; t++) {
		int ii = i + dx[t];
		int jj = j + dy[t];

		if (isInBound(ii, jj, rows, cols)) {
			if (image.at<uchar>(ii, jj) == WHITE) return true;
		}
	}

	return false;
}

const char* ExtractByCanny::getName()
{
	return "canny";
}

void ExtractByCanny::extractEdge(const char* imagePath, Mat& output)
{
	// read image
	Mat image;
	readImage(imagePath, image);

	// smoothing the origin image
	smoothing(image, output);

	// calculate gradient
	Mat gx, gy, g;
	calculateGradient(output, gx, gy, g);

	// calculate angles
	Mat angles;
	calculateAngles(gx, gy, angles);

	// NMS
	NMS(output, g, angles);

	// Threshold
	threshold(output);

	// Hysteresis
	Mat result;
	hysteresis(output);

	namedWindow("Canny", WINDOW_KEEPRATIO);
	imshow("Canny", output);
}
