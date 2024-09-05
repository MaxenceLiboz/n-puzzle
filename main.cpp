#include "main.hpp"
#include <unordered_set>

int main() {
    std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> openList;
    std::unordered_set<std::vector<int>, HashNode> closedList;

    std::vector<int> v = {0,2,3,1,6,7,4,8,5};

    NPuzzle puzzle(v, MANHATTAN_DISTANCE);

    try {
        puzzle.solve();
        return 0;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}

