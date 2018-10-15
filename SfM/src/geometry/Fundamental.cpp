#include "Fundamental.h"

namespace sfm {
namespace geometry {
bool BaseFundamental(const std::vector<Eigen::Vector3d>& points1,
                     const std::vector<Eigen::Vector3d>& points2,
                     Eigen::Matrix3d& fundamental)
{
    if (points1.size() < 4 || points2.size() < 4) {
        std::cerr << "size of correspondences less than 4,"; 
        std::cerr << "cannot estimate a homography\n";
        return false;
    }

    uint size = points1.size();
    Eigen::Matrix<double, 9, 1> h = Eigen::Matrix<double, 9, 1>::Zero();
    Eigen::MatrixXd A = Eigen::MatrixXd::Identity(size, 8);
    
    for (uint i = 0; i < size; i++) {
        A(i, 0) = points1[i][0] * points2[i][0];
        A(i, 1) = points1[i][1] * points2[i][0];
        A(i, 2) = points1[i][0];
        A(i, 3) = points1[i][0] * points2[i][1];
        A(i, 4) = points1[i][1] * points2[i][1];
        A(i, 5) = points2[i][1];
        A(i, 6) = points1[i][0];
        A(i, 7) = points1[i][1];
    }

    // Performing SVD decomposition to A
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinV);
    Eigen::MatrixXd V = svd.matrixV();
    // fundamental matrix is the last column of V
    for (int i = 0; i < 3; i++) {
        fundamental(i, 0) = V(i * 3 + 0, 8) / V(8, 8);
        fundamental(i, 1) = V(i * 3 + 1, 8) / V(8, 8);
        fundamental(i, 2) = V(i * 3 + 2, 8) / V(8, 8);
    }
}

bool NormalizedFundamental(const std::vector<Eigen::Vector3d>& points1,
                           const std::vector<Eigen::Vector3d>& points2,
                           Eigen::Matrix3d& fundamental)
{
    Eigen::Matrix3d sim1 = FindConditionerFromPoints(points1);
    Eigen::Matrix3d sim2 = FindConditionerFromPoints(points2);
    uint size = (points1.size() == points2.size()) ? points1.size() : 0;

    std::vector<Eigen::Vector3d> norm_points1, norm_points2;
    for (uint i = 0; i < size; i++) {
        norm_points1.push_back(sim1 * points1[i]);
        norm_points2.push_back(sim2 * points2[i]);
    }

    Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
    BaseFundamental(norm_points1, norm_points2, fundamental);
    Eigen::Matrix3d f = Eigen::Matrix3d::Zero();
    f = sim2.transpose() * F * sim1;
    for (uint i = 0; i < 3; i++) {
        for (uint j = 0; j < 3; j++) {
            // f(i, j) /= f(2, 2);
        }
    }
    return size;
}

}
}