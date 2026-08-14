#pragma once

#include <optional>
#include "Screen.h"
#include "AppContext.h"
#include "raylib.h"

class LaboratoryHubScreen : public Screen
{
public:
    explicit LaboratoryHubScreen(AppContext &context);

    std::optional<ScreenType> Update() override;
    void Draw() const override;

private:
    AppContext &context;

    void DrawProfileCard() const;
    void DrawExperimentConsole() const;

    Rectangle GetStartRunButtonRect() const;
    bool IsStartRunButtonClicked() const;
};