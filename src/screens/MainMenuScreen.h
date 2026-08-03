#pragma once

#include <optional>
#include "Screen.h"
#include "AppContext.h"
#include "raylib.h"

class MainMenuScreen : public Screen {
public:
    explicit MainMenuScreen(AppContext& context);

    std::optional<ScreenType> Update() override;
    void Draw() const override;

private:
    AppContext& context;

    Rectangle GetStartButtonRect() const;
    bool IsStartButtonClicked() const;
};