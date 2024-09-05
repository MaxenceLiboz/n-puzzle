#include "Parser.hpp"

Parser::Parser(int argsNumber, char **args) {

    if (argsNumber != 3) {

		throw std::invalid_argument("Need two arguments (input file and heuristic name)");
	}

    int whichHeuristic = args[2] - '0';

    switch (whichHeuristic) {

        case 0:
            this->_heuristicName = MANHATTAN_DISTANCE;
            break;
        case 1:
            this->_heuristicName = MISPLACED_TILES;
            break;
        case 2:
            this->_heuristicName = LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE;
            break;
        case 3:
            this->_heuristicName = EUCLEDIAN_DISTANCE;
            break;
        default:
            throw std::invalid_argument("Wrong heuristic name, must be MANHATTAN_DISTANCE, MISPLACED_TILES, LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE or EUCLEDIAN_DISTANCE");
    }

    std::cout << this->_heuristicName << std::endl;
}

Parser::~Parser() {}

// Parser::Parser(Parser const & src) {

// 	if (&src != this) 
// 		*this = src;
// }

// Parser & operator=(Parser const & rhs) {

//     this->_heuristicName = rhs._heuristicName;
	
// 	return *this;
// }


