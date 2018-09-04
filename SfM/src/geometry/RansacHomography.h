#ifndef GEOMETRY_RANSAC_HOMOGRAPHY_H
#define GEOMETRY_RANSAC_HOMOGRAPHY_H

#include <vector>
#include <iostream>

#include "Eigen/Core"
#include "Eigen/Dense"

#include "ceres/ceres.h"

namespace sfm {
namespace geometry {

    struct SingleImageCostFunction
    {
        Eigen::Vector3d _point1;
        Eigen::Vector3d _point2;

        SingleImageCostFunction(Eigen::Vector3d point1, Eigen::Vector3d point2)
            : _point1(point1), _point2(point2) {}

        template <typename T>
        bool operator()(const T* const h, T* residuals) const
        {
            Eigen::Matrix<3, 3, T> H;
            H << h[0], h[1], h[2], h[3], h[4], h[5], h[6], h[7], h[8];
            point1_hat = H * _point1;
            residuals[0] = point1_hat[0] - (T)_point2[0];
            residuals[1] = point1_hat[1] - (T)_point2[1];
            residuals[2] = point1_hat[2] - (T)_point2[2];
            return true;
        }

        static ceres::CostFunction* Create(const Eigen::Vector3d point1, 
                                           const Eigen::Vector3d point2)
        {
            return new ceres::AutoDiffCostFunction<SingleImageCostFunction, 3, 9>(
                new SingleImageCostFunction(point1, point2));
        }
    };

    bool RansacHomography(const std::vector<Eigen::Vector3d>& points1,
                          const std::vector<Eigen::Vector3d>& points2,
                          std::vector<Eigen::Vector3d>& inliers1,
                          std::vector<Eigen::Vector3d>& inliers2,
                          Matrix3d& homography,
                          const double p,
                          const double t);

    bool LMHomography(const std::vector<Eigen::Vector3d>& points1,
                      const std::vector<Eigen::Vector3d>& points2,
                      Matrix3d& homography);
}   // namespace geometry
}   // namespace sfm

#endif