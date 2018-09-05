#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>

#include "Eigen/Core"
#include "Eigen/Dense"

#include "Homography.h"
#include "RansacHomography.h"

using namespace sfm;
using namespace geometry;

const int data_size = 100;
const double data_range = 15.0;

void GenerateData(std::vector<Eigen::Vector3d>& points1,
                  std::vector<Eigen::Vector3d>& points2,
                  const Eigen::Matrix3d& H)
{
    srand((unsigned int)time(NULL));

    // generate data for points1
    for (int i = 0; i < data_size; i++) {
        double x = rand() / (double(RAND_MAX)) * data_range;
        double y = rand() / (double(RAND_MAX)) * data_range;
        points1.push_back(Eigen::Vector3d(x, y, 1.0));
    }

    // Transform points1 by H to generate points2
    for (int i = 0; i < data_size; i++) {
        points2.push_back(H * points1[i]);
    }
}

void TEST()
{
    std::vector<Eigen::Vector3d> points1, points2;
    Eigen::Matrix3d H;
    H << 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0;
    GenerateData(points1, points2, H);

    std::cout << "Original Homography is: " << H << std::endl;

    std::vector<Eigen::Vector3d> inliers1, inliers2;
    Eigen::Matrix3d estimated_h = Eigen::Matrix3d::Zero();

    BaseHomographyDLT(points1, points2, estimated_h);

    // RansacHomography(points1, points2, inliers1, inliers2, estimated_h, 0.99, 0.005);

    std::cout << "Inliers size is: " << inliers1.size() << std::endl;
    std::cout << "Estimated Homography is: " << estimated_h << std::endl;
}

int main(int argc, char** argv)
{
    TEST();
}