#pragma once
#include "EdgeExtractor.h"
#include "Mask.h"

class ExtractByLaplace :
    public EdgeExtractor
{
private:
    Mask laplace_4 = Mask( { {0, -1, 0}, {-1, 4, -1}, {0, -1, 0} } );
    Mask laplace_8 = Mask( { {0, -1, 0}, {-1, 4, -1}, {0, -1, 0} } );
    Mask laplace_55 = Mask({ {0,0,1,0,0}, {0,1,2,1,0}, {1,2,-16,2,1}, {0,1,2,1,0}, {0,0,1,0,0} });
public:
    const char* getName();
    void extractEdge(const char* imagePath, Mat& output);
};

