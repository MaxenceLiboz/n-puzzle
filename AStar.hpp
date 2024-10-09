#ifndef ASTAR_HPP
#define ASTAR_HPP

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

class AStar
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
    AStar(std::vector<int> puzzle, Heuristic heuristic);
    AStar(unsigned int dim, Heuristic heuristic);
    ~AStar();

    void solve();
};

#endif