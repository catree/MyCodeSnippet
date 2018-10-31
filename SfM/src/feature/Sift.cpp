#include "Sift.h"

#include <iostream>

namespace sfm {
namespace feature {

Sift::Sift(const unsigned char image[], 
           const int width, 
           const int height,
           const int octaves, 
           const int levels, 
           const int omin)
{
    _image_data = new vl_sift_pix[width * height];
    for (int i = 0; i < width * height; i++) { _image_data[i] = image[i]; }

    _filt = vl_sift_new(width, height, octaves, levels, omin);
}

Sift::~Sift()
{
    delete _image_data;
    _image_data = nullptr;

    if (_filt) { vl_sift_delete(_filt); _filt = nullptr; }
}

bool Sift::ConfigureSift(int edge_thresh, int peak_thresh, int magnif)
{
    if (edge_thresh >= 0) vl_sift_set_edge_thresh(_filt, edge_thresh);
    if (peak_thresh >= 0) vl_sift_set_peak_thresh(_filt, peak_thresh);
    if (magnif >= 0)  vl_sift_set_magnif(_filt, magnif);
    return true;
}

void Sift::ShowSiftSettings()
{
    std::cout << "SIFT - Filter Settings:\n";
    std::cout << "SIFT - Octaves:              " << vl_sift_get_noctaves(_filt)     << std::endl;
    std::cout << "SIFT - Levels:               " << vl_sift_get_nlevels(_filt)      << std::endl;
    std::cout << "SIFT - First Octave (o_min): " << vl_sift_get_octave_first(_filt) << std::endl;
    std::cout << "SIFT - Edge Threshold:       " << vl_sift_get_edge_thresh(_filt)  << std::endl;
    std::cout << "SIFT - Peak Threshold:       " << vl_sift_get_peak_thresh(_filt)  << std::endl;
    std::cout << "SIFT - Magnification:        " << vl_sift_get_magnif(_filt)       << std::endl;
}

bool Sift::Extract()
{
    // Process the first octave
    if (vl_sift_process_first_octave(_filt, _image_data) == VL_ERR_EOF) {
        std::cout << "Failed when processing the first octave\n";
        return false;
    }

    while (true) {
        vl_sift_detect(_filt);

        const VlSiftKeypoint* keypoints = vl_sift_get_keypoints(_filt);
        int keypoints_num = vl_sift_get_nkeypoints(_filt);
        std::cout << "SIFT: Detected " << keypoints_num << "(unoriented) keypoints\n";

        // calculate orientation for each keypoint
        for (int i = 0; i < keypoints_num; i++) {
            double angles[4];
            int angles_num;
            VlSiftKeypoint ik;
            VlSiftKeypoint const *k;

            // TODO: process ikeys (not necessary)
            double *ikeys = nullptr;
            if (ikeys) {
                vl_sift_keypoint_init(_filt, &ik,
                                    ikeys[4 * i + 0],
                                    ikeys[4 * i + 1],
                                    ikeys[4 * i + 2]);
                if (ik.o != vl_sift_get_octave_index(_filt)) { break; }

                k = &ik;

                // Optionally compute orientations too
                bool force_orientations = true;
                if (force_orientations) {
                    angles_num = vl_sift_calc_keypoint_orientations(_filt, angles, k);
                } else {
                    angles[0] = ikeys[4 * i + 3];
                    angles_num = 1;
                }
            } else {
                k = keypoints + 1;
                angles_num = vl_sift_calc_keypoint_orientations(_filt, angles, k);
            }

            // TODO: draw circle using OpenCV
            // cv::circle(Image, cv::Point(k->x, k->y, k->sigma / 2, CV_RGB(255, 0, 0)));

            // for each orientation
            for (unsigned int q = 0; q < (unsigned)angles_num; q++) {
                vl_sift_pix descriptor[128];
                // Optionally: compute descriptor
                bool force_descriptor = true;
                if (force_descriptor) {
                    vl_sift_calc_keypoint_descriptor(_filt, descriptor, k, angles[q]);
                }
            }
        }   // end of outer for loop

        // Process the next octave
        if (vl_sift_process_next_octave(_filt) == VL_ERR_EOF) { break; }
    }
    return true;
}

}   // namespace feature
}   // namespace sfm