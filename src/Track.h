#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct TrackNode
{
    int idx;            // image index
    KeyPoint keypoint;  ;// keypoint in image[idx]
}

struct Track
{
    vector<TrackNode> track; 
};

#endif