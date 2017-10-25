#include "TrackManager.h"
#include "Utility.h"
#include "ImagePair.h"
#include <map>
#include <utility>
#include <vector>

using namespace std;

void Tracks::matchAllPairs(vector<Mat> imgBuffer)
{
    double s = getCurrentTime();
    for(unsigned int i = 0; i < imgBuffer.size(); i++)
    {
        for(unsigned int j = i + 1; j < imgBuffer.size(); j++)
        {
            // imresize(imgBuffer[i], 480);
            // imresize(imgBuffer[j], 480);
            ImagePair imgPair(i, j, imgBuffer[i], imgBuffer[j], false);
            imgPair.startMatch();
            imgPair.estimateFundamentalMat();
            this->imgPairLists.push_back(imgPair);
        }
    }
    double e = getCurrentTime();
    cout << "using " << e - s << " s." << endl;
}

void Tracks::mergeTracks(vector<Mat> imgBuffer, vector<KeyPoint>* keypointsList)
{
    int len = imgBuffer.size();
    map<vector< pair<int, KeyPoint> >, bool> visitMap;
    initVisitMap(imgBuffer, visitMap);

    for(unsigned int i = 0; i < len; i++)
    {
        for(unsigned int j = i + 1; j < len; j++)
        {
            Track track;
            unsigned int index = i * len - (i + 1) * (i + 2) / 2 + j;
            ImagPair imgPair = this->imgPairLists[index];

            vector<DMatch> matches = imgPair.getMatches();
            

        }

    }
}

void initVisitMap(vector<Mat> imgBuffer, map<vector< pair<int, KeyPoint> >, bool>& visitMap)
{   
    int i = 0;

    pair<KeyPoint> kpts = this->imgPairLists[i]->getKeypoints1;
    vector< pair<int, KeyPoint> > tmp;
    for(auto keypoint : kpts)
    {
        pair<int, KeyPoint> tt;
        tt.first = i;
        tt.second = keypoint;
        tmp.push_back(tt);
    }
    visitMap[tmp] = false;

    for(i = 0; i < imgBuffer.size() - 1; i++)
    {
        vector<KeyPoint> kpts = this->imgPairLists[i].getKeypoints2;
        vector< pair<int, KeyPoint> > tmp;
        for(auto keypoint : kpts)
        {
            pair<int, KeyPoint> tt;
            tt.first = i + 1;
            tt.second = keypoint;
            tmp.push_back(tt);
        }
        visitMap[tmp] = false;
    }
}


vector<ImagePair> getImgPairLists() const
{
    return this->imgPairLists;
}


vector<Track> TrackManager::getTracks() const
{
    return this->tracks;
}