#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>
#include <iostream>

namespace sfm {
namespace graph {
class UnionFind 
{
private:
    size_t _size;
    std::vector<size_t> _rank;
    std::vector<size_t> _parent;

public:
    UnionFind(size_t size);
    size_t FindRoot(size_t x);
    void Union(size_t x, size_t y);

};

}   // namespace graph
}   // namespace sfm

#endif