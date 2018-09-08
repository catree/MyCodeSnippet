#ifndef MATH_COMMON_H
#define MATH_COMMON_H

#include <cmath>
#include <vector>
#include <iostream>

#include "Eigen/Core"
#include "Eigen/Dense"

namespace sfm {
namespace math {

    // template <typename T>
    // T Mean(const std::vector<T>& vec);

    // template <typename T>
    // T StdDeviation(const std::vector<T>& vec);

    double Mean(const std::vector<double>& vec);

    double StdDeviation(const std::vector<double>& vec);

    Eigen::VectorXd Homoge2NonHomoge(const Eigen::VectorXd& vec);

    Eigen::Vector3d Nonhomoge2Homoge(const Eigen::Vector2d& vec);
    
    Eigen::Vector3d Normalization(const Eigen::Vector3d& vec);

}   // math
}   // sfm

#endif