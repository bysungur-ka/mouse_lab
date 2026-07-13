#pragma once

#include "raylib.h"

struct Mouse {
    Vector2 position;
    Vector2 size;
    float speed;
};

void UpdateMouse(Mouse& mouse, float dt);
void DrawMouse(const Mouse& mouse);
void ClampMouseToScreen(Mouse& mouse, int screenWidth, int screenHeight);
