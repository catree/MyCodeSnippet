#ifndef GEOMETRY_RANSAC_HOMOGRAPHY_H
#define GEOMETRY_RANSAC_HOMOGRAPHY_H

#include <vector>
#include <iostream>

#include "Eigen/Core"
#include "Eigen/Dense"

#include "ceres/ceres.h"

#include "Ransac.h"
#include "Homography.h"
#include "math/Common.h"

namespace sfm {
namespace geometry {

    bool RansacHomography(const std::vector<Eigen::Vector2d>& points1,
                          const std::vector<Eigen::Vector2d>& points2,
                          std::vector<Eigen::Vector2d>& inliers1,
                          std::vector<Eigen::Vector2d>& inliers2,
                          Eigen::Matrix3d& homography,
                          const double p = 0.99,
                          const double t = 0.005);

    struct SingleImageCostFunction
    {
        Eigen::Vector2d _point1;
        Eigen::Vector2d _point2;

        SingleImageCostFunction(Eigen::Vector2d point1, Eigen::Vector2d point2)
            : _point1(point1), _point2(point2) {}

        template <typename T>
        bool operator()(const T* const h, T* residuals) const
        {
            Eigen::Vector3d homo_point1_hat;
            T p2_x = h[0] * (T)_point1[0] + h[1] * (T)_point1[1] + h[2];
            T p2_y = h[3] * (T)_point1[0] + h[4] * (T)_point1[1] + h[5];
            T p2_w = h[6] * (T)_point1[0] + h[7] * (T)_point1[1] + h[8];
            p2_x /= p2_w;
            p2_y /= p2_w;

            residuals[0] = p2_x - (T)_point2[0];
            residuals[1] = p2_y - (T)_point2[1];
            // residuals[2] = point1_hat[2] - (T)_point2[2];
            return true;
        }

        static ceres::CostFunction* Create(const Eigen::Vector2d point1, 
                                           const Eigen::Vector2d point2)
        {
            return new ceres::AutoDiffCostFunction<SingleImageCostFunction, 2, 9>(
                new SingleImageCostFunction(point1, point2));
        }
    };


    bool LMHomography(const std::vector<Eigen::Vector2d>& points1,
                      const std::vector<Eigen::Vector2d>& points2,
                      Eigen::Matrix3d& homography);

}   // namespace geometry
}   // namespace sfm

#endif