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

}

int Maze::GetTileSize() const{
    return tileSize;
}

int Maze::GetRows() const{
    return static_cast<int>(layout.size());
}

int Maze::GetCols() const{
    return static_cast<int>(layout[0].size());
}

bool Maze::IsWallCell(int row, int col) const
{
    if (row < 0 || row >= GetRows()) {
        return true;
    }

    if (col < 0 || col >= GetCols()) {
        return true;
    }

    return layout[row][col] == '#';
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