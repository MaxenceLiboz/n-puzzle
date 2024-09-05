#include "main.hpp"

int main() {
    std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> openList;
    std::unordered_set<Node *> closedList;

    std::vector<int> v = {1, 5, 3, 2, 0, 6, 4, 8, 7};
    // std::vector<int> v = {4, 5, 1, 2, 8, 10, 6, 3, 9, 14, 15, 7, 12, 11, 13, 0};
    Node *node = new Node(v, MANHATTAN_DISTANCE, NULL);
    openList.push(node);

    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();

    if (!node->isSolvable()) {
        std::cout << "Puzzle is not solvable" << std::endl;
        return 0;
    }

    while (!openList.empty() && !openList.top()->isValid()) {
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

        current->setChildrenIntoList(openList);
    }

    std::chrono::_V2::system_clock::time_point stop = std::chrono::high_resolution_clock::now();


    if (openList.empty()) {
        std::cout << "Time taken : " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;
        std::cout << "No solution found" << std::endl;
    } else {
        Node *current = openList.top();
        double depth = current->getGxScore();
        while (current != NULL) {
            std::cout << *current << std::endl;
            current = current->getParent();
        }
        std::cout << "Time taken : " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;
        std::cout << "Depth: " << depth << std::endl;
        std::cout << "Solution found, go upward to check the path" << std::endl;
    }


    while (!openList.empty()) {
        Node *child = openList.top();
        openList.pop();
        delete child;
    }
    while (!closedList.empty()) {
        Node *child = *closedList.begin();
        closedList.erase(child);
        delete child;
    }
}

