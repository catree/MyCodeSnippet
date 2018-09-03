#ifndef GEOMETRY_HOMOGRAPHY_H
#define GEOMETRY_HOMOGRAPHY_H

#include <vector>

#include "Eigen/Core"
#include "Eigen/Dense"

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
                           Matrix3d& homograpy);
    
    bool RansacHomograpy(const std::vector<Eigen::Vector3d>& points1,
                         const std::vector<Eigen::Vector3d>& points2,
                         Matrix3d& homograpy);
}   // namespace geometry
}   // namespace sfm

#endif