#ifndef NPUZZLE_HPP
#define NPUZZLE_HPP

#include <vector>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <random>
#include "RandomGenerator.hpp"

#include "Node.hpp"

class NPuzzle
{
private:
    std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> openList;
    std::unordered_set<Node *, HashNode> closedList;
    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point end;
    Node *endNode;
    double totalNumberOfNodes;
    double totalNumberOfNodesInMemory;

    void printResult();

public:
    NPuzzle(std::vector<int> puzzle, Heuristic heuristic);
    NPuzzle(unsigned int dim, Heuristic heuristic);
    ~NPuzzle();

    void solve();
};

#endif