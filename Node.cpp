#include "Node.hpp"

std::vector<int> Node::goal;
int Node::goalParity;

Node::Node(std::vector<int> puzzle, Heuristic heuristic, Node *parent) {
    if (sqrt(puzzle.size()) != (int)sqrt(puzzle.size())) {
        throw std::invalid_argument("Puzzle size must be a perfect square.");
    }
    this->parent = parent;
    this->heuristic = heuristic;
    this->puzzle = puzzle;

    // this->dim = sqrt(puzzle.size());

    // if (parent == NULL) {
    //     this->gxScore = 0;
    // } else {
    //     this->gxScore = parent->gxScore + 1;
    // }

    // setGoalsAndParities();

    // setFxScore();
}

void Node::setNode() {
    this->dim = sqrt(this->puzzle.size());

    if (parent == NULL) {
        this->gxScore = 0;
    } else {
        this->gxScore = parent->gxScore + 1;
    }

    setGoalsAndParities();

    setFxScore();
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

void Node::setGoalsAndParities() {
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
        this->goalParity = getParity(this->goal);
    }
    this->puzzleParity = getParity(this->puzzle);
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
    int puzzleSize = puzzle.size();
    for (int i = 0; i < puzzleSize; i++) {
        if (puzzle[i] == 0) {
            continue;
        }
        if (puzzle[i] != goal[i]) {
            return false;
        }
    }
    return true;
}

int Node::setChildrenIntoList(std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> &openList, std::unordered_set<Node *, HashNode> &closedList){
    
    int puzzleSize = puzzle.size();
    int blankTileIndex = 0;
    int children = 0;
    for (int i = 0; i < puzzleSize; i++) {
        if (puzzle[i] == 0) {
            blankTileIndex = i;
            break;
        }
    }

    Node *child = NULL;
    if (blankTileIndex % this->dim != 0) {
        std::vector<int> leftPuzzle = puzzle;
        std::swap(leftPuzzle[blankTileIndex], leftPuzzle[blankTileIndex - 1]);
        child = new Node(leftPuzzle, heuristic, this);
        if (closedList.find(child) == closedList.end()) {
            child->setNode();
            openList.push(child);
        } else {
            delete child;
        }
        children++;
    }

    if (blankTileIndex % this->dim != this->dim - 1) {
        std::vector<int> rightPuzzle = puzzle;
        std::swap(rightPuzzle[blankTileIndex], rightPuzzle[blankTileIndex + 1]);
        child = new Node(rightPuzzle, heuristic, this);
        if (closedList.find(child) == closedList.end()) {
            child->setNode();
            openList.push(child);
        } else {
            delete child;
        }
        children++;
    }

    if (blankTileIndex >= this->dim) {
        std::vector<int> upPuzzle = puzzle;
        std::swap(upPuzzle[blankTileIndex], upPuzzle[blankTileIndex - this->dim]);
        child = new Node(upPuzzle, heuristic, this);
        if (closedList.find(child) == closedList.end()) {
            child->setNode();
            openList.push(child);
        } else {
            delete child;
        }
        children++;
    }

    if (blankTileIndex + this->dim < puzzleSize) {
        std::vector<int> downPuzzle = puzzle;
        std::swap(downPuzzle[blankTileIndex], downPuzzle[blankTileIndex + this->dim]);
        child = new Node(downPuzzle, heuristic, this);
        if (closedList.find(child) == closedList.end()) {
            child->setNode();
            openList.push(child);
        } else {
            delete child;
        }
        children++;
    }
    
    return children;
}

std::ostream &operator<<(std::ostream &os, Node &Node) {
    std::vector<int> datapuzzle = Node.getPuzzle();
    int puzzleSize = datapuzzle.size();
    for (int i = 0; i < puzzleSize; i++) {
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
    for (size_t i = 0; i < node->getPuzzle().size(); i++) {
        hash ^= std::hash<int>{}(node->getPuzzle()[i]);
    }
    return hash;
}