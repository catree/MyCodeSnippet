#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct Track
{
    vector<KeyPoint> trackPoints;
    vector<unsigned int> imgLists;
};

#endif