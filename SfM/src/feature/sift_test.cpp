#include <iostream>
#include <vector>
#include <string>

#include <OpenImageIO/imageio.h>

extern "C" {
    #include <vl/generic.h>
    #include <vl/stringop.h>
    #include <vl/pgm.h>
    #include <vl/sift.h>
    #include <vl/getopt_long.h>
};

using namespace OIIO;

int main()
{
    std::string filename = "/home/chenyu/projects/MyCodeSnippet/SfM/data/river1.jpg";
    auto in = OIIO::ImageInput::open(filename);
    if(!in) {
        std::cout << "cannot open image " << filename << std::endl;
        return 0;
    }

    const ImageSpec spec = in->spec();
    int xres = spec.width;
    int yres = spec.height;
    int channels = spec.nchannels;

    std::vector<unsigned char> pixels(xres * yres * channels);
    in->read_image(TypeDesc::UINT8, &pixels[0]);
    in->close();

    VL_PRINT("Hello World!\n");
}