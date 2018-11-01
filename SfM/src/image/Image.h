#ifndef IMAGE_IMAGE_H
#define IMAGE_IMAGE_H

#include <string>
#include <OpenImageIO/imageio.h>

namespace sfm {
namespace image {

class Image
{
private:
    std::string _image_path;    // absolute path of image
    size_t _width;              // image widht
    size_t _height;             // image height
    size_t _channels;           // number of image channels
    unsigned char* _data;       // image data

public:
    Image();
    Image(const std::string& filename);
    Image(const std::string& filename,
          const size_t& width, 
          const size_t& height, 
          const size_t& channels);
    ~Image();

    bool SetImageData(const unsigned char* const data);

    // Get functions
    size_t GetWidth() const;
    size_t GetHeight() const;
    size_t GetChannels() const;
    unsigned char* GetImageData() const;

    // Image I/O operation
    bool ReadImage();
    bool WriteImage() const;
};
}
}

#endif