#include "ImageProcess.h"

namespace sfm {
namespace image {
bool RGB2Gray(const std::vector<unsigned char>& rgb_pixels,
                     unsigned char gray_pixels[],
                     const int width,
                     const int height,
                     const int channels)
{
    size_t data_length = width * height * channels;
    for (size_t i = 0; i < data_length; i += channels) {
        unsigned char r = rgb_pixels[i + 0];
        unsigned char g = rgb_pixels[i + 1];
        unsigned char b = rgb_pixels[i + 2];
        unsigned char grayscale = (r * 38 + g * 75 + b * 15) >> 7;
        gray_pixels[i / channels] = grayscale;
    }
    return true;
}

}   // namespace image
}   // namespace sfm