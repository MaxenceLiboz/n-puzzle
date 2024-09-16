#ifndef Parser_HPP
#define Parser_HPP

#include <fstream>
#include <string>
#include <iostream>
#include "Node.hpp"

class Parser {

private:

    enum Heuristic      _heuristic;
    std::vector<int>    _puzzle;
    int                 _dim;

    void    _setPuzzle(std::ifstream& inputFile);
    void    _setDim(int dim);

public:
    // Constructors and Destructors
    Parser(int argsNumber, char **args, std::ifstream& inputFile);
    ~Parser();

    std::vector<int>    getPuzzle() const;
    enum Heuristic      getHeuristic() const;
};

#endif