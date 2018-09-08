#include <algorithm>

#include "Homography.h" 
#include "math/Common.h"

#include "Eigen/Core"
#include "Eigen/Dense"

namespace sfm {
namespace geometry {

bool BaseHomographyDLT(const std::vector<Eigen::Vector3d>& points1,
                       const std::vector<Eigen::Vector3d>& points2,
                       Eigen::Matrix3d& homography)
{
    if (points1.size() < 4 || points2.size() < 4) {
        std::cerr << "size of correspondences less than 4,"; 
        std::cerr << "cannot estimate a homography\n";
        return false;
    }

    int size = points1.size();
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(3 * size, 9);

    for (int i = 0; i < size; i++) {
        double x1 = points1[i][0], y1 = points1[i][1], w1 = points1[i][2];
        double x2 = points2[i][0], y2 = points2[i][1], w2 = points2[i][2];

        A(i * 3 + 0, 3) = -w2 * x1; A(i * 3 + 0, 4) = -w2 * y1; A(i * 3 + 0, 5) = -w2 * w1;
        A(i * 3 + 0, 6) =  y2 * x1; A(i * 3 + 0, 7) =  y2 * y1; A(i * 3 + 0, 8) =  y2 * w1;
        A(i * 3 + 1, 0) =  w2 * x1; A(i * 3 + 1, 1) =  w2 * y1; A(i * 3 + 1, 2) =  w2 * w1;
        A(i * 3 + 1, 6) = -x2 * x1; A(i * 3 + 1, 7) = -x2 * y1; A(i * 3 + 1, 8) = -x2 * w1;
        // (optional) if the last row of A is used
        // A(i * 3 + 2, 0) = -y2 * x1; A(i * 3 + 2, 1) = -y2 * y1; A(i * 3 + 2, 2) = -y2 * w1;
        // A(i * 3 + 2, 3) =  x2 * x1; A(i * 3 + 2, 4) =  x2 * y1; A(i * 3 + 2, 5) =  x2 * w1;
    }

    // Performing SVD decomposition to A
    // Eigen::BDCSVD<Eigen::MatrixXd> svd_a(A, Eigen::ComputeThinV);
    Eigen::JacobiSVD<Eigen::MatrixXd> svd_a(A, Eigen::ComputeThinV);
    Eigen::MatrixXd V = svd_a.matrixV();
    // homograpy is the last column of V
    for (int i = 0; i < 3; i++) {
        homography(i, 0) = V(i * 3 + 0, 8) / V(8, 8); 
        homography(i, 1) = V(i * 3 + 1, 8) / V(8, 8);
        homography(i, 2) = V(i * 3 + 2, 8) / V(8, 8);
    }
    return true;
}

bool NormalizedHomographyDLT(const std::vector<Eigen::Vector3d>& points1,
                             const std::vector<Eigen::Vector3d>& points2,
                             Eigen::Matrix3d& homography)
{
    if (points1.size() < 4 || points2.size() < 4) {
        std::cerr << "size of correspondences less than 4,";
        std::cerr << "cannot estimate a homography\n";
        return false;
    }

    Eigen::Matrix3d T1 = FindConditionerFromPoints(points1);
    Eigen::Matrix3d T2 = FindConditionerFromPoints(points2);

    std::vector<Eigen::Vector3d> points1_hat, points2_hat;
    for (int i = 0; i < points1.size(); i++) {
        points1_hat.push_back(T1 * points1[i]);
        points2_hat.push_back(T2 * points2[i]);
    }

    Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
    BaseHomographyDLT(points1_hat, points2_hat, H);
    homography = T2.inverse() * H * T1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            homography(i, j) = homography(i, j) / homography(2, 2);
        }
    }

    return true;
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

double SingleImageError(const Eigen::Vector3d& point1,
                        const Eigen::Vector3d& point2,
                        const Eigen::Matrix3d& homography)
{
    double err = 0.0;
    Eigen::Vector3d point2_hat = math::Normalization(homography * point1);
    err += (point2_hat - point2).norm();

    return err;
}

double SymmetryTransferError(const Eigen::Vector3d& point1,
                             const Eigen::Vector3d& point2,
                             const Eigen::Matrix3d& homography)
{
    double err = 0.0;
    err += SingleImageError(point1, point2, homography);
    Eigen::Matrix3d inv_homography = homography.inverse();
    err += SingleImageError(point2, point1, inv_homography);

    return 0.5 * err;
}


}   // namespace geometry
}   // namespace sfm