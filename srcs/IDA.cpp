#include "IDA.hpp"

IDA::IDA(std::vector<int> puzzle, Heuristic heuristic) {
    Node * node = new Node(puzzle, heuristic, NULL);
    node->setNode();
    openList.push(node);
    nodeList.push_back(node);
}

IDA::IDA(unsigned int dim, Heuristic heuristic) {

    RandomGenerator gen;
    gen.generateRandom(dim);

    Node * node = new Node(gen.getPuzzle(), heuristic, NULL);
    std::cout << *node << std::endl;
    openList.push(node);
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

    if (!openList.top()->isSolvable()) {
        throw std::invalid_argument("Puzzle is not solvable");
    } else {
        std::cout << "Puzzle is solvable, starting the algo ..." << std::endl;
    }

    int costLimit = nodeList.back()->getHxScore();

    std::vector<Node *> solution = NULL;

    while (solution == NULL) {

        costLimit, solution = depthLimitedSearch(0, nodeList, costLimit);
    }

    // this->totalNumberOfNodes = 1;
    // this->totalNumberOfNodesInMemory = 1;

    // while (!openList.empty() && !openList.top()->isValid()) {
    //     if (closedList.size() + openList.size() > this->totalNumberOfNodesInMemory) {
    //         this->totalNumberOfNodesInMemory = closedList.size() + openList.size();
    //     }
    //     Node *current;
    //     while (!openList.empty()) {
    //         current = openList.top();
    //         openList.pop();
    //         if (closedList.find(current) == closedList.end()) {
    //             closedList.insert(current);
    //             break;
    //         } else {
    //             delete current;
    //         }
    //     }

    //     this->totalNumberOfNodes += current->setChildrenIntoList(openList, closedList);
    // }

    this->end = std::chrono::high_resolution_clock::now();
    // this->endNode = openList.top();

    printResult();
}

Node IDA::depthLimitedSearch(int startCost, int costLimit) {

    Node *current = nodeList.back();

    int currentCost =  current->getFxScore();
    
    if (currentCost > costLimit)
        return None, costLimit;
    if (current == goal)
        return pathSoFar;

        new_start_cost = start_cost + edge_cost(node, s);
        solution, new_cost_limit = depth_limited_search(new_start_cost, extend(path_so_far, s), cost_limit)

        if solution != None:
            return solution, new_cost_limit
        next_cost_limit = min(next_cost_limit, new_cost_limit)
    
    return None, next_cost_limit
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