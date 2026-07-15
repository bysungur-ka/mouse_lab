#include "Game.h"

#include "raylib.h"

Game::Game()
    : maze(),
      mouse(maze.GetStartCell()),
      state(State::Playing)
{
}

void Game::Update()
{
    if (state == State::Playing) {
        Action action = ReadInput();
        TryMoveMouse(action);
        return;
    }

    if (state == State::LevelCompleted) {
        if (IsResetButtonClicked()) {
            ResetLevel();
        }

        return;
    }
}

void Game::Draw() const
{
    maze.Draw();
    DrawMouse();

    if (state == State::LevelCompleted) {
        DrawLevelCompletedModal();
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
        CheckGoalReached();
    }
}

void Game::CheckGoalReached()
{
    Cell mouseCell = mouse.GetCell();
    Cell goalCell = maze.GetGoalCell();

    if (mouseCell.row == goalCell.row && mouseCell.col == goalCell.col) {
        state = State::LevelCompleted;
    }
}

void Game::ResetLevel()
{
    mouse.MoveTo(maze.GetStartCell());
    state = State::Playing;
}

void Game::DrawLevelCompletedModal() const
{
    float modalWidth = 280.0f;
    float modalHeight = 150.0f;

    float modalX = (GetScreenWidth() - modalWidth) / 2.0f;
    float modalY = (GetScreenHeight() - modalHeight) / 2.0f;

    Rectangle modal = {
        modalX,
        modalY,
        modalWidth,
        modalHeight
    };

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 90});

    DrawRectangleRec(modal, RAYWHITE);
    DrawRectangleLinesEx(modal, 2.0f, DARKGRAY);

    const char* title = "LEVEL COMPLETED";
    int titleFontSize = 22;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        static_cast<int>(modal.x + (modal.width - titleWidth) / 2.0f),
        static_cast<int>(modal.y + 25.0f),
        titleFontSize,
        DARKGRAY
    );

    Rectangle button = GetResetButtonRect();
    Vector2 mousePosition = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mousePosition, button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);

    const char* buttonText = "RESET";
    int buttonFontSize = 20;
    int buttonTextWidth = MeasureText(buttonText, buttonFontSize);

    DrawText(
        buttonText,
        static_cast<int>(button.x + (button.width - buttonTextWidth) / 2.0f),
        static_cast<int>(button.y + 10.0f),
        buttonFontSize,
        DARKGRAY
    );
}

Rectangle Game::GetResetButtonRect() const
{
    float buttonWidth = 140.0f;
    float buttonHeight = 42.0f;

    float x = (GetScreenWidth() - buttonWidth) / 2.0f;
    float y = (GetScreenHeight() / 2.0f) + 25.0f;

    return {
        x,
        y,
        buttonWidth,
        buttonHeight
    };
}

bool Game::IsResetButtonClicked() const
{
    Rectangle button = GetResetButtonRect();
    Vector2 mousePosition = GetMousePosition();

    return CheckCollisionPointRec(mousePosition, button)
        && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
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