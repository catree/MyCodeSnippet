#ifndef GEOMETRY_FUNDAMENTAL_H
#define GEOMETRY_FUNDAMENTAL_H

#include <vector>

#include "Eigen/Core"
#include "Eigen/Dense"

#include "Ransac.h"

namespace sfm {
namespace geometry {
    
    void BaseFundamental(const std::vector<Eigen::Vector3d>& points1,
                         const std::vector<Eigen::Vector3d>& points2,
                         Eigen::Matrix3d& fundamental);
    
}   // namespace geometry
}   // namespace sfm

#endif