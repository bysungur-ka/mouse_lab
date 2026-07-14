#include "Game.h"

#include "raylib.h"

Game::Game()
    : maze(),
      mouse(maze.GetStartCell())
{
}

void Game::Update()
{
    Action action = ReadInput();
    TryMoveMouse(action);
}

void Game::Draw() const
{
    maze.Draw();
    DrawMouse();
}

int Game::GetScreenWidth() const
{
    return maze.GetCols() * maze.GetTileSize();
}

int Game::GetScreenHeight() const
{
    return maze.GetRows() * maze.GetTileSize();
}

Action Game::ReadInput() const
{
    if (IsKeyPressed(KEY_UP)) {
        return Action::Up;
    }

    if (IsKeyPressed(KEY_DOWN)) {
        return Action::Down;
    }

    if (IsKeyPressed(KEY_LEFT)) {
        return Action::Left;
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        return Action::Right;
    }

    return Action::None;
}

Cell Game::GetTargetCell(Action action) const
{
    Cell currentCell = mouse.GetCell();
    Cell targetCell = currentCell;

    switch (action) {
        case Action::Up:
            targetCell.row -= 1;
            break;

        case Action::Down:
            targetCell.row += 1;
            break;

        case Action::Left:
            targetCell.col -= 1;
            break;

        case Action::Right:
            targetCell.col += 1;
            break;

        case Action::None:
            break;
    }

    return targetCell;
}

void Game::TryMoveMouse(Action action)
{
    if (action == Action::None) {
        return;
    }

    Cell targetCell = GetTargetCell(action);

    if (!maze.IsWallCell(targetCell)) {
        mouse.MoveTo(targetCell);
    }
}

void Game::DrawMouse() const
{
    Cell cell = mouse.GetCell();
    int tileSize = maze.GetTileSize();

    int padding = 6;

    DrawRectangle(
        cell.col * tileSize + padding,
        cell.row * tileSize + padding,
        tileSize - 2 * padding,
        tileSize - 2 * padding,
        RED
    );
}