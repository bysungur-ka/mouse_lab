#include "ProfileSetupScreen.h"

ProfileSetupScreen::ProfileSetupScreen(AppContext &context)
    : context(context)
{
    if (context.profile.name.empty())
    {
        context.profile.name = "Text here";
    }
}

std::optional<ScreenType> ProfileSetupScreen::Update()
{

    UpdateNameInput();

    if (IsContinueButtonClicked())
    {
        return ScreenType::Intro;
    }

    return std::nullopt;
}

void ProfileSetupScreen::Draw() const
{
    ClearBackground(Color{18, 22, 28, 255});

    DrawBadge();

    const char *title = "PROFILE SETUP";
    int titleFontSize = 48;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        (context.screenWidth - titleWidth) / 2,
        90,
        titleFontSize,
        RAYWHITE);

    const char *subtitle = "Choose your laboratory avatar";
    int subtitleFontSize = 20;
    int subtitleWidth = MeasureText(subtitle, subtitleFontSize);

    DrawText(
        subtitle,
        (context.screenWidth - subtitleWidth) / 2,
        150,
        subtitleFontSize,
        LIGHTGRAY);

    Rectangle button = GetContinueButtonRect();
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);

    const char *buttonText = "CONTINUE";
    int buttonFontSize = 24;
    int buttonTextWidth = MeasureText(buttonText, buttonFontSize);

    DrawText(
        buttonText,
        static_cast<int>(button.x + (button.width - buttonTextWidth) / 2),
        static_cast<int>(button.y + 13),
        buttonFontSize,
        DARKGRAY);
}

Rectangle ProfileSetupScreen::GetContinueButtonRect() const
{
    float width = 180.0f;
    float height = 56.0f;

    return {
        (context.screenWidth - width) / 2.0f,
        context.screenHeight - 1.5f*height,
        width,
        height};
}

bool ProfileSetupScreen::IsContinueButtonClicked() const
{
    Rectangle button = GetContinueButtonRect();

    return CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void ProfileSetupScreen::UpdateNameInput()
{
    int key = GetCharPressed();

    while (key > 0) {
        if (key >= 32 && key <= 126 && context.profile.name.size() < 18) {
            context.profile.name += static_cast<char>(key);
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !context.profile.name.empty()) {
        context.profile.name.pop_back();
    }
}

Rectangle ProfileSetupScreen::GetBadgeRect() const
{
   return {
        280.0f,
        200.0f,
        400.0f,
        250.0f
    };
}

Rectangle ProfileSetupScreen::GetNameInputRect() const
{
    Rectangle badge = GetBadgeRect();

    return {
        badge.x + 40.0f,
        badge.y + 90.0f,
        badge.width - 80.0f,
        42.0f
    };
}

void ProfileSetupScreen::DrawBadge() const
{
    Rectangle badge = GetBadgeRect();
    Rectangle nameInput = GetNameInputRect();

    DrawRectangleRec(badge, Color{235, 235, 225, 255});
    DrawRectangleLinesEx(badge, 3.0f, GOLD);

    DrawText("MOUSE LAB", static_cast<int>(badge.x + 30), static_cast<int>(badge.y + 25), 24, DARKGRAY);

    DrawText("NAME", static_cast<int>(nameInput.x), static_cast<int>(nameInput.y - 24), 16, DARKGRAY);
    DrawRectangleRec(nameInput, RAYWHITE);
    DrawRectangleLinesEx(nameInput, 2.0f, DARKGRAY);

    DrawText(
        context.profile.name.c_str(),
        static_cast<int>(nameInput.x + 10),
        static_cast<int>(nameInput.y + 10),
        20,
        DARKGRAY
    );

    DrawText("POSITION", static_cast<int>(badge.x + 40), static_cast<int>(badge.y + 155), 16, DARKGRAY);
    DrawText("Laboratory Worker", static_cast<int>(badge.x + 40), static_cast<int>(badge.y + 180), 22, DARKGRAY);
}

