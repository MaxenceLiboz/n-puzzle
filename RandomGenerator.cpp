#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator() {}

RandomGenerator::~RandomGenerator() {}

void RandomGenerator::generateRandom(int dim) {

    Node node(dim);
    srand((unsigned) time(NULL));
    int blankTileIndex;
    int puzzleSize = node.getPuzzle().size();

    for (int i = 0; i < 30; i++) {
        int random = rand() % 4;
        for (int i = 0; i < puzzleSize; i++) {
            if (node.getPuzzle()[i] == 0) {
                blankTileIndex = i;
                break;
            }
        }


        switch (random)
        {
            case 0:
                node.setPuzzle(node.moveUp(blankTileIndex));
                break;
            case 1:
                node.setPuzzle(node.moveDown(blankTileIndex));
                break;  
            case 2:
                node.setPuzzle(node.moveLeft(blankTileIndex));
                break;  
            case 3:
                node.setPuzzle(node.moveRight(blankTileIndex));
                break;       
        }
        
    }

    
    _setPuzzle(node.getPuzzle());
}

void RandomGenerator::_setPuzzle(std::vector<int> puzzle) { this->_puzzle = puzzle; }

std::vector<int> RandomGenerator::getPuzzle() const { return this->_puzzle; }
