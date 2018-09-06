#include "Common.h"

namespace sfm {
namespace math {

template <typename T>
T Mean(const std::vector<T>& vec)
{
    size_t size = vec.size();
    T sum = (T)0;
    for (int i = 0; i < size; i++) {
        sum += vec[i];
    }
    return (T)(sum / (T)size);
}

}   // namespace math
}   // namespace sfm