#pragma once

#include <cstddef>
#include <optional>
#include "Screen.h"
#include "AppContext.h"
#include "raylib.h"

class ProfileSetupScreen : public Screen
{
public:
    explicit ProfileSetupScreen(AppContext &context);

    std::optional<ScreenType> Update() override;
    void Draw() const override;

private:
    AppContext &context;
    std::size_t nameCursorPosition = 0;
    float backspaceRepeatTimer = 0.0f;

    Rectangle GetContinueButtonRect() const;
    bool IsContinueButtonClicked() const;

    Rectangle GetBadgeRect() const;
    Rectangle GetNameInputRect() const;

    void UpdateNameInput();
    void DrawBadge() const;
};