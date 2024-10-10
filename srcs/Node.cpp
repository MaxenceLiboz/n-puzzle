#include "Node.hpp"

std::vector<int> Node::goal;
int Node::goalParity;

Node::Node(int dim) {
    if (dim < 3) {
        throw std::invalid_argument("Puzzle size must be a perfect square and at least 3 by 3.");
    }
    this->dim = dim;

    setGoal();
    this->puzzle = this->goal;
    setBlankTileIndex();
}

Node::Node(std::vector<int> puzzle, Heuristic heuristic, Node *parent) {
    
    this->parent = parent;
    this->heuristic = heuristic;
    this->dim = sqrt(puzzle.size());

    this->puzzle = puzzle;
    isPuzzleValid(puzzle);

    if (parent == NULL) {
        this->gxScore = 0;
    } else {
        this->gxScore = parent->gxScore + 1;
    }

    setGoal();
    setGoalParity();
    setPuzzleParity();

    setFxScore();
    setBlankTileIndex();
}

Node::~Node() {}

std::vector<int> Node::getPuzzle() const {
    return puzzle;
}

double Node::getFxScore() const {
    return fxScore;
}

double Node::getGxScore() const {
    return gxScore;
}

double Node::getHxScore() const {
    return hxScore;
}

Node *Node::getParent() {
    return parent;
}

int Node::getDim() {
    return dim;
}

int Node::getBlankTileIndex() const {
    return blankTileIndex;
}

void Node::setGoal() {
    if (goal.size() == 0) {
        std::vector<int> goalState(this->dim * this->dim, 0);
        int number = 1;
        int top = 0, left = 0, bottom = this->dim - 1, right = this->dim -1;
        int finishIndex = 0;

        while (top < bottom && left < right) {

            // Fill top row
           for (int i = left; i <= right; ++i) {
                finishIndex = top * this->dim + i;
                goalState[finishIndex] = number++;
            }
            ++top;

            // Fill right column
            for (int i = top; i <= bottom; ++i) {
                finishIndex = i * this->dim + right;
                goalState[finishIndex] = number++;
            }
            --right;

            // Fill bottom row
            if (top <= bottom) {
                for (int i = right; i >= left; --i) {
                    finishIndex = bottom * this->dim + i;
                    goalState[finishIndex] = number++;
                }
                --bottom;
            }

            // Fill left column
            if (left <= right) {
                for (int i = bottom; i >= top; --i) {
                    finishIndex = i * this->dim + left;
                    goalState[finishIndex] = number++;
                }
                ++left;
            } 
        }
        if (this->dim % 2 == 0) {
            goalState[finishIndex] = 0;
        }
        this->goal = goalState;
    }
}

void Node::setGoalParity() {
    this->goalParity = getParity(this->goal);
}

void Node::setPuzzleParity() {
    this->puzzleParity = getParity(this->puzzle);
}

bool Node::setPuzzle(std::vector<int> puzzle) {
    if (puzzle.size() == this->puzzle.size()) {
        this->puzzle = puzzle;
        setBlankTileIndex();
        return true;
    }
    return false;
}

void Node::setFxScore() {
    if (MANHATTAN_DISTANCE == heuristic)
    {
        hxScore = calculateManhattanDistance();
        fxScore = hxScore + gxScore;
    }
    else if (MISPLACED_TILES == heuristic)
    {
        hxScore = calculateMisplacedTiles();
        fxScore = hxScore + gxScore;
    }
    else if (EUCLEDIAN_DISTANCE == heuristic)
    {
        hxScore = calculateEucledianDistance();
        fxScore = hxScore + gxScore;
    }
    else
    {
        throw std::invalid_argument("Heuristic not supported.");
    }
}

void Node::setBlankTileIndex() {
    for (size_t i = 0; i < this->puzzle.size(); i++) {
        if (this->puzzle[i] == 0) {
            blankTileIndex = i;
            break;
        }
    }
}

double Node::calculateManhattanDistance() {
    double manhattanDistance = 0;
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++)
    {
        int value = puzzle[i];
        ptrdiff_t pos = std::distance(goal.begin(), std::find(goal.begin(), goal.end(), value));
        if (value != 0) {
            int row = i / this->dim;
            int column = i % this->dim;
            int targetRow = pos / this->dim;
            int targetColumn = pos % this->dim;
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
        if (puzzle[i] != goal[i] && puzzle[i] != 0) {
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
        ptrdiff_t pos = std::distance(goal.begin(), std::find(goal.begin(), goal.end(), value));
        if (value != 0) {
            int row = i / this->dim;
            int column = i % this->dim;
            int targetRow = pos / this->dim;
            int targetColumn = pos % this->dim;
            eucledianDistance += sqrt(pow(row - targetRow, 2) + pow(column - targetColumn, 2));
        }
    }
    return eucledianDistance;
}


int Node::getInversionCount(std::vector<int> &puzzle) {
    int inversionCount = 0;
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++) {
        if (puzzle[i] == 0) {
            continue;
        }
        for (int j = i + 1; j < puzzleSize; j++) {
            if (puzzle[j] != 0 && puzzle[i] > puzzle[j]) {
                inversionCount++;
            }
        }
    }
    return inversionCount;
}

int Node::getParity(std::vector<int> &puzzle) {
    std::size_t puzzleSize = puzzle.size();
    int inversionCount = getInversionCount(puzzle);
    if (this->dim % 2 == 1) {
        return inversionCount & 1;
    } else {
        for (std::size_t i = 0; i < puzzleSize; i++) {
            if (puzzle[i] == 0) {
                inversionCount += (puzzleSize - 1 - i) / this->dim;
                break;
            }
        }
        return inversionCount & 1;
    }
}

bool Node::isSolvable() {
    if (puzzleParity == goalParity) {
        return true;
    }
    return false;
}

bool Node::isValid() {
    if (this->getHxScore() == 0) {
        return true;
    }
    return false;
}

void Node::isPuzzleValid(std::vector<int> &puzzle) {
    if (puzzle.size() < 9 || sqrt(puzzle.size()) != (int)sqrt(puzzle.size())) {
        throw std::invalid_argument("Puzzle size must be a perfect square and at least 3 by 3.");
    }

    std::sort(puzzle.begin(), puzzle.end());
    int i = 0;
    for (int puzzleCase : puzzle) {
        if (i != puzzleCase) {
            throw std::invalid_argument("Numbers inside of the puzzle are not in the good range");
        }
        i++;
    }
}

std::vector<int> Node::moveUp() {
    std::vector<int> upPuzzle;
    if (blankTileIndex >= this->dim) {
        upPuzzle = this->puzzle;
        std::swap(upPuzzle[blankTileIndex], upPuzzle[blankTileIndex - this->dim]);
    }
    return upPuzzle;
}

std::vector<int> Node::moveDown() {
    std::vector<int> downPuzzle;
    if (this->blankTileIndex + this->dim < (int)this->puzzle.size()) {
        downPuzzle = this->puzzle;
        std::swap(downPuzzle[blankTileIndex], downPuzzle[blankTileIndex + this->dim]);
    }
    return downPuzzle;
}

std::vector<int> Node::moveLeft() {
    std::vector<int> leftPuzzle;
    if (blankTileIndex % this->dim != 0) {
        leftPuzzle = this->puzzle;
        std::swap(leftPuzzle[blankTileIndex], leftPuzzle[blankTileIndex - 1]);
    }
    return leftPuzzle;
}

std::vector<int> Node::moveRight() {
    std::vector<int> rightPuzzle;
    if (blankTileIndex % this->dim != this->dim - 1) {
        rightPuzzle = this->puzzle;
        std::swap(rightPuzzle[blankTileIndex], rightPuzzle[blankTileIndex + 1]);
    }
    return rightPuzzle;
}

int Node::setChildrenIntoList(std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> &openList) {
    int children = 0;

    std::vector<int> upPuzzle = this->moveUp();
    if (upPuzzle.size() > 0) {
        openList.push(new Node(upPuzzle, heuristic, this));
        children++;
    }

    std::vector<int> downPuzzle = this->moveDown();
    if (downPuzzle.size() > 0) {
        openList.push(new Node(downPuzzle, heuristic, this));
        children++;
    }

    std::vector<int> leftPuzzle = this->moveLeft();
    if (leftPuzzle.size() > 0) {
        openList.push(new Node(leftPuzzle, heuristic, this));
        children++;
    }

    std::vector<int> rightPuzzle = this->moveRight();
    if (rightPuzzle.size() > 0) {
        openList.push(new Node(rightPuzzle, heuristic, this));
        children++;
    }
    
    return children;
}

std::vector<Node *> Node::getChildrens() {
    
    std::vector<Node *> childrens;
 
    std::vector<int> upPuzzle = this->moveUp();
    if (upPuzzle.size() > 0) {
        childrens.push_back(new Node(upPuzzle, heuristic, this));
    }

    std::vector<int> downPuzzle = this->moveDown();
    if (downPuzzle.size() > 0) {
        childrens.push_back(new Node(downPuzzle, heuristic, this));
    }

    std::vector<int> leftPuzzle = this->moveLeft();
    if (leftPuzzle.size() > 0) {
        childrens.push_back(new Node(leftPuzzle, heuristic, this));
    }

    std::vector<int> rightPuzzle = this->moveRight();
    if (rightPuzzle.size() > 0) {
        childrens.push_back(new Node(rightPuzzle, heuristic, this));
    }
    
    return childrens;
}

std::ostream &operator<<(std::ostream &os, Node &Node) {
    std::vector<int> datapuzzle = Node.getPuzzle();
    for (size_t i = 0; i < datapuzzle.size(); i++) {
        if (i % Node.getDim() == 0) {
            os << std::endl;
        }
        if (datapuzzle[i] == 0) {
            os << "x ";
        } else {
            os << datapuzzle[i] << " ";
        }
    }
    os << std::endl;
    return os;
}

bool CmpNodePtr::operator()(const Node* lhs, const Node* rhs) const {
    if (lhs->getFxScore() == rhs->getFxScore()) {
        return lhs->getHxScore() > rhs->getHxScore();
    } else {
        return lhs->getFxScore() > rhs->getFxScore();
    }
}

size_t HashNode::operator()(const Node *node) const {
    size_t hash = 0;
    std::size_t prime = 7;
    for (size_t i = 0; i < node->getPuzzle().size(); i++) {
        hash = hash * prime + std::hash<int>{}(node->getPuzzle()[i]);
    }
    return hash;
}

Heuristic getHeuristicFromValue(const std::string &heuristic) {
    if (heuristic == "0") {
        return MANHATTAN_DISTANCE;
    }
    else if (heuristic == "1") {
        return EUCLEDIAN_DISTANCE;
    }
    else if (heuristic == "2") {
        return MISPLACED_TILES;
    } else {
        throw std::invalid_argument("Heuristic value not supported");
    }
}