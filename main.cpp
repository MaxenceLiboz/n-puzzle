#include "main.hpp"

int main() {
    std::vector<int> v = {6, 13, 7, 10, 8, 9, 11, 0, 15, 2, 12, 5, 14, 3, 1, 4};
    Datastructure *datastructure = new Datastructure(v, LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE, NULL);

    std::cout << datastructure->getFxScore() << std::endl;
    std::cout << (datastructure->isSolvable() ? "TRUE" : "FALSE") << std::endl;

    delete datastructure;
}


