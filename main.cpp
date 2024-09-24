#include "main.hpp"
#include <unordered_set>

int main() {

    try {

        RandomGenerator gen;
        gen.generateRandom(3);
        
        for (int i : gen.getPuzzle())
            std::cout << i << " ";

        NPuzzle puzzle(gen.getPuzzle(), MANHATTAN_DISTANCE);

        puzzle.solve();
        return 0;

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}

