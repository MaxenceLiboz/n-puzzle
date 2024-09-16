#include "Parser.hpp"

Parser::Parser(int argsNumber, char **args, std::ifstream& inputFile) {

    if (argsNumber != 3) {

		throw std::invalid_argument("Need two arguments (input file and heuristic name)");
	}

    int whichHeuristic;
    sscanf(args[2], "%d", &whichHeuristic);

    switch (whichHeuristic) {

        case 0:
            this->_heuristic = MANHATTAN_DISTANCE;
            break;
        case 1:
            this->_heuristic = MISPLACED_TILES;
            break;
        case 2:
            this->_heuristic = LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE;
            break;
        case 3:
            this->_heuristic = EUCLEDIAN_DISTANCE;
            break;
        default:
            throw std::invalid_argument("Wrong heuristic name, must be MANHATTAN_DISTANCE, MISPLACED_TILES, LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE or EUCLEDIAN_DISTANCE");
    }

    this->_fillPuzzleVector(inputFile);
}

Parser::~Parser() {}

void Parser::_fillPuzzleVector(std::ifstream& inputFile) {

    std::vector<int> puzzle;
    std::string line;
    int lineCount = 0;

    while (std::getline(inputFile, line))
	{
        if (lineCount > 0) {

            std::string::size_type posEndL = line.find('#');
            if (posEndL == std::string::npos)
                posEndL = line.size();

            if (lineCount == 1)
                this->_setDim(std::atoi(line.substr(0, posEndL).c_str()));
            else if (lineCount > 1) {

                std::string::size_type posBlank = 0;
                std::string::size_type posBlankTmp = 0;
                std::size_t vectorSizeTmp = puzzle.size();

                while((posBlank = line.find(' ', posBlankTmp + 1)) != std::string::npos && posBlank < posEndL) {

                    if (posBlankTmp != posBlank && line.at(posBlank - 1) != ' ')
                        puzzle.push_back(std::atoi(line.substr(posBlankTmp, posBlank - posBlankTmp).c_str()));

                    posBlankTmp = posBlank;
                }

                if (puzzle.size() == vectorSizeTmp + (this->_dim - 1))
                    puzzle.push_back(std::atoi(line.substr(posBlankTmp, posBlank - posBlankTmp).c_str()));

            }
        }

        lineCount++;
    }

    this->_checkPuzzleValidity(puzzle);
}

void Parser::_checkPuzzleValidity(std::vector<int> puzzle) const {

    std::sort(puzzle.begin(), puzzle.end());

    int i = 0;
    for (int puzzleCase : puzzle) {

        if (i != puzzleCase)
            throw std::invalid_argument("Numbers inside of the puzzle are not in the good range");

        i++;
    }

    this->_setPuzzle(puzzle);
}

void Parser::_setPuzzle(std::vector<int> puzzle) { this->_puzzle = puzzle; }
void Parser::_setDim(int dim) { this->_dim = dim; }

std::vector<int>    Parser::getPuzzle() const { return this->_puzzle; }
enum Heuristic      Parser::getHeuristic() const { return this->_heuristic; }
