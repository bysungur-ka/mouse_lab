#include "MazeRunScreen.h"

MazeRunScreen::MazeRunScreen()
    : game()
{
}

std::optional<ScreenType> MazeRunScreen::Update()
{
    game.Update();

    return std::nullopt;
}

void MazeRunScreen::Draw() const
{
     ClearBackground(Color{18, 22, 28, 255});
    game.Draw();
}