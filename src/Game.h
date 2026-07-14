#pragma once

#include "GridTypes.h"
#include "Mouse.h"
#include "Maze.h"

class Game {
public:
    Game();

    void Update();
    void Draw() const;

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:
    Maze maze;
    Mouse mouse;

    Action ReadInput() const;
    Cell GetTargetCell(Action action) const;
    void TryMoveMouse(Action action);

    void DrawMouse() const;
};