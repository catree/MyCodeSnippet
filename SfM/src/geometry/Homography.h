#ifndef GEOMETRY_HOMOGRAPHY_H
#define GEOMETRY_HOMOGRAPHY_H

#include <vector>

#include "Eigen/Core"
#include "Eigen/Dense"

#include "Ransac.h"

namespace sfm {
namespace geometry {
    /**
     * @brief  
     * @note   
     * @param  points1: 
     * @param  points2: 
     * @param  homograpy: 
     * @retval 
     */
    bool BaseHomographyDLT(const std::vector<Eigen::Vector3d>& points1,
                           const std::vector<Eigen::Vector3d>& points2,
                           Eigen::Matrix3d& homography);
    
    bool NormalizedHomographyDLT(const std::vector<Eigen::Vector3d>& points1,
                                 const std::vector<Eigen::Vector3d>& points2,
                                 Eigen::Matrix3d& homography);
    
    double SingleImageError(const Eigen::Vector3d& point1,
                            const Eigen::Vector3d& point2,
                            const Eigen::Matrix3d& homography);

    double SymmetryTransferError(const Eigen::Vector3d& point1,
                                 const Eigen::Vector3d& point2,
                                 const Eigen::Matrix3d& homography);
}   // namespace geometry
}   // namespace sfm

#endif