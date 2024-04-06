#include "../Header/AppController.h"

void AppController::run(int argc, char** argv)
{
	if (isAlgorithm(argc, argv)) {
		// algorithm_name: sobel - prewitt - laplace - canny - opencv
		// .\21120168.exe <image_path> <algorithm_name> 
		execAlgorithm(argv[1], argv[2]);
	}
	else if (isDemo(argc, argv)) {
		// try all algorithms + opencv for a folder of images (~5)
		// .\21120168.exe <folder_path> demo
		execDemo(argv[1]);
	}
	else {
		// for help:
		showHelp();
	}
}

bool AppController::isAlgorithm(int argc, char** argv)
{
	// algorithm_name: sobel - prewitt - laplace - canny - opencv
	// .\21120168.exe <image_path> <algorithm_name> 
	int algNum = algorithm_name.size();

	if (argc != 3) return false;

	for (int i = 0; i < algNum; i++) {
		if (strcmp(argv[2], algorithm_name[i]) == 0) return true;
	}

	return false;
}

void AppController::execAlgorithm(char* filePath, char* algorithm)
{
	EdgeExtractor* detector = Factory::getDetector(algorithm);
	if (detector == nullptr) {
		exit(-1);
		cerr << "Can not find algorithm with name " << algorithm << " !";
	}

	Mat output;
	detector->extractEdge(filePath, output);
	delete detector;
}

bool AppController::isDemo(int argc, char** argv)
{
	// try all algorithms + opencv for a folder of images (~5)
	// .\21120168.exe <folder_path> demo

	if (argc != 3) return false;

	if (strcmp("demo", argv[2]) == 0) return true;

	return false;
}

void AppController::execDemo(char* folderPath)
{
	vector<EdgeExtractor*> detectors = Factory::getAllDetectors();
	int numAlgs = detectors.size();
	
	fs::path rootPath(folderPath);
	fs::path edgeDetectionPath = rootPath.parent_path() / "EdgeDetection";

	if (fs::exists(edgeDetectionPath)) {
		
		std::cerr << "Folder EdgeDetection already exists!" << std::endl;

		// Delete the existing EdgeDetection folder and its contents
		try {
			fs::remove_all(edgeDetectionPath);
			std::cout << "Deleted existing EdgeDetection folder." << std::endl;
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Failed to delete existing EdgeDetection folder: " << e.what() << std::endl;
			return;
		}
	}

	if (fs::create_directory(edgeDetectionPath)) {
		std::cout << "Created EdgeDetection folder." << std::endl;
	}
	else {
		std::cerr << "Failed to create EdgeDetection folder." << std::endl;
		return;
	}

	for (const auto& entry : fs::directory_iterator(rootPath)) {
		if (fs::is_regular_file(entry.path())) {
			fs::path fileName = entry.path().filename();
			fs::path subFolderPath = edgeDetectionPath / fileName.stem();

			if (!fs::exists(subFolderPath)) {
				if (fs::create_directory(subFolderPath)) {
					cout << "Created subfolder: " << subFolderPath << std::endl;
				
					for (int i = 0; i < numAlgs; i++) {
						string filepath_str = entry.path().string();
						const char* filepath = filepath_str.c_str();
						// cout << "file path: " << filepath << "\n";

						Mat output;
						detectors[i]->extractEdge(filepath, output);

						string name = detectors[i]->getName() + entry.path().extension().string();
						fs::path outfilepath = subFolderPath / name;
						cout << "outfile path: " << outfilepath << "\n";

						imwrite(outfilepath.string(), output);
					}
				}
				else {
					std::cerr << "Failed to create subfolder: " << subFolderPath << std::endl;
				}
			}
		}
	}
	
}

void AppController::showHelp()
{
	cout << "---------------- Helper for Lab02: Edge Detection ----------------\n";
	cout << "Run all algorithms with images in a folder:\n";
	cout << "\t .\\21120168.exe <folder_path> demo\n";
	cout << "\n";
	cout << "Extract edge of an image with an algorithm:\n";
	cout << "\t .\\21120168.exe <image_path> <algorithm_name>\n";
	cout << "\talgorithm name: sobel - prewitt - laplace - canny - opencv\n";
	cout << "------------------------------------------------------------------\n";
}
