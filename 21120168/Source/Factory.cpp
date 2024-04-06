#include "../Header/Factory.h"

EdgeExtractor* Factory::getDetector(char* algorithm)
{
    if (strcmp(algorithm, "sobel") == 0) {
        return new ExtractBySobel();
    }
    else if (strcmp(algorithm, "prewitt") == 0) {
        return new ExtractByPrewitt();
    }
    else if (strcmp(algorithm, "laplace") == 0) {
        return new ExtractByLaplace();
    }
    else if (strcmp(algorithm, "canny") == 0) {
        return new ExtractByCanny();
    }
    else if (strcmp(algorithm, "opencv") == 0) {
        return new ExtractByOpenCV();
    }
    return nullptr;
}

vector<EdgeExtractor*> Factory::getAllDetectors()
{
    vector<EdgeExtractor*> detectors;

    detectors.push_back(new ExtractBySobel());
    detectors.push_back(new ExtractByPrewitt());
    detectors.push_back(new ExtractByLaplace());
    detectors.push_back(new ExtractByCanny());
    detectors.push_back(new ExtractByOpenCV());

    return detectors;
}
