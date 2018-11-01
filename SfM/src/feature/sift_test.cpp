// Reference: http://www.vlfeat.org/api/sift.html
// Code Example: https://github.com/vlfeat/vlfeat/blob/master/src/sift.c

#include <iostream>
#include <vector>
#include <string>

#include <OpenImageIO/imageio.h>

#include "image/ImageProcess.h"
#include "image/Image.h"
#include "Feature.h"
#include "Sift.h"

#ifdef USE_OPENCV
    #include "opencv2/opencv.hpp"
    #include "opencv2/core/core.hpp"
    #include "opencv2/imgproc/imgproc.hpp"
    #include "opencv2/highgui/highgui.hpp"
    #include "opencv2/features2d/features2d.hpp"
    using namespace cv;
#endif

using namespace OIIO;

int main(int argc, char* argv[])
{   
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << "img_path\n";
        return 0;
    }
    std::string filename = argv[1];

    sfm::image::Image image(filename);
    image.ReadImage();

    int xres = image.GetWidth();
    int yres = image.GetHeight();
    int channels = image.GetChannels();
    const unsigned char* const data = image.GetImageData();

    size_t data_length = xres * yres * channels;
    std::vector<unsigned char> pixels;
    for (size_t i = 0; i < data_length; i++) { pixels.push_back(data[i]); }

    unsigned char gray[xres * yres * 1];
    sfm::image::RGB2Gray(pixels, gray, xres, yres, channels);

    // const char *gray_img = "gray.jpg";
    // ImageOutput* out = OIIO::ImageOutput::create(gray_img);
    // if (!out) { 
        // std::cout << "cannot open image" << std::endl;
        // return 0;
    // }
    // OIIO:ImageSpec gray_spec(xres, yres, 1, TypeDesc::UINT8);
    // out->open(gray_img, gray_spec);
    // out->write_image(TypeDesc::UINT8, gray);
    // out->close();

    // initialization of sift
    int noctaves = 4, nlevels = 3, o_min = 0;
    int width = xres, height = yres;
    int edge_thresh = -1;
    int peak_thresh = 10;
    int magnif = -1;

    sfm::feature::Sift sift(gray, width, height, noctaves, nlevels, o_min);
    sift.ConfigureSift(true, true, edge_thresh, peak_thresh, magnif);
    sift.ShowSiftSettings();

    std::vector<sfm::feature::SiftFeature> sift_features;
    sift.Extract(sift_features);
    std::cout << sift_features.size() << " sift features are detected\n";

#ifdef USE_OPENCV
    cv::Mat mat = cv::imread(filename.c_str());
    for (auto feature : sift_features) {
        double x = feature.GetX();
        double y = feature.GetY();
        double scale = feature.GetScale();
        cv::circle(mat, cv::Point(x, y), (int)(scale), CV_RGB(255, 0, 0), 1.2);
    }
    cv::imshow("Keypoint Image", mat);
    cv::waitKey(0);
#endif
}