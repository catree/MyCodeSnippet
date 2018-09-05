#include <iostream>
#include <cmath>

#include "Ransac.h"

namespace sfm {
namespace geometry {

size_t GetSampleCount(double o, int s, double p)
{   
    // according to "Multiple view geometry in computer vision"
    return (size_t) (log(1.0 - p) / log(1.0 - pow(1.0 - o, s)));
}

}   // namespace geometry
}   // namespace sfm