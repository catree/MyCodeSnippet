#include <iostream>
#include <cmath>

#include "Ransac.h"

namespace sfm {
namespace geometry {

int GetSampleCount(double o, int s, double p)
{   
    // according to "Multiple view geometry in computer vision"
    return (int) (log(1.0 - p) / log(1.0 - pow(1.0 - o, s)));
}

}   // namespace geometry
}   // namespace sfm