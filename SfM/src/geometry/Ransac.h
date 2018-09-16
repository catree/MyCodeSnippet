#ifndef GEOMETRY_RANSAC_H
#define GEOMETRY_RANSAC_H

#include <iostream>

#include "Eigen/Core"
#include "Eigen/Dense"
#include "math/Common.h"

namespace sfm {
namespace geometry {
    /**
     * @brief  Compute the sample count
     * @note   
     * @param  o: the probability of outliers
     * @param  s: the size of point set that we need to sample 
     * @param  p: the probability that if we sample N times, and s points 
     * each time, there is no outlier at least once
     * @retval The count we need to sample
     */
    size_t GetSampleCount(double o, int s, double p = 0.99);

    Eigen::Matrix3d FindConditionerFromPoints(const std::vector<Eigen::Vector3d>& points);

}   // namespace geometry
}   // namespace sfm

#endif