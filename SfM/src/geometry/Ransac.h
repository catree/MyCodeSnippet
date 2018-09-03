#ifndef GEOMETRY_RANSAC_H
#define GEOMETRY_RANSAC_H

#include <iostream>

namespace sfm {
namespace geometry {
    /**
     * @brief  
     * @note   
     * @param  o: the probability of outliers
     * @param  s: the size of point set that we need to sample 
     * @param  p: the probability that if we sample N times, and s points 
     * each time, there is no outlier at least once
     * @retval The count we need to sample
     */
    int GetSampleCount(double o, int s, double p = 0.99);

}   // namespace geometry
}   // namespace sfm

#endif