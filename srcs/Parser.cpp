#include "Parser.hpp"

Parser::Parser(const std::string &fileName, Heuristic heuristic) : _fileName(fileName), _heuristic(heuristic) {}

Parser::~Parser() {}

void Parser::parsing() {

    std::ifstream inputFile;
    inputFile.open(this->_fileName);
	if (inputFile.fail()) {
	
		throw std::invalid_argument("Invalid text file");
	}

    try {
        this->_fillPuzzleVector(inputFile);
    }
    catch (std::exception &e){

        throw std::invalid_argument( e.what() );
    }
}

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

    this->_setPuzzle(puzzle);
    this->_checkPuzzleValidity(puzzle);
}

void Parser::_checkPuzzleValidity(std::vector<int> puzzle) const {

    std::sort(puzzle.begin(), puzzle.end());

    int i = 0;
    for (int puzzleCase : puzzle) {

        if (i != puzzleCase)
            throw std::invalid_argument("Please make sure the input file is in correct format");

        i++;
    }
}

void Parser::_setPuzzle(std::vector<int> puzzle) { this->_puzzle = puzzle; }
void Parser::_setDim(int dim) { this->_dim = dim; }

std::vector<int>    Parser::getPuzzle() const { return this->_puzzle; }
enum Heuristic      Parser::getHeuristic() const { return this->_heuristic; }
