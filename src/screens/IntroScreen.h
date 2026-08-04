#pragma once

#include <optional>
#include "Screen.h"
#include "AppContext.h"
#include "raylib.h"

class IntroScreen : public Screen
{
public:
    explicit IntroScreen(AppContext &context);

    std::optional<ScreenType> Update() override;
    void Draw() const override;

private:
    AppContext &context;

    Rectangle GetEnterButtonRect() const;
    bool IsEnterButtonClicked() const;
};