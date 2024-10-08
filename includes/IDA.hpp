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
    std::vector<Node *> startingPath;
    std::vector<Node *> solution;
    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point end;
    Node *endNode;
    double totalNumberOfNodes;
    double totalNumberOfNodesInMemory;
    double nodes;

    void printResult();
    std::tuple<std::vector<Node *>, int> depthLimitedSearch(int startCost, std::vector<Node *> pathSoFar, int costLimit);

    void freeChildrens(std::vector<Node *> childrens, Node * current);

public:
    IDA(std::vector<int> puzzle, Heuristic heuristic);
    IDA(unsigned int dim, Heuristic heuristic);
    ~IDA();

    void solve();
};

#endif