#include "TrackManager.h"
#include "Utility.h"
#include "ImagePair.h"
#include <map>
#include <utility>
#include <vector>
#include <queue>

using namespace std;



void Tracks::mergeTracks()
{
    this->initUFSet(trackNodes);
    EGEdge** edge = egGraph->getEdgeMap();
    int nodeNum = egGraph->getNodeNum();
    // for(int i = 0; i < egGraph->getNodeNum(); i++)
    // {
    //     for(int j = i + 1; j < EGGraph->getNodeNum(); j++)
    //     {
    //         if(edge[i][j].isMatch())
    //         {
    //             vector<KeyPoint> keypoints1 = edge[i][j].keypoints1;
    //             // 对匹配的图片对中的第一张图片的每一个特征点，在所有其他图片中寻找匹配的特征点
    //             for(int k = 0; k < keypoints1.size(); k++)
    //             {
    //                 vector<KeyPoint> keypoints2 = edge[i][j].keypoints2;
    //                 for(int l = 0; l <)
    //             }

                
    //         }
    //     }
    // }
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    bool** visit = new bool* [nodeNum];
    for(int i = 0; i < nodeNum; i++) visit[i] = new bool [nodeNum];

    for(int i = 0; i < nodeNum; i++)
    {
        for(int j = 0; j < nodeNum; j++) visit[i][j] = false;
    }

    queue<EGEdge> edges;
    edges.push(edge[0][1]);
    KeyPoint keypoint = edge[0][1].keypoints1[0];

    while(!edges.empty())
    {
        edge tmp = edges.front();
        edges.pop();

        for(int i = 0; i < 4; i++)
        {
            int nx = tmp.left + dx[i];
            int ny = tmp.right + dy[i];
            if(0 <= nx && nx < nodeNum && 0 <= ny && ny < nodeNum 
                && edge[nx][ny] != NULL && edge[nx][ny].isMatch == true && visit[nx][ny] == false)
                {
                    edges.push(edge[nx][ny]);
                }
        }
    }
}




void TrackManager::initUFSet(vector<TrackNode>& trackNodes)
{
    for(int i = 0; i < trackNodes.size(); i++)
    {
        trackNodes[i].parent = i;
        trackNodes[i].rank = 0;
    }
}

int TrackManager::find(int x, vector<TrackNode>& trackNodes)
{
    return (x == trackNodes[x].parent) ? x : 
            (trackNodes[x].parent = find(trackNodes[x].parent, trackNodes));
}

void TrackManager::unite(int x, int y, vector<TrackNode>& trackNodes)
{
    x = find(x);
    y = find(y);

    if(x == y) return;  // x and has been united in the same set
    if(trackNodes[x].rank < trackNodes[y].rank) trackNodes[x].parent = y;
    else
    {
        trackNodes[y].parent = x;
        if(trackNodes[x].rank == trackNodes[y].rank) trackNodes[x].rank++;
    }

}


vector<Track> TrackManager::getTracks() const
{
    return this->tracks;
}