#ifndef TRACK_MANAGER_H
#define TRACK_MANAGER_H

#include "Track.h"
#include "TrackManager.h"
#include "EGGraph.h"
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


class TrackManager
{
private:
    vector<Track> tracks;


public:

    void mergeTracks(EGGraph egGraph);

    vector<Track> getTracks() const;

    void unite(TrackNode* node1, TrackNode* node2);
    TrackNode* findSet(TrackNode* node);
};

#endif