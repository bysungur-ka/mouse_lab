#include "LaboratoryHubScreen.h"
#include <string>

LaboratoryHubScreen::LaboratoryHubScreen(AppContext& context)
    : context(context)
{

}

std::optional<ScreenType> LaboratoryHubScreen::Update()
{
    if (IsStartRunButtonClicked()) {
        return ScreenType::MazeRun;
    }

    return std::nullopt;
}

void LaboratoryHubScreen::Draw() const
{
    ClearBackground(Color{18, 22, 28, 255});

    const char* title = "LABORATORY HUB";
    int titleFontSize = 44;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        (context.screenWidth - titleWidth) / 2,
        70,
        titleFontSize,
        RAYWHITE
    );

    DrawProfileCard();
    DrawExperimentConsole();
}

void LaboratoryHubScreen::DrawProfileCard() const
{
    std::string welcome = "Welcome, " + context.profile.name;
    int welcomeFontSize = 22;
    int welcomeWidth = MeasureText(welcome.c_str(), welcomeFontSize);

    DrawText(
        welcome.c_str(),
        (context.screenWidth - welcomeWidth) / 2,
        130,
        welcomeFontSize,
        LIGHTGRAY
    );
}

void LaboratoryHubScreen::DrawExperimentConsole() const
{
     const char* consoleTitle = "EXPERIMENT CONSOLE";
    int consoleFontSize = 26;
    int consoleWidth = MeasureText(consoleTitle, consoleFontSize);

    DrawText(
        consoleTitle,
        (context.screenWidth - consoleWidth) / 2,
        210,
        consoleFontSize,
        GOLD
    );

    const char* description = "Manual maze run: control the mouse with arrow keys.";
    int descriptionFontSize = 18;
    int descriptionWidth = MeasureText(description, descriptionFontSize);

    DrawText(
        description,
        (context.screenWidth - descriptionWidth) / 2,
        255,
        descriptionFontSize,
        LIGHTGRAY
    );

    Rectangle button = GetStartRunButtonRect();
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);
}

Rectangle LaboratoryHubScreen::GetStartRunButtonRect() const
{
    float width = 220.0f;
    float height = 56.0f;

    return {
        (context.screenWidth - width) / 2.0f,
        330.0f,
        width,
        height
    };
}

bool LaboratoryHubScreen::IsStartRunButtonClicked() const
{
    Rectangle button = GetStartRunButtonRect();

    return CheckCollisionPointRec(GetMousePosition(), button)
        && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}