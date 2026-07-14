#include "raylib.h"
#include "Game.h"

int main()
{
    Game game;

    InitWindow(
        game.GetScreenWidth(),
        game.GetScreenHeight(),
        "Mouse Maze"
    );

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        game.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}