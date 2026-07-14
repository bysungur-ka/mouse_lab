#include "Game.h"

Game::Game(int screenWidth, int screenHeight){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    mouse.position = {40.0f, 200.0f};
    mouse.speed = 200.0f;
    mouse.size = {40.0f, 40.0f};
}

void Game::Update(float dt) {
    UpdateMouse(mouse, dt);
    ClampMouseToScreen(mouse, screenWidth, screenHeight);
}

void Game::Draw() const {
    maze.Draw();
    DrawMouse(mouse);
}