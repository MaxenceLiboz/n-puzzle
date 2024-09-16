#ifndef Parser_HPP
#define Parser_HPP

#include <fstream>
#include <string>
#include <iostream>
#include "Node.hpp"
#include <algorithm>

class Parser {

private:

    enum Heuristic      _heuristic;
    std::vector<int>    _puzzle;
    int                 _dim;

    void    _fillPuzzleVector(std::ifstream& inputFile);
    void    _setDim(int dim);
    void    _setPuzzle(std::vector<int> puzzle);

    void    _checkPuzzleValidity(std::vector<int> puzzle) const;

public:
    // Constructors and Destructors
    Parser(int argsNumber, char **args, std::ifstream& inputFile);
    ~Parser();

    std::vector<int>    getPuzzle() const;
    enum Heuristic      getHeuristic() const;
};

#endif