// Reference: http://www.vlfeat.org/api/sift.html
// Code Example: https://github.com/vlfeat/vlfeat/blob/master/src/sift.c

#include <iostream>
#include <vector>
#include <string>

#include <OpenImageIO/imageio.h>

#include "image/ImageProcess.h"
#include "Sift.h"

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

    // For testing
    // VL_PRINT("Hello World!\n");

    const char *gray_img = "gray.jpg";
    ImageOutput* out = OIIO::ImageOutput::create(gray_img);
    if (!out) { 
        std::cout << "cannot open image" << std::endl;
        return 0;
    }
    OIIO:ImageSpec gray_spec(xres, yres, 1, TypeDesc::UINT8);
    out->open(gray_img, gray_spec);
    unsigned char gray[xres * yres * 1];
    sfm::image::RGB2Gray(pixels, gray, xres, yres, channels);

    out->write_image(TypeDesc::UINT8, gray);
    out->close();

    // initialization of sift
    int noctaves = 4, nlevels = 3, o_min = 0;
    int width = yres, height = xres;
    int edge_thresh = -1;
    int peak_thresh = -1;
    int magnif = -1;

    sfm::feature::Sift sift(gray, width, height, noctaves, nlevels, o_min);
    sift.ConfigureSift(edge_thresh, peak_thresh, magnif);
    sift.ShowSiftSettings();
    sift.Extract();

    // TODO: show image with OpenCV
    // cv::namedWIndow("Source Image", 1);
    // cv::imshow("Source Image", Image);
    // cv::waitKey(0);

    delete in;
    delete out;
}