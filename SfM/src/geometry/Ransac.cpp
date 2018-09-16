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

Eigen::Matrix3d FindConditionerFromPoints(const std::vector<Eigen::Vector3d>& points)
{
    std::vector<Eigen::VectorXd> nonh_points;
    for (Eigen::Vector3d point : points) {
        nonh_points.push_back(math::Homoge2NonHomoge(point));
    }

    std::vector<double> vec_x(nonh_points.size());
    std::vector<double> vec_y(nonh_points.size());
    for (int i = 0; i < nonh_points.size(); i++) {
        vec_x[i] = nonh_points[i][0];
        vec_y[i] = nonh_points[i][1];
    }
 
    Eigen::Vector2d mean_vec;
    mean_vec[0] = sfm::math::Mean(vec_x); 
    mean_vec[1] = sfm::math::Mean(vec_y);

    Eigen::Matrix<double, 1, 2> std_row_vec;
    double std_x = sfm::math::StdDeviation(vec_x);
    double std_y = sfm::math::StdDeviation(vec_y);
    std_row_vec(0, 0) = std_x + (std_x == 0);
    std_row_vec(0, 1) = std_y + (std_y == 0);

    Eigen::Matrix3d sim = Eigen::Matrix3d::Zero();
    sim(0, 0) = sqrt(2) / std_row_vec(0, 0);
    sim(1, 1) = sqrt(2) / std_row_vec(0, 1);
    sim(0, 2) = -sqrt(2) * mean_vec[0] / std_row_vec(0, 0);
    sim(1, 2) = -sqrt(2) * mean_vec[1] / std_row_vec(0, 1);
    sim(2, 2) = 1.0;

    return sim;
}

}   // namespace geometry
}   // namespace sfm