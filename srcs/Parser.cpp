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

    std::string         line;
    bool                dimFill = false;

    while (std::getline(inputFile, line))
	{
        for (std::size_t i = 0; i < line.size(); i++) {

            if (line[i] == '#')
                break;
            else if (!dimFill && std::isdigit(line[i])) {

                int newIndex = this->_whileIsDigit(line, i);

                // An atoi is made for the entire number 
                this->_setDim(std::atoi(line.substr(i, newIndex - i).c_str()));
                dimFill = true;

                break;
            }
            else if (dimFill && std::isdigit(line[i])) {

                int newIndex = this->_whileIsDigit(line, i);

                _puzzle.push_back(std::atoi(line.substr(i, newIndex - i).c_str()));

                // Minus 1 because i will be increase before the next iteration
                i = newIndex - 1;
            }
            else if (line[i] != ' ')
                throw std::invalid_argument("Invalid arguments in the text file, at the line : \"" + line + "\"");



        }
    }

    this->_checkPuzzleValidity();
}

int Parser::_whileIsDigit(std::string line, std::size_t newIndex) const {

    while (std::isdigit(line[newIndex]) && newIndex < line.size()) {

        newIndex++;
    }

    return newIndex;
}

void Parser::_checkPuzzleValidity() const {

    std::vector<int> puzzle = _puzzle;

    if (puzzle.size() != pow(_dim, 2))
        throw std::invalid_argument("The dimensions of the puzzle does not match");

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
