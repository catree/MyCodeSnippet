/*
pseudo-code of camera clustering algorithm
*Input:  G = (E, V)
*Output: G_out = {G_k | G_k = {E_k, V_k} }
* G_in = {G}, G_out = NULL
* while G_in != NULL                                    // Iteration between graph division and expansion
*   G_size = 0                                          // Graph division
*   while G_in != NULL                                  
*       Choose G_i = {V_i, E_i} from G_in
        G_in = G_in - {G_i}
        if |V_i| <= Delta_up
            G_size = G_size + {G_i}
        else
            Divide G_i into G_i1 and G_i2 by normalized-cut
            G_in = G_in + {G_i1} + {G_i2}
    E_dis = edges discarded in graph division           // Graph expansion
    for each e_ij belong to E_dis sorted by w(e_ij) in descending order do
        Select one from G(V_i), G(V_j) belong to G_size such that lambda(G(V_i)) < lambda_c,
        lambda(G(V_j)) < lambda_c uniformly at random, where G(V_i) is the sub-graph containing
        V_i and lambda(G) measures the completeness ration of G
        
        if G(V_i) is selected
            Add e_ij and V_j to G(V_i)
        else if G(V_j) is selected
            Add e_ij and V_i to G(V_i)
    for each G_i = {E_i, V_i} belongs to G_size 
        if |V_i| <= delta_up then
            G_out  = G_out + {G_i}
        else
            G_in = G_in + {G_i}
*/
#ifndef CAMERA_CLUSTER_H
#define CAMERA_CLUSTER_H

#include <vector>
using namespace std;

#define DELTA_UP 100
#define CTHRESHOLD 0.7
#define uint unsigned int
// struct Camera
// {
//     Point2f center; // camera center
//     Mat R;          // rotation matrix
//     Mat t;          // translation matrix
// };


struct CGEdge
{
    int to;         // end edge
    int weight;     // number of matches
};

class CameraGraph
{
private:
    vector<uint> cameras;             
    vector< vector<CGEdge*> > edges;
    int count;

public:
    // void cameraCluster()
    int getCount() const;
    void setCount(int c);

    vector<uint> getCameras() const;

    void insert(uint c, CGEdge* edge);

    static bool getCCSubset(int i, vector<CameraGraph*> g, CameraGraph*& cg);
    // CameraGraphNode getNode(int idx) const;
};


#endif

