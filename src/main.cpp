#include "raylib.h"
#include "GameApp.h"

int main()
{
    GameApp app;

    InitWindow(
        app.GetScreenWidth(),
        app.GetScreenHeight(),
        "Mouse Lab"
    );

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        app.Update();

        BeginDrawing();
        app.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}