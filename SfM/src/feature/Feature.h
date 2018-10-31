#ifndef FEATURE_FEATURE_H
#define FEATURE_FEATURE_H

namespace sfm {
namespace feature {

class FeatureBase
{
private:
    double _x;
    double _y;

public:
    FeatureBase();
    FeatureBase(int x, int y) { _x = x; _y = y; }

    double GetX() const { return _x; };
    double getY() const { return _y; };
};

class SiftFeature : FeatureBase
{
private:
    double _scale;

public:
    SiftFeature();
    SiftFeature(int x, int y, int s) : FeatureBase(x, y) { _scale = s; }

    double GetScale() const { return _scale; }
};

}   // namespace feature
}   // namespace sfm

#endif