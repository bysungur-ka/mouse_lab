#pragma once

#include <string>
#include <vector>

#include "GridTypes.h"

class Maze {
public:
    Maze();

    void Draw() const;

    bool IsWallCell(Cell cell) const;

    int GetTileSize() const;
    int GetRows() const;
    int GetCols() const;

    Cell GetStartCell() const;

private:
    std::vector<std::string> layout;
    int tileSize;
    Cell startCell;
};