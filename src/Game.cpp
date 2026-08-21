#include "Game.h"

#include "raylib.h"

Game::Game()
    : maze(),
      mouse(maze.GetStartCell()),
      state(State::Playing),
      moveCount(0)
{
}

void Game::Update(Vector2)
{
    if (state != State::Playing)
    {
        return;
    }

    Action action = ReadInput();
    TryMoveMouse(action);
}

void Game::Draw(Vector2 origin) const
{
    maze.Draw(origin);
    DrawMouse(origin);
    DrawHud(origin);
}

bool Game::IsLevelCompleted() const
{
    return state == State::LevelCompleted;
}

int Game::GetMoveCount() const
{
    return moveCount;
}

void Game::ResetLevel()
{
    mouse.MoveTo(maze.GetStartCell());
    moveCount = 0;
    state = State::Playing;
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
    if (IsKeyPressed(KEY_UP))
    {
        return Action::Up;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        return Action::Down;
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        return Action::Left;
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        return Action::Right;
    }

    return Action::None;
}

Cell Game::GetTargetCell(Action action) const
{
    Cell currentCell = mouse.GetCell();
    Cell targetCell = currentCell;

    switch (action)
    {
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
    if (action == Action::None)
    {
        return;
    }

    Cell targetCell = GetTargetCell(action);

    if (!maze.IsWallCell(targetCell))
    {
        mouse.MoveTo(targetCell);
        moveCount++;
        CheckGoalReached();
    }
}

void Game::CheckGoalReached()
{
    Cell mouseCell = mouse.GetCell();
    Cell goalCell = maze.GetGoalCell();

    if (mouseCell.row == goalCell.row && mouseCell.col == goalCell.col)
    {
        state = State::LevelCompleted;
    }
}

void Game::DrawMouse(Vector2 origin) const
{
    Cell cell = mouse.GetCell();
    int tileSize = maze.GetTileSize();

    int padding = 6;

    DrawRectangle(
        static_cast<int>(origin.x + cell.col * tileSize + padding),
        static_cast<int>(origin.y + cell.row * tileSize + padding),
        tileSize - 2 * padding,
        tileSize - 2 * padding,
        RED);
}

void Game::DrawHud(Vector2 origin) const
{
    const char* text = TextFormat("MOVES: %d", moveCount);
    int fontSize = 20;

    int textWidth = MeasureText(text, fontSize);

    int x = static_cast<int>(origin.x + (GetScreenWidth() - textWidth) / 2);
    int y = static_cast<int>(origin.y + 8);

    DrawText(
        text,
        x,
        y,
        fontSize,
        GREEN
    );
}