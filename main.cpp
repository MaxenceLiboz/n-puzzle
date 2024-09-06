#include "main.hpp"
#include <unordered_set>

int main() {
    std::vector<int> v = {1, 7, 2, 0, 8, 4, 3, 6, 5};
    NPuzzle puzzle(v, MANHATTAN_DISTANCE);

    // 1, 7, 2, 0, 8, 4, 3, 6, 5
    // 0,7,2,1,8,4,3,6,5
    // 0,6,2,8,7,3,5,4,1
    // 4, 6, 5, 7, 3, 8, 1, 2, 0 Très long
    // 4, 2, 3, 1, 7, 6, 8, 0, 5 Un enfant très rapide
    // NPuzzle puzzle(3, MANHATTAN_DISTANCE);

    try {
        puzzle.solve();
        return 0;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}

