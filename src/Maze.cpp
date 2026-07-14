#include "Maze.h"
#include <raylib.h>

Maze::Maze() {

    tileSize = 45;
    layout = {
        "############",
        "###.#...##.#",
        "##...##.##.#",
        "##.#.#.....#",
        "##.#.#.#.###",
        "#..#...#####",
        "############",
    };

    
    startCell = {5, 1};

}

void Maze::Draw() const
{
    for (int row = 0; row < GetRows(); row++) {
        for (int col = 0; col < GetCols(); col++) {
            if (layout[row][col] == '#') {
                DrawRectangle(
                    col * tileSize,
                    row * tileSize,
                    tileSize,
                    tileSize,
                    DARKGRAY
                );
            }
        }
    }
}

bool Maze::IsWallCell(Cell cell) const
{
    if (cell.row < 0 || cell.row >= GetRows()) {
        return true;
    }

    if (cell.col < 0 || cell.col >= GetCols()) {
        return true;
    }

    return layout[cell.row][cell.col] == '#';
}

int Maze::GetTileSize() const
{
    return tileSize;
}

int Maze::GetRows() const
{
    return static_cast<int>(layout.size());
}

int Maze::GetCols() const
{
    return static_cast<int>(layout[0].size());
}

Cell Maze::GetStartCell() const
{
    return startCell;
}