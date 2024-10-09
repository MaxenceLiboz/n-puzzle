#include "IDA.hpp"

IDA::IDA(std::vector<int> puzzle, Heuristic heuristic) {
    Node * node = new Node(puzzle, heuristic, NULL);
    nodeList.push_back(node);
}

IDA::IDA(unsigned int dim, Heuristic heuristic) {

    RandomGenerator gen;
    gen.generateRandom(dim);

    Node * node = new Node(gen.getPuzzle(), heuristic, NULL);
    nodeList.push_back(node);
}

IDA::~IDA() {
    while (!openList.empty()) {
        Node *child = openList.top();
        openList.pop();
        delete child;
    }

    for (std::unordered_set<Node *, HashNode>::iterator it = closedList.begin(); it != closedList.end(); it++) {
        delete *it;
    }
}

void IDA::solve() {
    this->start = std::chrono::high_resolution_clock::now();

    if (!nodeList.back()->isSolvable()) {
        throw std::invalid_argument("Puzzle is not solvable");
    } else {
        std::cout << "Puzzle is solvable, starting the algo ..." << std::endl;
    }

    int costLimit = nodeList.back()->getHxScore();

    std::vector<Node *> solution;
    bool run = true;

    while (run) {

        std::tie(solution, costLimit) = depthLimitedSearch(0, nodeList, costLimit);

        if (solution.size() > 0 && solution.back()->isValid()) {
            run = false;
        }
        if (costLimit == INT32_MAX) {

            throw std::invalid_argument("Puzzle is not solvable");
        }
    }

    this->end = std::chrono::high_resolution_clock::now();
    this->endNode = solution.back();

    printResult();
}

std::tuple<std::vector<Node *>, int> IDA::depthLimitedSearch(int startCost, std::vector<Node *> pathSoFar, int costLimit) {

    Node *current = pathSoFar.back();

    int currentCost =  current->getFxScore();
    std::vector<Node*> returnVec;

    if (currentCost > costLimit) {
        return std::make_tuple(returnVec, currentCost);
    }
    if (pathSoFar.size() > 0 && pathSoFar.back()->isValid()) {
        return std::make_tuple(pathSoFar, costLimit);
    }

    int nextCostLimit = INT32_MAX;
    std::vector<Node *> childrens =  current->getChildrens();
    for (Node * s : childrens) {

        int newStartCost = startCost + s->getHxScore();
        pathSoFar.push_back(s);
        
        int newCostLimit;
        std::tie(pathSoFar, newCostLimit) = depthLimitedSearch(newStartCost, pathSoFar, costLimit);

        if (pathSoFar.size() > 0 && pathSoFar.back()->isValid()) {
            this->freeChildrens(childrens, s);
            return std::make_tuple(pathSoFar, newCostLimit);
        }
        nextCostLimit = std::min(nextCostLimit, newCostLimit);
    }
    this->freeChildrens(childrens, NULL);
    return std::make_tuple(returnVec, nextCostLimit);
}

void IDA::freeChildrens(std::vector<Node *> childrens, Node * current) {
    for (Node * child : childrens) {
        if ( child != current) {
            delete child;
        }
    }
}

void IDA::printResult() {
    double depth = this->endNode->getGxScore();
    while (this->endNode != NULL) {
        Node * current = this->endNode;
        std::cout << *this->endNode << std::endl;
        this->endNode = this->endNode->getParent();
        delete current;
    }
    std::cout << "Time complexity: " << this->totalNumberOfNodes << std::endl;
    std::cout << "Space complexity: " << this->totalNumberOfNodesInMemory << std::endl;
    std::cout << "Time taken : " << std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->start).count() << " ms" << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Solution found, go upward to check the path" << std::endl;
}