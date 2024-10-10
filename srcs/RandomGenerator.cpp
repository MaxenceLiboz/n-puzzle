#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator() {}

RandomGenerator::~RandomGenerator() {}

void RandomGenerator::generateRandom(int dim) {

    Node node(dim);
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distMove(0, 3);
    std::uniform_int_distribution<int> distRange(10, 50);

    int range = distRange(rng);

    for (int i = 0; i < range; i++) {

        int random = distMove(rng);
        switch (random)
        {
            case 0:
                if(!node.setPuzzle(node.moveUp())) {
                    i--;
                }
                break;
            case 1:
                if (!node.setPuzzle(node.moveDown())) {
                    i--;
                }
                break;
            case 2:
                if (!node.setPuzzle(node.moveLeft())) {
                    i--;
                }
                break;
            case 3:
                if (!node.setPuzzle(node.moveRight())) {
                    i--;
                }
                break;
            default:
                break;
        }
        
    }

    std::cout << "Shuffle with " << range << " moves" << std::endl;
    for (int i : node.getPuzzle()) {
        std::cout << i << " ";
     }

    std::cout << '\n';
    
    _setPuzzle(node.getPuzzle());
}

void RandomGenerator::_setPuzzle(std::vector<int> puzzle) { this->_puzzle = puzzle; }

std::vector<int> RandomGenerator::getPuzzle() const { return this->_puzzle; }
