#include "ProfileSetupScreen.h"

ProfileSetupScreen::ProfileSetupScreen(AppContext& context)
    : context(context)
{
}

std::optional<ScreenType> ProfileSetupScreen::Update()
{
    if (IsContinueButtonClicked()) {
        return ScreenType::Intro;
    }

    return std::nullopt;
}

void ProfileSetupScreen::Draw() const
{
    ClearBackground(Color{18, 22, 28, 255});

    const char* title = "PROFILE SETUP";
    int titleFontSize = 48;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        (context.screenWidth - titleWidth) / 2,
        90,
        titleFontSize,
        RAYWHITE
    );

    const char* subtitle = "Choose your laboratory avatar";
    int subtitleFontSize = 20;
    int subtitleWidth = MeasureText(subtitle, subtitleFontSize);

    DrawText(
        subtitle,
        (context.screenWidth - subtitleWidth) / 2,
        150,
        subtitleFontSize,
        LIGHTGRAY
    );

    Rectangle button = GetContinueButtonRect();
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);

    const char* buttonText = "CONTINUE";
    int buttonFontSize = 24;
    int buttonTextWidth = MeasureText(buttonText, buttonFontSize);

    DrawText(
        buttonText,
        static_cast<int>(button.x + (button.width - buttonTextWidth) / 2),
        static_cast<int>(button.y + 13),
        buttonFontSize,
        DARKGRAY
    );
}

Rectangle ProfileSetupScreen::GetContinueButtonRect() const
{
    float width = 180.0f;
    float height = 56.0f;

    return {
        (context.screenWidth - width) / 2.0f,
        240.0f,
        width,
        height
    };
}

bool ProfileSetupScreen::IsContinueButtonClicked() const
{
    Rectangle button = GetContinueButtonRect();

    return CheckCollisionPointRec(GetMousePosition(), button)
        && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}