#include "raylib.h"
#include "Mouse.h"
#include "Game.h"

int main() {
    const int screenWidth = 800, screenHeight = 600;
    Mouse mouse;
    InitWindow(screenWidth, screenHeight, "mouse window");
    Game game(screenWidth, screenHeight);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        game.Update(dt);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        game.Draw();
        EndDrawing();       
    }
    CloseWindow();
    return 0;
}
