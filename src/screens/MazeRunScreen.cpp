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

    if (!game.IsLevelCompleted())
    {
        game.Update(GetGameOrigin());
    }
    else if (IsResetButtonClicked())
    {
        game.ResetLevel();
    }

    return std::nullopt;
}

void MazeRunScreen::Draw() const
{
    ClearBackground(Color{18, 22, 28, 255});

    DrawHeader();
    DrawMazePanel();

    game.Draw(GetGameOrigin());

    if (game.IsLevelCompleted())
    {
        DrawLevelCompletedModal();
    }

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

Rectangle MazeRunScreen::GetResetButtonRect() const
{
    Vector2 origin = GetGameOrigin();

    float buttonWidth = 140.0f;
    float buttonHeight = 42.0f;

    float x = origin.x + (game.GetScreenWidth() - buttonWidth) / 2.0f;
    float y = origin.y + (game.GetScreenHeight() / 2.0f) + 25.0f;

    return {
        x,
        y,
        buttonWidth,
        buttonHeight};
}

bool MazeRunScreen::IsResetButtonClicked() const
{
    Rectangle button = GetResetButtonRect();

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

void MazeRunScreen::DrawLevelCompletedModal() const
{
    Vector2 origin = GetGameOrigin();
    float gameWidth = static_cast<float>(game.GetScreenWidth());
    float gameHeight = static_cast<float>(game.GetScreenHeight());

    float modalWidth = 280.0f;
    float modalHeight = 150.0f;

    float modalX = origin.x + (gameWidth - modalWidth) / 2.0f;
    float modalY = origin.y + (gameHeight - modalHeight) / 2.0f;

    Rectangle modal = {
        modalX,
        modalY,
        modalWidth,
        modalHeight};

    DrawRectangle(
        static_cast<int>(origin.x),
        static_cast<int>(origin.y),
        game.GetScreenWidth(),
        game.GetScreenHeight(),
        Color{0, 0, 0, 90});

    DrawRectangleRec(modal, RAYWHITE);
    DrawRectangleLinesEx(modal, 2.0f, DARKGRAY);

    const char *title = "LEVEL COMPLETED";
    int titleFontSize = 22;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        static_cast<int>(modal.x + (modal.width - titleWidth) / 2.0f),
        static_cast<int>(modal.y + 25.0f),
        titleFontSize,
        DARKGRAY);

    Rectangle button = GetResetButtonRect();
    Vector2 mousePosition = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mousePosition, button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);

    const char *buttonText = "RESET";
    int buttonFontSize = 20;
    int buttonTextWidth = MeasureText(buttonText, buttonFontSize);

    DrawText(
        buttonText,
        static_cast<int>(button.x + (button.width - buttonTextWidth) / 2.0f),
        static_cast<int>(button.y + 10.0f),
        buttonFontSize,
        DARKGRAY);
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