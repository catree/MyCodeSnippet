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

const int data_size1 = 100;
const int data_size2 = 1000;
const int data_size3 = 10000;
const double data_range = 15.0;

void GenerateData(std::vector<Eigen::Vector3d>& points1,
                  std::vector<Eigen::Vector3d>& points2,
                  const int data_size,
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
    // add noise
    double outlier_ratio = rand() / (double(RAND_MAX)) * 0.05;
    std::cout << "Pre-setted outlier ratio: " << outlier_ratio << std::endl;
    for (int i = 0; i < (int)(outlier_ratio * data_size); i++) {
        int idx = rand() % data_size;
        Eigen::Vector3d noise_offset;
        noise_offset << rand() / (double(RAND_MAX)) * data_range,
                        rand() / (double(RAND_MAX)) * data_range,
                        rand() / (double(RAND_MAX)) * data_range;
        points2[idx] += noise_offset;
    }
}

void TEST1()
{
    std::vector<Eigen::Vector3d> points1, points2;
    Eigen::Matrix3d H;
    H << 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0;
    GenerateData(points1, points2, data_size1, H);

    std::cout << "Original Homography is: \n" << H << std::endl;

    std::vector<Eigen::Vector3d> inliers1, inliers2;
    Eigen::Matrix3d estimated_h = Eigen::Matrix3d::Zero();
    RansacHomography(points1, points2, inliers1, inliers2, estimated_h, 0.99, 0.005);

    std::cout << "Inliers size is: " << inliers1.size() << std::endl;
    std::cout << "Estimated Homography is: \n" << estimated_h << "\n\n";
}

void TEST2()
{
    std::vector<Eigen::Vector3d> points1, points2;
    Eigen::Matrix3d H;
    H << 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0;
    GenerateData(points1, points2, data_size2, H);

    std::cout << "Original Homography is: \n" << H << std::endl;

    std::vector<Eigen::Vector3d> inliers1, inliers2;
    Eigen::Matrix3d estimated_h = Eigen::Matrix3d::Zero();
    RansacHomography(points1, points2, inliers1, inliers2, estimated_h, 0.99, 0.005);

    std::cout << "Inliers size is: " << inliers1.size() << std::endl;
    std::cout << "Estimated Homography is: \n" << estimated_h << "\n\n";
}

void TEST3()
{
    std::vector<Eigen::Vector3d> points1, points2;
    Eigen::Matrix3d H;
    H << 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0;
    GenerateData(points1, points2, data_size3, H);

    std::cout << "Original Homography is: \n" << H << std::endl;

    std::vector<Eigen::Vector3d> inliers1, inliers2;
    Eigen::Matrix3d estimated_h = Eigen::Matrix3d::Zero();
    RansacHomography(points1, points2, inliers1, inliers2, estimated_h, 0.99, 0.005);

    std::cout << "Inliers size is: " << inliers1.size() << std::endl;
    std::cout << "Estimated Homography is: \n" << estimated_h << "\n\n";
}

int main(int argc, char** argv)
{
    TEST1();
    TEST2();
    TEST3();
}