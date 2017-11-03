#include "TrackManager.h"
#include "Utility.h"
// #include "ImagePair.h"
#include <map>
#include <utility>
#include <vector>
#include <queue>

using namespace std;



void TrackManager::mergeTracks(EGGraph egGraph)
{
    EGEdge** edge = egGraph.getEdgeMap();
    int nodeNum = egGraph.getNodeNum();

    cout << "Merge tracks begins...\n";

    for(int i = 0; i < nodeNum; i++)
    {
        for(int j = 0; j < nodeNum; j++)
        {
            if(edge[i][j].isMatch)
            {
                for(int k = 0; k < edge[i][j].trackNodes1.size(); k++)
                {
                    this->unite(edge[i][j].trackNodes1[k], edge[i][j].trackNodes2[k]);
                }
            }
        }
    }
    cout << "Merge tracks ends...\n";
}


TrackNode* TrackManager::findSet(TrackNode* node)
{
    if(node->parent == node) return node;
    else
    {
        return node->parent = findSet(node->parent);
    }
}


void TrackManager::unite(TrackNode* node1, TrackNode* node2)
{
    cout << "Unite begins...\n";
    TrackNode* n1 = this->findSet(node1);
    TrackNode* n2 = this->findSet(node2);

    if(n1 == n2) return;
    else
    {
        if(n1->rank < n2->rank) n1->parent = n2;
        else
        {
            n2->parent = n1;
            if(n1->rank == n2->rank) n1->rank++;
        }
    }
    cout << "unite ends...\n";
}


vector<Track> TrackManager::getTracks() const
{
    return this->tracks;
}