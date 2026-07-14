#pragma once
#include <vector>
#include <string>

class Maze {
    public:
    Maze();

    void Draw() const;
    bool IsWallCell(int row, int col) const;

    int GetTileSize() const;
    int GetRows() const;
    int GetCols() const;

private:
    std::vector<std::string> layout;
    int tileSize;

};