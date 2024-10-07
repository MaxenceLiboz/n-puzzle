#ifndef RandomGenerator_HPP
#define RandomGenerator_HPP

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>
#include <iostream>
#include <functional>
#include "Node.hpp"

class Node;

class RandomGenerator
{
private:
    std::vector<int>    _puzzle;

    void    _setPuzzle(std::vector<int> puzzle);

public:
    // Constructors and Destructors
    RandomGenerator();
    ~RandomGenerator();

    void                generateRandom(int dim);
    std::vector<int>    getPuzzle() const;
};

#endif
