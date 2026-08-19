#include "MazeRunScreen.h"
#include <string>

MazeRunScreen::MazeRunScreen(AppContext &context)
    : context(context),
      game()
{
}

std::optional<ScreenType> MazeRunScreen::Update()
{
    if (IsLabHubButtonClicked())
    {
        return ScreenType::LaboratoryHub;
    }

    game.Update(GetGameOrigin());

    return std::nullopt;
}

void MazeRunScreen::Draw() const
{
    ClearBackground(Color{18, 22, 28, 255});

    DrawHeader();
    DrawMazePanel();

    game.Draw(GetGameOrigin());

    DrawFooter();
}

Rectangle MazeRunScreen::GetMazePanelRect() const
{
    return {
        150.0f,
        125.0f,
        660.0f,
        355.0f};
}

Vector2 MazeRunScreen::GetGameOrigin() const
{
    Rectangle panel = GetMazePanelRect();

    float gameWidth = static_cast<float>(game.GetScreenWidth());
    float gameHeight = static_cast<float>(game.GetScreenHeight());

    return {
        panel.x + (panel.width - gameWidth) / 2.0f,
        panel.y + (panel.height - gameHeight) / 2.0f};
}

Rectangle MazeRunScreen::GetLabHubButtonRect() const
{
    return {
        40.0f,
        485.0f,
        150.0f,
        38.0f};
}

bool MazeRunScreen::IsLabHubButtonClicked() const
{
    Rectangle button = GetLabHubButtonRect();

    return CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void MazeRunScreen::DrawHeader() const
{
    const char* title = "MAZE RUN";
    int titleFontSize = 40;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        (context.screenWidth - titleWidth) / 2,
        35,
        titleFontSize,
        RAYWHITE
    );

    const char* modeText = "Agent: Manual";

    DrawText(
        modeText,
        40,
        82,
        20,
        LIGHTGRAY
    );

    std::string researcher = "Researcher: " + context.profile.name;
    int researcherFontSize = 20;
    int researcherWidth = MeasureText(researcher.c_str(), researcherFontSize);

    DrawText(
        researcher.c_str(),
        context.screenWidth - researcherWidth - 40,
        82,
        researcherFontSize,
        LIGHTGRAY
    );
}

void MazeRunScreen::DrawMazePanel() const
{
    Rectangle panel = GetMazePanelRect();

    DrawRectangleRec(panel, Color{235, 235, 225, 255});
    DrawRectangleLinesEx(panel, 3.0f, GOLD);
}

void MazeRunScreen::DrawFooter() const
{
    Rectangle button = GetLabHubButtonRect();
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);

    const char *buttonText = "LAB HUB";
    int fontSize = 20;
    int textWidth = MeasureText(buttonText, fontSize);

    DrawText(
        buttonText,
        static_cast<int>(button.x + (button.width - textWidth) / 2.0f),
        static_cast<int>(button.y + 9.0f),
        fontSize,
        DARKGRAY);

    DrawText(
        "Arrow keys to move",
        400,
        495,
        18,
        LIGHTGRAY);
}