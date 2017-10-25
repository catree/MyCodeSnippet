#ifndef TRACK_MANAGER_H
#define TRACK_MANAGER_H

#include "Track.h"
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


class TrackManager
{
private:
    vector<Track> tracks;

    vector<ImagePair> imgPairLists;

public:
    void matchAllPairs(vector<Mat>);
    void mergeTracks();

    vector<ImagePair> getImgPairLists() const;

    vector<Track> getTracks() const;
};

#endif