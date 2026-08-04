#pragma once

#include <optional>
#include "Screen.h"
#include "AppContext.h"
#include "raylib.h"

class ProfileSetupScreen : public Screen {
public:
    explicit ProfileSetupScreen(AppContext& context);

    std::optional<ScreenType> Update() override;
    void Draw() const override;

private:
    AppContext& context;

    Rectangle GetContinueButtonRect() const;
    bool IsContinueButtonClicked() const;
};