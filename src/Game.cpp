#include "Game.h"

#include "raylib.h"

Game::Game()
    : maze(),
      mouse(maze.GetStartCell()),
      state(State::Playing),
      moveCount(0)
{
}

void Game::Update(Vector2 origin)
{
    if (state == State::Playing)
    {
        Action action = ReadInput();
        TryMoveMouse(action);
        return;
    }

    if (state == State::LevelCompleted)
    {
        if (IsResetButtonClicked(origin))
        {
            ResetLevel();
        }

        return;
    }
}

void Game::Draw(Vector2 origin) const
{
    maze.Draw(origin);
    DrawMouse(origin);
    DrawHud(origin);

    if (state == State::LevelCompleted)
    {
        DrawLevelCompletedModal(origin);
    }
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

void Game::ResetLevel()
{
    mouse.MoveTo(maze.GetStartCell());
    moveCount = 0;
    state = State::Playing;
}

void Game::DrawLevelCompletedModal(Vector2 origin) const
{
    float modalWidth = 280.0f;
    float modalHeight = 150.0f;

    float modalX = (GetScreenWidth() - modalWidth) / 2.0f;
    float modalY = (GetScreenHeight() - modalHeight) / 2.0f;

    Rectangle modal = {
        modalX,
        modalY,
        modalWidth,
        modalHeight};

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 90});

    DrawRectangleRec(modal, RAYWHITE);
    DrawRectangleLinesEx(modal, 2.0f, DARKGRAY);

    const char *title = "LEVEL COMPLETED";
    int titleFontSize = 22;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        static_cast<int>(modal.x + (modal.width - titleWidth) / 2.0f),
        static_cast<int>(modal.y + 25.0f),
        titleFontSize,
        DARKGRAY);

    Rectangle button = GetResetButtonRect(origin);
    Vector2 mousePosition = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mousePosition, button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);

    const char *buttonText = "RESET";
    int buttonFontSize = 20;
    int buttonTextWidth = MeasureText(buttonText, buttonFontSize);

    DrawText(
        buttonText,
        static_cast<int>(button.x + (button.width - buttonTextWidth) / 2.0f),
        static_cast<int>(button.y + 10.0f),
        buttonFontSize,
        DARKGRAY);
}

Rectangle Game::GetResetButtonRect(Vector2 origin) const
{
    float buttonWidth = 140.0f;
    float buttonHeight = 42.0f;

    float x = (GetScreenWidth() - buttonWidth) / 2.0f;
    float y = (GetScreenHeight() / 2.0f) + 25.0f;

    return {
        x,
        y,
        buttonWidth,
        buttonHeight};
}

bool Game::IsResetButtonClicked(Vector2 origin) const
{
    Rectangle button = GetResetButtonRect(origin);
    Vector2 mousePosition = GetMousePosition();

    return CheckCollisionPointRec(mousePosition, button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
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