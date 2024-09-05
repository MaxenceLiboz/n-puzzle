#ifndef Parser_HPP
#define Parser_HPP

#include <fstream>
#include <string>
#include <iostream>
#include "Node.hpp"

class Parser {

private:

    enum Heuristic  _heuristicName;

public:
    // Constructors and Destructors
    Parser(int argsNumber, char **args);
    ~Parser();
    // Parser(Parser const & src);

    // Parser & operator=(Parser const & rhs);

};

#endif