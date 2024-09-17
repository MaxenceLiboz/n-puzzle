#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator(int dim) {

    std::vector<int>    puzzle;

    srand((unsigned) time(NULL));

    for (int i = 0; i < pow(dim, 2); i++) {

        int puzzleSize = pow(dim, 2);
	    puzzle.push_back(rand() % puzzleSize);
    }

    for (int i : puzzle)
        std::cout << i << " ";
}

RandomGenerator::~RandomGenerator() {}
