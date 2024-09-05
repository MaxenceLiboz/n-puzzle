#include "NPuzzle.hpp"

NPuzzle::NPuzzle(std::vector<int> puzzle, Heuristic heuristic) {
    Node * node = new Node(puzzle, heuristic, NULL);
    openList.push(node);
}

NPuzzle::~NPuzzle() {
    while (!openList.empty()) {
        Node *child = openList.top();
        openList.pop();
        delete child;
    }

    for (std::unordered_set<Node *, HashNode>::iterator it = closedList.begin(); it != closedList.end(); it++) {
        delete *it;
    }
}

void NPuzzle::solve() {
    this->start = std::chrono::high_resolution_clock::now();

    if (!openList.top()->isSolvable()) {
        throw std::invalid_argument("Puzzle is not solvable");
    }

    this->totalNumberOfNodes = 1;
    this->totalNumberOfNodesInMemory = 1;

    while (!openList.empty() && !openList.top()->isValid()) {
        if (closedList.size() + openList.size() > this->totalNumberOfNodesInMemory) {
            this->totalNumberOfNodesInMemory = closedList.size() + openList.size();
        }
        Node *current;
        while (!openList.empty()) {
            current = openList.top();
            openList.pop();
            if (closedList.find(current) == closedList.end()) {
                closedList.insert(current);
                break;
            } else {
                delete current;
            }
        }

        this->totalNumberOfNodes += current->setChildrenIntoList(openList);
    }

    this->end = std::chrono::high_resolution_clock::now();
    this->endNode = openList.top();

    printResult();
}

void NPuzzle::printResult() {
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