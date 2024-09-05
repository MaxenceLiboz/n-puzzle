#include "Node.hpp"

Node::Node(std::vector<int> puzzle, Heuristic heuristic, Node *parent) {
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

Node::~Node() {}

std::vector<int> Node::getPuzzle() {
    return puzzle;
}

double Node::getFxScore() const {
    return fxScore;
}

double Node::getGxScore() const {
    return gxScore;
}

Node *Node::getParent() {
    return parent;
}

int Node::getDim() {
    return dim;
}

void Node::setFxScore() {
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
    else if (EUCLEDIAN_DISTANCE == heuristic)
    {
        fxScore = calculateEucledianDistance() + gxScore;
    }
    else
    {
        throw std::invalid_argument("Heuristic not supported.");
    }
}

void Node::setParentPuzzle(std::vector<int> puzzle) {
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++)
    {
        this->puzzle.push_back(puzzle[i] - 1);
    }
}

double Node::calculateManhattanDistance() {
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

double Node::calculateMisplacedTiles() {
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

double Node::calculateEucledianDistance() {
    double eucledianDistance = 0;
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++)
    {
        int value = puzzle[i];
        if (value != -1) {
            int row = i / this->dim;
            int column = i % this->dim;
            int targetRow = value / this->dim;
            int targetColumn = value % this->dim;
            eucledianDistance += sqrt(pow(row - targetRow, 2) + pow(column - targetColumn, 2));
        }
    }
    return eucledianDistance;
}

double Node::calculateLinearConflictAndManhattanDistance() {
    double linearConflict = 0;
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++)
    {
        if (i % this->dim != this->dim - 1 && isLinearConflict(i, i + 1)) { // Check right tile
            linearConflict++;
        } else if (i + this->dim < puzzleSize && isLinearConflict(i, i + this->dim)) { // Check down tile
            linearConflict++;
        } else if (i % this->dim != 0 && isLinearConflict(i, i - 1)) { // Check left tile
            linearConflict++;
        } else if (i >= this->dim && isLinearConflict(i, i - this->dim)) { // Check up tile
            linearConflict++;
        } 
    }
    return linearConflict + calculateManhattanDistance();
}

bool Node::isLinearConflict(int i, int j){
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

int Node::getInversionCount() {
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

bool Node::isSolvable() {
    int inversionCount = getInversionCount();
    std::size_t puzzleSize = puzzle.size();
    if (this->dim % 2 == 1) {
        return inversionCount % 2 == 0;
    } else {
        int blankTileRow = 0;
        int j = puzzleSize - 1;
        for (std::size_t i = 0; i < puzzleSize; i++) {
            if (puzzle[j] == -1) {
                blankTileRow = (i / this->dim) + 1;
                break;
            }
            j--;
        }
        return (inversionCount + blankTileRow) % 2 == 1;
    }
}

bool Node::isValid() {
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++) {
        if (puzzle[i] == -1) {
            continue;
        }
        if (puzzle[i] != i) {
            return false;
        }
    }
    return true;
}

void Node::setChildrenIntoList(std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> &openList) {
    int puzzleSize = puzzle.size();
    int blankTileIndex = 0;
    for (int i = 0; i < puzzleSize; i++) {
        if (puzzle[i] == -1) {
            blankTileIndex = i;
            break;
        }
    }

    if (blankTileIndex % this->dim != 0) {
        std::vector<int> leftPuzzle = puzzle;
        std::swap(leftPuzzle[blankTileIndex], leftPuzzle[blankTileIndex - 1]);
        openList.push(new Node(leftPuzzle, heuristic, this));
    }

    if (blankTileIndex % this->dim != this->dim - 1) {
        std::vector<int> rightPuzzle = puzzle;
        std::swap(rightPuzzle[blankTileIndex], rightPuzzle[blankTileIndex + 1]);
        openList.push(new Node(rightPuzzle, heuristic, this));
    }

    if (blankTileIndex >= this->dim) {
        std::vector<int> upPuzzle = puzzle;
        std::swap(upPuzzle[blankTileIndex], upPuzzle[blankTileIndex - this->dim]);
        openList.push(new Node(upPuzzle, heuristic, this));
    }

    if (blankTileIndex + this->dim < puzzleSize) {
        std::vector<int> downPuzzle = puzzle;
        std::swap(downPuzzle[blankTileIndex], downPuzzle[blankTileIndex + this->dim]);
        openList.push(new Node(downPuzzle, heuristic, this));
    }
}

std::ostream &operator<<(std::ostream &os, Node &Node) {
    std::vector<int> datapuzzle = Node.getPuzzle();
    int puzzleSize = datapuzzle.size();
    for (int i = 0; i < puzzleSize; i++) {
        if (i % Node.getDim() == 0) {
            os << std::endl;
        }
        if (datapuzzle[i] == -1) {
            os << "x ";
        } else {
            os << datapuzzle[i] + 1 << " ";
        }
    }
    os << std::endl;
    return os;
}

bool CmpNodePtr::operator()(const Node* lhs, const Node* rhs) const {
    return lhs->getFxScore() > rhs->getFxScore();
}