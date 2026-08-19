#pragma once

#include <string>
#include <vector>

#include "GridTypes.h"
#include "raylib.h"

class Maze {
public:
    Maze();

    void Draw(Vector2 origin = {0.0f, 0.0f}) const;

    bool IsWallCell(Cell cell) const;

    int GetTileSize() const;
    int GetRows() const;
    int GetCols() const;

    Cell GetStartCell() const;
    Cell GetGoalCell() const;

private:
    std::vector<std::string> layout;
    int tileSize;
    Cell startCell;
    Cell goalCell;
};