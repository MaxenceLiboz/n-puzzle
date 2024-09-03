#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

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

struct CmpDatastructurePtr;

class Datastructure
{
private:
    std::vector<int> puzzle;
    double fxScore;
    Datastructure *parent;
    int dim;
    Heuristic heuristic;
    int gxScore;

    bool isLinearConflict(int i, int j);
    void setParentPuzzle(std::vector<int> puzzle);
    int getInversionCount();

public:
    // Constructors and Destructors
    Datastructure(std::vector<int> puzzle, Heuristic heuristic, Datastructure *parent);
    ~Datastructure();

    // Getters
    std::vector<int> getPuzzle();
    double getFxScore() const;
    double getGxScore() const;
    Datastructure *getParent();
    int getDim();
    

    // Setters
    void setFxScore();

    // Heuristic functions
    double calculateManhattanDistance();
    double calculateMisplacedTiles();
    double calculateLinearConflictAndManhattanDistance();
    double calculateEucledianDistance();

    // Move functions
    void setChildenIntoList(std::priority_queue<Datastructure *, std::vector<Datastructure*>, CmpDatastructurePtr> &openList);

    // Utility functions
    bool isSolvable();
    bool isValid();

};

struct CmpDatastructurePtr
{
    bool operator()(const Datastructure* lhs, const Datastructure* rhs) const;
};


std::ostream &operator<<(std::ostream &os, Datastructure &datastructure);

#endif