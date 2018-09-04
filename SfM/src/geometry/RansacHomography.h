#ifndef GEOMETRY_RANSAC_HOMOGRAPHY_H
#define GEOMETRY_RANSAC_HOMOGRAPHY_H

#include <vector>
#include <iostream>

#include "Eigen/Core"
#include "Eigen/Dense"

namespace sfm {
namespace geometry {
    // bool (*homography_approach)(const std::vector<Eigen::Vector3d>&,
    //                             const std::vector<Eigen::Vector3d>&,
    //                             Matrix3d&);

    bool RansacHomography(const std::vector<Eigen::Vector3d>& points1,
                          const std::vector<Eigen::Vector3d>& points2,
                          std::vector<Eigen::Vector3d>& inliers1,
                          std::vector<Eigen::Vector3d>& inliers2,
                          Matrix3d& homography,
                          const double p,
                          const double t);
}   // namespace geometry
}   // namespace sfm

#endif