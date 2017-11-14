#include "CameraCluster.h"
#include <queue>

int CameraGraph::getCount() const
{
    return this->count;
}

void CameraGraph::setCount(int c)
{
    this->count = c;
}


void CameraGraph::insert(uint c, CGEdge* edge)
{
    this->cameras.push_back(c);
    //this->edges.push_back(edge);
}


void normalizedCut(CameraGraph g, CameraGraph*& g1, CameraGraph*& g2)
{
    // Normalized Cut algorithm
}

void descendSort(vector<CGEdge*>& e)
{

}

void cameraCluster(CameraGraph cg, vector<CameraGraph*>& g_out)
{
    queue<CameraGraph*> g_in;
    vector<CameraGraph*> g_size;

    CameraGraph *subG1, *subG2;    
    normalizedCut(cg, subG1, subG2);
    g_in.push(subG1);
    g_in.push(subG2);

    while(!g_in.empty())
    {
        // Graph Division
        
        while(!g_in.empty())
        {
            // CameraGraphNode tmp = g_in.getSubset(i);
            CameraGraph* tmp = g_in.front();
            g_in.pop();
            
            if((*tmp).getCount() <= DELTA_UP) 
                g_size.push_back(tmp);
            else
            {
                CameraGraph* g_i1, *g_i2;
                normalizedCut(*tmp, g_i1, g_i2);
                g_in.push(g_i1);
                g_in.push(g_i2);
            }
        }

        // Graph Expansion
        vector<CGEdge*> e_dis;
        descendSort(e_dis);

        for(int k = 0; k < e_dis.size(); k++)
        {
            int i = k;
            int j = e_dis[k]->to;
            CameraGraph* g_vi, *g_vj;
            bool isSelectedi = CameraGraph::getCCSubset(i, g_size, g_vi);
            bool isSelectedj = CameraGraph::getCCSubset(j, g_size, g_vj);

            if(isSelectedi)
                g_vi->insert(cg.getCameras()[j], e_dis[k]);
            if(isSelectedj)
                g_vj->insert(cg.getCameras()[i], e_dis[k]);
        }
            
        for(auto g : g_size)
        {
            if(g->getCount() <= DELTA_UP) g_out.push_back(g);
            else g_in.push(g);
        }
    }
}

bool CameraGraph::getCCSubset(int i, vector<CameraGraph*> g, CameraGraph*& cg)
{
    return false;
}

vector<uint> CameraGraph::getCameras() const
{
    return this->cameras;
}