#ifndef Node_HPP
#define Node_HPP

#include <vector>
#include <tgmath.h>
#include <stdexcept>
#include <iostream>
#include <queue>
#include <unordered_set>

enum Heuristic
{
    MANHATTAN_DISTANCE,
    MISPLACED_TILES,
    LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE,
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
    int gxScore;

    Node *parent;
    Heuristic heuristic;

    bool isLinearConflict(int i, int j);
    int getInversionCount(std::vector<int> &puzzle);
    int getParity(std::vector<int> &puzzle);

    // Setters
    void setFxScore();
    void setGoalsAndParities();

public:
    // Constructors and Destructors
    Node(std::vector<int> puzzle, Heuristic heuristic, Node *parent);
    ~Node();

    // Getters
    std::vector<int> getPuzzle();
    double getFxScore() const;
    double getGxScore() const;
    Node *getParent();
    int getDim();
    


    // Heuristic functions
    double calculateManhattanDistance();
    double calculateMisplacedTiles();
    double calculateEucledianDistance();

    // Move functions
    void setChildrenIntoList(std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> &openList);

    // Utility functions
    bool isSolvable();
    bool isValid();

};

struct CmpNodePtr
{
    bool operator()(const Node* lhs, const Node* rhs) const;
};


std::ostream &operator<<(std::ostream &os, Node &Node);

#endif