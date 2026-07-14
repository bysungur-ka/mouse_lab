#include "Mouse.h"
#include "raymath.h"

void UpdateMouse(Mouse& mouse, float dt)
{
    Vector2 direction = {0.0f, 0.0f};
    if(IsKeyDown(KEY_RIGHT)) {direction.x += 1;}
    if(IsKeyDown(KEY_LEFT)) {direction.x -= 1;}
    if(IsKeyDown(KEY_UP)) {direction.y -= 1;}
    if(IsKeyDown(KEY_DOWN)) {direction.y += 1;}

    if (Vector2Length(direction) > 0.0f)
    {
        direction = Vector2Normalize(direction);
    }

    mouse.position += direction * mouse.speed * dt;
}

void DrawMouse(const Mouse& mouse)
{
    DrawRectangleV(mouse.position, mouse.size, RED); 
}

void ClampMouseToScreen(Mouse& mouse, int screenWidth, int screenHeight)
{
    if (mouse.position.x < 0) { mouse.position.x = 0; } 
    if (mouse.position.x > screenWidth - mouse.size.x) {
         mouse.position.x = screenWidth - mouse.size.x; 
    } 
    if (mouse.position.y > screenHeight - mouse.size.y) { 
        mouse.position.y = screenHeight - mouse.size.y; 
    }
    if (mouse.position.y < 0) { mouse.position.y = 0; } 
}