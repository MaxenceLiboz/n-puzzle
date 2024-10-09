#ifndef IDA_HPP
#define IDA_HPP

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

class IDA
{
private:
    std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> openList;
    std::unordered_set<Node *, HashNode> closedList;
    std::vector<Node *> nodeList;
    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point end;
    Node *endNode;
    double totalNumberOfNodes;
    double totalNumberOfNodesInMemory;

    void printResult();

public:
    IDA(std::vector<int> puzzle, Heuristic heuristic);
    IDA(unsigned int dim, Heuristic heuristic);
    ~IDA();

    void solve();
    Node depthLimitedSearch(int startCost, pathSoFar, int costLimit);
};

#endif