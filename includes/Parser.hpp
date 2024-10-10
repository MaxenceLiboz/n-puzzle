#ifndef Parser_HPP
#define Parser_HPP

#include <fstream>
#include <string>
#include <iostream>
#include "Node.hpp"
#include <algorithm>

class Parser {

private:

    std::string         _fileName;
    enum Heuristic      _heuristic;
    std::vector<int>    _puzzle;
    int                 _dim;

    // Setters
    void    _setDim(int dim);
    void    _setPuzzle(std::vector<int> puzzle);

    void    _fillPuzzleVector(std::ifstream& inputFile);
    void    _checkPuzzleValidity(std::vector<int> puzzle) const;

public:
    // Constructors and Destructors
    Parser(const std::string & fileName, Heuristic Heuristic);
    ~Parser();

    // Getters
    std::vector<int>    getPuzzle() const;
    enum Heuristic      getHeuristic() const;

    void    parsing();
};

#endif