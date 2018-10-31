#ifndef FEATURE_SIFT_H
#define FEATURE_SIFT_H

extern "C" {
    #include <vlfeat/generic.h>
    #include <vlfeat/stringop.h>
    #include <vlfeat/pgm.h>
    #include <vlfeat/sift.h>
    #include <vlfeat/getopt_long.h>
};

namespace sfm {
namespace feature {

class Sift
{
private:
    vl_sift_pix* _image_data;
    VlSiftFilt* _filt;

public:
    Sift(const unsigned char image[], 
         const int width, 
         const int height,
         const int octaves, 
         const int levels, 
         const int omin);
    ~Sift();

    bool ConfigureSift(int edge_thresh = -1, int peak_thresh = -1, int magnif = -1);
    bool Extract();
    

    void ShowSiftSettings();
};

}   // namespace feature
}   // namespace sfm

#endif