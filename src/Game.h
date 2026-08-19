#pragma once

#include "GridTypes.h"
#include "Mouse.h"
#include "Maze.h"
#include "raylib.h"

class Game
{
public:
    Game();

    void Update(Vector2 origin = {0.0f, 0.0f});
    void Draw(Vector2 origin = {0.0f, 0.0f}) const;

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:
    enum class State
    {
        Playing,
        LevelCompleted
    };

    Maze maze;
    Mouse mouse;
    State state;
    int moveCount;

    Action ReadInput() const;
    Cell GetTargetCell(Action action) const;
    void TryMoveMouse(Action action);
    void CheckGoalReached();
    void ResetLevel();

    void DrawLevelCompletedModal(Vector2 origin) const;
    Rectangle GetResetButtonRect(Vector2 origin) const;
    bool IsResetButtonClicked(Vector2 origin) const;

    void DrawMouse(Vector2 origin) const;
    void DrawHud(Vector2 origin) const;
};