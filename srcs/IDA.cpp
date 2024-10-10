#include "IDA.hpp"

IDA::IDA(std::vector<int> puzzle, Heuristic heuristic) {

    Node * node = new Node(puzzle, heuristic, NULL);
    nodeList.push_back(node);

    this->totalNumberOfNodes = 1;
    this->nodes = 1;
}

IDA::IDA(unsigned int dim, Heuristic heuristic) {

    RandomGenerator gen;
    gen.generateRandom(dim);

    Node * node = new Node(gen.getPuzzle(), heuristic, NULL);
    nodeList.push_back(node);
        
    this->totalNumberOfNodes = 1;
    this->nodes = 1;
}

IDA::~IDA() {

    this->endNode = this->nodeList.back();

    while (this->endNode != NULL) {

        Node * current = this->endNode;
        this->endNode = this->endNode->getParent();
        delete current;
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

        if (!solution.empty() && solution.back()->isValid()) {
            run = false;
        }
        if (costLimit == INT32_MAX) {

            throw std::invalid_argument("Puzzle is not solvable");
        }
    }

    this->end = std::chrono::high_resolution_clock::now();
    this->endNode = solution.back();
    this->nodeList = solution;

    printResult();
}

std::tuple<std::vector<Node *>, int> IDA::depthLimitedSearch(int startCost, std::vector<Node *> pathSoFar, int costLimit) {

    std::vector<Node*> returnVec;
    Node *current = pathSoFar.back();
    int currentCost =  current->getFxScore();

    if (currentCost > costLimit) {
        return std::make_tuple(returnVec, currentCost);
    }
    if (!pathSoFar.empty() && pathSoFar.back()->isValid()) {
        return std::make_tuple(pathSoFar, costLimit);
    }

    int nextCostLimit = INT32_MAX;

    std::vector<Node *> childrens =  current->getChildrens();
    this->nodes += childrens.size();
    this->totalNumberOfNodes += childrens.size();

    for (Node * s : childrens) {

        int newCostLimit;
        int newStartCost = startCost + s->getHxScore();
        pathSoFar.push_back(s);

        std::tie(pathSoFar, newCostLimit) = depthLimitedSearch(newStartCost, pathSoFar, costLimit);

        if (!pathSoFar.empty() && pathSoFar.back()->isValid()) {
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
        if (child != current) {
            if (this->totalNumberOfNodesInMemory < this->nodes) {
                this->totalNumberOfNodesInMemory = this->nodes;
            }
            this->nodes -= 1;
            delete child;
        }
    }
}

void IDA::printResult() {

    double depth = this->endNode->getGxScore();
    while (this->endNode != NULL) {
        std::cout << *this->endNode << std::endl;
        this->endNode = this->endNode->getParent();
    }
    std::cout << "Time complexity: " << this->totalNumberOfNodes << std::endl;
    std::cout << "Space complexity: " << this->totalNumberOfNodesInMemory << std::endl;
    std::cout << "Time taken : " << std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->start).count() << " ms" << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Solution found, go upward to check the path" << std::endl;
}