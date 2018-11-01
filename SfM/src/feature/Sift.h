#ifndef FEATURE_SIFT_H
#define FEATURE_SIFT_H

#include <vector>
#include "Feature.h"

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

    bool _force_orientations;   // Determin whether computing orientations
    bool _force_descriptors;    // Determin whether computing descriptors

public:
    Sift(const unsigned char image[], 
         const int width, 
         const int height,
         const int octaves, 
         const int levels, 
         const int omin);
    ~Sift();

    bool ConfigureSift(bool compute_orientations = true, 
                       bool compute_descriptors = false, 
                       int edge_thresh = -1, 
                       int peak_thresh = -1, 
                       int magnif = -1);


    bool Extract(std::vector<SiftFeature>& sift_features);
    

    void ShowSiftSettings();
};

}   // namespace feature
}   // namespace sfm

#endif