#ifndef FEATURE_FEATURE_H
#define FEATURE_FEATURE_H

#include <vector>

extern "C" {
    #include <vlfeat/generic.h>
    #include <vlfeat/stringop.h>
    #include <vlfeat/pgm.h>
    #include <vlfeat/sift.h>
    #include <vlfeat/getopt_long.h>
};
namespace sfm {
namespace feature {

class FeatureBase
{
private:
    double _x;
    double _y;

public:
    FeatureBase() { }
    FeatureBase(int x, int y) { _x = x; _y = y; }

    void SetX(double x) { _x = x; }
    void SetY(double y) { _y = y; }
    void SetLocation(double x, double y) { _x = x; _y = y; }

    double GetX() const { return _x; };
    double GetY() const { return _y; };
};

class SiftFeature : public FeatureBase
{
private:
    double _scale;  // the radius of the region
    /**
     * @brief  angles expressed in radians
     * @note   Depending on the symmetry of the keypoint appearance, 
     * determining the orientation can be ambiguous. In this case, the SIFT detectors
     * returns a list of up to four possible orientations, constructing up to four
     * frames (differing only by their orientation) for each detected image blob.
     */
    std::vector<double> _angles;
    std::vector<vl_sift_pix*> _descriptors;

public:
    SiftFeature() { }
    SiftFeature(int x, int y, int s) : FeatureBase(x, y) { _scale = s; }

    void SetScale(double s) { _scale = s; }
    void SetAngle(double angle) { _angles.push_back(angle); }
    void SetDescriptor(vl_sift_pix* des) { _descriptors.push_back(des); }

    double GetScale() const { return _scale; }
    std::vector<double> GetAngles() const { return _angles; }
    std::vector<vl_sift_pix*> GetDescriptors() const { return _descriptors; }
};

}   // namespace feature
}   // namespace sfm

#endif