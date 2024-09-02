#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <vector>
#include <tgmath.h>
#include <stdexcept>

enum Heuristic
{
    MANHATTAN_DISTANCE,
    MISPLACED_TILES,
    LINEAR_CONFLICT_AND_MANHATTAN_DISTANCE
};

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
    double getFxScore();
    Datastructure *getParent();

    // Setters
    void setFxScore();

    // Heuristic functions
    double calculateManhattanDistance();
    double calculateMisplacedTiles();
    double calculateLinearConflictAndManhattanDistance();

    // Move functions
    std::vector<Datastructure *> getChildren();

    // Utility functions
    bool isSolvable();
};

#endif