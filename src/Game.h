#pragma once 
#include "Mouse.h"

class Game {
public:
    Game(int screenWidth, int screenHeight);

    void Update(float dt);
    void Draw() const;

private:
    int screenWidth;
    int screenHeight;
    Mouse mouse;
};