#ifndef MATH_COMMON_H
#define MATH_COMMON_H

#include <cmath>
#include <vector>

namespace sfm {
namespace math {
    template <typename T>
    T Mean(const std::vector<T>& vec);

}   // math
}   // sfm

#endif