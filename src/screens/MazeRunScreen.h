#pragma once

#include <optional>
#include "Screen.h"
#include "../Game.h"

class MazeRunScreen : public Screen
{
public:
    MazeRunScreen();

    std::optional<ScreenType> Update() override;
    void Draw() const override;

private:
    Game game;
};