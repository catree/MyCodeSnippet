#include "Common.h"

namespace sfm {
namespace math {

// template <typename T>
// T Mean(const std::vector<T>& vec)
// {
//     T sum = (T)0;
//     for (int i = 0; i < vec.size(); i++) {
//         sum += vec[i];
//     }
//     return (T)(sum / (T)vec.size());
// }

// template <typename T>
// T StdDeviation(const std::vector<T>& vec)
// {
//     T std = (T)0;
//     T mean = Mean(vec);
//     for (int i = 0; i < vec.size(); i++) {
//         std += (vec[i] - mean) * (vec[i] - mean);
//     }
//     std = sqrt(std / (T)vec.size());
//     return std;
// }


double Mean(const std::vector<double>& vec)
{
    double sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    return (sum / vec.size());
}


double StdDeviation(const std::vector<double>& vec)
{
    double std = 0;
    double mean = Mean(vec);
    for (int i = 0; i < vec.size(); i++) {
        std += (vec[i] - mean) * (vec[i] - mean);
    }
    std = sqrt(std / vec.size());
    return std;
}

Eigen::VectorXd Homoge2NonHomoge(const Eigen::VectorXd& vec)
{
    size_t rows = vec.rows();
    Eigen::VectorXd nonh_vec(rows - 1);
    for (int i = 0; i < rows - 1; i++) {
        nonh_vec[i] = vec[i] / vec[rows - 1];
    }
    return nonh_vec;
}

Eigen::Vector3d Nonhomoge2Homoge(const Eigen::Vector2d& vec)
{   
    Eigen::Vector3d homo_vec;
    homo_vec[0] = vec[0];
    homo_vec[1] = vec[1];
    homo_vec[2] = 1.0;
    return homo_vec;
}

Eigen::Vector3d Normalization(const Eigen::Vector3d& vec)
{
    Eigen::Vector3d normalized_point;
    normalized_point[0] = vec[0] / vec[2];
    normalized_point[1] = vec[1] / vec[2];
    normalized_point[2] = vec[2] / vec[2];
    return normalized_point;
}

}   // namespace math
}   // namespace sfm