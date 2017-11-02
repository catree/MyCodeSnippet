#ifndef TRACK_MANAGER_H
#define TRACK_MANAGER_H

#include "Track.h"
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


struct UFSet
{
    int par[MAX_N];     // parent
    int rank[MAX_N];    // 秩，树的高度

    void init(int n)
    {
        for(int i = 0; i < n; i++)
        {
            par[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x)
    {
        return (x == par[x]) ? x : (par[x] = find(par[x]));
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) return;
        if(rank[x] < rank[y]) par[x] = y;
        else
        {
            par[y] = x;
            if(rank[x] == rank[y]) rank[x]++;
        }
    }
};


class TrackManager
{
private:
    vector<Track> tracks;


public:

    void mergeTracks();

    vector<Track> getTracks() const;
};

#endif