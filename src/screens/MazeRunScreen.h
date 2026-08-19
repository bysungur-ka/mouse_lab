#pragma once

#include <optional>

#include "Screen.h"
#include "AppContext.h"
#include "../Game.h"

class MazeRunScreen : public Screen
{
public:
    explicit MazeRunScreen(AppContext& context);

    std::optional<ScreenType> Update() override;
    void Draw() const override;

private:
    AppContext& context;
    Game game;

    Rectangle GetMazePanelRect() const;
    Vector2 GetGameOrigin() const;

    Rectangle GetLabHubButtonRect() const;
    bool IsLabHubButtonClicked() const;

    void DrawHeader() const;
    void DrawMazePanel() const;
    void DrawFooter() const;
};