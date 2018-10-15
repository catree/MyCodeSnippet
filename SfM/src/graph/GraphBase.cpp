#include "GraphBase.h"

namespace sfm {
namespace graph {

LocalGraph::LocalGraph()
{

}

LocalGraph::LocalGraph(size_t size) 
{
    _nodes.resize(size);
    _edge_list.resize(size);
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
    _edge_list.push_back(EdgeMap());
    return true;
}

bool LocalGraph::AddNode(size_t idx, std::string name)
{
    _nodes.push_back(Node(idx, name));
    _edge_list.push_back(EdgeMap());
    return true;
}

bool LocalGraph::AddNode(const Node& node)
{
    _nodes.push_back(Node(node));
    _edge_list.push_back(EdgeMap());
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
    return true;
}

bool LocalGraph::HasNode(size_t idx) const
{
    for (auto node : _nodes) {
        if (node.idx == idx) return true;
    }
    return false;
}

bool LocalGraph::AddEdge(size_t src, size_t dst)
{
    if (_edge_list[src].find(dst) == _edge_list[src].end()) {
        _edge_list[src].insert(std::make_pair(dst, Edge(src, dst)));
    }
    return true;
}

bool LocalGraph::AddEdge(size_t src, size_t dst, double w)
{
    if (_edge_list[src].find(dst) == _edge_list[src].end()) {
        _edge_list[src].insert(std::make_pair(dst, Edge(src, dst, w)));
    }
    return true;
}

bool LocalGraph::RemoveEdge(size_t src, size_t dst)
{
    EdgeMap& em = _edge_list[src];
    for (auto it = em.begin(); it != em.end(); ) {
        if (it->first == dst) it = em.erase(it);
        else ++it;
    }
}

}   // namespace graph
}   // namespace sfm