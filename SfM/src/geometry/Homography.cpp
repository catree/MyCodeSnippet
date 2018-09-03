#include "Homography.h" 

#include "Eigen/Core"
#include "Eigen/Dense"

#include "Ransac.h"

namespace sfm {
namespace geometry {

bool BaseHomographyDLT(const std::vector<Eigen::Vector3d>& points1,
                       const std::vector<Eigen::Vector3d>& points2,
                       Eigen::Matrix3d& homography)
{
    if (points1.size() < 4 || points2.size() < 4) {
        std::cerr << "size of correspondences less than 4," 
        std::cerr << "cannot estimate a homography\n"
        return false;
    }

    int size = points1.size();
    Eigen::MatrixXd A = Eigen::MatrixXd::Zeros(3 * size, 9);

    for (int i = 0; i < size; i++) {
        double x1 = points1[i][0], y1 = points1[i][1], w1 = points1[i][2];
        double x2 = points2[i][0], y2 = points2[i][1], w2 = points2[i][2];

        A(i * 3 + 0, 3) = -w2 * x1; A(i * 3 + 0, 4) = -w2 * y1; A(i * 3 + 0, 5) = -w2 * w1;
        A(i * 3 + 0, 6) =  y2 * x1; A(i * 3 + 0, 7) =  y2 * y1; A(i * 3 + 0, 8) =  y2 * w1;
        A(i * 3 + 1, 0) =  w2 * x1; A(i * 3 + 1, 1) =  w2 * y1; A(i * 3 + 1, 2) =  w2 * w1;
        A(i * 3 + 1, 6) = -x2 * x1; A(i * 3 + 1, 7) = -x2 * y1; A(i * 3 + 1, 8) = -x2 * w1;
        // (optional) if the last row of A is used
        A(i * 3 + 2, 0) = -y2 * x1; A(i * 3 + 2, 1) = -y2 * y1; A(i * 3 + 2, 2) = -y2 * w1;
        A(i * 3 + 2, 3) =  x2 * x1; A(i * 3 + 2, 4) =  x2 * y1; A(i * 3 + 2, 5) =  x2 * w1;
    }

    // Performing SVD decomposition to A
    Eigen::BDCSVD<Eigen::MatrixXd> svd_a(A, Eigen::ComputeThinV);
    Eigen::MatrixXd V = svd_a.matrixV();
    // homograpy is the last column of V
    for (int i = 0; i < 3; i++) {
        homography(i, 0) = V(i * 3 + 0, 8); 
        homography(i, 1) = V(i * 3 + 1, 8);
        homography(i, 2) = V(i * 3 + 2, 8);
    }

    return true;
}

bool RansacHomography(const std::vector<Eigen::Vector3d>& points1,
                      const std::vector<Eigen::Vector3d>& points2,
                      Matrix3d& homograpy)
{

}

}   // namespace geometry
}   // namespace sfm