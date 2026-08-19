#include "Maze.h"
#include <raylib.h>

Maze::Maze()
{

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

    goalCell = {1, 10};
}

void Maze::Draw(Vector2 origin) const
{
    for (int row = 0; row < GetRows(); row++)
    {
        for (int col = 0; col < GetCols(); col++)
        {
            if (layout[row][col] == '#')
            {
                DrawRectangle(
                    static_cast<int>(origin.x + col * tileSize),
                    static_cast<int>(origin.y + row * tileSize),
                    tileSize,
                    tileSize,
                    DARKGRAY);
            }
        }
    }

    int padding = 8;

    float x = origin.x + static_cast<float>(goalCell.col * tileSize);
    float y = origin.y + static_cast<float>(goalCell.row * tileSize);

    Vector2 top = {
        x + tileSize / 2.0f,
        y + padding};

    Vector2 left = {
        x + padding,
        y + tileSize - padding};

    Vector2 right = {
        x + tileSize - padding,
        y + tileSize - padding};

    DrawTriangle(top, left, right, GOLD);
}

bool Maze::IsWallCell(Cell cell) const
{
    if (cell.row < 0 || cell.row >= GetRows())
    {
        return true;
    }

    if (cell.col < 0 || cell.col >= GetCols())
    {
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

Cell Maze::GetGoalCell() const
{
    return goalCell;
}