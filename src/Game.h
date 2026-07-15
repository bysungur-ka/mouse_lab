#pragma once

#include "GridTypes.h"
#include "Mouse.h"
#include "Maze.h"
#include "raylib.h"

class Game
{
public:
    Game();

    void Update();
    void Draw() const;

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

    Action ReadInput() const;
    Cell GetTargetCell(Action action) const;
    void TryMoveMouse(Action action);
    void CheckGoalReached();
    void ResetLevel();

    void DrawLevelCompletedModal() const;
    Rectangle GetResetButtonRect() const;
    bool IsResetButtonClicked() const;

    void DrawMouse() const;
};