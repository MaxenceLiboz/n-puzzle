#ifndef Node_HPP
#define Node_HPP

#include <vector>
#include <tgmath.h>
#include <stdexcept>
#include <iostream>
#include <queue>
#include <iterator>
#include <algorithm>

enum Heuristic
{
    MANHATTAN_DISTANCE,
    MISPLACED_TILES,
    EUCLEDIAN_DISTANCE
};

struct CmpNodePtr;

class Node
{
private:
    std::vector<int> puzzle;
    int dim;
    static std::vector<int> goal;
    static int goalParity;
    int puzzleParity;

    double fxScore;
    double gxScore;
    double hxScore;

    int blankTileIndex;

    Node *parent;
    Heuristic heuristic;

    int getInversionCount(std::vector<int> &puzzle);
    int getParity(std::vector<int> &puzzle);

    // Setters
    void setFxScore();
    void setGoal();
    void setGoalParity();
    void setPuzzleParity();
    void setBlankTileIndex();

    // Validator throw error if not
    void isPuzzleValid(std::vector<int> &puzzle);

public:
    // Constructors and Destructors
    Node(std::vector<int> puzzle, Heuristic heuristic, Node *parent);
    Node(int dim);
    ~Node();

    // Getters
    std::vector<int> getPuzzle() const;
    double getFxScore() const;
    double getGxScore() const;
    double getHxScore() const;
    Node *getParent();
    int getDim();
    int getBlankTileIndex() const;
    std::vector<Node *> getChildrens() ;

    // Heuristic functions
    double calculateManhattanDistance();
    double calculateMisplacedTiles();
    double calculateEucledianDistance();

    // Setter
    bool setPuzzle(std::vector<int> puzzle);
    
    // Move functions
    std::vector<int> moveUp();
    std::vector<int> moveDown();
    std::vector<int> moveLeft();
    std::vector<int> moveRight();
    int setChildrenIntoList(std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> &openList);

    // Utility functions
    bool isSolvable();
    bool isValid();

};

struct CmpNodePtr
{
    bool operator()(const Node* lhs, const Node* rhs) const;
};

struct HashNode
{
    std::size_t operator()(const Node *node) const;
};


std::ostream &operator<<(std::ostream &os, Node &Node);

#endif