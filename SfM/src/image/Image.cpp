#include "Image.h"

#include <iostream>

namespace sfm {
namespace image {
    
Image::Image()
{

}   

Image::Image(const std::string& filename)
{
    _image_path = filename;
}

Image::Image(const std::string& filename,
             const size_t& width, 
             const size_t& height, 
             const size_t& channels)
{
    _image_path = filename;
    _width = width;
    _height = height;
    _channels = channels;
}

Image::~Image()
{
    if (_data) {
        delete [] _data;
        _data = nullptr;
    }
}

bool Image::SetImageData(const unsigned char* const data)
{
    size_t data_length = _width * _height * _channels;
    for (size_t i = 0; i < data_length; i++) {
        _data[i] = data[i];
    }
    return true;
}

size_t Image::GetWidth() const
{
    return _width;
}

size_t Image::GetHeight() const
{
    return _height;
}

size_t Image::GetChannels() const
{
    return _channels;
}

unsigned char* Image::GetImageData() const
{
    return _data;
}

bool Image::ReadImage()
{
    OIIO::ImageInput* in = OIIO::ImageInput::open(_image_path);
    if (!in) {
        std::cout << "Cannot open image " << _image_path << std::endl;
        return false;
    }

    const OIIO::ImageSpec spec = in->spec();
    _width = spec.width;
    _height = spec.height;
    _channels = spec.nchannels;

    _data = new unsigned char [_width * _height * _channels];
    in->read_image(OIIO::TypeDesc::UINT8, _data);
    in->close();

    delete in;
    return true;
}

bool Image::WriteImage() const
{
    OIIO::ImageOutput* out = OIIO::ImageOutput::create(_image_path);
    if (!out) {
        std::cout << "Cannot create image " << _image_path << std::endl;
        return false;
    }
    OIIO::ImageSpec spec(_width, _height, _channels, OIIO::TypeDesc::UINT8);
    out->open(_image_path, spec);
    out->write_image(OIIO::TypeDesc::UINT8, _data);
    out->close();

    delete out;
    return true;
}

} // image

}