#include "raylib.h"
#include "Mouse.h"

int main() {
    const int screenWidth = 800, screenHeight = 600;
    Mouse mouse;
    mouse.position = {0.0f, 400.0f};
    mouse.speed = 200.0f;
    mouse.size = {40.0f, 40.0f};

    InitWindow(screenWidth, screenHeight, "mouse window");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        UpdateMouse(mouse, dt);
        ClampMouseToScreen(mouse, screenWidth, screenHeight);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawMouse(mouse);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
