#include "GraphBase.h"

namespace sfm {
namespace graph {

LocalGraph::LocalGraph()
{

}

LocalGraph::LocalGraph(const std::vector<Node>& nodes, const std::vector<EdgeMap>& edgeList)
{

}

LocalGraph::LocalGraph(const LocalGraph& localGraph)
{

}

LocalGraph::~LocalGraph()
{

}

Node LocalGraph::GetNode(size_t idx) const
{
    return _nodes[idx];
}

bool LocalGraph::AddNode(size_t idx)
{
    _nodes.push_back(Node(idx));
    return true;
}

bool LocalGraph::AddNode(size_t idx, std::string name)
{
    _nodes.push_back(Node(idx, name));
    return true;
}

bool LocalGraph::AddNode(const Node& node)
{
    _nodes.push_back(Node(node));
    return true;
}

bool LocalGraph::RemoveNode(size_t idx)
{
    // remove node
    bool is_find = false;
    for (auto ite = _nodes.begin(); ite != _nodes.end(); ite++) {
        if (ite->idx == idx) {
            is_find = true;
            ite = _nodes.erase(ite);
            break;
        }
        else ite++;
    }
    if (!is_find) return false;

    // Update edges
    // delete edges that node idx is the start node
    size_t i = 0;
    for (auto ite = _edge_list.begin(); ite != _edge_list.end(); ) {
        if (i == idx) {
            ite = _edge_list.erase(ite);
            break;
        }
        ite++; i++;
    }  

    // delete edges that node idx is the end node
    for (EdgeMap& em : _edge_list) {
        for (auto ite = em.begin(); ite != em.end(); ite++) {
            if (ite->first == idx) em.erase(ite);
        }
    }
    return true;
}

bool LocalGraph::AddEdge(size_t src, size_t dst)
{
    // check if node src and dst are contained in graph
    
}

}   // namespace graph
}   // namespace sfm