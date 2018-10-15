#ifndef GRAPH_GRAPH_BASE_H
#define GRAPH_GRAPH_BASE_H

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>


namespace sfm {
namespace graph {

struct Node 
{
    size_t idx;
    std::string filename;

    // constructor
    Node(size_t i, std::string name = "")
    {
        idx = i;
        filename = name;
    }

    // Copy constructor
    Node(const Node& node)
    {
        idx = node.idx;
        filename = node.filename;
    }

    bool operator ==(const Node& node)
    {
        if (idx == node.idx && 
            filename == node.filename) {
            return true;
        }
        return false;
    }
};

struct Edge 
{
    size_t src;
    size_t dst;
    double weight;

    Edge(size_t s, size_t d, double w = 0)
    {
        src = s;
        dst = d;
        weight = w;
    }

    Edge(const Edge& edge)
    {
        src = edge.src;
        dst = edge.dst;
        weight = edge.weight;
    }

    bool operator ==(const Edge& edge)
    {
        if (src == edge.src &&
            dst == dst &&
            weight == edge.weight) {
            return true;
        }
        return false;
    }
};

typedef std::unordered_map<size_t, Edge> EdgeMap;
typedef std::pair<size_t, size_t> IdPair;
enum IdType { LOCAL_ID, GLOBAL_ID };

class GraphBase
{
public:
    // Node operation
    virtual bool AddNode(size_t idx) = 0;
    virtual bool AddNode(size_t idx, std::string name) = 0;
    virtual bool AddNode(const Node& node) = 0;
    virtual bool RemoveNode(size_t idx) = 0;
    virtual bool HasNode(size_t idx) const = 0;

    // Edge operation
    virtual bool AddEdge(size_t src, size_t dst) = 0;
    virtual bool AddEdge(size_t src, size_t dst, double w) = 0;
    virtual bool AddEdge(const Edge& edge) = 0;
    virtual bool RemoveEdge(size_t src, size_t dst) = 0;
    virtual bool HasEdge(size_t src, size_t dst) const = 0;

    // minimum spanning tree algorithm
    virtual std::vector<Edge> Prim() const = 0;
    virtual std::vector<Edge> Kruskal() const = 0;
};

class LocalGraph : GraphBase
{
private:
    std::vector<Node> _nodes;
    std::vector<EdgeMap> _edge_list;

public:
    // constructor
    LocalGraph();
    LocalGraph(size_t size);
    LocalGraph(const std::vector<Node>& nodes, const std::vector<EdgeMap>& edgeList);
    LocalGraph(const LocalGraph& localGraph);

    // destructor
    ~LocalGraph();

    // Node operation
    std::vector<Node> GetNodes() const { return _nodes; }
    Node GetNode(size_t idx) const; 
    virtual bool AddNode(size_t idx);
    virtual bool AddNode(size_t idx, std::string name);
    virtual bool AddNode(const Node& node);
    virtual bool RemoveNode(size_t idx);
    virtual bool HasNode(size_t idx) const;

    // Edge operation
    std::vector<EdgeMap> GetEdgeList() const { return _edge_list; }
    Edge GetEdge(size_t src, size_t dst) const;
    virtual bool AddEdge(size_t src, size_t dst);
    virtual bool AddEdge(size_t src, size_t dst, double w = 1.0);
    virtual bool AddEdge(const Edge& edge);
    virtual bool RemoveEdge(size_t src, size_t dst);
    virtual bool HasEdge(size_t src, size_t dst) const;

    // minimum spanning tree algorithm
    virtual std::vector<Edge> Prim() const;
    virtual std::vector<Edge> Kruskal() const;

};


class GlobalGraph : GraphBase 
{
private:
    std::unordered_map<IdPair, Node> _nodes;
    std::vector<EdgeMap> _edge_list;

public:
    // constructor
    GlobalGraph();
    GlobalGraph(const std::unordered_map<IdPair, Node>& nodes, const std::vector<EdgeMap>& edgeList);
    GlobalGraph(const GlobalGraph& globalGraph);

    // destructor
    ~GlobalGraph();

    // Node operation
    std::unordered_map<IdPair, Node> GetNodes() const { return _nodes; }
    Node GetNode(size_t idx, IdType idType) const;
    virtual bool AddNode(size_t idx);
    virtual bool AddNode(size_t idx, std::string name);
    virtual bool AddNode(const Node& node);
    virtual bool RemoveNode(size_t idx);


    // Edge operation
    std::vector<EdgeMap> GetEdgeList() const { return _edge_list; }
    Edge GetEdge(size_t src, size_t dst) const;
    virtual bool AddEdge(size_t src, size_t dst);
    virtual bool AddEdge(size_t src, size_t dst, double w);
    virtual bool AddEdge(const Edge& edge);
    virtual bool RemoveEdge(size_t src, size_t dst);

    // minimum spanning tree algorithm
    virtual std::vector<Edge> Prim() const;
    virtual std::vector<Edge> Kruskal() const;
};

}   // namespace graph
}   // namespace sfm



#endif