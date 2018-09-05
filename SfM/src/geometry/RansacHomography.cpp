#include <ctime>
#include <random>
#include <algorithm>

#include "ceres/ceres.h"

#include "RansacHomography.h"

using namespace std;

namespace sfm {
namespace geometry {

bool RansacHomography(const std::vector<Eigen::Vector3d>& points1,
                      const std::vector<Eigen::Vector3d>& points2,
                      std::vector<Eigen::Vector3d>& inlier_set1,
                      std::vector<Eigen::Vector3d>& inlier_set2,
                      Eigen::Matrix3d& homography,
                      const double p,
                      const double t)
{
    size_t N = 10000;
    int sample_count = 0;
    int s = 5;
    int size = points1.size();
    int inlier_num = 0;
    
    
    vector<int> indeces;
    for (int i = 0; i < size; i++) { indeces.push_back(i); }

    srand((unsigned)time(NULL));
    while (N > sample_count) {
        std::vector<Eigen::Vector3d> inliers1, inliers2;
        random_shuffle(indeces.begin(), indeces.end());
        vector<Eigen::Vector3d> sample_points1, sample_points2;
        for (int i = 0; i < s; i++) {
            int index = indeces[i];
            sample_points1.push_back(points1[index]);
            sample_points2.push_back(points2[index]);
            // std::cout << "index: " << index << std::endl;
        }

        Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
        // TODO
        // if (!NormalizedHomographyDLT(sample_points1, sample_points2, H)) {
        //     return false;
        // }
        if (!BaseHomographyDLT(sample_points1, sample_points2, H)) {
            return false;
        }
        std::cout << "H: \n" << H << std::endl;
        // Compute inliers
        for (int i = 0; i < size; i++) {
            // double dis = SymmetryTransferError(points1[i], points2[i], H);
            double dis = SingleImageError(points1[i], points2[i], H);
            // std::cout << "error: " << dis << std::endl;
            if (dis <= t) {
                inliers1.push_back(points1[i]);
                inliers2.push_back(points2[i]);
            }
        }

        if (inlier_num < inliers1.size()) {
            inlier_num = inliers1.size();
            inliers1.swap(inlier_set1);
            inliers2.swap(inlier_set2);
            homography = H;
        }
        else if (inlier_num == inliers1.size()) {
            // TODO: choose the one that has the lowest variance
        }

        double o = 1.0 - (double)inlier_num / (double)size;
        N = GetSampleCount(o, s, p);
        std::cout << "inlier_num: " << inlier_num << std::endl;
        std::cout << "outlier ratio: " << o << std::endl;
        std::cout << "Updated(N): " << N << "\n";
        sample_count++;
    }
    return true;
}

// bool LMHomography(const std::vector<Eigen::Vector3d>& points1,
//                   const std::vector<Eigen::Vector3d>& points2,
//                   Eigen::Matrix3d& homography)
// {
//     // TODO
//     // NormalizedHomographyDLT(points1, points2, homography);
//     BaseHomographyDLT(points1, points2, homography);
//     std::vector<double> h(9);
//     h[0] = homography(0, 0); h[1] = homography(0, 1); h[2] = homography(0, 2);
//     h[3] = homography(1, 0); h[4] = homography(1, 1); h[5] = homography(1, 2);
//     h[6] = homography(2, 0); h[7] = homography(2, 1); h[8] = homography(2, 2);

//     ceres::Problem problem;
//     for (int i = 0; i < points1.size(); i++) {
//         ceres::CostFunction* cost_function = 
//             SingleImageCostFunction::Create(points1[i], points2[i]);
//         ceres::LossFunction* loss_function = NULL;
//         problem.AddResidualBlock(cost_function, loss_function, h);
//     }

//     ceres::Solver::Options options;
//     options.linear_solver_type = ceres::DENSE_SCHUR;
//     options.minimizer_progress_to_stdout = true;
//     // options.num_threads = 

//     ceres::Solver::Summary summary;
//     ceres::Solve(options, &problem, &summary);
//     std::cout << summary.FullReport() << std::endl;

//     homography(0, 0) = h[0]; homography(0, 1) = h[1]; homography(0, 2) = h[2];
//     homography(1, 0) = h[3]; homography(1, 1) = h[4]; homography(1, 2) = h[5];
//     homography(2, 0) = h[6]; homography(2, 1) = h[7]; homography(2, 2) = h[8];
    
//     return true;
// }

}   // namespace geometry
}   // namespace sfm