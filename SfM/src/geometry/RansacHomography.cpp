#include <ctime>
#include <random>
#include <algorithm>

#include "RansacHomography.h"
#include "Ransac.h"
#include "Homography.h"

using namespace std;

namespace sfm {
namespace geometry {

bool RansacHomography(std::vector<Eigen::Vector3d>& points1,
                      std::vector<Eigen::Vector3d>& points2,
                      std::vector<Eigen::Vector3d>& inliers1,
                      std::vector<Eigen::Vector3d>& inliers2,
                      Matrix3d& homography,
                      const double p,
                      const double t)
{
    int N = 0x7fffffff;
    int sample_count = 0;
    int s = 4;
    int size = points1.size();
    int inlier_num = 0;
    
    vector<int> indeces;
    for (int i = 0; i < size; i++) { indeces.push_back(i); }

    srand((unsigned)time(NULL));
    while (N > sample_count) {
        random_shuffle(indeces.begin(), indeces.end());
        vector<Eigen::Vector3d> sample_points1, sample_points2;
        for (int i = 0; i < s; i++) {
            int index = indeces[i];
            sample_points1.push_back(points1[index]);
            sample_points2.push_back(points2[index]);
        }

        Eigen::Matrix3d H = Eigen::Matrix3d::Zeros();
        if (!NormalizedHomographyDLT(sample_points1, sample_points2, H)) {
            return false;
        }
        
        // Compute inliers
        for (int i = 0; i < size; i++) {
            double dis = SymmetryTransferError(points1[i], points2[i], H);
            if (dis <= t) {
                inliers1.push_back(points1[i]);
                inliers2.push_back(points2[i]);
            }
        }

        if (inlier_num < inliers1.size()) {
            inlier_num = inliers1.size();
            homography = H;
        }
        else if (inlier_num == inliers1.size()) {
            // TODO: choose the one that has the lowest variance
        }

        double o = 1.0 - (double)inlier_num / (double)size;
        N = GetSampleCount(o, s, p);
        sample_count++;
    }
    return true;
}

}   // namespace geometry
}   // namespace sfm