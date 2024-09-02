#include "main.hpp"

int main() {
    std::vector<int> v = {2, 1, 3, 4, 6, 8, 7, 5, 0};
    Datastructure *datastructure = new Datastructure(v, LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE, NULL);

    std::cout << datastructure->getFxScore() << std::endl;

    delete datastructure;
}