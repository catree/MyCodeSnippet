#include "CameraCluster.h"

int CameraGraph::getCount() const
{
    return this->count;
}

void CameraGraph::setCount(int c)
{
    this->count = c;
}

// CameraGraphNode CameraGraph::getNode(int idx) const
// {
//     CameraGraphNode cgNode;
//     cgNode.camera = this->cameras[idx];
//     cgNode.edge = this->edges[idx];

//     return cgNode;
// }

//--------------------------HOW TO DO ?-----------------------------
CameraGraphNode CameraGraph::getSubset(int i) const
{
    CameraGraph cg;
    return cg;
}

void CameraGraph::insert(CameraGraphNode cgNode)
{
    this->cameras.push_back(cgNode.camera);
    this->edges.push_back(cgNode.edge);
}

void CameraGraph::remove(CameraGraphNode cgNode)
{
    int i = 0;
    vector<Camera>::iterator ite;
    for(ite = this->cameras.begin(); ite != this->cameras.end();)
    {
        if(cameras[i] == cgNode.camera) 
        {
            ite = this->cameras.erase(ite);
            break;
        }
        else 
        {
            i++;
            ite++;
        }
    }

    i = 0;
    vector< vector<CGEdge*> >:: iterator eite;
    for(eite = this->edges.begin(); eite != this->edges.end();)
    {
        if(edges[i] == cgNode.edge)
        {
            eite = this->edges.erase(eite);
            break;
        }
        else
        {
            i++;
            eite++;
        }
    }
}

void normalizedCut(CameraGraph g_i, CameraGraph& g_i1, CameraGraph& g_i2)
{
    // Normalized Cut algorithm
}

void descendSort(vector<CGEdge>& e)
{

}

void cameraCluster(CameraGraph cg, CameraGraph& g_out)
{
    CameraGraph g_in = cg;
    while(g_in.getCount() != 0)
    {
        // Graph Division
        CameraGraph g_size;
        
        for(int i = 0; i < g_in.getCount(); i++)
        {
            CameraGraphNode tmp = g_in.getSubset(i);
            g_size.insert(tmp);
            g_in.remove(tmp);
            
            if(g_size.getCount() <= DELTA_UP) g_size.setCount(g_size.getCount() + 1);
            else
            {
                CameraGraph g_i1, g_i2;
                normalizedCut(g_size, g_i1, g_i2);
                g_in.insert(g_i1);
                g_in.insert(g_i2);
            }
        }

        // Graph Expansion
        vector<CGEdge> e_dis;
        descendSort(e_dis);

        for(int k = 0; k < e_dis.size(); k++)
        {
            int i = k;
            int j = e_dis[k].to;
            CameraGraph g_vi, g_vj;
            bool isSelectedi = g_size.getCCSubset(i, g_vi);
            bool isSelectedj = g_size.getCCSubset(j, g_vj);

            if(isSelectedi)
                g_vi.insert(CamaraGraphNode(cg.cameras[j], e_dis[k]));
            if(isSelectedj)
                g_vj.insert(CameraGraphNode(cg.cameras[i], e_dis[k]));
        }
            
        for(auto g : g_size)
        {
            if(g.getCount() <= DELTA_UP) g_out.insert(g);
            else g_in.insert(g);
        }
    }
}

bool CameraGraph::getCCSubset(int i, CameraGraph& cg)
{
    return false;
}