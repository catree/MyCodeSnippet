#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include "Eigen/Core"
#include "Eigen/Dense"

namespace sfm {
Eigen::VectorXd Homoge2NonHomoge(const Eigen::VectorXd vec)
{
    size_t rows = vec.rows();
    Eigen::VectorXd nonh_vec(rows - 1)
    for (int i = 0; i < rows - 1; i++) {
        nonh_vec[i] = vec[i] / vec[rows - 1];
    }
    return nonh_vec;
}
}   // namespace sfm

#endif