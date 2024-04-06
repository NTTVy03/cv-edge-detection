#pragma once
#include <vector>
#include "EdgeExtractor.h"
#include "Factory.h"
#include <filesystem>
#include <string>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

class AppController
{
private:
	vector<const char*> algorithm_name = {"sobel", "prewitt", "laplace", "canny", "opencv"};

public: 
	void run(int argc, char** argv);

private:
	bool isAlgorithm(int argc, char** argv);
	void execAlgorithm(char* filePath, char* algorithm);

	bool isDemo(int argc, char** argv);
	void execDemo(char* folderPath);

	void showHelp();
};

