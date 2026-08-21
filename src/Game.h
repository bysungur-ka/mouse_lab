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

    bool IsLevelCompleted() const;
    int GetMoveCount() const;
    void ResetLevel();

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

    void DrawMouse(Vector2 origin) const;
    void DrawHud(Vector2 origin) const;
};