#include "Datastructure.hpp"

Datastructure::Datastructure(std::vector<int> puzzle, Heuristic heuristic, Datastructure *parent) {
    if (sqrt(puzzle.size()) != (int)sqrt(puzzle.size())) {
        throw std::invalid_argument("Puzzle size must be a perfect square.");
    }
    this->parent = parent;
    this->heuristic = heuristic;
    this->dim = sqrt(puzzle.size());

    if (parent == NULL) {
        setParentPuzzle(puzzle);
        this->gxScore = 0;
    } else {
        this->puzzle = puzzle;
        this->gxScore = parent->gxScore + 1;
    }

    setFxScore();
}

Datastructure::~Datastructure() {
    delete parent;
}

std::vector<int> Datastructure::getPuzzle() {
    return puzzle;
}

double Datastructure::getFxScore() {
    return fxScore;
}

Datastructure *Datastructure::getParent() {
    return parent;
}

void Datastructure::setFxScore() {
    if (MANHATTAN_DISTANCE == heuristic)
    {
        fxScore = calculateManhattanDistance() + gxScore;
    }
    else if (MISPLACED_TILES == heuristic)
    {
        fxScore = calculateMisplacedTiles() + gxScore;
    }
    else if (LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE == heuristic)
    {
        fxScore = calculateLinearConflictAndManhattanDistance() + gxScore;
    }
    else
    {
        throw std::invalid_argument("Heuristic not supported.");
    }
}

void Datastructure::setParentPuzzle(std::vector<int> puzzle) {
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++)
    {
        this->puzzle.push_back(puzzle[i] - 1);
    }
}

double Datastructure::calculateManhattanDistance() {
    double manhattanDistance = 0;
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++)
    {
        int value = puzzle[i];
        if (value != -1) {
            int row = i / this->dim;
            int column = i % this->dim;
            int targetRow = value / this->dim;
            int targetColumn = value % this->dim;
            manhattanDistance += abs(row - targetRow) + abs(column - targetColumn);
        }
    }
    return manhattanDistance;
}

double Datastructure::calculateMisplacedTiles() {
    double misplacedTiles = 0;
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++)
    {
        int value = puzzle[i];
        if (value != i && value != -1) {
            misplacedTiles++;
        }
    }
    return misplacedTiles;
}

double Datastructure::calculateLinearConflictAndManhattanDistance() {
    double linearConflict = 0;
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++)
    {
        if (i + 1 < this->dim && isLinearConflict(i, i + 1)) { // Check right tile
            linearConflict++;
        } else if (i + this->dim <= puzzleSize && isLinearConflict(i, i + this->dim)) { // Check down tile
            linearConflict++;
        } else if ((i > 0 || i % this->dim == 1) && isLinearConflict(i, i - 1)) { // Check left tile
            linearConflict++;
        } else if (i - this->dim >= 0 && isLinearConflict(i, i - this->dim)) { // Check up tile
            linearConflict++;
        } 
    }
    return linearConflict + calculateManhattanDistance();
}

bool Datastructure::isLinearConflict(int i, int j){
    int value = puzzle[i];
    if (value == -1) {
        return false;
    }
    int targetRow = value / this->dim;
    int targetColumn = value % this->dim;
    int row = i / this->dim;
    int column = i % this->dim;

    int otherValue = puzzle[j];
    int otherValueTargetRow = otherValue / this->dim;
    int otherValueTargetColumn = otherValue % this->dim;
    int otherValueRow = j / this->dim;
    int otherValueColumn = j % this->dim;

    if (targetRow == otherValueRow && targetColumn == otherValueColumn && otherValueTargetColumn == column && otherValueTargetRow == row) {
        return true;
    }
    return false;
}

int Datastructure::getInversionCount() {
    int inversionCount = 0;
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++) {
        if (puzzle[i] == -1) {
            continue;
        }
        for (int j = i + 1; j < puzzleSize; j++) {
            if (puzzle[j] != -1 && puzzle[i] > puzzle[j]) {
                inversionCount++;
            }
        }
    }
    return inversionCount;
}

bool Datastructure::isSolvable() {
    int inversionCount = getInversionCount();
    std::size_t puzzleSize = puzzle.size();
    if (this->dim % 2 == 1) {
        return inversionCount % 2 == 0;
    } else {
        int blankTileRow = 0;
        for (std::size_t i = 0; i < puzzleSize; i++) {
            if (puzzle[i] == -1) {
                blankTileRow = i / this->dim; // the index start from 0 so we can go from the top
                break;
            }
        }
        return (inversionCount + blankTileRow) % 2 == 1;
    }
}