#include "UnionFind.h"

namespace sfm {
namespace graph {

UnionFind::UnionFind(size_t size)
{
    _size = size;
    for (size_t i = 0; i < size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}    

size_t UnionFind::FindRoot(size_t x)
{
    return (_parent[x] == x) ? x : _parent[x] = FindRoot(_parent[x]);
}

void UnionFind::Union(size_t x, size_t y)
{
    x = FindRoot(x);
    y = FindRoot(y);

    if (x == y) return;
    
    if (_rank[x] < _rank[y]) _parent[x] = y;
    else {
        _parent[y] = x;
        if (_rank[x] == _rank[y]) _rank[x]++;
    }
}

}   // namespace graph
}   // namespace sfm