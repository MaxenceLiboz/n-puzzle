#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator() {}

RandomGenerator::~RandomGenerator() {}

void RandomGenerator::generateRandom(int dim) {

    if (dim < 3)
        throw std::invalid_argument("Puzzle dimension must be superior to 2");

    std::vector<int>    puzzle;

    srand((unsigned) time(NULL));
    int puzzleSize = pow(dim, 2);

    for (int i = 0; i < puzzleSize; i++) {

        int randomAdd = rand() % (puzzleSize - 1);

        if (puzzle.size() > 0) {

                for (std::vector<int>::iterator iter = puzzle.begin(); iter != puzzle.end(); ++iter) {

                    if (randomAdd == *iter) {

                        if (randomAdd == puzzleSize - 1)
                            randomAdd = 0;
                        else
                            randomAdd++;
                        
                        // At the next iteration, iter will be equal to puzzle.begin()
                        iter = puzzle.begin() - 1;
                    }
                }
        }
        
        puzzle.push_back(randomAdd);   
    }
    
    _setPuzzle(puzzle);
}

void RandomGenerator::_setPuzzle(std::vector<int> puzzle) { this->_puzzle = puzzle; }

std::vector<int> RandomGenerator::getPuzzle() const { return this->_puzzle; }
