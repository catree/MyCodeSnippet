#ifndef IMAGE_IMAGE_PROCESS_H
#define IMAGE_IMAGE_PROCESS_H

#include <OpenImageIO/imageio.h>

using namespace OIIO;

namespace sfm {
namespace image {
bool RGB2Gray(const std::vector<unsigned char>& rgb_pixels,
                     unsigned char gray_pixels[],
                     const int width,
                     const int height,
                     const int channels = 3);

}   // namespace image
}   // namespace sfm


#endif

