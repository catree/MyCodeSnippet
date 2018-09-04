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
    
    bool NormalizedHomographyDLT(const std::vector<Eigen::Vector3d>& points1,
                                 const std::vector<Eigen::Vector3d>& points2,
                                 Matrix3d& homograpy);
    
    Eigen::Matrix3d FindConditionerFromPoints(const std::vector<Eigen::Vector3d>& points);
    
    double SingleImageError(const Eigen::Vector3d& point1,
                            const Eigen::Vector3d& point2,
                            const Matrix3d& homograpy);

    double SymmetryTransferError(const Eigen::Vector3d& point1,
                                 const Eigen::Vector3d& point2,
                                 const Matrix3d& homography);
}   // namespace geometry
}   // namespace sfm

#endif